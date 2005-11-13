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

#ifndef STRUCT_TRACK
#define STRUCT_TRACK
struct track {
	bool isNull;
	unsigned short bin;
	unsigned int index;
	unsigned long audio_id;
	string md5;
	string title;
	string artist;
	unsigned long length_smpl;
    unsigned long trim_start_smpl;
    unsigned long trim_end_smpl;
    unsigned long fade_in_smpl;
    unsigned long fade_out_smpl;
};
#endif

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
