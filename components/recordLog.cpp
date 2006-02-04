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
	
	artist = new string(sqlesc(*artist));
	title = new string(sqlesc(*title));
	
	cout<<artist <<endl<<title<<endl;
	
	stringstream SQL;
		SQL << "INSERT INTO log ";
		SQL << "(userid, datetime, track_title, track_artist, location) VALUES (";
		SQL << user << ", " << now << ", '";
		SQL << *title << "', '" << *artist << "', " << location << ");";
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

void recordLog::getRecentlyLogged(Connection *C, QListView *parent) {
	Transaction *T = new Transaction(*C,"");
	QString artist, title, datestr;
	tm *dte;
	char date[30];
	
	stringstream SQL;
		SQL << "SELECT * FROM log ORDER BY datetime DESC LIMIT 50;";
//		cout << SQL.str() << endl;
	parent->clear();
	try {
		Result R = T->exec(SQL.str());
		delete T;
		for (int i = ((int)R.size())-1; i > -1; i--) {
			dte = localtime(new time_t(atoi(R[i]["datetime"].c_str())));
			strftime(date, 30, "%Ex %H:%M", dte);
			artist = R[i]["track_artist"].c_str();
			title = R[i]["track_title"].c_str();
			parent->insertItem(new QListViewItem(parent, date, artist, title));
		}

	}
	catch (...) {
		cout << " -> ERROR: Failed to get recently logged records." << endl;
	}

}


// ====== PRIVATE =======
// 
