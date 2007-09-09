/*
 * Authentication base class
 * Auth.h
 * Provides basis for the authentication framework 
 *
 * Copyright (c) 2006-2007 Chris Cantwell
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

#include "DataAccess.h"

#define AUTH_FAILED					10000
#define AUTH_INVALID_CREDENTIALS 	10001
#define AUTH_PERMISSION_DENIED      10002


class Auth {
	public:
		Auth();
		virtual ~Auth() = 0;
		bool isPermitted(std::string privilage);
		bool isAuthenticated();
        std::string getUser();
		virtual void authSession(std::string username, 
                                        std::string password) = 0;
		void closeSession();

	protected:
		void addPrivilage(std::string privilage);
		void addUserInfo(std::string item, std::string value);

	private:
		Auth(Auth &A);
		DataAccess *DB;
		int location;
        std::vector<std::string> _privilages;
        std::map<std::string,std::string> _userInfo;
		bool isAuthenticatedFlag;
};	
#endif
