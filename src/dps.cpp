/*
 * Common DPS routines
 * dps.h
 * Provides common structure definitions and routines for all applications
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
#include "dps.h"

#include <iostream>
#include <sstream>
using namespace std;

//#include <sys/types.h>
//#include <pwd.h>
//#include <unistd.h>
//#include <stdlib.h>

track dps_getTrack(Connection *C, string md5) {
    track t;
    t.isNull = true;
    Result R;
    string SQL, type;
    Transaction T(*C,"");
	try {
		SQL = "SELECT audiotypes.name AS type "
				"FROM audio,audiotypes "
				"WHERE audiotypes.id = audio.type "
				"AND md5='" + md5 + "'";
		type = T.exec(SQL)[0]["type"].c_str();
	}
	catch (...) {
		cout << "Cannot get track " + md5 << endl;
		return t;
	}
	if (type == "music") {
	    try {
	        SQL = "SELECT audio.md5 AS md5, audio.title AS title, "
	            "artists.name AS artist, albums.name AS album, "
	            "archives.name AS archive, audio.music_track AS track, "
	            "audio.music_released AS released, "
	            "audio.length_smpl AS length, audio.start_smpl AS start, "
	            "audio.end_smpl AS end, audio.intro_smpl AS fade_in, "
	            "audio.extro_smpl AS fade_out, audio.censor AS censor "
	            "FROM audio, audioartists, artists, albums, archives "
	            "WHERE audioartists.audio = audio.id "
	                "AND audioartists.artist = artists.id "
	                "AND audio.archive = archives.id "
	                "AND audio.music_album = albums.id "
	                "AND audio.md5 = '" + md5 + "' "
	            "ORDER BY audio.md5";
	        R = T.exec(SQL);
	    }
	    catch (...) {
	        cout << "SQL failed on getTrack." << endl;
	        cout << " -> SQL: " << SQL << endl;
	    }
    
	    if (R.size() > 0) {
	        t.md5 = R[0]["md5"].c_str();
	        t.title = R[0]["title"].c_str();
	        t.artist = R[0]["artist"].c_str();
	        t.album = R[0]["album"].c_str();
	        t.release_date = R[0]["released"].c_str();
	        t.tracknum = atoi(R[0]["track"].c_str());
			if (R[0]["censor"].c_str() == "t")
				t.censor = true;
			else
				t.censor = false;
	        t.length_smpl = atoi(R[0]["length"].c_str());
	        t.trim_start_smpl = atoi(R[0]["start"].c_str());
	        t.trim_end_smpl = atoi(R[0]["end"].c_str());
	        t.fade_in_smpl = atoi(R[0]["fade_in"].c_str());
	        t.fade_out_smpl = atoi(R[0]["fade_out"].c_str());
	        t.isNull = false;
	    }
	}
	if (type == "jingle") {
	    try {
	        SQL = "SELECT audio.md5 AS md5, audio.title AS title, "
	            "albums.name AS album, "
	            "archives.name AS archive, audio.music_track AS track, "
	            "audio.length_smpl AS length, audio.start_smpl AS start, "
	            "audio.end_smpl AS end, audio.intro_smpl AS fade_in, "
	            "audio.extro_smpl AS fade_out, audio.censor AS censor "
	            "FROM audio, archives, albums "
	            "WHERE audio.archive = archives.id "
	                "AND audio.music_album = albums.id "
	                "AND audio.md5 = '" + md5 + "' "
	            "ORDER BY audio.md5";
	        R = T.exec(SQL);
	    }
	    catch (...) {
	        cout << "SQL failed on getTrack." << endl;
	        cout << " -> SQL: " << SQL << endl;
	    }
    
	    if (R.size() > 0) {
	        t.md5 = R[0]["md5"].c_str();
	        t.title = R[0]["title"].c_str();
	        t.album = R[0]["album"].c_str();
	        t.length_smpl = atoi(R[0]["length"].c_str());
	        t.trim_start_smpl = atoi(R[0]["start"].c_str());
	        t.trim_end_smpl = atoi(R[0]["end"].c_str());
	        t.fade_in_smpl = atoi(R[0]["fade_in"].c_str());
	        t.fade_out_smpl = atoi(R[0]["fade_out"].c_str());
	        t.isNull = false;
		}
	}
	T.abort();
	return t;
}   

string dps_itoa(long num) {
    stringstream S (stringstream::in | stringstream::out);
    S << num;
    return S.str();
}

/*string dps_strTrim(string *Str) {
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
}*/

string& dps_strTrim(string& s) {
	string::size_type pos = s.find_last_not_of(' ');
	if (pos != string::npos) {
		s.erase(pos + 1);
		pos = s.find_first_not_of(' ');
		if (pos != string::npos) s.erase(0,pos);
	}
	else {
		s.erase(s.begin(), s.end());
	}
	return s;
}

string& dps_strLcase(string& s) {
	for (unsigned int i = 0; i < s.length(); i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] + 32;
	}
	return s;
}

string dps_strPcase(string *Str) {
    bool upper = true;
    bool punctuate = false;
    if (Str->length() < 1) return *Str;
    for (unsigned int i = 0; i < Str->length() - 1; i++) {
        char now = (*Str)[i];
        char next = (*Str)[i];
        if ((now == '.' || now == ',' || now == '?') && next == ' ') {
            punctuate = true;
            upper = true;
            continue;
        }
        if ((now == '(' || now == '\'' || now == '\"')
                && (i == 0 || (*Str)[i-1] == ' ')) {
            upper = true;
            continue;
        }
        if ((punctuate) && now != ' ') {
            Str->insert(i+1,1,' ');
            punctuate = false;
            continue;
        }
        if (now == ' ') {
            upper = true;
            continue;
        }
        if (upper) {
            if (now >= 'a' && now <= 'z')
                (*Str)[i] = (*Str)[i] - 32;
            upper = false;
        }
        else {
            if (now >= 'A' && now <= 'Z')
                (*Str)[i] = (*Str)[i] + 32;
        }
    }
    if ((*Str)[Str->length() - 1] >= 'A' && (*Str)[Str->length() - 1] <= 'Z')
        (*Str)[Str->length() - 1] = (*Str)[Str->length() - 1] + 32;
    return *Str;
}

string dps_strNum(long num, unsigned int digits) {
    string result = dps_itoa(num);
    for (unsigned int i = 1; i < digits; i++) {
        if (result.length() < digits) {
            result = "0" + result;
        }
    }
    return result;
}

string dps_prettyTime(long samples) {
	string result = "";
	int hours = (int)(samples / 158760000);
	if (hours > 0) {
		result += dps_itoa(hours) + "h ";
	}
	samples -= hours*158760000;
	int mins = (int)(samples / 2646000);
	if (mins > 0) {
		if (mins < 10) {
			result += "0";
		}
		result += dps_itoa(mins) + "m ";
	}
	samples -= mins*2656000;
	int secs = (int)(samples / 44100);
	if (secs < 10) {
		result += "0";
	}
	result += dps_itoa(secs) + ".";
	samples -= secs*44100;
	int ms = (int)(samples / 441);
	if (ms < 10) {
		result += "0";
	}
	result += dps_itoa(ms) + "s";
	return result;
}

long dps_current_time() {
	    return (long)time(NULL) - 946080000;
}
/*
unsigned int getDigiplayUser() {
	struct passwd *digiplay_user;
	digiplay_user = getpwnam("digiplay");
	return digiplay_user->pw_uid;
}

void dropPrivilage() {
	if (ruid == -1) {
		ruid = getuid();
		euid = geteuid();
	}
	unsigned int newuid = getDigiplayUser();
	#ifdef _POSIX_SAVED_IDS
	int status = setuid(newuid);
	#else
	int status = setreuid(ruid,newuid);
	#endif
	if (status != 0) {
		cout << "ERROR: Could not change to required unprivilaged user" << endl;
		cout << " Make sure ownership is by unprivilaged user" << endl;
		cout << " and the setuid bit is set, or run as root" << endl;
		abort();
	}
}

void gainPrivilage() {
    #ifdef _POSIX_SAVED_IDS
    int status = setuid(ruid);
    #else
    int status = setreuid(ruid,euid);
    #endif
	if (status != 0) {
		cout << "ERROR: Could not regain privilages for some reason." << endl;
	}
}

void showPrivilage() {
	unsigned int x = getuid();
	unsigned int y = geteuid();
	struct passwd *z = getpwuid(x);
	cout << "Real User: " << z->pw_name << endl;
	z = getpwuid(y);
	cout << "Effe User: " << z->pw_name << endl;
}*/
