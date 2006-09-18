#ifndef CLASS_LIBSEARCH
#define CLASS_LIBSEARCH

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

//#include "track.h"
#include "dps.h"
#include "config.h"

class libsearch {
    public:
		libsearch();
		~libsearch();
		vector<track>* query(string search_string);
		bool searchTitle();
		bool searchTitle(bool flag);
		bool searchArtist();
		bool searchArtist(bool flag);
		bool searchAlbum();
		bool searchAlbum(bool flag);
		int searchLimit();
		int searchLimit(int value);
		string lastQuery();

	private:
		Connection* C;
		Transaction* T;
		bool searchTitle_flag;
		bool searchArtist_flag;
		bool searchAlbum_flag;
		int searchLimit_value;
		string lastQuery_string;

};			

#endif
