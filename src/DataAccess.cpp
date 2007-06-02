#include <fstream>
#include <string>
#include <map>

#include "Logger.h"

#include "DataAccess.h"

Connection* DataAccess::C = 0;
Transaction* DataAccess::T = 0;
pthread_mutex_t* DataAccess::t_trans_mutex = 0;
unsigned int DataAccess::instanceCount = 0;

DataAccess::DataAccess() {
	// For each instance increment counter. We can only close the connection
	// when the last instance is destroyed.
    DataAccess::instanceCount++;

	// If this is the first instance create the connection to database
    if (DataAccess::instanceCount == 1) {
        try {
			// Create connection
			C = new Connection( getConnectionString() );
			// Init the transaction mutex
            t_trans_mutex = new pthread_mutex_t;
            pthread_mutex_init(t_trans_mutex,NULL);
			T = 0;
        }
        catch (...) {
			// Whoops! We can't connect to the DB
            cout << "DataAccess::";
            cout << "An error occured while trying to connect to DB" << endl;
            throw;
        }
    }
}

DataAccess::~DataAccess() {
	// Decrement the instance count
    DataAccess::instanceCount--;
    // Close connection on destruction of last instance
    if (DataAccess::instanceCount == 0) {
        delete T;
        delete C;
    }
}

Result DataAccess::exec(std::string query) {
	// Lock mutex to prevent multiple queries simultaneously
    pthread_mutex_lock(t_trans_mutex);
    Result R;

	// If there isn't an active an active transaction, create one
    try {
        if (!T) {
            T = new Transaction(*C,"DataAccess");
        }
    }
    catch (...) {
		// Whoops! We can't have a transaction. This is bad.
        pthread_mutex_unlock(t_trans_mutex);
        cout << "DataAccess::";
        cout << "Failed to create transaction!" << endl;
        throw;
    }

	// Perform the query
//    try {
        R = T->exec(query);
//    }
/*    catch (...) {
        pthread_mutex_unlock(t_trans_mutex);
        cout << "DataAccess::";
        cout << "Error occured in query: " << endl;
        cout << query << endl;
        throw;
    }
*/
	// Unlock the mutex and return data
    pthread_mutex_unlock(t_trans_mutex);
    return R;
}

void DataAccess::commit() {
	// We shouldn't try to commit when we've not done anything. Stupid.
    if (!T) throw;

	// Lock the mutex, commit the changes, delete the transaction and unlock
	// the mutex again.
    pthread_mutex_lock(t_trans_mutex);
    T->commit();
    delete T;
    T = 0;
    pthread_mutex_unlock(t_trans_mutex);
}

void DataAccess::abort() {
	// We're kind, so we'll let it pass if someone tries to abort a transaction
	// which doesn't exist.
    if (!T) return;

	// Lock mutex, abort transaction, delete transaction and unlock mutex
    pthread_mutex_lock(t_trans_mutex);
    T->abort();
    delete T;
    T = 0;
    pthread_mutex_unlock(t_trans_mutex);
}

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
