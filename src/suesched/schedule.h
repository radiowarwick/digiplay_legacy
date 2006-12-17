/*
 * Sustainer Schedule
 * schedule.h
 * Manages a schedule of tracks
 *
 * Copyright (c) 2004-2005 Chris Cantwell
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
#ifndef CLASS_SCHEDULE
#define CLASS_SCHEDULE

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "sched_bin.h"
#include "dps.h"

class schedule {
	public:
		schedule(Transaction *T_new);
		~schedule();
		
		void newSchedule();
		void add(track t, short position);
		void remove(unsigned short position);
		bool check(track t);
		track at(unsigned short position);

		unsigned long getLength_smpl();
		unsigned int size();
		
		string getLength_pretty();
		unsigned int getCrossfadePoints();

		void printToScreen();
		void exportToDatabase();

	private:
		Transaction *T;
		vector<track> *S;
};

#endif
