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
#include "Logger.h"

#include <iostream>
#include <sstream>
#include <cstdlib>
using std::endl;

#include <pqxx/pqxx>

track dps_getTrack(std::string md5) {
    const char *routine = "dps::dps_getTrack";
    DataAccess DB;
    track t;
    t.isNull = true;
    PqxxResult R;
    std::string SQL, type;
	try {
		SQL = "SELECT audiotypes.name AS type "
				"FROM audio,audiotypes "
				"WHERE audiotypes.id = audio.type "
				"AND md5='" + md5 + "'";
		type = DB.exec("DpsGetTrack",SQL)[0]["type"].c_str();
	}
	catch (...) {
		L_ERROR(LOG_DB, "Cannot get track " + md5);
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
	        R = DB.exec("DpsGetTrack",SQL);
	    }
	    catch (...) {
	        L_ERROR(LOG_DB, "SQL failed on getTrack.");
	        L_ERROR(LOG_DB, " -> SQL: " + SQL );
	    }
    
	    if (R.size() > 0) {
	        t.md5 = R[0]["md5"].c_str();
	        t.title = R[0]["title"].c_str();
	        t.artists.push_back(R[0]["artist"].c_str());
	        t.album = R[0]["album"].c_str();
	        t.release_date = R[0]["released"].c_str();
	        t.tracknum = atoi(R[0]["track"].c_str());
			if (std::string(R[0]["censor"].c_str()) == "t")
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
	        R = DB.exec("DpsGetTrack", SQL);
	    }
	    catch (...) {
	        L_ERROR(LOG_DB, "SQL failed on getTrack.");
	        L_ERROR(LOG_DB, " -> SQL: " + SQL);
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
    DB.abort("DpsGetTrack");
	return t;
}   

std::string dps_itoa(long num) {
    std::stringstream S (std::stringstream::in | std::stringstream::out);
    S << num;
    return S.str();
}

std::string& dps_strTrim(std::string& s) {
    std::string::size_type pos = s.find_last_not_of(' ');
	if (pos != std::string::npos) {
		s.erase(pos + 1);
		pos = s.find_first_not_of(' ');
		if (pos != std::string::npos) s.erase(0,pos);
	}
	else {
		s.erase(s.begin(), s.end());
	}
	return s;
}

// TODO: replace users of this function with stdlib version
std::string& dps_strLcase(std::string& s) {
	for (unsigned int i = 0; i < s.length(); i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] + 32;
	}
	return s;
}


std::string dps_strPcase(std::string *Str) {
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

std::string dps_strNum(long num, unsigned int digits) {
    std::string result = dps_itoa(num);
    for (unsigned int i = 1; i < digits; i++) {
        if (result.length() < digits) {
            result = "0" + result;
        }
    }
    return result;
}

std::string dps_prettyTime(long samples) {
    std::string result = "";
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
	samples -= mins*2646000;
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
