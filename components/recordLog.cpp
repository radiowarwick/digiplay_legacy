/* Record logging class */

#include "recordLog.h"
#include "dps.h"
#include <time.h>

recordLog::recordLog(Connection *newC, int loc) {
	location = loc;
	C = newC;
}

recordLog::~recordLog() {
}

int recordLog::reclibid(int user, string id) {
	//string artist;
	//string title;
	//return details (user, artist, title);
	return -1;
}

int recordLog::md5(int user, string hash){
	track t = dps_getTrack(C,hash);
//	trackinfo *trk = new trackinfo(C, *hash);
//	string *artist = new string (trk->artist());
//	string *title = new string (trk->title());
	return details (user, t.artist, t.title);
}

int recordLog::details(int user, string artist, string title){
	// Get current time
	int now = (int)time(NULL);
	
	// Escape the artist and title
	artist = sqlesc(artist);
	title = sqlesc(title);
	
	// Try and insert into database
	string SQL = "INSERT INTO log "
		"(userid, datetime, track_title, track_artist, location) VALUES ("
		+ dps_itoa(user) + ", " + dps_itoa(now) + ", '"
		+ title + "', '" + artist + "', " + dps_itoa(location) + ");";
	try {
		Transaction T(*C,"");
		T.exec(SQL);
		T.commit();
	}
	catch (...) {
		cout << "ERROR: Failed to log record." << endl;
		cout << " -> " << SQL << endl;
		return 1;
	}
	return 0;
}

void recordLog::getRecentlyLogged(QListView *parent) {
	Transaction *T = new Transaction(*C,"");
	QString artist, title, datestr;
	tm *dte;
	char date[30];
	
	stringstream SQL;
		SQL << "SELECT * FROM log ORDER BY datetime DESC LIMIT 50;";
	parent->clear();
	try {
		Result R = T->exec(SQL.str());
		for (int i = ((int)R.size())-1; i > -1; i--) {
			time_t thetime(atoi(R[i]["datetime"].c_str()));
			dte = localtime(&thetime);
			strftime(date, 30, "%Ex %H:%M", dte);
			artist = R[i]["track_artist"].c_str();
			title = R[i]["track_title"].c_str();
			parent->insertItem(new QListViewItem(parent, date, artist, title));
		}

	}
	catch (...) {
		cout << " -> ERROR: Failed to get recently logged records." << endl;
	}
	delete T;

}


// ====== PRIVATE =======
// 
