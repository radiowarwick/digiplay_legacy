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
            "audio.extro_smpl AS fade_out "
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

