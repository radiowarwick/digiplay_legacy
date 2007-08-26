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
#include <string>
using namespace std;

#include <dlfcn.h>

#include "Logger.h"
#include "DataAccess.h"
#include "DbDefine.h"

#include "AuthLdap.h"

AuthLdap::AuthLdap(string host, unsigned int port, string baseDn, 
                        string filter) {
	char* routine = "AuthLdap::AuthLdap";

    // Attempt to load the ldap shared library
    ldap_handle = dlopen("libldap.so", RTLD_LAZY);
    if (!ldap_handle) {
        L_CRITICAL(LOG_AUTH,"Cannot open LDAP library");
        L_CRITICAL(LOG_AUTH,string(dlerror()));
        throw AUTH_LDAP_CONNECT_FAILED;
    }

    // Load the symbols we need
    ldap_init = (ldap_init_t) dlsym(ldap_handle, "ldap_init");
    ldap_set_option = (ldap_set_option_t) dlsym(ldap_handle, "ldap_set_option");
    ldap_simple_bind_s 
        = (ldap_simple_bind_s_t) dlsym(ldap_handle, "ldap_simple_bind_s");
    ldap_err2string = (ldap_err2string_t) dlsym(ldap_handle, "ldap_err2string");
    ldap_search_s = (ldap_search_s_t) dlsym(ldap_handle, "ldap_search_s");
    ldap_count_entries = (ldap_count_entries_t) dlsym(ldap_handle, "ldap_count_entries");
    ldap_unbind_s = (ldap_unbind_s_t) dlsym(ldap_handle, "ldap_unbind_s");
    ldap_msgfree = (ldap_msgfree_t) dlsym(ldap_handle, "ldap_msgfree");
    // Now ready to use these routines

	DB = new DataAccess();
    _myLdap = 0;
    this->connect(host, port, baseDn, filter);
}

AuthLdap::~AuthLdap() {

}

void AuthLdap::reconnect(string host, unsigned int port, string baseDn,
                        string filter) {
    if (host == _host && port == _port && baseDn == _baseDn 
            && filter == _filter) {
        return;
    }
    this->connect(host, port, baseDn, filter);
}

void AuthLdap::authSession(string username, string password) {
	char* routine = "AuthLdap::authenticate";
	L_INFO(LOG_AUTH,"Authenticating user " + username);
	
	if (username == "") {
		L_ERROR(LOG_AUTH," -> No username supplied.");
		throw AUTH_INVALID_CREDENTIALS;
	}

	string dn = "uid=" + username + "," + _baseDn;
    string filter = "(&" + _filter + "(uid=" + username + "))";
	L_INFO(LOG_AUTH," -> bind DN is '" + dn + "'");
    L_INFO(LOG_AUTH," -> user filter is '" + filter + "'");

    // Bind to LDAP as user
	int ret = 0;
	int version = LDAP_VERSION3;
	ldap_set_option(_myLdap, LDAP_OPT_PROTOCOL_VERSION, &version);
	ret = ldap_simple_bind_s(_myLdap, dn.c_str(), password.c_str());
    
    switch (ret) {
	    case LDAP_SUCCESS: {
            L_INFO(LOG_AUTH," -> Bind successful.");
            LDAPMessage* res;
            if (ldap_search_s(_myLdap, dn.c_str(), LDAP_SCOPE_SUBTREE,
                        filter.c_str(), NULL, 0, &res) != LDAP_SUCCESS) {
                L_ERROR(LOG_AUTH, "Unable to query for user.");
            }
            if (ldap_count_entries(_myLdap, res) == 0) {
                L_INFO(LOG_AUTH," -> User denied by filter.");
                throw AUTH_PERMISSION_DENIED;
            }
            ldap_msgfree(res);
		    L_INFO(LOG_AUTH," -> Success.  Checking for username in database.");

            // Check whether user exists in the database.
            // Since we're using LDAP authentication, they may not.
            string SQL = "SELECT id, enabled FROM users WHERE username = '"
                            + username + "' LIMIT 1";
    		PqxxResult R;
    		try {
            	R = DB->exec("AuthLdap",SQL);
                DB->abort("AuthLdap");
    		}
    		catch (...) {
    			L_ERROR(LOG_AUTH,"Failed to check for user in database."); 
                DB->abort("AuthLdap");
                return;
    		}
    
            if (R.size() == 0) {
                L_ERROR(LOG_AUTH,"User is not in database. Login denied.");
                throw AUTH_PERMISSION_DENIED;            
            }
    		else {
    			L_INFO(LOG_AUTH,"Username " + username 
                                + " already in the database so not adding.");
                if (string(R[0]["enabled"].c_str()) == "f") {
                    L_ERROR(LOG_AUTH,"User account " + username 
                            + " is disabled.");
                    throw AUTH_PERMISSION_DENIED;
                }
		    }
		    Auth::authSession(username,password);
            break;
        }
        case LDAP_INVALID_CREDENTIALS: {
		    L_ERROR(LOG_AUTH," -> Invalid credentials.");
    		throw AUTH_INVALID_CREDENTIALS;
    	}
        case LDAP_PROTOCOL_ERROR: {
		    L_ERROR(LOG_AUTH," -> Protocol error");
    		throw AUTH_LDAP_PROTOCOL_ERROR;
    	}
        default: {
		    L_INFO(LOG_AUTH," -> return status: " 
                                + string(ldap_err2string(ret)));
    		throw AUTH_FAILED;
	    }
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

void AuthLdap::connect(string host, unsigned int port, string baseDn, 
                        string filter) {
    char* routine = "AuthLdap::connect";
    if (_myLdap) {
        ldap_unbind_s(_myLdap);
    }
    _myLdap = 0; 
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
    _filter = filter;

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
