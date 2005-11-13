#include "track.h"

track::track(Transaction *T, int id) {
	SQL << "SELECT audio.id AS id, "
		"audio.md5 AS md5, "
		"artists.name AS artist, " 
        "audio.title AS title, " 
        "albums.name AS album, "
		"audio.length_smpl AS length, "
		"audio.start_smpl AS start, "
		"audio.end_smpl AS end, "
		"audio.intro_smpl AS intro, "
		"audio.extro_smpl AS extro "
        "FROM audio, artists, albums, audioartists " 
        "WHERE audioartists.audio=audio.id " 
        "AND artists.id=audioartists.artist "
		"AND audio.music_album=albums.id "
		"AND audio.id='"; 
	SQL << id << "'"; 
	R = T->exec(SQL.str());
}

track::track(const track &t) {
	R = *(new Result(t.R));
}

track::~track() {

}

string track::id() {
	return R[0]["id"].c_str();
}

string track::md5() {
	return R[0]["md5"].c_str();
}

string track::title() {
	return R[0]["title"].c_str();
}

string track::artist() {
	return R[0]["artist"].c_str();
}

string track::album() {
	return R[0]["album"].c_str();
}

long track::length_smpl() {
	return (long)(atoi(R[0]["length"].c_str()));
}

long track::start_smpl() {
	return (long)(atoi(R[0]["start"].c_str()));
}

long track::end_smpl() {
	return (long)(atoi(R[0]["end"].c_str()));
}

string track::time() {
	stringstream s;
	int t = (int)((end_smpl() - start_smpl()) / 44100);
//	s << (t-t%3600)/3600 << "h ";
	t -= (t-t%3000);
	s << (t-t%60)/60 << "m ";
	t -= (t-t%60);
	s << t << "s";
	return s.str();
}

long track::intro_smpl() {
	return (long)(atoi(R[0]["intro"].c_str()));
}

long track::extro_smpl() {
	return (long)(atoi(R[0]["extro"].c_str()));
}
