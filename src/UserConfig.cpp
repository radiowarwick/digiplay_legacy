/*
 * User Configuration module
 * UserConfig.cpp
 * Extracts a users configuration from the database given an Auth module
 *
 * Copyright (c) 2006 Chris Cantwell
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#include "UserConfig.h"

#include "Auth.h"
#include "Logger.h"

UserConfig::UserConfig(Auth *authModule) {
    DB = new DataAccess();

    _userInfo.clear();
    _username = authModule->getUser();
    retrieveConfig();
}

UserConfig::~UserConfig() {

}

string UserConfig::get(string param) {
    return _userInfo[param];
}

void UserConfig::set(string param, string val) {
    char *routine = "UserConfig::set";
    string SQL =    "UPDATE usersconfigs "
                    "SET val=" + val +
                    "WHERE userid=(SELECT id FROM users WHERE username='"
                        + _username + "') "
                    "AND configoption=(SELECT id FROM configs WHERE name='"
                        + param + "')";
    try {
        DB->exec("UserConfigSet",SQL);
        DB->commit("UserConfigSet");
        _userInfo[param] = val;
    }
    catch (...) {
        L_ERROR(LOG_DB,"Failed to update '" + param + "' to '" + val
                        + "' for user '" + _username + "'");
        DB->abort("UserConfigSet");
    }
}

void UserConfig::retrieveConfig() {
    char *routine = "UserConfig::retrieveConfig";
    string SQL =    "SELECT configs.name AS name, usersconfigs.val AS value "
                    "FROM users, usersconfigs, configs "
                    "WHERE users.username = '" + _username + "' "
                    " AND usersconfigs.userid = users.id "
                    " AND usersconfigs.configoption = configs.id ";
    try {
        PqxxResult R = DB->exec("UserConfigRetrieve",SQL);
        DB->abort("UserConfigRetrieve");
        for (unsigned int i = 0; i < R.size(); i++) {
            _userInfo[R[i]["name"].c_str()] = R[i]["value"].c_str();
        }
    }
    catch (...) {
        L_ERROR(LOG_DB,"Failed to retrieve config for user '" 
                            + _username + "'");
        DB->abort("UserConfigRetrieve");
    }
}
