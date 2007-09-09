/*
 * Archive Management module
 * ArchiveManager.h
 * Provides management operations on a DPS archive
 *
 * Copyright (c) 2005-2007 Chris Cantwell
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
		
		/// Returns the track \a index from archive component \a c
		track at(ARCHIVE_COMPONENT c, unsigned int index);
        /// Returns the number of tracks in archive component \a c
		unsigned int size(ARCHIVE_COMPONENT);
        /// Cleans the meta data associated with track \a index in archive
        /// component \a c
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
	
        /// Read an XML file specified by \a filename
        std::vector<track> readXML(std::string filename);
        /// Writes track \a t to the file \a filename
		void writeXML(std::string filename, track t);
        /// Read an INFO file specified by \a filename
		track readInfo(std::string filename);

	private:
        /// Loads the database component of the archive
		void loadDB(std::vector<track> *tracks);
        /// Loads the inbox component of the archive
		void loadInbox(std::vector<track> *tracks);
        /// Loads the trash component of the archive
		void loadTrash(std::vector<track> *tracks);

        /// Adds a music track \a t to the database
        void addTrack(track t);
        /// Adds a jingle \a t to the database
        void addJingle(track t);
        /// Adds an advert \a t to the database
        void addAdvert(track t);
        /// Adds user prerecorded content \a t to the database
        void addPrerec(track t);
        /// Removes the track \a md5 and all metadata from the database
        void removeTrack(std::string md5);

        /// Cleans track information (trim whitespace, etc)
		void cleanInfo(track *t);
        /// Determines trim points for the audio data
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
