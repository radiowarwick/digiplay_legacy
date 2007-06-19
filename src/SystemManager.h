/*
 * System Management module
 * SystemManager.h
 * Provides global archive management operations on a DPS system
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
#ifndef CLASS_SYSTEMMANAGER
#define CLASS_SYSTEMMANAGER

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "dps.h"
#include "Config.h"
#include "ArchiveManager.h"

class SystemManager {
    public:
        SystemManager();
        ~SystemManager();

        /* Track management */
        ArchiveManager* atArchive(unsigned int index);
		ArchiveManager* atArchive(string name);
        short sizeArchive();
        void addArchive(string name, string localPath, string remotePath);
		void createArchive(string name, string localPath, string remotePath);	
        void dropArchive(unsigned int index);

	private:
		void loadArchives();
	
		Connection *C;
		Transaction *T;
		vector<ArchiveManager*>* archives;
};

#endif
