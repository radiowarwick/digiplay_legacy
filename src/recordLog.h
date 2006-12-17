/*
 * Music logging module
 * recordLog.h
 * Logs music tracks played into the database
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
#ifndef CLASS_RECORDLOG
#define CLASS_RECORDLOG

#include <iostream>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "dirent.h"
#include "sys/types.h"
#include "stdlib.h"
#include <qstring.h>
#include <sstream>
#include <qlistview.h>

class recordLog {
	public:
		recordLog(Connection *newC, int loc);
		~recordLog();

		// Logs a record using reclibid
        int reclibid(int user, string id);

		// Logs a record using md5 hash
		int md5(int user, string hash);

		// Logs a record by specifying artist and title
		int details(int user, string artist, string title);
		void getRecentlyLogged(QListView *parent);

	private:
		Connection *C;
		int location;

};

#endif

