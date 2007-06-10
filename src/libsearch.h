/*
 * Library search module
 * libsearch.h
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
#ifndef CLASS_LIBSEARCH
#define CLASS_LIBSEARCH

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "dps.h"
#include "DataAccess.h"
#include "Config.h"

class libsearch {
    public:
		libsearch();
		~libsearch();
		vector<track>* query(string search_string);
		bool searchTitle();
		bool searchTitle(bool flag);
		bool searchArtist();
		bool searchArtist(bool flag);
		bool searchAlbum();
		bool searchAlbum(bool flag);
		int searchLimit();
		int searchLimit(int value);
		string lastQuery();

	private:
//		Connection* C;
//		Transaction* T;
		Config *conf;
	        DataAccess* DB;
		bool searchTitle_flag;
		bool searchArtist_flag;
		bool searchAlbum_flag;
		int searchLimit_value;
		string lastQuery_string;
};			

#endif
