#include "trackinfo.h"

trackinfo::trackinfo(Connection *newC, string md5) {
    config_reader *Conf = new config_reader("digiplay");
    
	if (Conf->isDefined("AUDIO_PATH"))
        AUDIO_PATH = Conf->getParam("AUDIO_PATH");
	
    if (AUDIO_PATH == "") {
        cout << "FATAL: Missing or invalid AUDIO_PATH setting" << endl;
        cout << "  -> Check /etc/digiplay is correct" << endl;
        exit(-1);
	}
	if (AUDIO_PATH.substr(AUDIO_PATH.size() - 2, 1) != "/")
		AUDIO_PATH += "/";
	AUDIO_PATH += md5.substr(0,1);

	C = newC;
	strMD5 = md5;
	strTitle = NULL;
	strArtist = NULL;
	strAlbum = NULL;
	strRecLib = NULL;
	strOrigin = NULL;
	strTrack = NULL;
	strReleased = NULL;
	strLength = NULL;
}

trackinfo::~trackinfo() {
	flushMem();
}

string trackinfo::md5() {
	return "";
}

string trackinfo::title() {
	if (strTitle) return *strTitle;
	return "";
}

void trackinfo::title(string value) {
	if (strTitle) *strTitle = value;
}

string trackinfo::artist() {
	if (strArtist) return *strArtist;
	return "";
}

void trackinfo::artist(string value) {
	if (strArtist) *strArtist = value;
}

string trackinfo::album() {
	if (strAlbum) return *strAlbum;
	return "";
}

void trackinfo::album(string value) {
	if (strAlbum) *strAlbum = value;
}

string trackinfo::reclibid() {
	return *strRecLib;
}

void trackinfo::reclibid(string value) {
	*strRecLib = value;
}

short trackinfo::tracknum() {
	return 0;
}

void trackinfo::tracknum(short value) {

}

long trackinfo::length_ms() {
	return lngLengthSmpl;
}

long trackinfo::trim_start() {
	return lngStartSmpl;
}

long trackinfo::trim_end() {
	return lngEndSmpl;
}


/* ##################################################################
 * File Processing Routines
 * ##################################################################
 */
void trackinfo::readFromFile() {
	string filename = AUDIO_PATH + "/" + strMD5 + ".info";
	
	// Flush any existing data stored in the object
	flushMem();
	
	// Open the info file and seek to the start
	ifstream info_file(filename.c_str(), ios::in);
	info_file.seekg(0);

	string Buffer;
	
	// For each line, determine it's field, and recover the data
	while (!info_file.eof()) {
		getline(info_file, Buffer);
		if (Buffer.substr(0,6) == "title:") {
			strTitle = new string(Buffer.substr(7, Buffer.length() - 7));
			continue;
		}
		if (Buffer.substr(0,8) == "artists:") {
			strArtist = new string(Buffer.substr(9, Buffer.length() - 9));
			continue;
		}
		if (Buffer.substr(0,6) == "album:") {
			strAlbum = new string(Buffer.substr(7, Buffer.length() - 7));
			continue;
		}
		if (Buffer.substr(0,9) == "reclibid:") {
			strRecLib = new string(Buffer.substr(10, Buffer.length() - 10));
			continue;
		}
		if (Buffer.substr(0,7) == "origin:") {
			strOrigin = new string(Buffer.substr(8,Buffer.length() - 8));
			continue;
		}
		if (Buffer.substr(0,9) == "tracknum:") {
			strTrack = new string(Buffer.substr(10,Buffer.length() - 10));
			continue;
		}
		if (Buffer.substr(0,9) == "released:") {
			strReleased = new string(Buffer.substr(10,Buffer.length() - 10));
			continue;
		}
	}

	*strReleased = itoa(atoi(strReleased->c_str()));
	// close info file
	info_file.close();

	// determine the audio file size
	char buffer[10];
	ifstream raw_file (filename.substr(0,filename.length() - 5).c_str(),
											ios::in|ios::binary|ios::ate);
	if (!raw_file.good()) return;
	lngLengthSmpl = raw_file.tellg() / 4;
	lngStartSmpl = 0;
	lngEndSmpl = lngLengthSmpl;
	lngIntroSmpl = 0;
	lngExtroSmpl = lngLengthSmpl;
	sprintf(buffer, "%i", streamsize(raw_file.tellg()));
	strLength = new string(buffer);	
}

void trackinfo::readFromDB() {

}

void trackinfo::saveToFile() {

}

void trackinfo::saveToDB() {
	Transaction T(*C, "");
	long artistid=0, albumid=0, audioid=0;
	string SQL;
	Result R;
	string db_title = escape_binary(*strTitle);
	string db_artist = escape_binary(*strArtist);
	string db_album = escape_binary(*strAlbum);
	string db_source = escape_binary(*strOrigin);
	string db_reclib = escape_binary(*strRecLib);
	string db_released = escape_binary(*strReleased);
	bool isJingle = false;
	
	// We need to check the track isn't already in the database
	SQL = "SELECT id FROM audio "
			"WHERE md5='" + strMD5 + "'";
	R = T.exec(SQL);
	if (R.size() == 1) {
		SQL = "DELETE FROM audioartists "
				"WHERE audio=" + string(R[0][0].c_str());
		T.exec(SQL);
		SQL = "DELETE FROM audio "
				"WHERE id=" + string(R[0][0].c_str());
		T.exec(SQL);
		cout << "Old entry removed" << endl;
	}

	// Deal with jingles
	if (db_album.size() > 13 && strPcase(&db_album).substr(0,14) == "Jingle Package") isJingle = true;

	// First lets sort out the artist
	if (!isJingle) {
		SQL = "SELECT id FROM artists "
				"WHERE name='" + db_artist + "' "
				"OR alt_name LIKE '%" + db_artist + "%'";
		R = T.exec(SQL);
		if (R.size() > 0)
			artistid = atoi(R[0][0].c_str());
		else {
			SQL = "INSERT INTO artists (name) "
					"VALUES ('" + db_artist + "')";
			T.exec(SQL);
			SQL = "SELECT last_value FROM artists_id_seq";
			R = T.exec(SQL);
			if (R.size() > 0)
				artistid = atoi(R[0][0].c_str());
			else {
				cout << "Failed to get the new artist!" << endl;
				T.abort();
				exit(-1);
			}
		}
	}

	// Next lets sort out the album ID
	// if it's empty, we have it is a single and so we use the (none) entry
	if (db_album == "")
		albumid = 0;
	// if it's a jingle, we need to enter it into the jinglepackages relation
	else if (isJingle) {
		SQL = "SELECT * FROM jinglepackage "
				"WHERE name='" + db_album + "' ";
		R = T.exec(SQL);
		if (R.size() > 0)
			albumid = atoi(R[0][0].c_str());
		else {
			SQL = "INSERT INTO jinglepackage (name, description, enabled) "
					"VALUES ('" + db_album + "','" + db_album + "','f')";
			T.exec(SQL);
			SQL = "SELECT last_value FROM jinglepackage_id_seq";
			R = T.exec(SQL);
			if (R.size() > 0) 
				albumid = atoi(R[0][0].c_str());
			else {
				cout << "Failed to get the jingle package name!" << endl;
				T.abort();
				exit(-1);
			}
		}
	}
	// otherwise it's just music, so deal with normally
	else {
		SQL = "SELECT * FROM albums "
				"WHERE name='" + db_album + "' "
				"OR alt_name LIKE '%" + db_album + "%'";
		R = T.exec(SQL);
		if (R.size() > 0)
			albumid = atoi(R[0][0].c_str());
		else {
			SQL = "INSERT INTO albums (name, source, reclibid) "
					"VALUES ('" + db_album + "','" + db_source
					+ "','" + db_reclib + "')";
			T.exec(SQL);
			SQL = "SELECT last_value FROM albums_id_seq";
			R = T.exec(SQL);
			if (R.size() > 0)
				albumid = atoi(R[0][0].c_str());
			else {
				cout << "Failed to get the new albm!" << endl;
				T.abort();
				exit(-1);
			}
		}
	}
	
	// We can now add the audio
	// if it's a jingle
	if (isJingle) 
	    SQL = "INSERT INTO audio (md5, archive, length_smpl, start_smpl, "
			"end_smpl, intro_smpl, extro_smpl, type, creator, creation_date, "
            "import_date, title, jingle_package, music_track, music_released, "
            "sustainer, censor, lifespan, jingle_type) "
            "VALUES ('" + strMD5 + "',0," + itoa(lngLengthSmpl) + ","
            + itoa(lngStartSmpl) + "," + itoa(lngEndSmpl) + ","
            + itoa(lngIntroSmpl) + "," + itoa(lngExtroSmpl) + ",1,0,"
            "CURRENT_DATE,CURRENT_DATE,'" + db_title + "',"
            + itoa(albumid) + ",0," + db_released + ",'f','f',0,0)";
	else
		SQL = "INSERT INTO audio (md5, archive, length_smpl, start_smpl, "
			"end_smpl, intro_smpl, extro_smpl, type, creator, creation_date, "
			"import_date, title, music_album, music_track, music_released, "
			"sustainer, censor, lifespan) "
			"VALUES ('" + strMD5 + "',0," + itoa(lngLengthSmpl) + "," 
			+ itoa(lngStartSmpl) + "," + itoa(lngEndSmpl) + "," 
			+ itoa(lngIntroSmpl) + "," + itoa(lngExtroSmpl) + ",0,0,"
			"CURRENT_DATE,CURRENT_DATE,'" + db_title + "'," 
			+ itoa(albumid) + ",0," + db_released + ",'f','f',0)";
	T.exec(SQL);
	SQL = "SELECT last_value FROM audio_id_seq";
	R = T.exec(SQL);
	if (!isJingle) {
		if (R.size() > 0) {
			audioid = atoi(R[0][0].c_str());
			SQL = "INSERT INTO audioartists (audio, artist) "
					"VALUES (" + itoa(audioid) + "," + itoa(artistid) + ")";
			T.exec(SQL);
		}
		else {
			cout << "Failed to retrieve last audio id!" << endl;
			T.abort();
			exit (-1);
		}
	}
	T.commit();
}

bool trackinfo::inDB() {
	Transaction T(*C,"");
	string SQL = "SELECT id FROM audio "
					"WHERE md5='" + strMD5 + "'";
	Result R = T.exec(SQL);
	if (R.size() > 0) return true;
	return false;
}

bool trackinfo::hasAudio() {
    if (strMD5 == "") return false;
    string filename = AUDIO_PATH + "/" + strMD5;
    ifstream *file_handle = new ifstream(filename.c_str(),
                                         ios::in|ios::binary|ios::ate);
	bool result = file_handle->good();
	delete file_handle;
	return result;
}
						
void trackinfo::flushMem() {
	if (strTitle) delete strTitle;
	if (strAlbum) delete strAlbum;
	if (strRecLib) delete strRecLib;
	if (strOrigin) delete strOrigin;
	if (strTrack) delete strTrack;
	if (strReleased) delete strReleased;
	if (strLength) delete strLength;
}

void trackinfo::clean() {
	strTrim(strTitle);
	strPcase(strTitle);
	strTrim(strArtist);
	strPcase(strArtist);
	strTrim(strAlbum);
	strPcase(strAlbum);

	strTrim(strReleased);
	strTrim(strOrigin);
	strTrim(strTrack);
}

void trackinfo::audio_trim() {
	if (strMD5 == "") return;
	string filename = AUDIO_PATH + "/" + strMD5;
	cout << filename << endl;	
	char *audio_buffer = new char[2048];
	ifstream *file_handle = new ifstream(filename.c_str(),
											ios::in|ios::binary|ios::ate);
	if (!file_handle->good()) return;

	file_handle->seekg(0,ios::end);
	long length_byte = file_handle->tellg();
	short *left, *right;
//	long max = 0; UNUSED
	
	lngStartSmpl = 0;
	lngEndSmpl = length_byte / 4;
	cout << " -> Length: " << lngEndSmpl << " samples,   Trim: [";
	
	// Scan for start of track
	file_handle->seekg(0,ios::beg);
	do {
		file_handle->read(audio_buffer,2048);
		for (int i = 0; i < 512; i++) {
			left = (short*)(audio_buffer + 4*i);
			right = (short*)(audio_buffer + 4*i + 2);
			if (abs(*left) < 512 && abs(*right) < 512 ) lngStartSmpl += 1;
			else break;
		}
	} while (abs(*left) < 512 && abs(*right) < 512);
	cout << lngStartSmpl << ", ";

	// Scan for end of track
	file_handle->seekg((lngEndSmpl - 512)*4,ios::beg);
	do {
		file_handle->read(audio_buffer,2048);
		for (int i = 511; i >= 0; i--) {
			left = (short*)(audio_buffer + 4*i);
			right = (short*)(audio_buffer + 4*i + 2);
			if (abs(*left) < 512 && abs(*right) < 512) lngEndSmpl -= 1;
			else break;
		}
		file_handle->seekg((lngEndSmpl - 512)*4, ios::beg);
	} while (abs(*left) < 512 && abs(*right) < 512);
	cout << (length_byte / 4) - lngEndSmpl << "]" << endl;

	// Clean up
	delete audio_buffer;
	delete file_handle;
}


/* ####
 * Helper Routines
 * ###
 */
string trackinfo::strTrim(string *Str) {
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

string trackinfo::strPcase(string *Str) {
	bool upper = true;
	bool punctuate = false;
	
	for (unsigned int i = 0; i < Str->length(); i++) {
		if ((*Str)[i] == '.' || (*Str)[i] == ',' || (*Str)[i] == '?') {
			punctuate = true;
			upper = true;
			continue;
		}
		if ((*Str)[i] == '(' || (*Str)[i] == '\'' || (*Str)[i] == '\"') {
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

string trackinfo::itoa(long num) {
	stringstream S (stringstream::in | stringstream::out);
	S << num;
	return S.str();
}
