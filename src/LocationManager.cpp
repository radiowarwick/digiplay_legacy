#include <string>

#include "Logger.h"
#include "DataAccess.h"
#include "dps.h"

#include "LocationManager.h"

LocationManager::LocationManager() {
    DB = new DataAccess();
    defaults["channel_1"] = "/dev/dsp";
    defaults["channel_2"] = "/dev/dsp1";
    defaults["channel_3"] = "/dev/dsp2";
    defaults["channel_4"] = "/dev/dsp3";
    defaults["station_cartset"] = "0";
    defaults["user_cartset"] = "0";
    defaults["userid"] = "0";
    defaults["next_on_showplan"] = "";
    defaults["player1_md5"] = "";
    defaults["player2_md5"] = "";
    defaults["player3_md5"] = "";
    getLocations();

}

LocationManager::~LocationManager() {
    delete DB;
}

void LocationManager::add(unsigned int loc_index, std::string T) {
    char* routine = "LocationManager::add";

    bool standalone = false;
    if (T == "LMAdd") standalone = true;

    if (loc_index <= 0) {
        L_ERROR(LOG_DB,"Cannot set a non-positive location number.");
        throw;
    }

    PqxxResult R;
    std::string SQL;
    std::string loc = dps_itoa(loc_index);

    try {
        SQL = "SELECT * FROM configuration WHERE location=" + loc;
        R = DB->exec(T,SQL);
        if (R.size() > 0) {
            if (standalone) DB->abort(T);
            L_ERROR(LOG_DB,"Location " + loc + " already exists.");
            throw;
        }
        std::map<std::string,std::string>::iterator x;
        for (x = defaults.begin(); x != defaults.end(); x++) {
            SQL = "INSERT INTO configuration (location,parameter,val) VALUES ("
                + loc + ",'" + x->first + "','" + x->second + "')";
            DB->exec(T,SQL);
        }
        if (standalone) DB->commit(T);
        getLocations();
    }
    catch (...) {
        if (standalone) DB->abort(T);
        L_ERROR(LOG_DB,"Failed to add new location. SQL: " + SQL);
        throw;
    }
}

void LocationManager::remove(unsigned int loc_index, std::string T) {
    char* routine = "LocationManager::remove";

    bool standalone = false;
    if (T == "LMRemove") standalone = true;

    if (loc_index <= 0) {
        L_ERROR(LOG_DB,"Cannot remove a non-positive location number.");
        throw;
    }

    PqxxResult R;
    std::string SQL;
    std::string loc = dps_itoa(loc_index);

    try {
        SQL = "DELETE FROM configuration WHERE location=" + loc;
        DB->exec(T,SQL);
        if (standalone) DB->commit(T);
        getLocations();
    }
    catch (...) {
        if (standalone) DB->abort(T);
        L_ERROR(LOG_DB,"Failed to delete location " + loc);
        throw;
    }
}

void LocationManager::setValue(unsigned int loc_index, std::string parameter,
                                std::string value, std::string T) {
    char* routine = "LocationManager::setValue";
    
    bool standalone = false;
    if (T == "LMSetValue") standalone = true;

    PqxxResult R;
    std::string SQL;
    std::string loc = dps_itoa(loc_index);

    try {
        SQL = "SELECT * FROM configuration WHERE location=" + loc
                + " AND parameter='" + parameter + "'";
        R = DB->exec(T,SQL);
        if (R.size() == 0) {
            if (standalone) DB->abort(T);
            L_ERROR(LOG_DB,"No such parameter '" + parameter + "' at location "
                    + loc);
            throw;
        }
        SQL = "UPDATE configuration SET val='" + value + "' WHERE location="
                + loc + " AND parameter='" + parameter + "'";
        DB->exec(T,SQL);
        if (standalone) DB->commit(T);
    }
    catch (...) {
        if (standalone) DB->abort(T);
        L_ERROR(LOG_DB,"Failed to set configuration value. SQL: " + SQL);
        throw;
    }
}

unsigned int LocationManager::count(std::string T) {
    return locations.size();
}

Location LocationManager::get(unsigned int index, std::string T) {
    char* routine = "LocationManager::get";

    if (index >= locations.size()) {
        L_ERROR(LOG_DB,"Location index " + dps_itoa(index) + " out of range.");
        throw;
    }

    bool standalone = false;
    if (T == "LMGet") standalone = true;

    PqxxResult R;
    std::string SQL;
    std::string loc = locations[index];
    Location L;
    L.location = atoi(locations[index].c_str());

    try {
        SQL = "SELECT parameter, val FROM configuration WHERE location=" + loc;
        R = DB->exec(T,SQL);
        DB->abort(T);
        for (unsigned int i = 0; i < R.size(); ++i) {
            L.data[R[i]["parameter"].c_str()] = R[i]["val"].c_str();
        }
        return L;
    }
    catch (...) {
        DB->abort(T);
        L_ERROR(LOG_DB,"Failed to get location.");
        throw;
    }
}

void LocationManager::getLocations() {
    char* routine = "LocationManager::getLocations";

    std::string T = "LMGetLocations";

    PqxxResult R;
    std::string SQL;
    locations.clear();

    try {
        SQL = "SELECT DISTINCT location FROM configuration "
              "WHERE NOT location=0 AND NOT location=1";
        R = DB->exec(T,SQL);
        DB->abort(T);
        locations.resize(R.size());
        for (unsigned int i = 0; i < R.size(); ++i) {
            locations[i] = R[i][0].c_str();
        }
    }
    catch (...) {
        DB->abort(T);
        L_ERROR(LOG_DB,"Failed to get list of locations. SQL: " + SQL);
        throw;
    }
}
