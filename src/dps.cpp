#include "dps.h"

#include <iostream>
#include <sstream>
using namespace std;

track dps_getTrack(Connection *C, string md5) {
    track t;
    Result R;
    string SQL;
    try {
        Transaction T(*C,"");
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
        T.abort();
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
        return t;
    }
    else {
        t.isNull = true;
        return t;
    }
}   

string dps_itoa(long num) {
    stringstream S (stringstream::in | stringstream::out);
    S << num;
    return S.str();
}

string dps_strTrim(string *Str) {
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

