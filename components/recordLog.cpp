/* Record logging class */

#include "recordLog.h"
#include "trackinfo.h"
#include <time.h>

recordLog::recordLog(int loc) {
	location = loc;

}

recordLog::~recordLog() {
}

int recordLog::reclibid(Connection *C, int user, string *id) {
	string artist;
	string title;
	sleep(1);
	return details (C, user, &artist, &title);
}

int recordLog::md5(Connection *C, int user, string *hash){
	trackinfo *trk = new trackinfo(C, *hash);
	string *artist = new string (trk->artist());
	string *title = new string (trk->title());
	return details (C, user, artist, title);
}

int recordLog::details(Connection *C, int user, string *artist, string *title){
	Transaction *T = new Transaction(*C,"");
	int now = (int)time(NULL);
	
	stringstream SQL;
		SQL << "INSERT INTO log ";
		SQL << "(userid, datetime, track_title, track_artist) VALUES (";
		SQL << user << ", " << now << ", '";
		SQL << *title << "', '" << *artist << "');";
		cout << SQL.str() << endl;
	try {
		T->exec(SQL.str());
		T->commit();
		delete T;
	}
	catch (...) {
		cout << " -> ERROR: Failed to log record." << endl;
		return 1;
	}
	return 0;
}


// ====== PRIVATE =======
// 
