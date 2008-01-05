/*
 * Music Library search module
 * DpsMusicSearch.h
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
#ifndef CLASS_DPS_MUSIC_SEARCH
#define CLASS_DPS_MUSIC_SEARCH

#include <string>
#include <vector>
#include <qobject.h>
#include <qmutex.h>

#include "Thread.h"
#include "dps.h"
#include "DataAccess.h"
#include "Config.h"

class DpsMusicSearch	:	public QObject,
							public Thread {

	Q_OBJECT

    public:
		DpsMusicSearch();
		~DpsMusicSearch();
        std::vector<track>* getResults();
		void query(std::string search_string);
		bool searchTitle();
		bool searchTitle(bool flag);
		bool searchArtist();
		bool searchArtist(bool flag);
		bool searchAlbum();
		bool searchAlbum(bool flag);
		int searchLimit();
		int searchLimit(int value);
		void threadExecute();
        std::string lastQuery();
	
	signals:
		void resultsReady();
		
	private:
		QMutex mutex;
		std::vector<track>* Q;
		Config *conf;
	    DataAccess* DB;
		bool searchTitle_flag;
		bool searchArtist_flag;
		bool searchAlbum_flag;
		int searchLimit_value;
        std::string lastQuery_string;
        std::string strQueryString;
};			

#endif
