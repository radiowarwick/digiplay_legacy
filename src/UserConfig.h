/*
 * User Configuration module
 * UserConfig.h
 * Extracts a users configuration from the database given an Auth module
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
#include <string>
#include <map>

#include "DataAccess.h"

class Auth;

class UserConfig {
    public:
        UserConfig(Auth *authModule);
        ~UserConfig();
        std::string get(std::string param);
        void set(std::string param, std::string val);

    private:
        DataAccess* DB;
        void retrieveConfig();
        std::string _username;
        std::map<std::string,std::string> _userInfo;
};
