#ifndef CLASS_SYSTEMMANAGER
#define CLASS_SYSTEMMANAGER

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "dps.h"
#include "config.h"
#include "archivemanager.h"

class systemmanager {
    public:
        systemmanager();
        ~systemmanager();

        /* Track management */
        archivemanager* atArchive(unsigned int index);
		archivemanager* atArchive(string name);
        short sizeArchive();
        void addArchive(string name, string localPath, string remotePath);
		void createArchive(string name, string localPath, string remotePath);	
        void dropArchive(unsigned int index);

	private:
		void loadArchives();
	
		Connection *C;
		Transaction *T;
		vector<archivemanager*>* archives;
};
#endif

