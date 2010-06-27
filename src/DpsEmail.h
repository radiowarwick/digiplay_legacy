/*
 * Email module
 * DpsEmail.h
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
#ifndef CLASS_MODEMAIL
#define CLASS_MODEMAIL

#include <vector>
#include <string>

#include "dps.h"

class DataAccess;

class DpsEmail {
	public:
		DpsEmail();
		~DpsEmail();
        std::vector<std::map<std::string,std::string> > getEmails();
//		const char* getEmailBody(std::string id);
		void markRead(std::string id);

    private:
        DataAccess* DB;
};

#endif

