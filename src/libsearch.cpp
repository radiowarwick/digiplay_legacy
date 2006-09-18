#include "libsearch.h"

libsearch::libsearch() {
 
    /* Read in configuration for database connection */
    config *conf = new config("digiplay");

    /* Create the new connection */
    C = new Connection( conf->getDBConnectString() );
}

libsearch::~libsearch() {

}

/* 
 * query
 *
 * Uses the first parameter as a search string in the database.
 *
 * Potential resource issue here, for example, searching for the
 * word 'The' is going to return a whole lot of results.  Might want
 * to return results incrementally as the search progresses.
 */

vector<track>* libsearch::query(string search_string) {
 string SQL;
 search_string = escape_binary(search_string);
 lastQuery_string = search_string;

 vector<track>* Q = new vector<track>;
 T = new Transaction(*C, "");
 
 SQL = "SELECT audio.md5 AS md5, "
  "artists.name AS artist, "
  "audio.title, "
  "albums.name AS album "
  "FROM artists, audioartists, audio, albums "
  "WHERE audioartists.audio=audio.id "
  "AND audioartists.artist=artists.id "
  "AND albums.id=audio.music_album";

 if (searchArtist_flag == false &&
     searchTitle_flag == false && 
     searchAlbum_flag == false) 
 {
   /* Do nothing */
 }
 else if (searchTitle_flag == true)
 {
   SQL += " AND (audio.title ILIKE '%" + search_string + "%'";
     
   if (searchArtist_flag == true) {
     SQL += " OR artists.name ILIKE '%" + search_string + "%'";
   }
   
   if (searchAlbum_flag == true) {
     SQL += " OR albums.name ILIKE '%" + search_string + "%'";
   }
   
   SQL += ") ORDER BY audio.title";
 }
 else if (searchArtist_flag == true)
 {
   SQL += " AND (artists.name ILIKE '%" + search_string + "%'";
   if (searchAlbum_flag == true) {
     SQL += " OR albums.name ILIKE '%" + search_string + "%'";
   }
   SQL += ") ORDER BY audio.title";      
  }
 else 
 { 
   SQL += " AND (albums.name ILIKE '%" + search_string + "%') ORDER BY audio.title";
 }

 if (searchLimit_value > 0) {
  stringstream S;
  S << searchLimit_value;
  SQL += " LIMIT " + S.str();
 }
 
 Result R = T->exec(SQL);
 T->abort();
 delete T;

 for (int i = 0; i < (int)R.size(); i++) {
	 track t = dps_getTrack(C,R[i]["md5"].c_str());
//  int id = atoi(R[i]["id"].c_str());
//  _track* t = new _track(T,id);
  Q->push_back(t);
 }
 return Q;
}

bool libsearch::searchTitle() {
//            searchTitle_flag = false;
 return searchTitle_flag;
}

bool libsearch::searchTitle(bool flag) {
  searchTitle_flag = flag;
  return searchTitle_flag;
}

bool libsearch::searchArtist() {
//            searchArtist_flag = false;
  return searchArtist_flag;
}

bool libsearch::searchArtist(bool flag) {
  searchArtist_flag = flag;
  return searchArtist_flag;
}

bool libsearch::searchAlbum() {
//            searchAlbum_flag = false;
   return searchAlbum_flag;
}

bool libsearch::searchAlbum(bool flag) {
   searchAlbum_flag = flag;
   return searchAlbum_flag;
}

int libsearch::searchLimit() {
  return searchLimit_value;
}

int libsearch::searchLimit(int value) {
  searchLimit_value = value;
  return searchLimit_value;
}

string libsearch::lastQuery() {
  return lastQuery_string;
}

/*_track* libsearch::getTrack(int ID) {
	
  T = new Transaction(*C,"");
  _track* t = new _track(T,ID);
  T->abort();
  delete T;
  
  return t;
}*/
