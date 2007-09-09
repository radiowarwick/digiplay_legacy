/*
 * PostgreSQL Authentication module
 * AudioPsql.h
 * Authenticates users using the digiplay user database relation
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
#include <openssl/md5.h>

#include "DataAccess.h"
#include "Logger.h"
#include "dps.h"

#include "AuthPsql.h"

AuthPsql::AuthPsql() {
    DB = new DataAccess();
}

AuthPsql::~AuthPsql() {

}

void AuthPsql::authSession(std::string username, std::string password) {
	char* routine = "AuthPsql:authenticate";
	L_INFO(LOG_AUTH,"Authenticating user " + username);

	if (username == "") {
		L_ERROR(LOG_AUTH," -> No username supplied.");
		throw AUTH_INVALID_CREDENTIALS;
	}

    std::string SQL;
    PqxxResult R;

    try {
	    SQL = "SELECT password,enabled FROM users WHERE username='" 
					+ username + "'";
    	R = DB->exec("AuthPsql",SQL);
        DB->abort("AuthPsql");
    }
    catch (...) {
        DB->abort("AuthPsql");
        throw;
    }

	if (R.size() == 0) {
		L_ERROR(LOG_AUTH,"No such user!");
		throw AUTH_FAILED;
	}

    std::string db_pass = R[0]["password"].c_str();

    // MD5 hash user-supplied password
    MD5_CTX context;
    unsigned char digest[16];
    char encrypt[32];
    MD5_Init(&context);
    MD5_Update(&context, password.c_str(), password.size());
    MD5_Final(digest, &context);
    for (unsigned int i = 0; i < 16; ++i) {
        sprintf(encrypt + i*2, "%02x", digest[i]);
    }
    std::string hash(encrypt);
	
    // Check users password hash matches
    if (db_pass == hash) {
		L_INFO(LOG_AUTH," -> Success.");
        if (std::string(R[0]["enabled"].c_str()) == "f") {
            L_ERROR(LOG_AUTH,"Permission denied for '" + username + "'");
            throw AUTH_PERMISSION_DENIED;
        }
		Auth::authSession(username,password);
	}
	else {
        L_ERROR(LOG_AUTH,"Incorrect username or password for " + username);
		throw AUTH_INVALID_CREDENTIALS;
	}
}
