/*
 * Email module
 * modEmail.cpp
 * Retrieves and updates emails from the database
 *
 * Copyright (c) 2005-2006 Chris Cantwell
 * Copyright (c) 2005-2006 Ian Liverton
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
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
		string flag;

//		cout << (int)R.size()-1 << endl;
		for (int i = (int)R.size()-1; i > -1; i--) {
			time_t thetime(atoi(R[i]["datetime"].c_str()));
			dte = localtime(&thetime);
			strftime(date, 30, "%Ex %H:%M", dte);
			e.from = R[i]["sender"].c_str();
			e.subject = R[i]["subject"].c_str();
			e.received = date;
			e.body = R[i]["body"].c_str();
			e.id = R[i]["id"].c_str();

//			cout << "   *" << (R[i]["new_flag"].c_str()) << "*  " << endl;
			string flag = R[i]["new_flag"].c_str();
			if (  !flag.compare("t")   )
				e.flag = true;
			else
				e.flag = false;

			retVec->push_back(e);
		}
	}
	catch (...) {
		cout << " -> ERROR: Failed to get new e-mails." << endl;
	}
	delete T;
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
		delete T;
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
        }
        catch (...) {
				T->abort();
                cout << " -> ERROR: Failed to set e-mail read." << endl;
        }
        delete T;
}	

// ====== PRIVATE =======
// 
