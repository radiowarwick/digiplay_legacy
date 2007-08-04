#include <fstream>
#include <string>
#include <map>

#include <pqxx/pqxx>

#include "dps.h"
#include "Logger.h"

#include "DataAccess.h"

// Database Management
PqxxConnection* DataAccess::C = 0;
PqxxWork* DataAccess::W = 0;
pthread_mutex_t* DataAccess::t_trans_mutex = 0;
unsigned int DataAccess::instanceCount = 0;

// Transaction management
bool DataAccess::transActive = false;
std::string DataAccess::transName = "";
pthread_mutex_t* DataAccess::t_name_mutex = 0;

/**
 * Creates a new instance of the DataAccess class. Only one static connection
 * is made to the database in each program using this class, which is shared by
 * all instances. It is important to abort or commit transactions when they are
 * finished with to prevent database deadlock.
 */
DataAccess::DataAccess() {
    char* routine = "DataAccess::DataAccess";

	// For each instance increment counter. We can only close the connection
	// when the last instance is destroyed.
    DataAccess::instanceCount++;

	// If this is the first instance create the connection to database
    if (DataAccess::instanceCount == 1) {
        try {
			// Create connection
			C = new PqxxConnection( getConnectionString() );
            L_INFO(LOG_DB,"Connected to database " + string(C->dbname()));
            L_INFO(LOG_DB," -> Backend version: " 
                            + dps_itoa(C->server_version()));
            L_INFO(LOG_DB," -> Protocal version: " 
                            + dps_itoa(C->protocol_version()));
			// Init the transaction mutex
            t_trans_mutex = new pthread_mutex_t;
            t_name_mutex = new pthread_mutex_t;
            pthread_mutex_init(t_trans_mutex,NULL);
            pthread_mutex_init(t_name_mutex,NULL);
			W = 0;
        }
        catch (const exception &e) {
            L_ERROR(LOG_DB,"Exception: " + string(e.what()));
            throw;
        }
        catch (...) {
			// Whoops! We can't connect to the DB
            L_CRITICAL(LOG_DB,"An unexpected error occured");
            throw;
        }
    }
}

DataAccess::~DataAccess() {
	// Decrement the instance count
    DataAccess::instanceCount--;
    // Close connection on destruction of last instance
    if (DataAccess::instanceCount == 0) {
        delete W;
        delete C;
    }
}

/**
 * Executes an SQL statement under the given name.
 * If a differently named transaction is currently in progress, the calling
 * thread will be blocked until that transaction has completed.
 */
PqxxResult DataAccess::exec(std::string name, std::string query) {
    char* routine = "DataAccess::exec";

    // If it's a different transaction name to the current one open, make the
    // calling thread wait until the existing transaction is complete.
    if (transActive && transName != name) {
        L_INFO(LOG_DB,"Attempted transaction '" + name + "' while transaction '"
                + transName + "' is still active. Waiting");
        pthread_mutex_lock(t_name_mutex);
        L_INFO(LOG_DB,"Transaction '" + name + "' now commencing.");
    }

	// Lock mutex to prevent multiple queries simultaneously
    pthread_mutex_lock(t_trans_mutex);
    PqxxResult R;

	// If there isn't an active an active transaction, create one
    try {
        if (!W) {
            // Create a new transaction
            W = new PqxxWork(*C,"DataAccess");
            transActive = true;
            transName = name;
            // Lock the name mutex to prevent different named transactions
            // starting.
            pthread_mutex_lock(t_name_mutex);
        }
    }
    catch (const exception &e) {
        pthread_mutex_unlock(t_trans_mutex);
        L_ERROR(LOG_DB,"Exception: " + string(e.what()));
        throw;
    }
    catch (...) {
        pthread_mutex_unlock(t_trans_mutex);
        L_CRITICAL(LOG_DB,"Unexpected exception.");
        throw;
    }

	// Perform the query
    try {
        R = W->exec(query);
    }
    catch (const pqxx::sql_error &e) {
        pthread_mutex_unlock(t_trans_mutex);
    L_ERROR(LOG_DB,e.what());
        L_ERROR(LOG_DB,"SQL Query: " + e.query());
    }
    catch (const exception &e) {
        pthread_mutex_unlock(t_trans_mutex);
        L_ERROR(LOG_DB,"Exception: " + string(e.what()));
        throw;
    }
    catch (...) {
        pthread_mutex_unlock(t_trans_mutex);
        L_CRITICAL(LOG_DB,"Unexpected exception.");
        throw;
    }

	// Unlock the transaction mutex and return data
    pthread_mutex_unlock(t_trans_mutex);
    return R;
}

/**
 * Commits any changes to the database in the last transaction and unlocks the
 * transaction lock.
 */
void DataAccess::commit(std::string name) {
    char* routine = "DataAccess::commit";

    // If we commit a different transaction, we must be stupid
    if (transActive && transName != name) {
        L_ERROR(LOG_DB,"Attempted to commit the wrong transaction!");
        return;
    }
	
    // We shouldn't try to commit when we've not done anything. Stupid.
    if (!W) throw;

	// Lock the mutex, commit the changes, delete the transaction and unlock
	// the mutex again.
    pthread_mutex_lock(t_trans_mutex);
    W->commit();
    delete W;
    W = 0;
    pthread_mutex_unlock(t_trans_mutex);

    transActive = false;
    transName = "";

    // We can start a differently named transaction if we like now
    pthread_mutex_unlock(t_name_mutex);
}

/**
 * Aborts any changes to the database in the last transaction and unlocks the
 * transaction lock.
 */
void DataAccess::abort(std::string name) {
    char* routine = "DataAccess::abort";

    // If we abort a different transaction, we must be stupid
    if (transActive && transName != name) {
        L_ERROR(LOG_DB,"Attempted to abort the wrong transaction!");
        return;
    }
	
    // We're kind, so we'll let it pass if someone tries to abort a transaction
	// which doesn't exist.
    if (!W) return;

	// Lock mutex, abort transaction, delete transaction and unlock mutex
    pthread_mutex_lock(t_trans_mutex);
    W->abort();
    delete W;
    W = 0;
    pthread_mutex_unlock(t_trans_mutex);

    transActive = false;
    transName = "";

    // We can start a differently named transaction if we like now
    pthread_mutex_unlock(t_name_mutex);
}

/**
 * Parses the configuration file to get database connection information.
 */
std::string DataAccess::getConnectionString() {
    char* routine = "DataAccess::getConnectionString";
    std::string f = "/etc/digiplay.conf";
    std::string DB_CONNECT = "";
    std::map<std::string,std::string> _file;

    L_INFO(LOG_CONFIG,"Processing config file " + f);
    std::ifstream config_file(f.c_str(), ios::in);
    if (config_file.is_open() && config_file.good()) {
        config_file.seekg(0);
        string str;
        int y = 0;

        while (!config_file.eof()) {
            y++;
            getline(config_file, str);
            if (str.substr(0,1) == "#") continue;
            unsigned int x = str.find_first_of("=",0);
            if (x == string::npos) {
            }
            else {
                string name = str.substr(0,x);
                string val = str.substr(x+1,str.length());
                dps_strTrim(name);
                dps_strTrim(val);
                dps_strLcase(name);
                if (name == "" || val == "") continue;
                _file[name] = val;
            }
        }

        if (_file.count("db_host")) 
            DB_CONNECT += "host=" + _file["db_host"] + " ";
        if (_file.count("db_port")) 
            DB_CONNECT += "port=" + _file["db_port"] + " ";
        if (_file.count("db_name"))
            DB_CONNECT += "dbname=" + _file["db_name"] + " ";
		else
			DB_CONNECT += "dbname=digiplay ";
        if (_file.count("db_user")) 
            DB_CONNECT += "user=" + _file["db_user"] + " ";
		else
			DB_CONNECT += "user=digiplay_user ";
        if (_file.count("db_pass"))
            DB_CONNECT += "password=" + _file["db_pass"] + " ";
    }
    config_file.close();
    return DB_CONNECT;
}

/**
 * Wrapper routine to provide string escaping
 */
std::string DataAccess::esc(std::string str) {
    char* routine = "DataAccess::esc";

    std::string result;

    // If there isn't an active an active transaction, create one
    try {
        if (!W) {
            W = new PqxxWork(*C,"DataAccess");
            result = W->esc(str);
            W->abort();
            delete W;
            W = 0;
            return result;
        }
        else {
            result = W->esc(str);
            return result;
        }
    }
    catch (const exception &e) {
        pthread_mutex_unlock(t_trans_mutex);
        L_ERROR(LOG_DB,"Exception: " + string(e.what()));
        throw;
    }
    catch (...) {
        pthread_mutex_unlock(t_trans_mutex);
        L_CRITICAL(LOG_DB,"Unexpected exception.");
        throw;
    }
    return str;
}
