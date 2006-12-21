/*
 * System configuration module
 * config.cpp
 * Manages the system configuration information in the database
 *
 * Copyright (c) 2005-2006 Chris Cantwell
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
#include "dps.h"
#include "Logger.h"

#include "config.h"

config::config(string application) {
	char* routine = "config::config";
	setFlag = false;
	string f = "/etc/" + application + ".conf";
	L_INFO(LOG_CONFIG,"Processing config file " + f);
	ifstream config_file(f.c_str(), ios::in);
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
		_db = _file;

		DB_CONNECT = "";
	    if (isDefined("DB_HOST"))
			DB_CONNECT += "host=" + getParam("DB_HOST") + " ";
		if (isDefined("DB_PORT"))
			DB_CONNECT += "port=" + getParam("DB_PORT") + " ";
		if (isDefined("DB_NAME"))
	        DB_CONNECT += "dbname=" + getParam("DB_NAME") + " ";
	    if (isDefined("DB_USER"))
	        DB_CONNECT += "user=" + getParam("DB_USER") + " ";
		if (isDefined("DB_PASS"))
			DB_CONNECT += "password=" + getParam("DB_PASS") + " ";
		if (isDefined("LOCATION"))
			LOCATION = getParam("LOCATION");
	}
	config_file.close();
	if (DB_CONNECT == "") {
		L_CRITICAL(LOG_CONFIG,"Missing config file " + f
								+ " or syntax error in file.");
		exit(-1);
	}
	if (LOCATION == "") {
		L_CRITICAL(LOG_CONFIG,"'LOCATION' not specificed in " + f);
		exit(-1);
	}
	
	try {
		C = new Connection(DB_CONNECT);
		T = new Transaction(*C,"");
	}
	catch (...) {
		L_ERROR(LOG_CONFIG,"Failed to connect to database.");
		exit(-1);
	}
	requery();
}

config::~config() {

}

string config::getDBConnectString() {
	return DB_CONNECT;
}

string config::getParam(string name) {
	dps_strLcase(name);
	if (isDefined(name)) return _db[name];
    return "";
}

void config::setParam(string name, string value) {
	char* routine = "config::setParam";
	if (isDefined(name)) {
		string SQL = "UPDATE configuration SET val='" + value 
					+ "' WHERE parameter='" + name 
					+ "' AND location=" + LOCATION ;
		try {
			setFlag = true;
			T->exec(SQL);
			T->commit();
			delete T;
			T = new Transaction(*C,"");
			_db[name] = value;
		}
		catch (...) {
			L_ERROR(LOG_CONFIG,"Failed to update parameter.");
		}
	}
	else {
		L_ERROR(LOG_CONFIG,"Parameter '" + name + "' is not defined!");
	}
}

void config::requery() {
	char* routine = "conf::requery";
	if (setFlag) {
		setFlag = false;
		return;
	}
	_db.clear();
	_db = _file;
	try {
		Result R = T->exec("SELECT * FROM configuration WHERE "
							"location=" + LOCATION + " OR location=-1");
		for (unsigned int i = 0; i < R.size(); i++) {
			_db[R[i]["parameter"].c_str()] = R[i]["val"].c_str();
		}
	}
	catch (...) {
		L_CRITICAL(LOG_CONFIG,"Failed to retrieve configuration data.");
		exit(-1);
	}
}

// ====== PRIVATE =======
bool config::isDefined(string name) {
	dps_strLcase(name);
	if (_db.find(name) != _db.end()) {
		return true;
	}
	return false;
}

