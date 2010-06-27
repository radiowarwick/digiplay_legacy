#include <iostream>
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
unsigned int DataAccess::instanceCount = 0;

// Transaction management
bool DataAccess::transActive = false;
std::string DataAccess::transName = "";
pthread_mutex_t* DataAccess::t_routine_mutex = 0;


/**
 * Creates a new instance of the DataAccess class. Only one static connection
 * is made to the database in each program using this class, which is shared by
 * all instances. It is important to abort or commit transactions when they are
 * finished with to prevent database deadlock.
 */
DataAccess::DataAccess() {
    const char* routine = "DataAccess::DataAccess";

	// For each instance increment counter. We can only close the connection
	// when the last instance is destroyed.
    DataAccess::instanceCount++;

	// If this is the first instance create the connection to database
    if (DataAccess::instanceCount == 1) {
        try {
			// Create connection
			C = new PqxxConnection( getConnectionString() );
            L_INFO(LOG_DB,"Connected to database " + std::string(C->dbname()));
            L_INFO(LOG_DB," -> Backend version: " 
                            + dps_itoa(C->server_version()));
            L_INFO(LOG_DB," -> Protocal version: " 
                            + dps_itoa(C->protocol_version()));
			// Init the transaction mutex
            t_routine_mutex = new pthread_mutex_t;
            pthread_mutex_init(t_routine_mutex,NULL);
			W = 0;
        }
        catch (const std::exception &e) {
            L_ERROR(LOG_DB,"Exception: " + std::string(e.what()));
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
        delete t_routine_mutex;
    }
}


/**
 * Executes an SQL statement under the given name.
 * If a differently named transaction is currently in progress, the calling
 * thread will be blocked until that transaction has completed.
 */
PqxxResult DataAccess::exec(std::string name, std::string query) {
    const char* routine = "DataAccess::exec";

    // Only one routine at a time.
    pthread_mutex_lock(t_routine_mutex);
    
	// If it's a different transaction name to the current one open, make the
    // calling thread wait until the existing transaction is complete.
    if (transActive && transName != name) {
        L_INFO(LOG_DB,"Attempted transaction '" + name + "' while transaction '"
                + transName + "' is still active. Waiting");
		// Wait until the current transaction is no longer active
        while (transActive && transName != name) {
            L_INFO(LOG_DB,"Transaction '" + transName + "' is still active.");
            L_INFO(LOG_DB,"Want to start transaction '" + name + "'");
			// unlock mutex while we wait so the existing transaction can
			// go about it's business.
			pthread_mutex_unlock(t_routine_mutex);
            usleep(10000);
			pthread_mutex_lock(t_routine_mutex);
        }
        L_INFO(LOG_DB,"Transaction '" + name + "' now commencing.");
    }
	
    // Lock mutex to prevent multiple queries simultaneously
    PqxxResult R;
	
    // If there isn't an active an active transaction, create one
    try {
        if (!W) {
            // Create a new transaction
            L_INFO(LOG_DB,"Beginning transaction '" + name + "'");
            W = new PqxxWork(*C,"DataAccess");
            transActive = true;
            transName = name;
        }
    }
    catch (const std::exception &e) {
        pthread_mutex_unlock(t_routine_mutex);
        L_ERROR(LOG_DB,"Exception: " + std::string(e.what()));
        throw;
    }
    catch (...) {
        pthread_mutex_unlock(t_routine_mutex);
        L_CRITICAL(LOG_DB,"Unexpected exception.");
        throw;
    }

	// Perform the query
    try {
        R = W->exec(query);
    }
    catch (const pqxx::sql_error &e) {
        pthread_mutex_unlock(t_routine_mutex);
        L_ERROR(LOG_DB,e.what());
        L_ERROR(LOG_DB,"SQL Query: " + e.query());
        throw;
    }
    catch (const std::exception &e) {
        pthread_mutex_unlock(t_routine_mutex);
        L_ERROR(LOG_DB,"Exception: " + std::string(e.what()));
        throw;
    }
    catch (...) {
        pthread_mutex_unlock(t_routine_mutex);
        L_CRITICAL(LOG_DB,"Unexpected exception.");
        throw;
    }

	// Unlock routine mutex
    pthread_mutex_unlock(t_routine_mutex);
    return R;
}


/**
 * Commits any changes to the database in the last transaction and unlocks the
 * transaction lock.
 */
void DataAccess::commit(std::string name) {
    const char* routine = "DataAccess::commit";
    
	// Lock routine mutex
    pthread_mutex_lock(t_routine_mutex);
	
    // If we commit a different transaction, we must be stupid
    if (transActive && transName != name) {
        L_ERROR(LOG_DB,"Attempted to commit the wrong transaction!");
		L_ERROR(LOG_DB,"Tried to commit " + name + " while " + transName
			+ " is still active.");
		pthread_mutex_unlock(t_routine_mutex);
        return;
    }
    
	// We shouldn't try to commit when we've not done anything. Stupid.
    if (!W) {
		pthread_mutex_unlock(t_routine_mutex);
		throw -1;
	}

	// Try to commit the transaction
	try {	
	    L_INFO(LOG_DB,"Committing transaction '" + transName + "'");
	    W->commit();
	}
    catch (const std::exception &e) {
        pthread_mutex_unlock(t_routine_mutex);
        L_ERROR(LOG_DB,"Exception: " + std::string(e.what()));
        throw -1;
    }
    catch (...) {
        pthread_mutex_unlock(t_routine_mutex);
        L_CRITICAL(LOG_DB,"Unexpected exception.");
        throw -1;
    }

	// Clean up Work and set pointer null
	delete W;
	W = 0;
    transActive = false;
    transName = "";

    // Unlock routine mutex
    pthread_mutex_unlock(t_routine_mutex);
}


/**
 * Aborts any changes to the database in the last transaction and unlocks the
 * transaction lock.
 */
void DataAccess::abort(std::string name) {
    const char* routine = "DataAccess::abort";
    
    // Lock routine mutex
    pthread_mutex_lock(t_routine_mutex);

    // If we abort a different transaction, we must be stupid
    if (transActive && transName != name) {
        pthread_mutex_unlock(t_routine_mutex);
        L_ERROR(LOG_DB,"Attempted to abort the wrong transaction!");
		L_ERROR(LOG_DB,"Tried to abort " + name + " while " + transName
			+ " is still active.");
        return;
    }
	
    // We're kind, so we'll let it pass if someone tries to abort a transaction
	// which doesn't exist.
    if (!W) {
        pthread_mutex_unlock(t_routine_mutex);
        return;
    }

	// Try to abort the transaction
    try {
		L_INFO(LOG_DB,"Aborting transaction '" + transName + "'");
	    W->abort();
	}
    catch (const std::exception &e) {
        pthread_mutex_unlock(t_routine_mutex);
        L_ERROR(LOG_DB,"Exception: " + std::string(e.what()));
        throw -1;
    }
    catch (...) {
        pthread_mutex_unlock(t_routine_mutex);
        L_CRITICAL(LOG_DB,"Unexpected exception.");
        throw -1;
    }

	// Delete Work and set pointer to null
    delete W;
    W = 0;
    transActive = false;
    transName = "";

    // Unlock routine mutex
    pthread_mutex_unlock(t_routine_mutex);
}


/**
 * Parses the configuration file to get database connection information.
 */
std::string DataAccess::getConnectionString() {
    const char* routine = "DataAccess::getConnectionString";
    std::string f = "/etc/digiplay.conf";
    std::string DB_CONNECT = "";
    std::map<std::string,std::string> _file;

    L_INFO(LOG_CONFIG,"Processing config file " + f);
    std::ifstream config_file(f.c_str(), std::ios::in);
    if (config_file.is_open() && config_file.good()) {
        config_file.seekg(0);
        std::string str;
        int y = 0;

        while (!config_file.eof()) {
            y++;
            getline(config_file, str);
            if (str.substr(0,1) == "#") continue;
            unsigned int x = str.find_first_of("=",0);
            if (x == std::string::npos) {
            }
            else {
                std::string name = str.substr(0,x);
                std::string val = str.substr(x+1,str.length());
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
    const char* routine = "DataAccess::esc";

    // lock routine mutex
    pthread_mutex_lock(t_routine_mutex);

    std::string result;

    // If there isn't an active an active transaction, create one
    try {
        if (!W) {
            W = new PqxxWork(*C,"DataAccess");
            result = W->esc(str);
            W->abort();
            delete W;
            W = 0;
            pthread_mutex_unlock(t_routine_mutex);
            return result;
        }
        else {
            result = W->esc(str);
            pthread_mutex_unlock(t_routine_mutex);
            return result;
        }
    }
    catch (const std::exception &e) {
        pthread_mutex_unlock(t_routine_mutex);
        L_ERROR(LOG_DB,"Exception: " + std::string(e.what()));
        throw;
    }
    catch (...) {
        pthread_mutex_unlock(t_routine_mutex);
        L_CRITICAL(LOG_DB,"Unexpected exception.");
        throw;
    }
    pthread_mutex_unlock(t_routine_mutex);
    return str;
}
