/*
 * Archive Management module
 * archivemanager.cpp
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
#include "archivemanager.h"

#include <time.h>
#include "Logger.h"
#include "xmlDocument.h"
#include "xmlElement.h"

archivemanager::archivemanager(archive new_A) {
	A = new_A;
	initialised = false;
	t_null.isNull = true;
	trackDB = NULL;
	trackInbox = NULL;
	trackTrash = NULL;
}

archivemanager::~archivemanager() {

}

void archivemanager::load() {
	/* Reinitialise any vectors if they already exist */
	delete trackDB;
	delete trackInbox;
	delete trackTrash;

    try {
        /* Get configuration and connect to database*/
    	config *Conf = new config("digiplay");
		C = new Connection(Conf->getDBConnectString());
        delete Conf;

	    /* Create a new transaction and load current DB data into memory */
        trackDB = new vector<track>;
        loadDB(trackDB);
    }
	catch (broken_connection &e) {
		cout << "archivemanager::load: Failed to connect to database." << endl;
        cout << e.what() << endl;
		return;
	}
	catch (...) {
        cout << "archivemanager::load: An error has occured." << endl;
		//cout << "archivemanager::load: Failed to create transaction." << endl;
        //cout << e.what() << endl;
		return;
	}

	/* Parse Inbox and Trash info \ XML files */
	trackInbox = new vector<track>;
	loadInbox(trackInbox);
	trackTrash = new vector<track>;
	loadTrash(trackTrash);

	/* Manager is now ready for use */
	initialised = true;
}

archive archivemanager::spec() {
	return A;
}

track archivemanager::at(unsigned short location, unsigned int index) {
	if (!initialised) load();
	if (index > size(location) - 1) {
		cout << "archivemanager::at: index " << index 
						<< " out of range." << endl;
		return t_null;
	}
	switch (location) {
		case DPS_DB:
			return trackDB->at(index);
		case DPS_INBOX:
			return trackInbox->at(index);
		case DPS_TRASH:
			return trackTrash->at(index);
		default:
			cout << "archivemanager::at: unknown location" << endl;
			return t_null;
	}
}

unsigned int archivemanager::size(unsigned short location) {
	if (!initialised) load();
	switch (location) {
		case DPS_DB:
			return trackDB->size();
		case DPS_INBOX:
			return trackInbox->size();
		case DPS_TRASH:
			return trackTrash->size();
		default:
			cout << "archivemanager::size: unknown location" << endl;
			return 0;
	}
	return 0;
}

void archivemanager::clean(unsigned short location, unsigned int index) {
	if (!initialised) load();
	if (index > size(location) - 1) {
		cout << "archivemanager::clean: index out of range" << endl;
		return;
	}
	switch (location) {
		case DPS_DB:
			cleanInfo(&(trackDB->at(index)));
		case DPS_INBOX:
			cleanInfo(&(trackInbox->at(index)));
		case DPS_TRASH:
			cleanInfo(&(trackTrash->at(index)));
	}
}

/** Adds a track from the inbox into the database
 * @param	index	The index of the track in the inbox to add
 */
void archivemanager::add(unsigned int index) {
	char* routine = "archivemanager::add";
	if (!initialised) load();
	if (index > size(DPS_INBOX) - 1) {
		cout << "archivemanager::add: index out of range" << endl;
		return;
	}

	// get the required track
	track t = trackInbox->at(index);

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

	// escape data before adding to database
	t.title = escape_binary(t.title);
	t.artist = escape_binary(t.artist);
	t.album = escape_binary(t.album);
	t.origin = escape_binary(t.origin);
	t.reclibid = escape_binary(t.reclibid);
	t.release_date = escape_binary(t.release_date);

    // check if we have a jingle
    if (t.album.size() > 13
            && dps_strPcase(&(t.album)).substr(0,14) == "Jingle Package")
        addJingle(t);
    else
        addTrack(t);
    
	// Since we successfully added to database, put audio files in archive.
	string src = t.md5_archive.localPath + "/inbox/" + t.md5 + "*";
	string dest = t.md5_archive.localPath + "/" + t.md5.substr(0,1) + "/";
	string command = "mv " + src + " " + dest;
	int rv = system(command.c_str());
	if (rv != 0) {
		cout << "archivemanager::add: Unable to put files in archive" << endl;
		cout << " -> mv returned code " << rv << endl;
		return;
	}

	// write out xml for this track using the backup (unescaped) data
	writeXML(trackInbox->at(index));
	
	// Now the track is in the archive, not the inbox...
	trackDB->push_back(trackInbox->at(index));
	trackInbox->erase(trackInbox->begin() + index);
}

void archivemanager::remove(unsigned int index) {

}

void archivemanager::recover(unsigned int index) {

}

void archivemanager::backup(unsigned int index) {
    if (!initialised) load();
	if (index > size(DPS_DB) - 1) {
		cout << "archivemanager::backup: index out of range" << endl;
		return;
	}
	writeXML(at(DPS_DB,index));
}

/*
 * PRIVATE ROUTINES
 */

void archivemanager::loadDB(vector<track> *tracks) {
	track t;
    string SQL = "SELECT * FROM v_audio WHERE archiveid = " + dps_itoa(A.id);
    try {
        T = new Transaction(*C,"loadDB");
    	Result R = T->exec(SQL);
    	for (unsigned int i = 0; i < R.size(); i++) {
    		t.md5 = R[i]["md5"].c_str();
    		t.md5_archive = A;
    		t.title = R[i]["title"].c_str();
    		t.artist = R[i]["artist"].c_str();
    		t.album = R[i]["album"].c_str();
    		t.release_date = R[i]["released"].c_str();
    		t.tracknum = atoi(R[i]["track"].c_str());
    		t.length_smpl = atoi(R[i]["length_smpl"].c_str());
    		t.trim_start_smpl = atoi(R[i]["start_smpl"].c_str());
    		t.trim_end_smpl = atoi(R[i]["end_smpl"].c_str());
    		t.fade_in_smpl = atoi(R[i]["intro_smpl"].c_str());
    		t.fade_out_smpl = atoi(R[i]["extro_smpl"].c_str());
    		tracks->push_back(t);
    	}
        T->abort();
        delete T;
    }
    catch (...) {
        cout << "archivemanager::loadDB: An error occured." << endl;
        cout << SQL << endl;
        T->abort();
        delete T;
        return;
    }
}

void archivemanager::loadInbox(vector<track> *tracks) {
	char* routine = "archivemanager::loadInbox";
    DIR *dirp;
    struct dirent *dp;
    string fn, md5, path, test;
	track t;
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
			test = fn + ".info";
			f_test_info.open(test.c_str());
			if (f_test_xml.good()) {
				stringstream S;
				S << "Reading XML " << fn.c_str() << ".xml";
				L_INFO(LOG_DB,S.str());
				t = readXML(fn + ".xml");
			}
			else if (f_test_info.good()) {
				stringstream S;
				S << "Reading INFO " << fn.c_str() << ".info";
				L_INFO(LOG_DB,S.str());
				t = readInfo(fn + ".info");
			}
			else {
				cout << "FAILED on XML & INFO: " << md5 << endl;
				t.isNull = true;
			}
			f_test_xml.close();
			f_test_info.close();
			
			if (t.isNull) {
				cout << "archivemanager::loadInbox: Can't find info!" << endl;
				cout << " -> ignored this track " << endl;
				continue;
			}
			else {
				t.md5 = md5;
				cleanInfo(&t);
				tracks->push_back(t);
			}
        }
        else {
            closedir(dirp);
            break;
        }
    }
}

void archivemanager::loadTrash(vector<track> *tracks) {

}

void archivemanager::addTrack(track t) {
    Result R;
    int artist_id = -1, album_id = -1, audio_id = -1;
    string SQL;

    try {
        T = new Transaction(*C,"addtrack");
        // We need to check the track isn't already in the database
        // if it is, we remove it and all associated links
        SQL = "SELECT id FROM audio WHERE md5='" + t.md5 + "'";
        R = T->exec(SQL);
        if (R.size() == 1) removeTrack(R[0][0].c_str());

        // See if the artist already exists and use it if it does
        SQL = "SELECT id FROM artists WHERE name='" + t.artist + "' "
                "OR alt_name LIKE '%" + t.artist + "%'";
        R = T->exec(SQL);
        if (R.size() > 0) artist_id = atoi(R[0][0].c_str());
        // Otherwise, add a new artist
        else {
            SQL = "INSERT INTO artists (name) VALUES ('" + t.artist + "')";
            T->exec(SQL);
            SQL = "SELECT last_value FROM artists_id_seq";
            R = T->exec(SQL);
            if (R.size() > 0) artist_id = atoi(R[0][0].c_str());
            else {
                cout << "Failed to get the new artist!" << endl;
                throw;
            }
        }

        // Get the album id, or add it if necessary.
        if (t.album == "") album_id = 1;
        else {
            SQL = "SELECT * FROM albums WHERE name='" + t.album + "' "
                    "OR alt_name LIKE '%" + t.album + "%'";
            R = T->exec(SQL);
            if (R.size() > 0) album_id = atoi(R[0][0].c_str());
            else {
                SQL = "INSERT INTO albums (name) "
                        "VALUES ('" + t.album + "')";
                T->exec(SQL);
                SQL = "SELECT last_value FROM albums_id_seq";
                R = T->exec(SQL);
                if (R.size() > 0) album_id = atoi(R[0][0].c_str());
                else {
                    cout << "Failed to get the new albm!" << endl;
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
                +  ",1,1,"  + dps_itoa(dps_current_time()) + "," 
                + dps_itoa(dps_current_time()) + ",'" + t.title + "',"
                + dps_itoa(album_id) + "," + dps_itoa(t.tracknum) + ","
                + dps_itoa(atoi(t.release_date.c_str()))
                + ",'f','f',1,'" + t.origin + "','" + t.reclibid + "','raw')";
        T->exec(SQL);
        SQL = "SELECT last_value FROM audio_id_seq";
        R = T->exec(SQL);

        // Connect audio to its artist
        if (R.size() > 0) {
            audio_id = atoi(R[0][0].c_str());
            SQL = "INSERT INTO audioartists (audioid, artistid) "
                  "VALUES (" + dps_itoa(audio_id) + "," 
                  + dps_itoa(artist_id) + ")";
            T->exec(SQL);
        }
        else {
            cout << "Failed to retrieve last audio id!" << endl;
            throw;
        }

        // Add it to a directory
        SQL = "INSERT INTO audiodir (audioid, dirid, linktype) "
                "VALUES (" + dps_itoa(audio_id) + ", 2, 0)";
        T->exec(SQL);

        T->commit();
        delete T;
    }
    catch (...) {
        T->abort();
        delete T;
        cout << "Failed to create transaction, or SQL error:" << endl;
        cout << SQL << endl;
        throw;
    }
}

void archivemanager::addJingle(track t) {
    Result R;
    int pkg_id = -1, audio_id = -1;
    string SQL;

    try {
        T = new Transaction(*C,"addjingle");
        // We need to check the track isn't already in the database
        // if it is, we remove it and all associated links
        SQL = "SELECT id FROM audio WHERE md5='" + t.md5 + "'";
        R = T->exec(SQL);
        if (R.size() == 1) removeTrack(R[0][0].c_str());

        // See if the jingle package exists
        SQL = "SELECT * FROM jinglepkgs WHERE name='" + t.album + "'";
        R = T->exec(SQL);
        if (R.size() > 0) pkg_id = atoi(R[0][0].c_str());
        // if not, create it
        else {
            SQL = "INSERT INTO jinglepkgs (name, description, enabled) "
                    "VALUES ('" + t.album + "','" + t.album + "','f')";
            T->exec(SQL);
            SQL = "SELECT last_value FROM jinglepkgs_id_seq";
            R = T->exec(SQL);
            if (R.size() > 0) pkg_id = atoi(R[0][0].c_str());
            else {
                cout << "Failed to get the jingle package name!" << endl;
                T->abort();
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
        T->exec(SQL);
        SQL = "SELECT last_value FROM audio_id_seq";
        R = T->exec(SQL);
        if (R.size() > 0) {
            audio_id = atoi(R[0][0].c_str());
        }
        else {
            cout << "Failed to add audio!"<< endl;
            T->abort();
            return;
        }

        // Now add the audio to the jingle package
        SQL = "INSERT INTO audiojinglepkgs (audioid, jinglepkgid, jingletypeid)"
                " VALUES (" + dps_itoa(audio_id) + "," 
                + dps_itoa(pkg_id) + ", 1)";
        T->exec(SQL);

        // Put the jingle in the jingles directory
        // TODO: Create subdirectories for jingle packages
        SQL = "INSERT INTO audiodir (audioid, dirid, linktype) "
                "VALUES (" + dps_itoa(audio_id) + ",6, 0)";
        T->exec(SQL);

        T->commit();
        delete T;
    }
    catch (...) {
        cout << "SQL error:" << endl;
        cout << SQL << endl;
        return;
    }
}

void archivemanager::addAdvert(track t) {

}

// Clean out directory, user, group entries, etc
void archivemanager::removeTrack(string id) {
    string SQL;
    try {
        if (!T) throw;
        SQL = "DELETE FROM audioartists WHERE audioid=" + id;
        T->exec(SQL);
        SQL = "DELETE FROM audio WHERE id=" + id;
        T->exec(SQL);
        SQL = "DELETE FROM audiogroups WHERE audioid=" + id;
        T->exec(SQL);
        SQL = "DELETE FROM audiousers WHERE audioid=" + id;
        T->exec(SQL);
        SQL = "DELETE FROM audiokeywords WHERE audioid=" + id;
        T->exec(SQL);
        SQL = "DELETE FROM audiodir WHERE audioid=" + id;
        T->exec(SQL);
        cout << "Old entry removed" << endl;
    }
    catch (...) {
        cout << "No transaction, or failed on SQL: " << SQL << endl;
        throw;
    }
}

void archivemanager::writeXML(track t) {
	xmlDocument *D = new xmlDocument();
	xmlElement *e1, *e2, *e3;

	D->set_header("<?xml version=\"1.0\"?>");
	D->set_doctype("<!DOCTYPE audio_v1 SYSTEM \"dps.dtd\">");
	e1 = D->get_root();
	e1->set_name("audio");
	e1->add_attribute("md5",t.md5);
	e1->add_attribute("type","music");
	e1->add_attribute("creation_date","2006");

	if (t.album != "") {
		e2 = e1->add_element("album");
		e2->add_attribute("name",t.album);
		if (t.origin != "") {
			e3 = e2->add_element("origin");
			e3->set_cdata(t.origin);
		}
		if (t.release_date != "") {
			e3 = e2->add_element("released");
			e3->set_cdata(t.release_date);
		}
		if (t.reclibid != "") {
			e3 = e2->add_element("reclibid");
			e3->set_cdata(t.reclibid);
		}
	}
	
	e2 = e1->add_element("segment");
	e3 = e2->add_element("title");
	e3->set_cdata(t.title);
	if (t.artist != "") {
		e3 = e2->add_element("artist");
		e3->add_attribute("name",t.artist);
	}
	if (t.tracknum != 0) {
		e3 = e2->add_element("tracknum");
		e3->set_cdata(dps_itoa(t.tracknum));
	}
	e3 = e2->add_element("censor");
	if (t.censor) e3->set_cdata("Yes");
	else e3->set_cdata("No");
	e3 = e2->add_element("smpl");
	e3->add_attribute("length",dps_itoa(t.length_smpl));
	e3->add_attribute("trim_start",dps_itoa(t.trim_start_smpl));
	e3->add_attribute("trim_end",dps_itoa(t.trim_end_smpl));
	e3->add_attribute("fade_in",dps_itoa(t.fade_in_smpl));
	e3->add_attribute("fade_out",dps_itoa(t.fade_out_smpl));

	string filename = t.md5_archive.localPath + "/" + t.md5.at(0) 
							+ "/" + t.md5 + ".xml";
	D->write_file(filename);
	delete D;
}

track archivemanager::readInfo(string filename) {
	string buffer;
	track t;
	ifstream *f_info, *f_raw;

	/* Attempt to open the info file */
	t.isNull = false;
	try {
		f_info = new ifstream(filename.c_str(), ios::in);
		if (!f_info->good()) throw 1;
		
		f_info->seekg(0);
		t.md5_archive = A;
		while (!f_info->eof()) {
			getline(*f_info, buffer);
	        if (buffer.substr(0,6) == "title:") {
	            t.title = buffer.substr(7, buffer.length() - 7);
	            continue;
	        }
	        if (buffer.substr(0,8) == "artists:") {
	            t.artist = buffer.substr(9, buffer.length() - 9);
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
	            t.tracknum = atoi(buffer.substr(10,buffer.length() - 10).c_str());
	            continue;
	        }
	        if (buffer.substr(0,9) == "released:") {
	            t.release_date = buffer.substr(10,buffer.length() - 10).c_str();
	            continue;
	        }
		}
		f_info->close();
		delete f_info;
	}
    catch (...) {
        cout << "archivemanager::readInfo: Unable to open file." << endl;
        cout << " -> " << filename << endl;
        return t_null;
    }
	t.censor = false;

	/* Attempt to open audio file */
	f_raw = new ifstream(filename.substr(0,filename.length() - 5).c_str(), 
								ios::in|ios::binary|ios::ate);
	if (!f_raw->good()) {
		return t_null;
	}
	t.length_smpl = f_raw->tellg() / 4;
	t.trim_start_smpl = 0;
	t.trim_end_smpl = 0;
	t.fade_in_smpl = 0;
	t.fade_out_smpl = 0;
	f_raw->close();
	delete f_raw;

	return t;
}

track archivemanager::readXML(string filename) {
	track t;
	xmlElement *root, *e_album, *e_segment, *e_smpl;
	xmlDocument *D = new xmlDocument(filename);
	if (!D) {
		t.isNull = true;
		return t;
	}
	root = D->get_root();

	t.md5 = root->get_attribute("md5").value;
	t.md5_archive = A;
	if ((e_album = root->get_element("album"))) {
	    t.album = e_album->get_attribute("name").value;
		if (e_album->get_element("origin"))
		    t.origin = e_album->get_element("origin")->get_cdata();
		if (e_album->get_element("reclibid"))
		    t.reclibid = e_album->get_element("reclibid")->get_cdata();
	}

	if ((e_segment = root->get_element("segment"))) {
		t.title = e_segment->get_element("title")->get_cdata();
		if (e_segment->get_element("artist"))
			t.artist = e_segment->get_element("artist")->get_attribute("name").value;
		if (e_segment->get_element("tracknum"))
			t.tracknum = atoi(e_segment->get_element("tracknum")->get_cdata().c_str());
		if (e_segment->get_element("censor")) {
			if (e_segment->get_element("censor")->get_cdata() == "Yes")
				t.censor = true;
			else
				t.censor = false;
		}
		if ((e_smpl = e_segment->get_element("smpl"))) {
			t.length_smpl = atoi(e_smpl->get_attribute("length").value.c_str());
			t.trim_start_smpl = atoi(e_smpl->get_attribute("trim_start").value.c_str());
			t.trim_end_smpl = atoi(e_smpl->get_attribute("trim_end").value.c_str());
			t.fade_in_smpl = atoi(e_smpl->get_attribute("fade_in").value.c_str());
			t.fade_out_smpl = atoi(e_smpl->get_attribute("fade_out").value.c_str());
		}
	}
	t.isNull = false;
	return t;
}

bool archivemanager::hasAudio(string md5) {
	return true;
}

void archivemanager::cleanInfo(track *t) {
    dps_strTrim(t->title);
    dps_strPcase(&(t->title));
	if ((t->title).length() > 4 && (t->title).substr(0,4) == "The ") {
		t->title = (t->title).substr(4,(t->title).length() - 4) + ", The";
	}
    dps_strTrim(t->artist);
    dps_strPcase(&(t->artist));
	if ((t->artist).length() > 4 && (t->artist).substr(0,4) == "The ") {
		t->artist = (t->artist).substr(4,(t->artist).length() - 4) + ", The";
	}
    dps_strTrim(t->album);
    dps_strPcase(&(t->album));
	if ((t->album).length() > 4 && (t->album).substr(0,4) == "The ") {
		t->album = (t->album).substr(4,(t->album).length() - 4) + ", The";
	}
	
	dps_strTrim(t->reclibid);
	dps_strPcase(&(t->reclibid));
	if ((t->reclibid).length() > 0 && (t->reclibid).length() < 5) {
		cout << "Malformed reclibid: " << t->reclibid << endl;
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
	dps_strTrim(t->release_date);
    dps_strTrim(t->origin);
	dps_strPcase(&(t->origin));
	if (t->origin == "Reclibid" || t->origin == "Eclib" || t->origin == "Raclib" || t->origin == "Reclab" || t->origin == "Riclab")
		t->origin = "Reclib";
}

void archivemanager::trimAudio(track *t) {
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
		cout << "WARNING: audio file " << t->md5 
			<< " does not contain any non-zero samples!" << endl;
	}
#undef BLOCK_SAMPLES
#undef SAMPLE_TOL
}

