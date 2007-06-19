/*
 * Archive Management module
 * ArchiveManager.h
 * Provides management operations on a DPS archive
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
#ifndef CLASS_ARCHIVEMANAGER
#define CLASS_ARCHIVEMANAGER

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "dirent.h"
#include "sys/types.h"

#include "dps.h"
#include "Config.h"

class ArchiveManager {
	public:
		ArchiveManager(archive new_A);
		~ArchiveManager();

		void load();
		archive spec();
		
		/* Track management */
		track at(unsigned short location, unsigned int index);
		unsigned int size(unsigned short location);
		void clean(unsigned short location, unsigned int index);
		void add(unsigned int index);
		void remove(unsigned int index);
		void recover(unsigned int index);
		void backup(unsigned int index);
		
		void writeXML(track t);
		track readInfo(string filename);
		track readXML(string filename);

	private:
		void loadDB(vector<track> *tracks);
		void loadInbox(vector<track> *tracks);
		void loadTrash(vector<track> *tracks);

        void addTrack(track t);
        void addJingle(track t);
        void addAdvert(track t);
        void removeTrack(string id);

		bool hasAudio(string md5);
		void cleanInfo(track *t);
		void trimAudio(track *t);

		bool initialised;
		track t_null;
		archive A;
		Connection *C;
		Transaction *T;
		vector<track> *trackDB;
		vector<track> *trackInbox;
		vector<track> *trackTrash;
};

#endif
