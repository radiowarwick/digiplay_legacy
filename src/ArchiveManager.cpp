/*
 * Archive Management module
 * ArchiveManager.cpp
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
#include <time.h>
#include "Logger.h"
#include "XmlDocument.h"
#include "XmlElement.h"
#include "DbDefine.h"

#include "ArchiveManager.h"

/**
 * Initialise archive manager.
 */
ArchiveManager::ArchiveManager(archive new_A) {
	A = new_A;
	initialised = false;
	t_null.isNull = true;
	trackDB = 0;
	trackInbox = 0;
	trackTrash = 0;

    DB = new DataAccess();
}


/**
 * Clean up archive manager
 */
ArchiveManager::~ArchiveManager() {
    delete trackDB;
    delete trackInbox;
    delete trackTrash;
    delete DB;
}


/**
 * Load the archive data. Tracks may be in one of three locations: the
 * database, the inbox or the trash. Each location is loaded into a separate
 * \a vector of \a tracks. This routine loads all three locations into their
 * respective vectors.
 */
void ArchiveManager::load() {
    char* routine = "ArchiveManager::load";
	/* Reinitialise any vectors if they already exist */
	delete trackDB;
	delete trackInbox;
	delete trackTrash;

    try {
        trackDB = new vector<track>;
        loadDB(trackDB);
    	trackInbox = new vector<track>;
    	loadInbox(trackInbox);
    	trackTrash = new vector<track>;
    	loadTrash(trackTrash);
    }
	catch (...) {
        L_ERROR(LOG_DB,"An unknown error has occured.");
		return;
	}

	/* Manager is now ready for use */
	initialised = true;
}


/**
 * Returns an archive struct defining the archive
 */
archive ArchiveManager::spec() {
	return A;
}


/**
 * Returns a track struct describing track \a index in the location.
 * Location specifies: DB, inbox, trash
 */
track ArchiveManager::at(ARCHIVE_COMPONENT c, unsigned int index) {
    char* routine = "ArchiveManager::at";
	if (!initialised) load();
	if (index > size(c) - 1) {
        L_ERROR(LOG_DB,"index " + dps_itoa(index) + " out of range.");
		return t_null;
	}
	switch (c) {
		case DPS_DB:    return trackDB->at(index);
		case DPS_INBOX:	return trackInbox->at(index);
		case DPS_TRASH:	return trackTrash->at(index);
		default:
            L_ERROR(LOG_DB,"unknown location " + c);
			return t_null;
	}
}


/**
 * Returns the size of the specified component of the archive 
 */
unsigned int ArchiveManager::size(ARCHIVE_COMPONENT c) {
    char* routine = "ArchiveManager::size";
	if (!initialised) load();
	switch (c) {
		case DPS_DB:    return trackDB->size();
		case DPS_INBOX:	return trackInbox->size();
		case DPS_TRASH:	return trackTrash->size();
		default:
            L_ERROR(LOG_DB,"unknown location " + c);
			return 0;
	}
	return 0;
}


/**
 * Clean up the info and formatting for the track at index \a index
 * in the specified location.
 */
void ArchiveManager::clean(ARCHIVE_COMPONENT c, unsigned int index) {
    char* routine = "ArchiveManager::clean";

	if (!initialised) load();
	if (index > size(c) - 1) {
        L_ERROR(LOG_DB,"Index out of range: " + dps_itoa(index));
		return;
	}
	switch (c) {
		case DPS_DB:	cleanInfo(&(trackDB->at(index)));
		case DPS_INBOX:	cleanInfo(&(trackInbox->at(index)));
		case DPS_TRASH:	cleanInfo(&(trackTrash->at(index)));
	}
}


/** 
 * Adds a track from the inbox into the database
 * @param	index	The index of the track in the inbox to add
 */
void ArchiveManager::add(unsigned int index) {
	char* routine = "ArchiveManager::add";
	if (!initialised) {
        L_ERROR(LOG_DB,"Attempted to add track before archive loaded.");
        return;
    }

	if (index > size(DPS_INBOX) - 1) {
        L_ERROR(LOG_DB,"ArchiveManager::add: index out of range.");
		return;
	}

	// get the required track
	track t = trackInbox->at(index);
    t.creation_date = dps_current_time();
    t.import_date = dps_current_time();

	// if we've not already processed the audio file, do so now
	if (t.trim_end_smpl == 0) {
		L_INFO(LOG_DB,"Scanning audio file for trim points.");
		trimAudio(&t);
		t.fade_in_smpl = t.trim_start_smpl;
		t.fade_out_smpl = t.trim_end_smpl;
	}

	// detect if the audio file is completely blank and cancel if it is
    if (t.trim_end_smpl <= t.trim_start_smpl) {
		L_WARNING(LOG_DB,"No non-zero samples, so track ignored.");
		return;
	}

    // Save a copy for writing out XML later
    track t_save = t;

	// escape data before adding to database
	t.title = DB->esc(t.title);
    for (unsigned int i = 0; i < t.artists.size(); i++) {
    	t.artists.at(i) = DB->esc(t.artists.at(i));
    }
	t.album = DB->esc(t.album);
	t.origin = DB->esc(t.origin);
	t.reclibid = DB->esc(t.reclibid);
	t.release_date = DB->esc(t.release_date);

    // check what type of audio we have
    switch (t.type) {
        case AUDIO_TYPE_MUSIC:  addTrack(t); break;
        case AUDIO_TYPE_JINGLE: addJingle(t); break;
        case AUDIO_TYPE_ADVERT: addAdvert(t); break;
        case AUDIO_TYPE_PREREC: addPrerec(t); break;
    }
    
	// Since we successfully added to database, put audio files in archive.
	string src = t.md5_archive.localPath + "/inbox/" + t.md5 + "*";
	string dest = t.md5_archive.localPath + "/" + t.md5.substr(0,1) + "/";
	string command = "mv " + src + " " + dest;
	int rv = system(command.c_str());
	if (rv != 0) {
		L_ERROR(LOG_DB,"Unable to put files in archive");
        L_ERROR(LOG_DB," -> mv returned code " + rv);
        removeTrack(t.md5);
		return;
	}

	// write out xml for this track using the backup (unescaped) data
	writeXML(dest + t.md5 + ".xml", t_save);
	
	// Now the track is in the archive, not the inbox...
	trackDB->push_back(t_save);
	trackInbox->erase(trackInbox->begin() + index);
}


/**
 * Remove a track from the database back into the inbox
 */
void ArchiveManager::remove(unsigned int index) {
    char* routine = "ArchiveManager::remove";

    track t = trackDB->at(index);
    try {
        removeTrack(t.md5);
        trackInbox->push_back(t);
        trackDB->erase(trackDB->begin() + index);
    }
    catch (...) {
        L_ERROR(LOG_DB,"Failed to remove track information from database.");
        return;
    }

    string src = t.md5_archive.localPath + "/" + t.md5.substr(0,1) + "/"
                    + t.md5 + "*";
    string dest = t.md5_archive.localPath + "/inbox/";
    string command = "mv " + src + " " + dest;
    int rv = system(command.c_str());
    if (rv != 0) {
        L_ERROR(LOG_DB,"Unable to move removed files to inbox.");
        L_ERROR(LOG_DB," -> mv returned code " + rv);
        return;
    }
}


/**
 * Delete a track - move it from the database into the trash directory
 */
void ArchiveManager::trash(unsigned int index) {
    char* routine = "ArchiveManager::trash";

    track t = trackDB->at(index);
    try {
        removeTrack(t.md5);
        trackTrash->push_back(t);
        trackDB->erase(trackDB->begin() + index);
    }
    catch (...) {
        L_ERROR(LOG_DB,"Failed to remove track information from database.");
        return;
    }

    string src = t.md5_archive.localPath + "/" + t.md5.substr(0,1) + "/"
                    + t.md5 + "*";
    string dest = t.md5_archive.localPath + "/trash/";
    string command = "mv " + src + " " + dest;
    int rv = system(command.c_str());
    if (rv != 0) {
        L_ERROR(LOG_DB,"Unable to move deleted files to trash.");
        L_ERROR(LOG_DB," -> mv returned code " + rv);
        return;
    }
}


/**
 * Recover a track from the trash back into the database
 */
void ArchiveManager::recover(unsigned int index) {
    char* routine = "ArchiveManager::recover";

    track t = trackTrash->at(index);

    string src = t.md5_archive.localPath + "/trash/" + t.md5 + "*";
    string dest = t.md5_archive.localPath + "/inbox/";
    string command = "mv " + src + " " + dest;
    int rv = system(command.c_str());
    if (rv != 0) {
        L_ERROR(LOG_DB,"Unable to recover trashed files to inbox.");
        L_ERROR(LOG_DB," -> mv returned code " + rv);
        return;
    }

    trackInbox->push_back(t);
    add(trackInbox->size() - 1);
}


/**
 * Upgrade all info files in the inbox to XML documents. Import only supports
 * the XML format now. INFO is depreciated. New ripping software will use XML
 * format for track information, rather than INFO so this should not be
 * required by users other than Radio Warwick.
 *
 * After upgrading an INFO file, the .info file is moved into the trash
 * directory to be cleaned out manually.
 */
void ArchiveManager::upgradeInfo() {
    char* routine = "ArchiveManager::upgradeInfo";

    if (!initialised) load();

    DIR *dirp;
    struct dirent *dp;
    std::string fn, md5, path, file_info, file_xml, command;
	ifstream f_info;

	path = A.localPath + "/inbox";
    dirp = opendir(path.c_str());
    while (dirp) {
        if ((dp = readdir(dirp)) != NULL) {
            fn = path + "/" + dp->d_name;

			//we want only tracks that have audio files so use audio filename
			//as a base for searching for info files
			if (string(dp->d_name).size() != 32) continue;
			md5 = dp->d_name;

			file_info = fn + ".info";
			f_info.open(file_info.c_str());
			if (f_info.good()) {
                try {
                    track t = readInfo(file_info);
                    if (t.isNull) throw;
                    cleanInfo(&t);
                    file_xml = fn + ".xml";
                    writeXML(file_xml, t);
                    command = "mv " + file_info + " " + A.localPath + "/trash";
                    system(command.c_str());
                }
                catch (...) {
                    L_ERROR(LOG_DB,"Failed to upgrade '" + file_info + "'");
                    continue;
                }
			}
			f_info.close();
        }
        else {
            closedir(dirp);
            break;
        }
    }
}


/**
 * Backs up the information from the database into the associated XML file
 * This backs up the database track \a index
 */
void ArchiveManager::backup(unsigned int index) {
    char* routine = "ArchiveManager::backup";

    if (!initialised) load();
	if (index > size(DPS_DB) - 1) {
        L_ERROR(LOG_DB,"index out of range.");
		return;
	}
    track t = trackDB->at(index);
    std::string filename = t.md5_archive.localPath + "/" + t.md5.substr(0,1)
                            + "/" + t.md5 + ".xml";
	writeXML(filename, t);
}


/**
 * Merges another archive into this archive.
 */
void ArchiveManager::merge(ArchiveManager *A) {
    for (unsigned int i = 0; i < A->size(DPS_DB); i++) {
        // Move associated files from A into this archive

        // Change archive id in database
    }
    // reload A and this archive

    // move inbox files

    // move trash files
}


/**
 * Reads the track information from an XML document into a track structure.
 */
std::vector<track> ArchiveManager::readXML(string filename) {
    char* routine = "ArchiveManager::readXML";
    std::string s;
    std::vector<track> tracks;
	XmlDocument* D = new XmlDocument(filename);
	if (!D) {
		return tracks;
	}
	XmlElement* root = D->get_root();

    // create track objects for each segment in the xml document
    // they will all have the same basic data
    for (unsigned int i = 0; i < root->count_elements(); ++i) {
        track t;
        t.md5 = root->get_attribute("md5").value;
    	t.md5_archive = A;
        t.rip_result = root->get_attribute("ripresult").value;
        t.creation_date 
            = atoi(root->get_attribute("creationdate").value.c_str());
        t.creator = root->get_attribute("creator").value;
        t.import_date = atoi(root->get_attribute("importdate").value.c_str());

        s = root->get_attribute("type").value;
        if (s == "music")       t.type = AUDIO_TYPE_MUSIC;
        else if (s == "jingle") t.type = AUDIO_TYPE_JINGLE;
        else if (s == "advert") t.type = AUDIO_TYPE_ADVERT;
        else if (s == "prerec") t.type = AUDIO_TYPE_PREREC;

        s = root->get_attribute("filetype").value;
        if (s == "raw")         t.ftype = AUDIO_FILETYPE_RAW;
        else if (s == "flac")   t.ftype = AUDIO_FILETYPE_FLAC;
        else if (s == "wav")    t.ftype = AUDIO_FILETYPE_WAV;
        
        tracks.push_back(t);
    }

    // Process each segment
    for (unsigned int i = 0; i < root->count_elements(); i++) {
        XmlElement* e = root->get_element(i);
        // sanity check
        if (e->get_name() != "segment") {
            L_WARNING(LOG_DB,"Malformed XML document");
            continue;
        }

        // Process this segment
        for (unsigned int j = 0; j < e->count_elements(); j++) {
            XmlElement* f = e->get_element(j);
            if (f->get_name() == "title") 
                tracks.at(i).title = f->get_cdata();
            if (f->get_name() == "artist")
                tracks.at(i).artists.push_back(f->get_attribute("name").value);
            if (f->get_name() == "album") {
                for (unsigned int j = 0; j < f->count_elements(); j++) {
                    xmlAttribute g = f->get_attribute(j);
        	        if (g.name == "album") 
                        tracks.at(i).album = g.value;
                    if (g.name == "origin") 
                        tracks.at(i).origin = g.value;
                    if (g.name == "released") 
                        tracks.at(i).release_date = g.value;
                    if (g.name == "reclibid") 
                        tracks.at(i).reclibid = g.value;
                }
            }
            if (f->get_name() == "tracknum")
                tracks.at(i).tracknum = atoi(f->get_cdata().c_str());
            if (f->get_name() == "censor")
                tracks.at(i).censor = (f->get_cdata() == "Yes");
            if (f->get_name() == "jingle") {
                s = f->get_attribute("type").value;
                if (s == "generic") 
                    tracks.at(i).jtype = JINGLE_TYPE_GENERIC;
                else if (s == "ident") 
                    tracks.at(i).jtype = JINGLE_TYPE_IDENT;
                else if (s == "contact") 
                    tracks.at(i).jtype = JINGLE_TYPE_CONTACT;
                else if (s == "news")
                    tracks.at(i).jtype = JINGLE_TYPE_NEWS;
                else if (s == "show")
                    tracks.at(i).jtype = JINGLE_TYPE_SHOW;
                XmlElement* g = f->get_element("package");
                tracks.at(i).package = g->get_attribute("name").value;
                tracks.at(i).package_desc 
                    = g->get_attribute("description").value;
            }
            if (f->get_name() == "smpl") {
                for (unsigned int k = 0; k < f->count_attributes(); k++) {
                    xmlAttribute g = f->get_attribute(k);
                    unsigned long x = atoi(g.value.c_str());
                    if (g.name == "length") 
                        tracks.at(i).length_smpl = x;
                    if (g.name == "trim_start") 
                        tracks.at(i).trim_start_smpl = x;
                    if (g.name == "trim_end") 
                        tracks.at(i).trim_end_smpl = x;
                    if (g.name == "fade_in") 
                        tracks.at(i).fade_in_smpl = x;
                    if (g.name == "fade_out") 
                        tracks.at(i).fade_out_smpl = x;
                }
            }
        }
	}
	return tracks;
}


/**
 * Writes out an XML document containing the information in \a t.
 */
void ArchiveManager::writeXML(std::string filename, track t) {
	XmlDocument *D = new XmlDocument();
	XmlElement *e1, *e2, *e3, *e4;

	D->set_header("<?xml version=\"1.0\"?>");
	D->set_doctype("<!DOCTYPE audio_v1 SYSTEM \"dps.dtd\">");
	e1 = D->get_root();

	e1->set_name("audio");
	e1->add_attribute("md5",t.md5);

    switch (t.ftype) {
        case AUDIO_FILETYPE_RAW:    
            e1->add_attribute("filetype","raw"); break;
        case AUDIO_FILETYPE_FLAC:   
            e1->add_attribute("filetype","flac"); break;
        case AUDIO_FILETYPE_WAV:    
            e1->add_attribute("filetype","wav"); break;
    }
	e1->add_attribute("creationdate",dps_itoa(t.creation_date));
    e1->add_attribute("creator",t.creator);
    e1->add_attribute("importdate",dps_itoa(t.import_date));
    e1->add_attribute("ripresult",t.rip_result);

    switch (t.type) {
        case AUDIO_TYPE_MUSIC:  
            e1->add_attribute("type","music"); break;
        case AUDIO_TYPE_JINGLE: 
            e1->add_attribute("type","jingle"); break;
        case AUDIO_TYPE_ADVERT: 
            e1->add_attribute("type","advert"); break;
        case AUDIO_TYPE_PREREC: 
            e1->add_attribute("type","prerec"); break;
    }

    // Write segment
	e2 = e1->add_element("segment");
	e2->add_element("title", t.title);
	if (t.type == AUDIO_TYPE_MUSIC) {
		e3 = e2->add_element("album");
		e3->add_attribute("name",t.album);
        e3->add_attribute("origin",t.origin);
		e3->add_element("released", t.release_date);
		e3->add_element("reclibid", t.reclibid);
	}
    for (unsigned int i = 0; i < t.artists.size(); i++) {
        e3 = e2->add_element("artist");
        e3->add_attribute("name",t.artists.at(i));
    }
	e2->add_element("tracknum", dps_itoa(t.tracknum));
    if (t.censor) e2->add_element("censor","Yes");
    else e2->add_element("censor","No");

    if (t.type == AUDIO_TYPE_JINGLE) {
        e3 = e2->add_element("jingle");
        switch (t.jtype) {
            case JINGLE_TYPE_GENERIC:   
                e3->add_attribute("type","generic"); break;
            case JINGLE_TYPE_IDENT:    
                e3->add_attribute("type","ident"); break;
            case JINGLE_TYPE_CONTACT:
                e3->add_attribute("type","contact"); break;
            case JINGLE_TYPE_NEWS:
                e3->add_attribute("type","news"); break;
            case JINGLE_TYPE_SHOW:
                e3->add_attribute("type","show"); break;
        }
        e4 = e3->add_element("package");
        e4->add_attribute("name",t.package);
        e4->add_attribute("description",t.package_desc);
    }

	e3 = e2->add_element("smpl");
	e3->add_attribute("length",dps_itoa(t.length_smpl));
	e3->add_attribute("trim_start",dps_itoa(t.trim_start_smpl));
	e3->add_attribute("trim_end",dps_itoa(t.trim_end_smpl));
	e3->add_attribute("fade_in",dps_itoa(t.fade_in_smpl));
	e3->add_attribute("fade_out",dps_itoa(t.fade_out_smpl));

	D->write_file(filename);
	delete D;
}


/**
 * Reads in the info from a .info into a track structure. The INFO format is
 * now depreciated and this routine is only kept to allow the upgrade of INFO
 * to XML formats.
 */
track ArchiveManager::readInfo(std::string filename) {
    char* routine = "ArchiveManager::readInfo";
    unsigned short info_version = 0;

	/* Attempt to open the info file */
    track t;
    std::string buffer;
	t.isNull = false;
	try {
		ifstream* f_info = new ifstream(filename.c_str(), ios::in);
		if (!f_info->good()) throw 1;
		
		f_info->seekg(0);
		t.md5_archive = A;
        t.type = AUDIO_TYPE_MUSIC;
        t.ftype = AUDIO_FILETYPE_RAW;
		while (!f_info->eof()) {
			getline(*f_info, buffer);
            if (buffer.substr(0,4) == "uid:") {
                t.md5 = buffer.substr(5, buffer.length() - 5);
                if (buffer.length() - 5 != 32) {
                    L_WARNING(LOG_DB,"UID was not a 32 byte MD5");
                }
                continue;
            }
	        if (buffer.substr(0,6) == "title:") {
	            t.title = buffer.substr(7, buffer.length() - 7);
	            continue;
	        }
	        if (buffer.substr(0,8) == "artists:") {
	            t.artists.push_back(buffer.substr(9, buffer.length() - 9));
	            continue;
	        }
	        if (buffer.substr(0,6) == "album:") {
	            t.album = buffer.substr(7, buffer.length() - 7);
	            continue;
	        }
	        if (buffer.substr(0,9) == "reclibid:") {
	            t.reclibid = buffer.substr(10, buffer.length() - 10);
	            continue;
	        }
	        if (buffer.substr(0,7) == "origin:") {
	            t.origin = buffer.substr(8,buffer.length() - 8);
	            continue;
	        }
	        if (buffer.substr(0,9) == "tracknum:") {
	            t.tracknum = atoi(buffer.substr(10,
                                            buffer.length() - 10).c_str());
	            continue;
	        }
	        if (buffer.substr(0,9) == "released:") {
	            t.release_date = buffer.substr(10,
                                            buffer.length() - 10).c_str();
	            continue;
	        }
            if (buffer.substr(0,10) == "cdpresult:") {
                t.rip_result = buffer.substr(11,buffer.length() - 11).c_str();
                continue;
            }
            if (buffer.substr(0,5) == "type:") {
                switch (atoi(buffer.substr(6,buffer.length() - 6).c_str())) {
                    case AUDIO_TYPE_MUSIC:  t.type = AUDIO_TYPE_MUSIC;
                    case AUDIO_TYPE_JINGLE: t.type = AUDIO_TYPE_JINGLE;
                    case AUDIO_TYPE_ADVERT: t.type = AUDIO_TYPE_ADVERT;
                    case AUDIO_TYPE_PREREC: t.type = AUDIO_TYPE_PREREC;
                }
                continue;
            }
		}
		f_info->close();
		delete f_info;
        L_INFO(LOG_DB,"Completed read of '" + t.md5 + "' as INFO-V"
                        + dps_itoa(info_version));
	}
    catch (...) {
        L_ERROR(LOG_DB,"Unable to open file '" + filename + "'");
        return t_null;
    }
	t.censor = false;

    // Check if it was designated as a jingle and adjust accordingly
    if (t.album.size() > 13
             && dps_strPcase(&(t.album)).substr(0,14) == "Jingle Package") {
        t.type = AUDIO_TYPE_JINGLE;
        t.jtype = JINGLE_TYPE_GENERIC;
        t.package = t.album.substr(15,t.album.size() - 14);
        t.album = "";
    }

	// Attempt to open audio file to check it's there
	ifstream* f_raw = new ifstream(
                              filename.substr(0,filename.length() - 5).c_str(), 
							  ios::in|ios::binary|ios::ate
                          );
	if (!f_raw->good()) {
	    t.length_smpl = 0;
	}
    else {
    	t.length_smpl = f_raw->tellg() / 4;
    }
	f_raw->close();
	delete f_raw;
	
    t.trim_start_smpl = 0;
	t.trim_end_smpl = 0;
	t.fade_in_smpl = 0;
	t.fade_out_smpl = 0;
    t.creation_date = 0;
    t.import_date = 0;
    t.creator = "";

	return t;
}



/*
 * =========================================================================
 * PRIVATE ROUTINES
 * -------------------------------------------------------------------------
 */

/**
 * Loads the database entries for this archive into the \a tracks vector.
 * \todo handle multiple artists properly
 */
void ArchiveManager::loadDB(vector<track> *tracks) {
    char* routine = "ArchiveManager::loadDB";

	track t;
    string SQL = "SELECT * FROM v_audio WHERE archiveid = " + dps_itoa(A.id);
    try {
        PqxxResult R = DB->exec("ArchiveManagerLoadDB",SQL);
        DB->abort("ArchiveManagerLoadDB");
    	for (unsigned int i = 0; i < R.size(); i++) {
    		t.md5 = R[i]["md5"].c_str();
    		t.md5_archive = A;
    		t.title = R[i]["title"].c_str();
    		t.artists.push_back(R[i]["artist"].c_str());
    		t.album = R[i]["album"].c_str();
    		t.release_date = R[i]["released"].c_str();
    		t.tracknum = atoi(R[i]["track"].c_str());
    		t.length_smpl = atoi(R[i]["length_smpl"].c_str());
    		t.trim_start_smpl = atoi(R[i]["start_smpl"].c_str());
    		t.trim_end_smpl = atoi(R[i]["end_smpl"].c_str());
    		t.fade_in_smpl = atoi(R[i]["intro_smpl"].c_str());
    		t.fade_out_smpl = atoi(R[i]["extro_smpl"].c_str());
            switch (atoi(R[i]["audiotype"].c_str())) {
                case 0: t.type = AUDIO_TYPE_MUSIC;
                case 1: t.type = AUDIO_TYPE_JINGLE;
                case 2: t.type = AUDIO_TYPE_ADVERT;
                case 3: t.type = AUDIO_TYPE_PREREC;
            }
    		tracks->push_back(t);
    	}
    }
    catch (...) {
        DB->abort("ArchiveManagerLoadDB");
        L_ERROR(LOG_DB,"Error occured loading track from database.");
        L_ERROR(LOG_DB," -> SQL: " + SQL);
        return;
    }
}


/**
 * Loads the information from tracks currently in the inbox into \a tracks.
 */
void ArchiveManager::loadInbox(vector<track> *tracks) {
	char* routine = "ArchiveManager::loadInbox";
    
    DIR *dirp;
    struct dirent *dp;
    string fn, md5, path, test;
    std::vector<track> t;
	ifstream f_test_xml, f_test_info;

	path = A.localPath + "/inbox";
    dirp = opendir(path.c_str());
    while (dirp) {
        if ((dp = readdir(dirp)) != NULL) {
            fn = path + "/" + dp->d_name;

			//we want only tracks that have audio files so use audio filename
			//as a base for searching for info files
			if (string(dp->d_name).size() != 32) continue;
			md5 = fn.substr(path.length() + 1, 32);

			test = fn + ".xml";
			f_test_xml.open(test.c_str());
			if (f_test_xml.good()) {
				L_INFO(LOG_DB,"Reading XML " + fn + ".xml");
				t = readXML(fn + ".xml");
			}
			f_test_xml.close();
			
			if (t.empty()) {
                L_WARNING(LOG_DB,"Failed to read XML for '" + md5 + "'");
                L_WARNING(LOG_DB," -> ignoring this track");
				continue;
			}
			else {
                for (unsigned int i = 0; i < t.size(); i++) {
    				cleanInfo(&(t.at(i)));
    				tracks->push_back(t.at(i));
                }
			}
        }
        else {
            closedir(dirp);
            break;
        }
    }
}


/**
 * Loads the information about tracks currently in the trash directory.
 */
void ArchiveManager::loadTrash(vector<track> *tracks) {

}


/**
 * Adds the track information from \a t into the database as a music item. This
 * routine handles the addition of a music track into the database,
 * automatically checking and creating artist and album entries where
 * necessary.
 */
void ArchiveManager::addTrack(track t) {
    char* routine = "ArchiveManager::addTrack";

    PqxxResult R;
    int album_id = -1, audio_id = -1;
    vector<int> artist_ids;
    string SQL;

    try {
        L_INFO(LOG_DB,"Adding track " + t.md5);
        // We need to check the track isn't already in the database
        // if it is, we remove it and all associated links
        //SQL = "SELECT md5 FROM audio WHERE md5='" + t.md5 + "'";
        //R = DB->exec("ArchiveManagerAddTrack",SQL);
        //if (R.size() == 1) removeTrack(t.md5);
        removeTrack(t.md5);

        // See if the artists already exists and use them if they do
        for (unsigned int i = 0; i < t.artists.size(); i++) {
            SQL = "SELECT id FROM artists WHERE name='" + t.artists.at(i) + "' "
                    "OR alt_name LIKE '%" + t.artists.at(i) + "%'";
            R = DB->exec("ArchiveManagerAddTrack",SQL);
            if (R.size() > 0) artist_ids.push_back(atoi(R[0][0].c_str()));
            // Otherwise, add a new artist
            else {
                SQL = "INSERT INTO artists (name) VALUES ('" 
                            + t.artists.at(i) + "')";
                DB->exec("ArchiveManagerAddTrack",SQL);
                SQL = "SELECT last_value FROM artists_id_seq";
                R = DB->exec("ArchiveManagerAddTrack",SQL);
                if (R.size() > 0) artist_ids.push_back(atoi(R[0][0].c_str()));
                else {
                    L_ERROR(LOG_DB,"Failed to get new artist");
                    throw;
                }
            }
        }

        // Get the album id, or add it if necessary.
        if (t.album == "") album_id = 1;
        else {
            SQL = "SELECT * FROM albums WHERE name='" + t.album + "' "
                    "OR alt_name LIKE '%" + t.album + "%'";
            R = DB->exec("ArchiveManagerAddTrack",SQL);
            if (R.size() > 0) album_id = atoi(R[0][0].c_str());
            else {
                SQL = "INSERT INTO albums (name) "
                        "VALUES ('" + t.album + "')";
                DB->exec("ArchiveManagerAddTrack",SQL);
                SQL = "SELECT last_value FROM albums_id_seq";
                R = DB->exec("ArchiveManagerAddTrack",SQL);
                if (R.size() > 0) album_id = atoi(R[0][0].c_str());
                else {
                    L_ERROR(LOG_DB,"Failed to get the new album");
                    throw;
                }
            }
        }
        
        // Now add the audio
        SQL = "INSERT INTO audio (md5, archive, length_smpl, start_smpl, "
                    "end_smpl, intro_smpl, extro_smpl, type, creator, "
                    "creation_date, import_date, title, music_album, "
                    "music_track, music_released, sustainer, censor, "
                    "lifespan, origin, reclibid, filetype) "
                "VALUES ('" + t.md5 + "'," + dps_itoa(t.md5_archive.id) + ","
                + dps_itoa(t.length_smpl) + "," + dps_itoa(t.trim_start_smpl) 
                + "," + dps_itoa(t.trim_end_smpl) + "," 
                + dps_itoa(t.fade_in_smpl) + "," + dps_itoa(t.fade_out_smpl) 
                +  ",1,1,"  + dps_itoa(t.creation_date) + "," 
                + dps_itoa(t.import_date) + ",'" + t.title + "',"
                + dps_itoa(album_id) + "," + dps_itoa(t.tracknum) + ","
                + dps_itoa(atoi(t.release_date.c_str()))
                + ",'f','f',1,'" + t.origin + "','" + t.reclibid + "','raw')";
        DB->exec("ArchiveManagerAddTrack",SQL);
        SQL = "SELECT last_value FROM audio_id_seq";
        R = DB->exec("ArchiveManagerAddTrack",SQL);

        // Connect audio to its artist
        if (R.size() > 0) {
            audio_id = atoi(R[0][0].c_str());
            for (unsigned int i = 0; i < t.artists.size(); i++) {
                SQL = "INSERT INTO audioartists (audioid, artistid) "
                      "VALUES (" + dps_itoa(audio_id) + "," 
                      + dps_itoa(artist_ids.at(i)) + ")";
                DB->exec("ArchiveManagerAddTrack",SQL);
            }
        }
        else {
            L_ERROR(LOG_DB,"Failed to get the new audio id");
            throw;
        }

        // Add it to a directory
        SQL = "INSERT INTO audiodir (audioid, dirid, linktype) "
                "VALUES (" + dps_itoa(audio_id) + ", 2, 0)";
        DB->exec("ArchiveManagerAddTrack",SQL);

        DB->commit("ArchiveManagerAddTrack");
    }
    catch (...) {
        DB->abort("ArchiveManagerAddTrack");
        L_ERROR(LOG_DB,"Error occured. SQL: " + SQL);
        throw;
    }
}


/**
 * Adds the information specified by \a t into the database as a jingle. This
 * inserts a jingle item into the database, creating the jingle package entries
 * where necessary.
 */
void ArchiveManager::addJingle(track t) {
    char* routine = "ArchiveManager::addJingle";

    PqxxResult R;
    int pkg_id = -1, audio_id = -1;
    string SQL;

    try {
        // We need to check the track isn't already in the database
        // if it is, we remove it and all associated links
        removeTrack(t.md5);

        // See if the jingle package exists
        SQL = "SELECT * FROM jinglepkgs WHERE name='" + t.album + "'";
        R = DB->exec("ArchiveManagerAddJingle",SQL);
        if (R.size() > 0) pkg_id = atoi(R[0][0].c_str());
        // if not, create it
        else {
            SQL = "INSERT INTO jinglepkgs (name, description, enabled) "
                    "VALUES ('" + t.package + "','" + t.package_desc + "','f')";
            DB->exec("ArchiveManagerAddJingle",SQL);
            SQL = "SELECT last_value FROM jinglepkgs_id_seq";
            R = DB->exec("ArchiveManagerAddJingle",SQL);
            if (R.size() > 0) pkg_id = atoi(R[0][0].c_str());
            else {
                DB->abort("ArchiveManagerAddJingle");
                L_ERROR(LOG_DB, "Failed to get the jingle package name");
                return;
            }
        }

        // Now add the audio entry
        SQL = "INSERT INTO audio (md5, archive, length_smpl, start_smpl, "
                "end_smpl, intro_smpl, extro_smpl, type, creator, "
                "creation_date, import_date, title, sustainer, censor, "
                "lifespan, music_album) "
                "VALUES ('" + t.md5 + "'," + dps_itoa(t.md5_archive.id) + "," 
                + dps_itoa(t.length_smpl) + "," + dps_itoa(t.trim_start_smpl) 
                + "," + dps_itoa(t.trim_end_smpl) + "," 
                + dps_itoa(t.fade_in_smpl) + "," + dps_itoa(t.fade_out_smpl) 
                +  ",2,1," + dps_itoa(dps_current_time()) + "," 
                +dps_itoa(dps_current_time()) + ",'" + t.title 
                + "','f','f',1,1)";
        DB->exec("ArchiveManagerAddJingle",SQL);
        SQL = "SELECT last_value FROM audio_id_seq";
        R = DB->exec("ArchiveManagerAddJingle",SQL);
        if (R.size() > 0) {
            audio_id = atoi(R[0][0].c_str());
        }
        else {
            DB->abort("ArchiveManagerAddJingle");
            L_ERROR(LOG_DB,"Failed to add audio");
            return;
        }

        // Now add the audio to the jingle package
        SQL = "INSERT INTO audiojinglepkgs (audioid, jinglepkgid, jingletypeid)"
                " VALUES (" + dps_itoa(audio_id) + "," 
                + dps_itoa(pkg_id) + ", 1)";
        DB->exec("ArchiveManagerAddJingle",SQL);

        // Put the jingle in the jingles directory
        // TODO: Create subdirectories for jingle packages
        SQL = "INSERT INTO audiodir (audioid, dirid, linktype) "
                "VALUES (" + dps_itoa(audio_id) + ",6, 0)";
        DB->exec("ArchiveManagerAddJingle",SQL);

        DB->commit("ArchiveManagerAddJingle");
    }
    catch (...) {
        DB->abort("ArchiveManagerAddJingle");
        L_ERROR(LOG_DB,"Error occured. SQL: " + SQL);
        return;
    }
}


/**
 * Adds the information in \a t to the database as an advert.
 */
void ArchiveManager::addAdvert(track t) {

}


/**
 * Adds the information in \a t to the database as a users prerec.
 */
void ArchiveManager::addPrerec(track t) {

}


/**
 * Clean out directory, user, group and any artist or jinglepackage links such
 * that the track can be removed. The track is then removed.
 */
void ArchiveManager::removeTrack(string md5) {
    char* routine = "ArchiveManager::removeTrack";
    std::string SQL, id;
    try {
        SQL = "SELECT id FROM audio WHERE md5='" + md5 + "'";
        PqxxResult R = DB->exec("ArchiveManagerRemoveTrack",SQL);
        if (R.size() == 0) {
            DB->abort("ArchiveManagerRemoveTrack");
            return;
        }
        id = R[0][0].c_str();

        L_INFO(LOG_DB,"Removing track " + md5);
        SQL = "DELETE FROM audioartists WHERE audioid=" + id;
        DB->exec("ArchiveManagerRemoveTrack",SQL);
        SQL = "DELETE FROM audiogroups WHERE audioid=" + id;
        DB->exec("ArchiveManagerRemoveTrack",SQL);
        SQL = "DELETE FROM audiousers WHERE audioid=" + id;
        DB->exec("ArchiveManagerRemoveTrack",SQL);
        SQL = "DELETE FROM audiokeywords WHERE audioid=" + id;
        DB->exec("ArchiveManagerRemoveTrack",SQL);
        SQL = "DELETE FROM audiojinglepkgs WHERE audioid=" + id;
        DB->exec("ArchiveManagerRemoveTrack",SQL);
        SQL = "DELETE FROM audiodir WHERE audioid=" + id;
        DB->exec("ArchiveManagerRemoveTrack",SQL);
        SQL = "DELETE FROM audio WHERE id=" + id;
        DB->exec("ArchiveManagerRemoveTrack",SQL);

        DB->commit("ArchiveManagerRemoveTrack");
        L_INFO(LOG_DB,"Removal of track " + id + " complete.");
    }
    catch (...) {
        DB->abort("ArchiveManagerRemoveTrack");
        L_ERROR(LOG_DB,"Failed to remove track information from DB");
        L_ERROR(LOG_DB," -> SQL: " + SQL);
        throw;
    }
}


/**
 * Cleans up the track information stored in \a t
 */
void ArchiveManager::cleanInfo(track *t) {
    char* routine = "ArchiveManager::cleanInfo";

    // title
    dps_strTrim(t->title);
    dps_strPcase(&(t->title));
	if ((t->title).length() > 4 && (t->title).substr(0,4) == "The ") {
		t->title = (t->title).substr(4,(t->title).length() - 4) + ", The";
	}
    // artists
    for (unsigned int i = 0; i < t->artists.size(); i++) {
        dps_strTrim(t->artists.at(i));
        dps_strPcase(&(t->artists.at(i)));
    	if ((t->artists.at(i)).length() > 4 
                && (t->artists.at(i)).substr(0,4) == "The ") {
    		t->artists.at(i) = (t->artists.at(i)).substr(4,
                            (t->artists.at(i)).length() - 4) + ", The";
    	}
    }
    // album
    dps_strTrim(t->album);
    dps_strPcase(&(t->album));
	if ((t->album).length() > 4 && (t->album).substr(0,4) == "The ") {
		t->album = (t->album).substr(4,(t->album).length() - 4) + ", The";
	}
	// reclibid
	dps_strTrim(t->reclibid);
	dps_strPcase(&(t->reclibid));
	if ((t->reclibid).length() > 0 && (t->reclibid).length() < 5) {
        L_WARNING(LOG_DB,"Malformed reclibid: " + t->reclibid);
	}
	else if ((t->reclibid).length() > 4) {
		int div = (t->reclibid).find("-",0);
		string year = (t->reclibid).substr(0,div);
		string number = (t->reclibid).substr(div+1,(t->reclibid).length() - 1);
		if (year.substr(0,1) == "C") {
			year = year.substr(1,year.length() - 1);
			t->reclibid = "C";
		}
		else {
			t->reclibid = "";
		}
		t->reclibid += dps_strNum(atoi(year.c_str()),2);
		t->reclibid += "-";
		t->reclibid += dps_strNum(atoi(number.c_str()),4);
	}
    // release date
	dps_strTrim(t->release_date);
    // origin
    dps_strTrim(t->origin);
	dps_strPcase(&(t->origin));
	if (t->origin == "Reclibid" || t->origin == "Eclib" || t->origin == "Raclib" || t->origin == "Reclab" || t->origin == "Riclab")
		t->origin = "Reclib";
    // jingle package
    dps_strTrim(t->package);
    dps_strPcase(&(t->package));
    // cdpresult
    dps_strTrim(t->rip_result);
}


/**
 * Scans the audio data associated with \a t to determine trim points.
 */
void ArchiveManager::trimAudio(track *t) {
    char* routine = "ArchiveManager::trimAudio";

#define BLOCK_SAMPLES 4096
#define SAMPLE_TOL 512		// Approx 2% = -42dB
    if (t->md5 == "") return;
    string filename = t->md5_archive.localPath + "/inbox/" + t->md5;
    char *audio_buffer = new char[BLOCK_SAMPLES * 4];
    ifstream *file_handle = new ifstream(filename.c_str(),
                                            ios::in|ios::binary|ios::ate);
    if (!file_handle->good()) return;

    file_handle->seekg(0,ios::end);
    long length_byte = file_handle->tellg();
    short *left, *right;

    t->trim_start_smpl = 0;
    t->trim_end_smpl = length_byte / 4; 
    
    // Scan for start of track
    file_handle->seekg(0,ios::beg);
    do {
        file_handle->read(audio_buffer,BLOCK_SAMPLES*4);
        for (int i = 0; i < BLOCK_SAMPLES; i++) {
            left = (short*)(audio_buffer + 4*i);
            right = (short*)(audio_buffer + 4*i + 2);
            if (abs(*left) < SAMPLE_TOL && abs(*right) < SAMPLE_TOL ) 
				t->trim_start_smpl += 1;
            else break;
        }
        if (file_handle->eof()) break;
    } while (abs(*left) < SAMPLE_TOL && abs(*right) < SAMPLE_TOL);

    // Scan for end of track
    file_handle->seekg((t->trim_end_smpl - BLOCK_SAMPLES)*4,ios::beg);
    do {
        file_handle->read(audio_buffer,BLOCK_SAMPLES*4);
        for (int i = BLOCK_SAMPLES - 1; i >= 0; i--) {
            left = (short*)(audio_buffer + 4*i);
            right = (short*)(audio_buffer + 4*i + 2);
            if (abs(*left) < SAMPLE_TOL && abs(*right) < SAMPLE_TOL) 
				t->trim_end_smpl -= 1;
            else break;
        }
        if (long(t->trim_end_smpl) - BLOCK_SAMPLES < 0) break;
        file_handle->seekg((t->trim_end_smpl - BLOCK_SAMPLES)*4, ios::beg);
    } while (abs(*left) < SAMPLE_TOL && abs(*right) < SAMPLE_TOL);
    
    // Clean up
    delete audio_buffer;
    delete file_handle;
	if (t->trim_end_smpl <= t->trim_start_smpl) {
        L_WARNING(LOG_DB,"Audio file " + t->md5
                + " does not contain any non-zero samples.");
	}
#undef BLOCK_SAMPLES
#undef SAMPLE_TOL
}

