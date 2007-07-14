/*
 * Email module
 * DpsEmail.cpp
 * Retrieves and updates emails from the database
 *
 * Copyright (c) 2005-2007 Chris Cantwell
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
#include <string>
#include <vector>
#include <time.h>

#include "Logger.h"
#include "DataAccess.h"

#include "DpsEmail.h"

DpsEmail::DpsEmail() {
    DB = new DataAccess();
}

DpsEmail::~DpsEmail() {
    delete DB;
}

/**
 * Extracts the most recent 50 emails from the database, and populates a vector
 * of type \a email, and returns them.
 */
std::vector<email> DpsEmail::getEmails() {
    char* routine = "DpsEmail::getEmails";

    email e;
    tm *dte;
    char date[30];
    std::vector<email> retVec;
    std::string SQL = "SELECT * FROM email ORDER BY datetime DESC LIMIT 50;";
	
    try {
		PqxxResult R = DB->exec("EmailGet",SQL);
        DB->abort("EmailGet");
        unsigned int I = R.size() - 1;
		for (unsigned int i = 0; i < R.size(); i++) {
			time_t thetime(atoi(R[I-i]["datetime"].c_str()));
			dte = localtime(&thetime);
			strftime(date, 30, "%Ex %H:%M", dte);
			e.from = R[I-i]["sender"].c_str();
			e.subject = R[I-i]["subject"].c_str();
			e.received = date;
			e.body = R[I-i]["body"].c_str();
			e.id = R[I-i]["id"].c_str();

            std::string flag = R[i]["new_flag"].c_str();
			if ( !flag.compare("t") )
				e.flag = true;
			else
				e.flag = false;

			retVec.push_back(e);
		}
	}
	catch (...) {
        DB->abort("EmailGet");
        L_ERROR(LOG_DB,"Failed to get new emails.");
	}
	return retVec;
}

/**
 * Marks a message as read in the database.
 */
void DpsEmail::markRead(std::string id) {
    char* routine = "DpsEmail::markRead";

    std::string SQL = "UPDATE email SET new_flag='f' WHERE id='" + id + "';";
    try {
        DB->exec("EmailMarkRead",SQL);
		DB->commit("EmailMarkRead");
    }
    catch (...) {
	    DB->abort("EmailMarkRead");
        L_ERROR(LOG_DB,"Filed to set email as read.");
    }
}	
