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
#include "config.h"

config::config(string application) {
	names = new vector<string>;
	values = new vector<string>;

	string f = "/etc/" + application + ".conf";
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
				names->push_back(str.substr(0,x));
				values->push_back(str.substr(x+1,str.length()));
			}
		}
		DB_CONNECT = "";
	    if (isDefined("DB_HOST"))
			DB_CONNECT += "hostaddr=" + getParam("DB_HOST") + " ";
		if (isDefined("DB_NAME"))
	        DB_CONNECT += "dbname=" + getParam("DB_NAME") + " ";
	    if (isDefined("DB_USER"))
	        DB_CONNECT += "user=" + getParam("DB_USER") + " ";
		if (isDefined("LOCATION"))
			LOCATION = getParam("LOCATION");
	}
	config_file.close();
	if (DB_CONNECT == "") {
		cout << " -> FATAL: Missing config file " << f 
								<< " or syntax error in file." << endl;
		exit(-1);
	}
	if (LOCATION == "") {
		cout << " -> FATAL: 'LOCATION' not specified in " << f << endl;
		exit(-1);
	}
	try {
		C = new Connection(DB_CONNECT);
		T = new Transaction(*C,"");
	}
	catch (...) {
		cout << " -> FATAL: Failed to connect to database." << endl;
		exit(-1);
	}
	requery();
}

config::~config() {
	delete names;
	delete values;
}

string config::getDBConnectString() {
	return DB_CONNECT;
}

string config::getParam(string name) {
	if (name == "location") return LOCATION;
    for (unsigned short i = 0; i < names->size(); i++) {
        if (names->at(i) == name)
            return values->at(i);
    }
    return "";
}

void config::setParam(string name, string value) {
	if (isDefined(name)) {
		string SQL = "UPDATE configuration SET val='" 
			+ value + "' WHERE parameter='" + name + "' "
			"AND location=" + LOCATION ;
		try {
			T->exec(SQL);
			T->commit();
			delete T;
			T = new Transaction(*C,"");
		}
		catch (...) {
			cout << " -> ERROR: Failed to update parameter." << endl;
		}
	}
	else {
		cout << " -> ERROR: Parameter '" << name << "' is not defined!" << endl;
	}
}

void config::requery() {
    delete names;
    delete values;
    names = new vector<string>;
    values = new vector<string>;
	try {	
	    Result Conf = T->exec("SELECT * FROM configuration WHERE location=" 
															+ LOCATION);
	    for (unsigned int i = 0; i < Conf.size(); i++) {
	        names->push_back(Conf[i]["parameter"].c_str());
	        values->push_back(Conf[i]["val"].c_str());
    	}
	}
	catch (...) {
		cout << " -> FATAL: Failed to retrieve configuration data." << endl;
		exit(-1);
	}
}

// ====== PRIVATE =======
bool config::isDefined(string name) {
	for (unsigned short i = 0; i < names->size(); i++) {
		if (names->at(i) == name)
			return true;
	}
	return false;
}

