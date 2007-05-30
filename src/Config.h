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
using namespace std;

#include "dirent.h"
#include "sys/types.h"

class DataAccess;

/**
 * Manages access and modification to system configuration parameters.
 * Initially parses the application .conf file to determine database parameters
 * and then connects to the database and retrieves those configuration
 * parameters for the particular \c location specified in the config file.
 */
class Config {
	public:
		Config(string filename);
		~Config();
		string getDBConnectString();
		string getParam(string name);
		void setParam(string name, string value);
		void requery();

	private:
		bool isDefined(string name);
		
		vector<string> *names;
		vector<string> *values;
		map<string,string> _file;
		map<string,string> _db;
		bool setFlag;
		string DB_CONNECT;
		string LOCATION;
        DataAccess *DB;
};

#endif
