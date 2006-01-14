/* Record logging class */

#include "modEmail.h"
#include <time.h>

modEmail::modEmail() {
}

modEmail::~modEmail() {
}

vector<email>* modEmail::getEmails(Connection *C) {
	Transaction *T = new Transaction(*C,"");
        vector<email>* retVec;
        email e;
        tm *dte;
        char date[30];
        stringstream SQL;
	retVec = new vector<email>;

	
		SQL << "SELECT * FROM email ORDER BY datetime DESC LIMIT 50;";
//		cout << SQL.str() << endl;
	try {
		Result R = T->exec(SQL.str());
		delete T;
		string flag;

//		cout << (int)R.size()-1 << endl;
		for (int i = (int)R.size()-1; i > -1; i--) {
			dte = localtime(new time_t(atoi(R[i]["datetime"].c_str())
						+ 945080000));
			strftime(date, 30, "%Ex %H:%M", dte);
			e.from = R[i]["sender"].c_str();
			e.subject = R[i]["subject"].c_str();
			e.received = date;
			e.body = R[i]["body"].c_str();
			e.id = R[i]["id"].c_str();

//			cout << "   *" << (R[i]["new_flag"].c_str()) << "*  " << endl;
			string flag = R[i]["new_flag"].c_str();
			if (  !flag.compare("t")   )
				e.flag = TRUE;
			else
				e.flag = FALSE;

			retVec->push_back(e);
		}
	}
	catch (...) {
		cout << " -> ERROR: Failed to get new e-mails." << endl;
	}
	return retVec;

}

const char* modEmail::getEmailBody(Connection *C, string id) {
	Transaction *T = new Transaction(*C,"");
	stringstream SQL;
		SQL << "SELECT * FROM email WHERE id='"
		    << id
		    << "' ORDER BY datetime DESC LIMIT 50;";
//	cout << SQL.str() << endl;
	try {
		Result R = T->exec(SQL.str());
		delete T;
		return R[0]["body"].c_str();
	}
	catch (...) {
		cout << " -> ERROR: Failed to get e-mail body." << endl;
	}
	return NULL;
}

void modEmail::markRead(Connection *C, string id) {
	Transaction *T = new Transaction(*C,"");
        stringstream SQL;
                SQL << "UPDATE email SET new_flag='f' WHERE id='"
                    << id << "';";
  //      cout << SQL.str() << endl;
        try {
                T->exec(SQL.str());
		T->commit();
                delete T;
        }
        catch (...) {
                cout << " -> ERROR: Failed to set e-mail read." << endl;
        }
}	

// ====== PRIVATE =======
// 
