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

#include <vector>
#include <string>
#include <unistd.h>

#include "dirent.h"
#include "sys/types.h"

#include "dps.h"
#include "DataAccess.h"

class ArchiveManager {
	public:
		ArchiveManager(archive new_A);
		~ArchiveManager();

		void load();
		archive spec();
		
		/* Track management */
		track at(ARCHIVE_COMPONENT c, unsigned int index);
		unsigned int size(ARCHIVE_COMPONENT);
		void clean(ARCHIVE_COMPONENT c, unsigned int index);

        /// Adds a track from the inbox to the database
		void add(unsigned int index);
        /// Remove a track from the database back to the inbox
		void remove(unsigned int index);
        /// Move a track from the database to the trash
        void trash(unsigned int index);
        /// Recover a track from the trash back into the database
		void recover(unsigned int index);

        /// Upgrades INFO files to XML documents
        void upgradeInfo();
        /// Backup the database information into an XML file
		void backup(unsigned int index);

        /// Merge two another archive into this archive.
        void merge(ArchiveManager *A);
	
        // Read and write XML and info
        std::vector<track> readXML(std::string filename);
		void writeXML(std::string filename, track t);
		track readInfo(std::string filename);

	private:
		void loadDB(std::vector<track> *tracks);
		void loadInbox(std::vector<track> *tracks);
		void loadTrash(std::vector<track> *tracks);

        void addTrack(track t);
        void addJingle(track t);
        void addAdvert(track t);
        void addPrerec(track t);
        void removeTrack(std::string md5);

		void cleanInfo(track *t);
		void trimAudio(track *t);

		bool initialised;
		track t_null;
		archive A;
        DataAccess *DB;
        std::vector<track> *trackDB;
        std::vector<track> *trackInbox;
        std::vector<track> *trackTrash;
};

#endif
