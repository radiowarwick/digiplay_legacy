/*
 * LDAP Authentication module
 * AuthLdap.h
 * Provides authentication of users against an LDAP server
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
#include "DataAccess.h"

#include "AuthLdap.h"

AuthLdap::AuthLdap(string host, unsigned int port, string baseDn) {
	char* routine = "AuthLdap::AuthLdap";
	
	_myLdap = NULL;
	if (host == "") {
		L_ERROR(LOG_AUTH,"No host specified.");
		throw AUTH_LDAP_INVALID_PARAM;
	}
	if (port == 0 || port >= 65536) {
		L_ERROR(LOG_AUTH,"Invalid port.");
		throw AUTH_LDAP_INVALID_PARAM;
	}
	if (baseDn == "") {
		L_ERROR(LOG_AUTH,"No Base DN specified.");
		throw AUTH_LDAP_INVALID_PARAM;
	}
	_host = host;
	_port = port;
	_baseDn = baseDn;
	DB = new DataAccess();

	L_INFO(LOG_AUTH,"Creating connection to LDAP server...");
	L_INFO(LOG_AUTH," -> server: " + host);
	L_INFO(LOG_AUTH," -> base DN: " + baseDn);

	try {
		_myLdap = ldap_init(host.c_str(),port);
	}
	catch (...) {
		L_ERROR(LOG_AUTH,"Failed to create LDAP connection.");
		throw AUTH_LDAP_CONNECT_FAILED;
	}
	L_INFO(LOG_AUTH,"LDAP initialisation successful.");
}

AuthLdap::~AuthLdap() {

}

void AuthLdap::authSession(string username, string password) {
	char* routine = "AuthLdap::authenticate";
	L_INFO(LOG_AUTH,"Authenticating user " + username);
	
	if (username == "") {
		L_ERROR(LOG_AUTH," -> No username supplied.");
		throw AUTH_INVALID_CREDENTIALS;
	}

	string dn = "uid=" + username + "," + _baseDn;
	L_INFO(LOG_AUTH," -> bind DN is '" + dn + "'");

	int ret = 0;
	int version = LDAP_VERSION3;
	ldap_set_option(_myLdap, LDAP_OPT_PROTOCOL_VERSION, &version);

	ret = ldap_simple_bind_s(_myLdap, dn.c_str(), password.c_str());
	string retText = ldap_err2string(ret);

	if (retText == "Success") {
		L_INFO(LOG_AUTH," -> Success.  Checking for username in database.");

    string SQL = "SELECT id FROM users WHERE username = '"
                        + username + "' LIMIT 1";
		Result R;
		try {
    	R = DB->exec(SQL);
			DB->abort();
		}
		catch (...) {
			L_ERROR(LOG_AUTH,"Failed to check for user in database."); 
		}
    if (R.size() == 0) {
      L_INFO(LOG_AUTH,"No user ID matching username. Adding to database.");
		    SQL = "INSERT INTO users (username, password, enabled) "
       		           "VALUES ('" + username + "', '', 't'); ";
		    try {
    		  DB->exec(SQL);
		      DB->commit();
	     		SQL = "SELECT id FROM users WHERE username = '"
                              + username + "' LIMIT 1";
													    Result R = DB->exec(SQL);
					DB->exec(SQL);
					DB->abort();
					SQL = "INSERT INTO usersgroups (userid, groupid) "
											 "VALUES (" + string(R[0]["id"].c_str()) + ", 1);";
    		  DB->exec(SQL);
		      DB->commit();
    		}
		    catch (...) {
    		  L_ERROR(LOG_AUTH,"Failed to insert user " + username +
		                " into the database.");
   		 }


    }
		else {
			L_INFO(LOG_AUTH,"Username " + username + " already in the database so not adding.");
		}
		Auth::authSession(username,password);
	}
	else if (retText == "Invalid credentials") {
		L_ERROR(LOG_AUTH," -> Invalid credentials.");
		throw AUTH_INVALID_CREDENTIALS;
	}
	else if (retText == "Protocol error") {
		L_ERROR(LOG_AUTH," -> Protocol error");
		throw AUTH_LDAP_PROTOCOL_ERROR;
	}
	else {
		L_INFO(LOG_AUTH," -> return status: " + retText);
		throw AUTH_FAILED;
	}

	return;

	//TODO: Get information about user
/*	string filter = "(uid=" + username;
	LDAPMessage *res;
	ret = ldap_search_s(_myLdap, _baseDn.c_str(), LDAP_SCOPE_BASE, 
							filter.c_str(), NULL, 0, &res);

	char *attr_name;
	char *ldapDn;
	char **attr_vals;
	LDAPMessage *e;
	BerElement *ber;
	for (e = ldap_first_entry(_myLdap, res); e != NULL; 
				e = ldap_next_entry(_myLdap, e)) {
		if ((ldapDn = ldap_get_dn(_myLdap, e)) != NULL) {
			L_INFO(LOG_AUTH,ldapDn);
		}
		for (attr_name = ldap_first_attribute(_myLdap, e, &ber); 
				attr_name != NULL;
				attr_name = ldap_next_attribute(_myLdap, e, ber)) {
			
		}
	}*/
}
