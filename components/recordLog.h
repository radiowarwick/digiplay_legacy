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
#include <qlistview.h>

class recordLog {
	public:
		recordLog(Connection *newC, int loc);
		~recordLog();

		// Logs a record using reclibid
        int reclibid(int user, string id);

		// Logs a record using md5 hash
		int md5(int user, string hash);

		// Logs a record by specifying artist and title
		int details(int user, string artist, string title);
		void getRecentlyLogged(QListView *parent);

	private:
		Connection *C;
		int location;

};

#endif

