/*
 * Authentication base class
 * Auth.h
 * Provides basis for the authentication framework 
 *
 * Copyright (c) 2006 Chris Cantwell
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

#ifndef CLASS_AUTH
#define CLASS_AUTH

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "DataAccess.h"

#define AUTH_FAILED					10000
#define AUTH_INVALID_CREDENTIALS 	10001


class Auth {
	public:
		Auth();
		virtual ~Auth() = 0;
		bool isPermitted(string privilage);
		bool isAuthenticated();
		string getUser();
		virtual void authSession(string username, string password) = 0;
		void closeSession();

	protected:
		void addPrivilage(string privilage);
		void addUserInfo(string item, string value);

	private:
		Auth(Auth &A);
		DataAccess *DB;
		int location;
		vector<string> _privilages;
		map<string,string> _userInfo;
};	
#endif
