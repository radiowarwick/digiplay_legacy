/*
 * Music Library search module
 * DpsMusicSearch.cpp
 * Provides music search functionality for applications
 *
 * Copyright (c) 2005-2009 Chris Cantwell
 * Copyright (c) 2008-2009 Simon Pain
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
#include <cstdlib>
#include <algorithm>

#include "DataAccess.h"
#include "DpsMusicSearch.h"
#include "dps/Dps.h"
#include "Logger.h"

#include "sphinxclient.h"

DpsMusicSearch::DpsMusicSearch() {
    // Create a configuration object
    conf = new Config("digiplay");
}

DpsMusicSearch::~DpsMusicSearch() {
    delete conf;
}

/** 
 * Uses the first parameter as a search string in the database.
 *
 * Potential resource issue here, for example, searching for the
 * word 'The' is going to return a whole lot of results.  Might want
 * to return results incrementally as the search progresses.
 */
std::vector<DpsAudioItem> DpsMusicSearch::query(std::string search_string) {
	const char* routine = "DpsMusicSearch::query";
	strQueryString = search_string;
    
    // Convert to lowercase
    std::transform(strQueryString.begin(), strQueryString.end(),
                   strQueryString.begin(), ::tolower);

    //strQueryString = DB->esc(strQueryString);
    lastQuery_string = strQueryString;

    std::string query;
    bool comma = false;
    if (searchTitle_flag) {
        if (comma) query += ",";
        comma = true;
        query += "title";
    }
    if (searchArtist_flag) {
        if (comma) query += ",";
        comma = true;
        query += "artist";
    }
    if (searchAlbum_flag) {
        if (comma) query += ",";
        comma = true;
        query += "album";
    }
    query = "@(" + query + ") " + strQueryString;

    //std::string s_host = conf->getParam("sphinx_host");
    std::string s_host = "127.0.0.1";
    int         s_port = atoi(conf->getParam("sphinx_port").c_str());

    Q.clear();
    sphinx_client * s = sphinx_create( SPH_TRUE );
    sphinx_result * r;
    if (!s) {
        cout << "FAILED TO CREATE SPHINX SEARCH" << endl;
    }
    else {
        sphinx_set_server( s, s_host.c_str(), s_port);
        sphinx_set_match_mode ( s, SPH_MATCH_BOOLEAN );
        sphinx_set_sort_mode ( s, SPH_SORT_RELEVANCE, NULL );
        sphinx_set_limits( s, 0, 25,25,25);
        r = sphinx_query( s, query.c_str(), "music music-delta", NULL);
        if (!r) {
            cout << "Failed to perform query." << endl;
            cout << sphinx_error(s) << endl;
        }
        else {
            cout << "Found: " << r->total_found << " out of " << r->total << endl;
            for (int i = 0; i < r->num_matches; ++i) {
                cout << "ID: " << sphinx_get_id( r, i ) << endl;
                Q.push_back(DpsAudioItem(sphinx_get_id(r, i)));
            }
        }
    }
    return Q;
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

