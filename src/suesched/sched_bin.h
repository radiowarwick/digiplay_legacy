#ifndef CLASS_SCHED_BIN
#define CLASS_SCHED_BIN

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "dps.h"

class sched_bin {
	public:
		sched_bin(Transaction *T,string where_clause,unsigned short b);
		~sched_bin();

		unsigned int size();
		track at(unsigned int index);
		track getRandom();
		track getShorter(track t, unsigned long min_smpl);

	private:
		Result bin;
		unsigned short bin_id;
		track t_null;
};

#endif
