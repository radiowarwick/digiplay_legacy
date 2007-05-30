#include <fstream>
#include <string>
#include <map>

#include "Logger.h"

#include "DataAccess.h"

bool DataAccess::init = false;
Connection* DataAccess::C = 0;
Transaction* DataAccess::T = 0;
pthread_mutex_t* DataAccess::t_trans_mutex = 0;
unsigned int DataAccess::instanceCount = 0;

DataAccess::DataAccess() {
    instanceCount++;
    if (!init) {
        try {
            C = new Connection( getConnectionString() );

            t_trans_mutex = new pthread_mutex_t;
            pthread_mutex_init(t_trans_mutex,NULL);
            T = 0;
            init = true;
        }
        catch (...) {
            cout << "DataAccess::";
            cout << "An error occured while trying to connect to DB" << endl;
            throw;
        }
    }
}

DataAccess::~DataAccess() {
    instanceCount--;
    // Close connection on destruction of last instance
    if (instanceCount == 0) {
        delete T;
        delete C;
    }
}

Result DataAccess::exec(std::string query) {
    pthread_mutex_lock(t_trans_mutex);
    Result R;
    try {
        if (!T) {
            T = new Transaction(*C,"DataAccess");
        }
    }
    catch (...) {
        pthread_mutex_unlock(t_trans_mutex);
        cout << "DataAccess::";
        cout << "Failed to create transaction!" << endl;
        throw;
    }

    try {
        R = T->exec(query);
    }
    catch (...) {
        pthread_mutex_unlock(t_trans_mutex);
        cout << "DataAccess::";
        cout << "Error occured in query: " << endl;
        cout << query << endl;
        throw;
    }
    pthread_mutex_unlock(t_trans_mutex);
    cout << "Data access: finished query" << endl;
    return R;
}

void DataAccess::commit() {
    if (!T) throw;
    pthread_mutex_lock(t_trans_mutex);
    T->commit();
    delete T;
    T = 0;
    pthread_mutex_unlock(t_trans_mutex);
}

void DataAccess::abort() {
    if (!T) throw;
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
        if (_file.count("db_user")) 
            DB_CONNECT += "user=" + _file["db_user"] + " ";
        if (_file.count("db_pass"))
            DB_CONNECT += "password=" + _file["db_pass"] + " ";
    }
    config_file.close();
    return DB_CONNECT;
}
