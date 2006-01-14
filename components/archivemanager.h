#ifndef CLASS_ARCHIVEMANAGER
#define CLASS_ARCHIVEMANAGER

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "dirent.h"
#include "sys/types.h"

#include "dps.h"
#include "config.h"

class archivemanager {
	public:
		archivemanager(archive new_A);
		~archivemanager();

		void load();
		archive spec();
		
		/* Track management */
		track at(unsigned short location, unsigned int index);
		unsigned int size(unsigned short location);
		void clean(unsigned short location, unsigned int index);
		void add(unsigned int index);
		void remove(unsigned int index);
		void recover(unsigned int index);

	private:
		void loadDB(vector<track> *tracks);
		void loadInbox(vector<track> *tracks);
		void loadTrash(vector<track> *tracks);
		void writeXML(track t);
		track readInfo(string md5);
		track readXML(string md5);

		bool hasAudio(string md5);
		void cleanInfo(track *t);
		void trimAudio(track *t);
		string strTrim(string *Str);
		string strPcase(string *Str);
		string strNum(long num, unsigned int digits);
		string itoa(long num);
		long current_time();

		bool initialised;
		track t_null;
		archive A;
		Connection *C;
		Transaction *T;
		vector<track> *trackDB;
		vector<track> *trackInbox;
		vector<track> *trackTrash;
};

#endif
