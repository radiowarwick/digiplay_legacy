/*
 * LDAP Authentication module
 * AuthLdap.h
 * Provides authentication of users against an LDAP server
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
#ifndef CLASS_AUTH_LDAP
#define CLASS_AUTH_LDAP

#include <string>

// Include ldap header to get all the structures and types
#include "DpsLdap.h"
#include "Auth.h"

#define AUTH_LDAP_INVALID_PARAM		10100
#define AUTH_LDAP_CONNECT_FAILED 	10101
#define AUTH_LDAP_PROTOCOL_ERROR	10102

class AuthLdap : public Auth {
	public:
		AuthLdap(std::string host, unsigned int port, std::string baseDn,
                    std::string filter);
		~AuthLdap();
        void reconnect(std::string host, unsigned int port, std::string baseDn, 
                std::string filter);
		void authSession(std::string username, std::string password);

	private:
        void connect(std::string host, unsigned int port, std::string baseDn,
                std::string filter);

        void* ldap_handle;
        ldap_init_t ldap_init;
        ldap_set_option_t ldap_set_option;
        ldap_simple_bind_s_t ldap_simple_bind_s;
        ldap_err2string_t ldap_err2string;
        ldap_search_s_t ldap_search_s;
        ldap_count_entries_t ldap_count_entries;
        ldap_unbind_s_t ldap_unbind_s;
        ldap_msgfree_t ldap_msgfree;

        std::string _host;
		DataAccess *DB;
		unsigned int _port;
        std::string _baseDn;
        std::string _filter;
		LDAP *_myLdap;
};

#endif
