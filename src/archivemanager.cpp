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

	/* Get configuration and connect to database*/
	config *Conf = new config("digiplay");
	try {
		C = new Connection(Conf->getDBConnectString());
	}
	catch (...) {
		cout << "archivemanager::load: Failed to connect to database." << endl;
		cout << " -> " << Conf->getDBConnectString() << endl;
		return;
	}
	delete Conf;
	
	/* Create a new transaction and load current DB data into memory */
	try {
		T = new Transaction(*C,"");
	}
	catch (...) {
		cout << "archivemanager::load: Failed to create transaction." << endl;
		return;
	}
	trackDB = new vector<track>;
	loadDB(trackDB);
	T->abort();
	delete T;

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

	trackInbox->erase(trackInbox->begin() + index);

	// if we've not already processed the audio file, do so now
	if (t.trim_end_smpl == 0) {
		Logger::log(INFO,routine,"Scanning audio file for trim points.",2);
		trimAudio(&t);
		t.fade_in_smpl = t.trim_start_smpl;
		t.fade_out_smpl = t.trim_end_smpl;
	}

	// detect if the audio file is completely blank and cancel if it is
	if (t.trim_end_smpl > t.trim_start_smpl) {
		trackInbox->insert(trackInbox->begin() + index, 1, t);
	}
	else {
		Logger::log(WARNING,routine,"No non-zero samples, so track ignored.",1);
		return;
	}

	// Keep a copy of the unescaped track to write out to XML later
	track t_bak = t;

	// escape data before adding to database
	t.title = escape_binary(t.title);
	t.artist = escape_binary(t.artist);
	t.album = escape_binary(t.album);
	t.origin = escape_binary(t.origin);
	t.reclibid = escape_binary(t.reclibid);
	t.release_date = escape_binary(t.release_date);

	// start a new database transaction
	try {
		T = new Transaction(*C,"addtrack");
	}
	catch (...) {
		cout << "Failed to create transaction!!!" << endl;
		return;
	}
	
	Result R;
	int artist_id = -1, album_id = -1, audio_id = -1;
	bool is_jingle = false;
	string SQL;

	try {
    	// We need to check the track isn't already in the database
		SQL = "SELECT id FROM audio WHERE md5='" + t.md5 + "'";
		R = T->exec(SQL);
	    if (R.size() == 1) {
			string id = R[0][0].c_str();
			SQL = "DELETE FROM audioartists WHERE audio=" + id;
	        T->exec(SQL);
			SQL = "DELETE FROM audio WHERE id=" + id;
	        T->exec(SQL);
	        cout << "Old entry removed" << endl;
	    }
	
		// check if we have a jingle
		if (t.album.size() > 13 
				&& dps_strPcase(&(t.album)).substr(0,14) ==	"Jingle Package")
			is_jingle = true;
		
	    // First lets sort out the artist
		if (!is_jingle) {
			SQL = "SELECT id FROM artists WHERE name='" + t.artist + "' "
					"OR alt_name LIKE '%" + t.artist + "%'";
		    R = T->exec(SQL);
		    if (R.size() > 0) artist_id = atoi(R[0][0].c_str());
		    else {
				SQL = "INSERT INTO artists (name) VALUES ('" + t.artist + "')";
		        T->exec(SQL);
				SQL = "SELECT last_value FROM artists_id_seq";
		        R = T->exec(SQL);
		        if (R.size() > 0) artist_id = atoi(R[0][0].c_str());
		        else {
		            cout << "Failed to get the new artist!" << endl;
		            T->abort();
					return;
		        }
		    }
		}
	
	    // Next lets sort out the album ID
	    if (t.album == "") album_id = 0;
		else if (is_jingle) {
			SQL = "SELECT * FROM jinglepkgs WHERE name='" + t.album + "'";
			R = T->exec(SQL);
			if (R.size() > 0) album_id = atoi(R[0][0].c_str());
			else {
				SQL = "INSERT INTO jinglepkgs (name, description, enabled) "
						"VALUES ('" + t.album + "','" + t.album + "','f')";
				T->exec(SQL);
				SQL = "SELECT last_value FROM jinglepkgs_id_seq";
				R = T->exec(SQL);
				if (R.size() > 0) album_id = atoi(R[0][0].c_str());
				else {
					cout << "Failed to get the jingle package name!" << endl;
					T->abort();
					return;
				}
			}
		}
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
	                T->abort();
					return;
	            }
	        }
	    }
	
	    // We can now add the audio
	    if (is_jingle) {
	        SQL = "INSERT INTO audio (md5, archive, length_smpl, start_smpl, "
	            "end_smpl, intro_smpl, extro_smpl, type, creator, "
				"creation_date, import_date, title, sustainer, censor, "
				"lifespan, music_album) "
	            "VALUES ('" + t.md5 + "'," + dps_itoa(t.md5_archive.id) + "," + dps_itoa(t.length_smpl) + ","
	            + dps_itoa(t.trim_start_smpl) + "," + dps_itoa(t.trim_end_smpl) + ","
	            + dps_itoa(t.fade_in_smpl) + "," + dps_itoa(t.fade_out_smpl) + ",1,0,"
	            + dps_itoa(dps_current_time()) + "," + dps_itoa(dps_current_time()) + ",'" + t.title + "','f','f',0,0)";
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
			SQL = "SELECT id FROM jinglepkgs WHERE name='" + t.album + "'";
			R = T->exec(SQL);
			if (R.size() > 0) {
				album_id = atoi(R[0][0].c_str());
			}
			else {
				SQL = "INSERT INTO jinglepkgs (name, description, enabled) "
					"VALUES ('" + t.album + "','" + t.album + "','f')";
				T->exec(SQL);
				SQL = "SELECT last_value FROM jinglepkgs_id_seq";
				R = T->exec(SQL);
				if (R.size() > 0) album_id = atoi(R[0][0].c_str());
				else {
					cout << "Failed to get the new jingle package!" << endl;
					T->abort();
					return;
				}
			}
			SQL = "INSERT INTO audiojinglepkgs (audio, jinglepkg, jingletype) "
				"VALUES (" + dps_itoa(audio_id) + "," + dps_itoa(album_id) + ",0)";
			T->exec(SQL);
		}
		else {
			SQL = ("INSERT INTO audio (md5, archive, length_smpl, start_smpl, "
				"end_smpl, intro_smpl, extro_smpl, type, creator, creation_date, "
	            "import_date, title, music_album, music_track, music_released, "
	            "sustainer, censor, lifespan, origin, reclibid) "
	            "VALUES ('" + t.md5 + "'," + dps_itoa(t.md5_archive.id) + ","
				+ dps_itoa(t.length_smpl) + ","
	            + dps_itoa(t.trim_start_smpl) + "," + dps_itoa(t.trim_end_smpl) + ","
	            + dps_itoa(t.fade_in_smpl) + "," + dps_itoa(t.fade_out_smpl) + ",0,0,"
	            + dps_itoa(dps_current_time()) + "," + dps_itoa(dps_current_time()) + ",'" 
				+ t.title + "',"
	            + dps_itoa(album_id) + "," + dps_itoa(t.tracknum) + "," 
				+ dps_itoa(atoi(t.release_date.c_str())) 
				+ ",'f','f',0,'" + t.origin + "','" + t.reclibid + "')");
			T->exec(SQL);
		}
		SQL = "SELECT last_value FROM audio_id_seq";
	    R = T->exec(SQL);
		if (!is_jingle) {
		    if (R.size() > 0) {
		        audio_id = atoi(R[0][0].c_str());
				SQL = "INSERT INTO audioartists (audio, artist) "
                      "VALUES (" + dps_itoa(audio_id) + "," + dps_itoa(artist_id) + ")";
		        T->exec(SQL);
		    }
		    else {
		        cout << "Failed to retrieve last audio id!" << endl;
		        T->abort();
				return;
		    }
		}
	    T->commit();
		delete T;
	}
	catch (...) {
		cout << "Failed to make database modifications." << endl;
		cout << "SQL: " << SQL << endl;
		cout << "*** Track has not been added to system ***" << endl;
		T->abort();
		delete T;
		abort();
		return;
	}

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
	writeXML(t_bak);
	
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
	string SQL = "SELECT audio.md5 AS md5, audio.title AS title, "
		"artists.name AS artist, albums.name AS album, "
		"archives.name AS archive, audio.music_track AS track, " 
		"audio.music_released AS released, "
		"audio.length_smpl AS length, audio.start_smpl AS start, "
		"audio.end_smpl AS end, audio.intro_smpl AS fade_in, "
		"audio.extro_smpl AS fade_out "
		"FROM audio, audioartists, artists, albums, archives "
		"WHERE audioartists.audio = audio.id "
			"AND audioartists.artist = artists.id "
			"AND audio.archive = archives.id "
			"AND audio.music_album = albums.id "
			"AND archives.id = " + dps_itoa(A.id) +
		" ORDER BY audio.md5";
	track t;
	Result R = T->exec(SQL);
	for (unsigned int i = 0; i < R.size(); i++) {
		t.md5 = R[i]["md5"].c_str();
		t.md5_archive = A;
		t.title = R[i]["title"].c_str();
		t.artist = R[i]["artist"].c_str();
		t.album = R[i]["album"].c_str();
		t.release_date = R[i]["released"].c_str();
		t.tracknum = atoi(R[i]["track"].c_str());
		t.length_smpl = atoi(R[i]["length"].c_str());
		t.trim_start_smpl = atoi(R[i]["start"].c_str());
		t.trim_end_smpl = atoi(R[i]["end"].c_str());
		t.fade_in_smpl = atoi(R[i]["fade_in"].c_str());
		t.fade_out_smpl = atoi(R[i]["fade_out"].c_str());
		tracks->push_back(t);
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
				Logger::log(INFO,routine,S.str(),5);
				t = readXML(fn + ".xml");
			}
			else if (f_test_info.good()) {
				stringstream S;
				S << "Reading INFO " << fn.c_str() << ".info";
				Logger::log(INFO,routine,S.str(),5);
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
    dps_strTrim(&(t->title));
    dps_strPcase(&(t->title));
	if ((t->title).length() > 4 && (t->title).substr(0,4) == "The ") {
		t->title = (t->title).substr(4,(t->title).length() - 4) + ", The";
	}
    dps_strTrim(&(t->artist));
    dps_strPcase(&(t->artist));
	if ((t->artist).length() > 4 && (t->artist).substr(0,4) == "The ") {
		t->artist = (t->artist).substr(4,(t->artist).length() - 4) + ", The";
	}
    dps_strTrim(&(t->album));
    dps_strPcase(&(t->album));
	if ((t->album).length() > 4 && (t->album).substr(0,4) == "The ") {
		t->album = (t->album).substr(4,(t->album).length() - 4) + ", The";
	}
	
	dps_strTrim(&(t->reclibid));
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
	dps_strTrim(&(t->release_date));
    dps_strTrim(&(t->origin));
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

