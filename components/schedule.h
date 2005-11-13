#ifndef CLASS_SCHEDULE
#define CLASS_SCHEDULE

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "sched_bin.h"

class schedule {
	public:
		schedule(Transaction *T_new);
		~schedule();
		
		void newSchedule();
		void add(track t, short position);
		void remove(unsigned short position);
		bool check(track t);
		track at(unsigned short position);

		unsigned long getLength_smpl();
		unsigned int size();
		
		string getLength_pretty();
		unsigned int getCrossfadePoints();

		void printToScreen();
		void exportToDatabase();

	private:
		Transaction *T;
		vector<track> *S;
};

#endif
