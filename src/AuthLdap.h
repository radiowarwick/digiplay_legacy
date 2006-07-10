#ifndef CLASS_AUTH_LDAP
#define CLASS_AUTH_LDAP

#include <string>
using namespace std;

#include <ldap.h>

#include "Auth.h"

#define AUTH_LDAP_INVALID_PARAM		10100
#define AUTH_LDAP_CONNECT_FAILED 	10101
#define AUTH_LDAP_PROTOCOL_ERROR	10102
class AuthLdap : public Auth {
	public:
		AuthLdap(string host, unsigned int port, string baseDn);
		~AuthLdap();
		void authSession(string username, string password);

	private:
		string _host;
		unsigned int _port;
		string _baseDn;
		LDAP *_myLdap;
};

#endif
