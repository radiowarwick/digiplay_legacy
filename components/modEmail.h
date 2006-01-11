#ifndef CLASS_MODEMAIL
#define CLASS_MODEMAIL

#include <iostream>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "dirent.h"
#include "sys/types.h"
#include "stdlib.h"
#include <qstring.h>
#include <sstream>
#include <qlistview.h>
#include <qpixmap.h>

struct email {
    string from;
    string subject;
    string received;
    string body;
    bool flag;
    string id;
};

class modEmail {
	public:
		modEmail();
		~modEmail();
		vector<email>* getEmails(Connection *C);
		const char* modEmail::getEmailBody(Connection *C, string id);
		void modEmail::markRead(Connection *C, string id);
};

#endif

