/*
 * PostgreSQL Authentication module
 * AudioPsql.h
 * Authenticates users using the digiplay user database relation
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
#include "Logger.h"
#include "config.h"

#include "AuthPsql.h"

AuthPsql::AuthPsql() {
	config* conf = new config("digiplay");
	C = new Connection(conf->getDBConnectString());
	delete conf;
}

AuthPsql::~AuthPsql() {

}

void AuthPsql::authSession(string username, string password) {
	char* routine = "AuthPsql:authenticate";
	L_INFO(LOG_AUTH,"Authenticating user " + username);

	if (username == "") {
		L_ERROR(LOG_AUTH," -> No username supplied.");
		throw AUTH_INVALID_CREDENTIALS;
	}

	Transaction T(*C,"");
	string SQL = "SELECT password FROM users WHERE username='" 
					+ username + "'";
	Result R = T.exec(SQL);

	if (R.size() == 0) {
		L_ERROR(LOG_AUTH,"No such user!");
		throw AUTH_FAILED;
	}

	if (string(R[0]["password"].c_str()) == password) {
		L_INFO(LOG_AUTH," -> Success.");
		Auth::authSession(username,password);
	}
	else {
		throw AUTH_INVALID_CREDENTIALS;
	}
}
