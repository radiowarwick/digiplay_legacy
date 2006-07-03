#ifndef CLASS_CONFIG
#define CLASS_CONFIG
    
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "dirent.h"
#include "sys/types.h"

class config {
	public:
		config(string filename);
		~config();
		string getDBConnectString();
		string getParam(string name);
		void setParam(string name, string value);
		void requery();

	private:
		bool isDefined(string name);

		vector<string> *names;
		vector<string> *values;
		Connection *C;
		Transaction *T;
		string DB_CONNECT;
		string LOCATION;
};

#endif
