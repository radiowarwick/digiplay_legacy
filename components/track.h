/* Track Handle Header
 * track.h
 *
 * Stores information about an audio file including filename and title, etc
 * (c) Copyright Chris Cantwell 2004
 */

#ifndef CLASS_TRACK
#define CLASS_TRACK

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

class _track {
	public:
		_track(Transaction *T, int id);
		_track(const _track &t);
		~_track();
		string id();
		string md5();
		string title();
		string artist();
		string album();
		long length_smpl();
		long start_smpl();
		long end_smpl();
		string time();
		long intro_smpl();
		long extro_smpl();

	private:
		Result R;
		stringstream SQL;
};

#endif
