#include "Logger.h"

#include "AuthLdap.h"

AuthLdap::AuthLdap(string host, unsigned int port, string baseDn) {
	char* routine = "AuthLdap::AuthLdap";
	_myLdap = NULL;
	if (host == "") {
		Logger::log(ERROR,routine,"No host specified",1);
		throw AUTH_LDAP_INVALID_PARAM;
	}
	if (port == 0 || port >= 65536) {
		Logger::log(ERROR,routine,"Invalid Port",1);
		throw AUTH_LDAP_INVALID_PARAM;
	}
	if (baseDn == "") {
		Logger::log(ERROR,routine,"No base DN specified",1);
		throw AUTH_LDAP_INVALID_PARAM;
	}
	_host = host;
	_port = port;
	_baseDn = baseDn;

	Logger::log(INFO,routine,"Creating connection to LDAP server...",1);
	Logger::log(INFO,routine," -> server:  " + host,3);
	Logger::log(INFO,routine," -> base DN: " + baseDn,3);

	try {
		_myLdap = ldap_init(host.c_str(),port);
	}
	catch (...) {
		Logger::log(ERROR,routine,"Failed to create LDAP connection",1);
		throw AUTH_LDAP_CONNECT_FAILED;
	}
	Logger::log(INFO,routine,"Success.",2);
}

AuthLdap::~AuthLdap() {

}

void AuthLdap::authSession(string username, string password) {
	char* routine = "AuthLdap::authenticate";
	Logger::log(INFO,routine,"Authenticating user " + username,2);
	
	string dn = "uid=" + username + "," + _baseDn;
	Logger::log(INFO,routine," -> bind DN is '" + dn + "'",3);

	int ret = 0;
	int version = LDAP_VERSION3;
	ldap_set_option(_myLdap, LDAP_OPT_PROTOCOL_VERSION, &version);

	ret = ldap_simple_bind_s(_myLdap, dn.c_str(), password.c_str());
	string retText = ldap_err2string(ret);


	if (retText == "Success") {
		Logger::log(INFO,routine," -> " + retText,3);
		Auth::authSession(username,password);
	}
	else if (retText == "Invalid credentials") {
		Logger::log(ERROR,routine," -> " + retText,2);
		throw AUTH_INVALID_CREDENTIALS;
	}
	else if (retText == "Protocol error") {
		Logger::log(INFO,routine," -> " + retText,1);
		throw AUTH_LDAP_PROTOCOL_ERROR;
	}
	else {
		Logger::log(INFO,routine," -> " + retText,1);
		throw AUTH_FAILED;
	}

	return;

	//TODO: Get information about user
	string filter = "(uid=" + username;
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
			Logger::log(INFO,routine,ldapDn,4);
		}
		for (attr_name = ldap_first_attribute(_myLdap, e, &ber); 
				attr_name != NULL;
				attr_name = ldap_next_attribute(_myLdap, e, ber)) {
			
		}
	}
}
