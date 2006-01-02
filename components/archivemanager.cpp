#include "archivemanager.h"

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

void archivemanager::add(unsigned int index) {
	if (!initialised) load();
	if (index > size(DPS_INBOX) - 1) {
		cout << "archivemanager::add: index out of range" << endl;
		return;
	}

	track t = trackInbox->at(index);
	trackInbox->erase(trackInbox->begin() + index);
	trimAudio(&t);
	if (t.trim_end_smpl > t.trim_start_smpl) {
		trackInbox->insert(trackInbox->begin() + index, 1, t);
	}
	else {
		cout << "No non-zero samples, so track ignored." << endl;
		return;
	}

	t.title = escape_binary(t.title);
	t.artist = escape_binary(t.artist);
	t.album = escape_binary(t.album);
	t.origin = escape_binary(t.origin);
	t.reclibid = escape_binary(t.reclibid);
	t.release_date = escape_binary(t.release_date);

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
				&& strPcase(&(t.album)).substr(0,14) ==	"Jingle Package")
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
				SQL = "INSERT INTO albums (name, source, reclibid) "
						"VALUES ('" + t.album + "','" + t.origin
						+ "','" + t.reclibid + "')";
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
				"lifespan) "
	            "VALUES ('" + t.md5 + "'," + itoa(t.md5_archive.id) + "," + itoa(t.length_smpl) + ","
	            + itoa(t.trim_start_smpl) + "," + itoa(t.trim_end_smpl) + ","
	            + itoa(t.fade_in_smpl) + "," + itoa(t.fade_out_smpl) + ",1,0,"
	            "CURRENT_DATE,CURRENT_DATE,'" + t.title + "','f','f',0)";
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
				"VALUES (" + itoa(audio_id) + "," + itoa(album_id) + ",0)";
			T->exec(SQL);
		}
		else {
			SQL = ("INSERT INTO audio (md5, archive, length_smpl, start_smpl, "
				"end_smpl, intro_smpl, extro_smpl, type, creator, creation_date, "
	            "import_date, title, music_album, music_track, music_released, "
	            "sustainer, censor, lifespan) "
	            "VALUES ('" + t.md5 + "'," + itoa(t.md5_archive.id) + ","
				+ itoa(t.length_smpl) + ","
	            + itoa(t.trim_start_smpl) + "," + itoa(t.trim_end_smpl) + ","
	            + itoa(t.fade_in_smpl) + "," + itoa(t.fade_out_smpl) + ",0,0,"
	            "CURRENT_DATE,CURRENT_DATE,'" + t.title + "',"
	            + itoa(album_id) + ",0," + itoa(atoi(t.release_date.c_str())) 
				+ ",'f','f',0)");
			T->exec(SQL);
		}
		SQL = "SELECT last_value FROM audio_id_seq";
	    R = T->exec(SQL);
		if (!is_jingle) {
		    if (R.size() > 0) {
		        audio_id = atoi(R[0][0].c_str());
				SQL = "INSERT INTO audioartists (audio, artist) "
                      "VALUES (" + itoa(audio_id) + "," + itoa(artist_id) + ")";
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

	// Now the track is in the archive, not the inbox...
	trackDB->push_back(trackInbox->at(index));
	trackInbox->erase(trackInbox->begin() + index);
}

void archivemanager::remove(unsigned int index) {

}

void archivemanager::recover(unsigned int index) {

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
		"ORDER BY audio.md5";
	track t;
	Result R = T->exec(SQL);
	for (int i = 0; i < R.size(); i++) {
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
    DIR *dirp;
    struct dirent *dp;
    string fn, md5, path;
	track t;

	path = A.localPath + "/inbox";
    dirp = opendir(path.c_str());
    while (dirp) {
        if ((dp = readdir(dirp)) != NULL) {
            fn = path + "/" + dp->d_name;
			if (fn.length() > 5 && fn.substr(fn.length() - 5, 5) != ".info") {
				continue;
			}
			if (fn.length() < 37) continue;
			md5 = fn.substr(path.length() + 1, 32);
			if ((t = readInfo(fn)).isNull) {
				cout << "archivemananger::loadInbox: No audio file." << endl;
				cout << " -> " << fn << " ignored. " << endl;
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

}

track archivemanager::readInfo(string fn) {
	string buffer;
	track t;
	ifstream *f_info, *f_raw;
	
	/* Attempt to open the info file */
	t.isNull = false;
	try {
		f_info = new ifstream(fn.c_str(), ios::in);
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
        cout << " -> " << fn << endl;
        return t_null;
    }

	/* Attempt to open audio file */
	f_raw = new ifstream(fn.substr(0,fn.length() - 5).c_str(), 
								ios::in|ios::binary|ios::ate);
	if (!f_raw->good()) {
		return t_null;
	}
	t.length_smpl = f_raw->tellg() / 4;
	t.trim_start_smpl = 0;
	t.trim_end_smpl = t.length_smpl;
	t.fade_in_smpl = 0;
	t.fade_out_smpl = t.length_smpl;
	f_raw->close();
	delete f_raw;

	return t;
}

track archivemanager::readXML(string md5) {
	track t;
	return t;
}

bool archivemanager::hasAudio(string md5) {
	return true;
}

void archivemanager::cleanInfo(track *t) {
    strTrim(&(t->title));
    strPcase(&(t->title));
    strTrim(&(t->artist));
    strPcase(&(t->artist));
    strTrim(&(t->album));
    strPcase(&(t->album));

    strTrim(&(t->release_date));
    strTrim(&(t->origin));
}

void archivemanager::trimAudio(track *t) {
#define BLOCK_SAMPLES 4096
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
            if (abs(*left) < BLOCK_SAMPLES && abs(*right) < BLOCK_SAMPLES ) 
				t->trim_start_smpl += 1;
            else break;
        }
    } while (abs(*left) < BLOCK_SAMPLES && abs(*right) < BLOCK_SAMPLES);

    // Scan for end of track
    file_handle->seekg((t->trim_end_smpl - BLOCK_SAMPLES)*4,ios::beg);
    do {
        file_handle->read(audio_buffer,BLOCK_SAMPLES*4);
        for (int i = BLOCK_SAMPLES - 1; i >= 0; i--) {
            left = (short*)(audio_buffer + 4*i);
            right = (short*)(audio_buffer + 4*i + 2);
            if (abs(*left) < BLOCK_SAMPLES && abs(*right) < BLOCK_SAMPLES) 
				t->trim_end_smpl -= 1;
            else break;
        }
        file_handle->seekg((t->trim_end_smpl - BLOCK_SAMPLES)*4, ios::beg);
    } while (abs(*left) < BLOCK_SAMPLES && abs(*right) < BLOCK_SAMPLES);
    
    // Clean up
    delete audio_buffer;
    delete file_handle;
	if (t->trim_end_smpl <= t->trim_start_smpl) {
		cout << "WARNING: audio file " << t->md5 
			<< " does not contain any non-zero samples!" << endl;
	}
#undef BLOCK_SAMPLES
}


/************************************
 * HELPER ROUTINES
 ************************************/
string archivemanager::strTrim(string *Str) {
    int i = Str->length();
    if (i == 0) return *Str;
    while (Str->substr(i - 1,1) == " ") {
        Str->erase(i - 1);
        i--;
        if (i == 0) break;
    }
    if (i == 0) return *Str;
    while (Str->substr(0,1) == " ") {
        Str->erase(0);
    }
    return *Str;
}

string archivemanager::strPcase(string *Str) {
    bool upper = true;
    bool punctuate = false;

    for (unsigned int i = 0; i < Str->length(); i++) {
        if ((*Str)[i] == '.' || (*Str)[i] == ',' || (*Str)[i] == '?') {
            punctuate = true;
            upper = true;
            continue;
        }
        if (((*Str)[i] == '(' || (*Str)[i] == '\'' || (*Str)[i] == '\"') 
				&& (i == 0 || (*Str)[i-1] == ' ')) {
            upper = true;
            continue;
        }
        if ((punctuate) && (*Str)[i] != ' ') {
            Str->insert(i+1,1,' ');
            punctuate = false;
            continue;
        }
        if ((*Str)[i] == ' ') {
            upper = true;
            continue;
        }
        if (upper) {
            if ((*Str)[i] >= 'a' && (*Str)[i] <= 'z')
                (*Str)[i] = (*Str)[i] - 32;
            upper = false;
        }
        else {
            if ((*Str)[i] >= 'A' && (*Str)[i] <= 'Z')
                (*Str)[i] = (*Str)[i] + 32;
        }
    }
    return *Str;
}

string archivemanager::itoa(long num) {
    stringstream S (stringstream::in | stringstream::out);
    S << num;
    return S.str();
}   
