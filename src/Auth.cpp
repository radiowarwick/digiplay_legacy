/*
 * Authentication base class
 * Auth.cpp
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

#include <iostream>
using namespace std;

#include "Logger.h"

#include "Auth.h"

Auth::Auth() {
    closeSession();
}

Auth::~Auth() {

}

bool Auth::isPermitted(string privilage) {
	for (unsigned int i = 0; i < _privilages.size(); i++) {
		if (_privilages.at(i) == privilage) {
			return true;
		}
	}
	return false;
}

bool Auth::isAuthenticated() {
	if (_userInfo.size() == 0) return false;
	return true;
}

string Auth::getUser() {
	if (_userInfo.size() == 0) return "Guest";
	return _userInfo["username"];
}

void Auth::authSession(string username, string password) {
    char *routine = "Auth::authSession";
    if (password == "") {
        L_INFO(LOG_AUTH,"Note user " + username + " supplied blank password");
    }
	_privilages.clear();
	_userInfo.clear();
	addUserInfo("username",username);
    
	// bodge --cc
	addPrivilage("TabInfo");
	addPrivilage("TabSearch");
	addPrivilage("TabPlaylist");
	addPrivilage("TabFileBrowser");
	addPrivilage("TabEmail");
	addPrivilage("TabLogging");
//	addPrivilage("TabScripts");
}

void Auth::closeSession() {
	_privilages.clear();
	_userInfo.clear();
	addPrivilage("TabInfo");
	addPrivilage("TabSearch");
	addPrivilage("TabLogging");
    addPrivilage("TabFileBrowser");
}

void Auth::addPrivilage(string privilage) {
	for (unsigned int i = 0; i < _privilages.size(); i++) {
		if (_privilages.at(i) == privilage) {
			cout << "WARNING: Privilage is already present" << endl;
			return;
		}
	}
	_privilages.push_back(privilage);
}

void Auth::addUserInfo(string item, string value) {
	_userInfo[item] = value;
}
