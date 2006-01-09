#ifndef CLASS_RECORDLOG
#define CLASS_RECORDLOG

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

class recordLog {
	public:
		recordLog(int loc);
		~recordLog();
	        int reclibid(Connection *C, int user, string *id);
		int md5(Connection *C, int user, string *hash);
		int details(Connection *C, int user, string *artist, string *title);
		
	private:
		int location;

};

#endif

