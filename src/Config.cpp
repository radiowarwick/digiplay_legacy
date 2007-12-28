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
#include <fstream>
#include <iostream>

#include "dirent.h"
#include "sys/types.h"

#include "dps.h"
#include "Logger.h"
#include "DataAccess.h"
#include "DbTrigger.h"
#include "MessagingInterface.h"

#include "Config.h"

/**
 * Config Manager
 */
ConfigManager::ConfigManager(std::string application)
		: Trigger("trig_id1") {
	DB = new DataAccess();
	setFlag = false;
	
	processConfigFile(application);
	
	requery();
}

ConfigManager::~ConfigManager() throw() {
	delete DB;
}

void ConfigManager::addClient(MessagingInterface* M) {
	vector<MessagingInterface*>::iterator x;
	x = find(clientList.begin(), clientList.end(), M);
	if (x == clientList.end()) {
		clientList.push_back(M);
	}
	else {
		cout << "Client already connected." << endl;
	}	
}

void ConfigManager::removeClient(MessagingInterface* M) {
	vector<MessagingInterface*>::iterator x;
	x = find(clientList.begin(), clientList.end(), M);
	if (x != clientList.end()) {
		clientList.erase(x);
	}
	else {
		cout << "Client is not connected." << endl;
	}	
}

void ConfigManager::operator()(int be_pid) {
	const char* routine = "ConfigManager::operator()";
	L_INFO(LOG_CONFIG,"Database trigger activated. Messaging clients.");
	
	requery();
	for (unsigned int i = 0; i < clientList.size(); ++i) {
		clientList.at(i)->onMessage();
	}	
}

std::string ConfigManager::getParam(std::string name) {
	const char* routine = "ConfigManager::getParam";
	
	dps_strLcase(name);
	if (isDefined(name)) {
        return _db[name];
    }
	L_ERROR(LOG_CONFIG,"Requested config paramater '" + name 
                        + "' does not exist.");
	return "";	
}

void ConfigManager::setParam(std::string name, std::string value) {
	const char* routine = "ConfigManager::setParam";
	if (isDefined(name)) {
        std::string SQL = "UPDATE configuration SET val='" + value 
					+ "' WHERE parameter='" + name 
					+ "' AND location=" + LOCATION + ";" ;
		try {
			setFlag = true;
            DB->exec("ConfigSetParam",SQL);
            DB->commit("ConfigSetParam");
			_db[name] = value;
		}
		catch (...) {
            DB->abort("ConfigSetParam");
			L_ERROR(LOG_CONFIG,"Failed to update parameter.");
		}
	}
	else {
		L_ERROR(LOG_CONFIG,"Parameter '" + name + "' is not defined!");
	}	
}		

void ConfigManager::processConfigFile(std::string application) {
	const char* routine = "ConfigManager::processConfigFile";
	
    std::string f = "/etc/" + application + ".conf";
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
		_db = _file;

		DB_CONNECT = "";
	    if (isDefined("DB_HOST"))
			DB_CONNECT += "host=" + getParam("DB_HOST") + " ";
		if (isDefined("DB_PORT"))
			DB_CONNECT += "port=" + getParam("DB_PORT") + " ";
		if (isDefined("DB_NAME"))
	        DB_CONNECT += "dbname=" + getParam("DB_NAME") + " ";
		else
			DB_CONNECT += "dbname=digiplay ";
	    if (isDefined("DB_USER"))
	        DB_CONNECT += "user=" + getParam("DB_USER") + " ";
		else
			DB_CONNECT += "user=digiplay_user ";
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
}

void ConfigManager::requery() {
	const char* routine = "ConfigManager::requery";
    L_INFO(LOG_CONFIG,"Requerying Configuration.");

	if (setFlag) {
		setFlag = false;
		return;
	}
	_db.clear();
	_db = _file;
	try {
        //+ LOCATION
        std::string SQL = "SELECT * FROM configuration WHERE location=" + 
            LOCATION + " OR location=-1;";
        PqxxResult R = DB->exec("ConfigRequery", SQL);
        DB->abort("ConfigRequery");
		for (unsigned int i = 0; i < R.size(); i++) {
			_db[R[i]["parameter"].c_str()] = R[i]["val"].c_str();
		}
	}
	catch (...) {
        DB->abort("ConfigRequery");
		L_CRITICAL(LOG_CONFIG,"Failed to retrieve configuration data.");
	}	
}

bool ConfigManager::isDefined(std::string name) {
	//cout << "[" << name << "]" << endl;
	dps_strLcase(name);
	//cout << "[" << name << "]" << endl;
	//for (map<string,string>::iterator i = _db.begin(); i != _db.end(); i++) {
	//	cout << i->first << endl;
	//}
	if (_db.find(name) != _db.end()) {
		return true;
	}
	return false;
}


/**
 * Parse the configuration file and read in configuration parameters from the
 * Database for this location.
 */
 
ConfigManager * Config::CM = 0;
unsigned int Config::instanceCount = 0;

Config::Config(std::string application) {
	M = 0;
	instanceCount++;	
	if (instanceCount == 1) {
		CM = new ConfigManager(application);
	}
}

Config::Config(std::string application, MessagingInterface * m) {
	M = m;
	instanceCount++;
	if (instanceCount == 1) {
		CM = new ConfigManager(application);
	}
	CM->addClient(M);
}

Config::~Config() {
	instanceCount--;
	if (M) CM->removeClient(M);
	if (instanceCount == 0) {
		delete CM;
	}
}

/**
 * Return the value of a parameter from the database
 */
std::string Config::getParam(std::string name) {
	return CM->getParam(name);
}

/**
 * Set the value of a parameter in the database
 */
void Config::setParam(std::string name, std::string value) {
	CM->setParam(name,value);
}
