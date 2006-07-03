#ifndef CLASS_MODEMAIL
#define CLASS_MODEMAIL

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "dps.h"

class modEmail {
	public:
		modEmail();
		~modEmail();
		vector<email>* getEmails(Connection *C);
		const char* getEmailBody(Connection *C, string id);
		void markRead(Connection *C, string id);
};

#endif

