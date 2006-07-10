#include <iostream>
using namespace std;

#include "Auth.h"

Auth::Auth() {

}

Auth::~Auth() {

}

bool Auth::isPermitted(string privilage) {
	// bodge to avoid needing to authenticate while testing!! --cc
	return true;
	// -- end bodge

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
	if (_userInfo.size() == 0) return "";
	return _userInfo["username"];
}

void Auth::authSession(string username, string password) {
	addUserInfo("username",username);
}

void Auth::closeSession() {
	_privilages.clear();
	_userInfo.clear();
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
