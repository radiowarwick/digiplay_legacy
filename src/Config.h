/*
 * System configuration module
 * Config.h
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
#ifndef CLASS_CONFIG
#define CLASS_CONFIG
    
#include <string>
#include <vector>
#include <map>

#include <pqxx/pqxx>

#include "DbTrigger.h"

class DataAccess;
class MessagingInterface;


/**
 * Keeps an updated version of the system configuration. This should not be used
 * directly, but only as a static instance within the Config class. Thus, only
 * one instance of this class should be created to minimise database overhead.
 */
class ConfigManager : public Trigger {
	public:
		ConfigManager(std::string application);
		~ConfigManager() throw();

		void addClient(MessagingInterface* M);
		void removeClient(MessagingInterface* M);

		void operator()(int be_pid);

		std::string getParam(std::string name);
		void setParam(std::string name, std::string value);		
		
	private:
		void processConfigFile(std::string application);
		void requery();
		bool isDefined(std::string name);

        std::vector<std::string> *names;
        std::vector<std::string> *values;
        std::map<std::string,std::string> _file;
        std::map<std::string,std::string> _db;

        DataAccess *DB;
        vector<MessagingInterface*> clientList;

		bool setFlag;
        std::string DB_CONNECT;
        std::string LOCATION;		
};


/**
 * Manages access and modification to system configuration parameters.
 * Initially parses the application .conf file to determine database parameters
 * and then connects to the database and retrieves those configuration
 * parameters for the particular \c location specified in the config file.
 */
class Config {
	public:
		// Don't receive update notifications
		Config(std::string filename);
		// Receive update notifications
		Config(std::string filename, MessagingInterface * M);
		~Config();
		
        std::string getParam(std::string name);
		void setParam(std::string name, std::string value);
		
	private:
		MessagingInterface * M;
		static ConfigManager* CM;
		
		static unsigned int instanceCount;
};

#endif
