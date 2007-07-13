/*
 * Authentication base class
 * Auth.cpp
 * Provides basis for the authentication framework
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

#include <iostream>
using namespace std;

#include "Logger.h"
#include "Config.h"
#include "DbDefine.h"

#include "Auth.h"

Auth::Auth() {
	isAuthenticatedFlag = false;
	DB = new DataAccess();
	Config *conf = new Config("digiplay");
	location = atoi( conf->getParam("LOCATION").c_str() );
	delete conf;
    closeSession();
}

Auth::~Auth() {

}

bool Auth::isPermitted(string privilage) {
	for (unsigned int i = 0; i < _privilages.size(); i++) {
		if (_privilages.at(i) == privilage) {
			return true;
		}
	}
	return false;
}

bool Auth::isAuthenticated() {
	return isAuthenticatedFlag;
}

string Auth::getUser() {
	if (_userInfo.size() == 0) return "Guest";
	return _userInfo["username"];
}

/**
 * Base authentication of user. This routine does not perform the actual
 * authentication as this is backend dependant. Instead, this routine will
 * perform general post-authentication tasks, such as updating the
 * configuration to reflect the change in userid
 */
void Auth::authSession(string username, string password) {
    char *routine = "Auth::authSession";

    // Warn if user supplied a blank password
    if (password == "") {
        L_INFO(LOG_AUTH,"Note user " + username + " supplied blank password");
    }

    // Get the users id
	PqxxResult R;
    std::string SQL, userid;
    try {
        SQL = "SELECT id FROM users WHERE username = '"
                        + username + "' LIMIT 1";
		R = DB->exec("AuthGetUser",SQL);
		userid = string(R[0]["id"].c_str());
    }
    catch (...) {
      	L_ERROR(LOG_AUTH,"Failed to find user in database.");
    }

    // If the user is in the database...
	if (R.size()!=0) {
        // Set the userid in the configuration
		try {
		    SQL = "UPDATE configuration SET val='" + userid
	    	    + "' WHERE parameter='userid' AND location=" 
                + dps_itoa(location);
			R = DB->exec("AuthUser",SQL);
     		DB->commit("AuthUser");
		}
		catch (...) {
            DB->abort("AuthUser");
			L_ERROR(LOG_AUTH,"Failed to change userid in the configuration"
                            " table.");
		}

        // See if the user has a directory and add it if necessary
   	 	try {
            // Get their home directory
   		    SQL = "SELECT id FROM dir WHERE name='" + username 
                    + "' AND parent = " + DIR_USERS + ";";
       		R = DB->exec("AuthUser",SQL);
		    if (R.size()==0) {
    			try {
                    // Create a directory for them
        			SQL = "INSERT INTO dir (name, parent, notes) VALUES "
        					"('" + username + "', " + DIR_USERS + ", '" 
                            + username + "\\'s home directory')";
                    DB->exec("AuthUser",SQL);
                    // Assign permissions to that directory to them
                    SQL = "INSERT INTO dirusers (dirid, userid, permissions) "
                            "VALUES ((SELECT id FROM dir WHERE name='" 
                            + username + "' AND parent=" + DIR_USERS + ")," 
                            + userid + ", '11000000');";
    				R = DB->exec("AuthUser",SQL);
        		  	DB->commit("AuthUser");
    			}
     	  		catch (...) {
                    DB->abort("AuthUser");
     		    	L_ERROR(LOG_AUTH,"Failed to add user's folder to "
                            "database and assign permissions.");
                    return;
        		}
	    	}
		    else {
                DB->abort("AuthUser");
		    	L_INFO(LOG_AUTH,"User " + username + " already has a folder.");
		    }
    	}
    	catch (...) {
            DB->abort("AuthUser");
        	L_ERROR(LOG_AUTH,"Failed to find user's folder in database.");
            return;
    	}
	}
	else {
        DB->abort("AuthUser");
		L_ERROR(LOG_AUTH,"Failed to find user in database.");
        return;
	}

    // Mark the user as authenticated
	isAuthenticatedFlag = true;

	_privilages.clear();
	_userInfo.clear();
	addUserInfo("username",username);

	// bodge --cc
	addPrivilage("TabInfo");
	addPrivilage("TabSearch");
	addPrivilage("TabPlaylist");
	addPrivilage("TabFileBrowser");
	addPrivilage("TabEmail");
	addPrivilage("TabLogging");
	addPrivilage("TabScript");
}

void Auth::closeSession() {
	char *routine = "Auth::closeSession";
	string SQL = "UPDATE configuration SET val=("
		  "SELECT id FROM users WHERE username='Guest'"
	      ") WHERE parameter='userid' AND location=" + dps_itoa(location) + ";";
	try {
		PqxxResult R = DB->exec("AuthCloseSession", SQL);
   	 	DB->commit("AuthCloseSession");
	}
	catch (...) {
		L_ERROR(LOG_AUTH,"Failed to change userid in the configuration table.");
	}

	isAuthenticatedFlag = false;
	_privilages.clear();
	_userInfo.clear();
	addPrivilage("TabInfo");
	addPrivilage("TabSearch");
	addPrivilage("TabLogging");
    addPrivilage("TabFileBrowser");
}

void Auth::addPrivilage(string privilage) {
	for (unsigned int i = 0; i < _privilages.size(); i++) {
		if (_privilages.at(i) == privilage) {
			cout << "WARNING: Privilage is already present" << endl;
			return;
		}
	}
	_privilages.push_back(privilage);
}

void Auth::addUserInfo(string item, string value) {
	_userInfo[item] = value;
}
