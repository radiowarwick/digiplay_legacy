/*
 * Music Library search module
 * DpsMusicSearch.cpp
 * Provides music search functionality for applications
 *
 * Copyright (c) 2005-2007 Chris Cantwell
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
#include <string>
#include <vector>
#include <sstream>

#include "DataAccess.h"
#include "DpsMusicSearch.h"
#include "Logger.h"

DpsMusicSearch::DpsMusicSearch() {
    // Create a configuration object
    conf = new Config("digiplay");
	Q = new std::vector<track>;
}

DpsMusicSearch::~DpsMusicSearch() {
    delete conf;
	delete Q;
}

/** 
 * Uses the first parameter as a search string in the database.
 *
 * Potential resource issue here, for example, searching for the
 * word 'The' is going to return a whole lot of results.  Might want
 * to return results incrementally as the search progresses.
 */
std::vector<track> DpsMusicSearch::query(std::string search_string) {
	const char* routine = "DpsMusicSearch::query";
	strQueryString = search_string;

    std::string SQL;
	vector<string> searchTerms;
    string buf; // Buffer string for splitting up search terms
	int noTerms=0;
	int i;
    
    // Convert to lowercase
    std::transform(strQueryString.begin(), strQueryString.end(),
                   strQueryString.begin(), ::tolower);

    // Remove "the" if it's at the start
    if (strQueryString.substr(0,4) == "the ") {
        strQueryString = strQueryString.substr(4,strQueryString.length() - 4);
    }

    strQueryString = DB->esc(strQueryString);
    lastQuery_string = strQueryString;

    stringstream ssSearchTerms(strQueryString);
	while (ssSearchTerms >> buf)
		searchTerms.push_back(buf);
	noTerms = searchTerms.size();

    SQL = "SELECT id, md5, artist, title, album, censor FROM v_audio_music "
 		    "WHERE dir = 2";

    int censor_start = atoi(conf->getParam("censor_start").c_str());
    int censor_end   = atoi(conf->getParam("censor_end").c_str());
    time_t tim=time(NULL);
    tm *now=localtime(&tim);

    if (censor_start < censor_end) {
	    //showing PM & hiding AM
	    if (now->tm_hour < censor_end && now->tm_hour > censor_start) {
	    	SQL += " AND censor = 'f'";
	    }
    } 
    else {
	    if (now->tm_hour < censor_end || now->tm_hour > censor_start) {
		    SQL += " AND censor = 'f'";
	    }
    }

    if (searchArtist_flag == false &&
            searchTitle_flag == false && 
            searchAlbum_flag == false) {
        /* Do nothing */
    }
    else if (searchTitle_flag == true) {
        SQL += " AND (title ILIKE '%";
			for (i=0; i < noTerms - 1; i++) {
				SQL += searchTerms.at(i) + "%' OR title ILIKE '%";
			}
			SQL += searchTerms.at(i) + "%'";
        if (searchArtist_flag == true) {
            SQL += " OR artist ILIKE '%";
			for (i=0; i < noTerms - 1; i++) {
				SQL += searchTerms.at(i) + "%' OR artist ILIKE '%";
			}
			SQL += searchTerms.at(i) + "%'";
        }
   
        if (searchAlbum_flag == true) {
            SQL += " OR album ILIKE '%";
			for (i=0; i < noTerms - 1; i++) {
				SQL += searchTerms.at(i) + "%' OR album ILIKE '%";
			}
			SQL += searchTerms.at(i) + "%'";
        }
   
        SQL += ") ORDER BY title";
    }
    else if (searchArtist_flag == true) {
        SQL += " AND (artist ILIKE '%";
		for (i=0; i < noTerms - 1; i++) {
			SQL += searchTerms.at(i) + "%' OR artist ILIKE '%";
		}
		SQL += searchTerms.at(i) + "%'";
        if (searchAlbum_flag == true) {
            SQL += " OR album ILIKE '%";
			for (i=0; i < noTerms - 1; i++) {
				SQL += searchTerms.at(i) + "%' OR album ILIKE '%";
			}
			SQL += searchTerms.at(i) + "%'";
        }
        SQL += ") ORDER BY title";      
    }
    else { 
        SQL += " AND (album ILIKE '%";
		for (i=0; i < noTerms - 1; i++) {
			SQL += searchTerms.at(i) + "%' OR album ILIKE '%";
		}
		SQL += searchTerms.at(i) + "%') ORDER BY title";
    }

    if (searchLimit_value > 0) {
        SQL += " LIMIT " + dps_itoa(searchLimit_value);
    }

    PqxxResult R;
    try {
        R = DB->exec("MusicSearch",SQL);
        DB->abort("MusicSearch");
    }
    catch (...) {
        DB->abort("MusicSearch");
        L_ERROR(LOG_DB,"Failed to search for music.");
        throw;
    }

    Q->resize(R.size());
    for (unsigned int i = 0; i < R.size(); i++) {
	    Q->at(i).title = R[i]["title"].c_str();
	    Q->at(i).artists.push_back(R[i]["artist"].c_str());
	    Q->at(i).album = R[i]["album"].c_str();
	    Q->at(i).md5 = R[i]["md5"].c_str();
	    Q->at(i).id = R[i]["id"].c_str();
	    if (std::string(R[i]["censor"].c_str()) == "f") {
		    Q->at(i).censor = false;
	    } 
        else {
		    Q->at(i).censor = true;
	    }
    }
	return *Q;
}

bool DpsMusicSearch::searchTitle() {
    return searchTitle_flag;
}

bool DpsMusicSearch::searchTitle(bool flag) {
    searchTitle_flag = flag;
    return searchTitle_flag;
}

bool DpsMusicSearch::searchArtist() {
    return searchArtist_flag;
}

bool DpsMusicSearch::searchArtist(bool flag) {
    searchArtist_flag = flag;
    return searchArtist_flag;
}

bool DpsMusicSearch::searchAlbum() {
    return searchAlbum_flag;
}

bool DpsMusicSearch::searchAlbum(bool flag) {
    searchAlbum_flag = flag;
    return searchAlbum_flag;
}

int DpsMusicSearch::searchLimit() {
    return searchLimit_value;
}

int DpsMusicSearch::searchLimit(int value) {
    searchLimit_value = value;
    return searchLimit_value;
}

std::string DpsMusicSearch::lastQuery() {
    return lastQuery_string;
}

