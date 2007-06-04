/*
 * Library search module
 * libsearch.cpp
 * Provides music search functionality for applications
 *
 * Copyright (c) 2005-2006 Chris Cantwell
 * Copyright (c) 2005-2006 Ian Liverton
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
#include "libsearch.h"

libsearch::libsearch() {
 
    /* Read in configuration for database connection */
//    config *conf = new config("digiplay");

    /* Create the new connection */
//    C = new Connection( conf->getDBConnectString() );
}

libsearch::~libsearch() {
//    if (C && C->is_open()) {
//        C->Disconnect();
//    }
//    delete C;
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
 // Convert to lowercase
 std::transform(search_string.begin(), search_string.end(),
                search_string.begin(), ::tolower);
 // Remove "the" if it's at the start
 if (search_string.substr(0,4) == "the ") {
     search_string = search_string.substr(4,search_string.length() - 4);
 }

 search_string = escape_binary(search_string);
 lastQuery_string = search_string;

 vector<track>* Q = new vector<track>;
 
 SQL = "SELECT audio.id AS id, audio.md5 AS md5, "
  "artists.name AS artist, "
  "audio.title, "
  "albums.name AS album "
  "FROM artists, audioartists, audio, albums, audiodir "
  "WHERE audioartists.audioid=audio.id "
  "AND audioartists.artistid=artists.id "
  "AND albums.id=audio.music_album "
  "AND audio.censor='f' "
  "AND audiodir.audioid = audio.id "
  "AND audiodir.dirid = 2";

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
 Result R = DB->exec(SQL);
 DB->abort();

 Q->resize(R.size());
 for (unsigned int i = 0; i < R.size(); i++) {
	Q->at(i).title = R[i]["title"].c_str();
	Q->at(i).artist = R[i]["artist"].c_str();
	Q->at(i).album = R[i]["album"].c_str();
	Q->at(i).md5 = R[i]["md5"].c_str();
    Q->at(i).id = R[i]["id"].c_str();
 }
 return Q;
}

bool libsearch::searchTitle() {
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
