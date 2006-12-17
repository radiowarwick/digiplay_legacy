/*
 * Schedule Music bin
 * sched_bin.h
 * Retreives tracks matching a condition
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
#ifndef CLASS_SCHED_BIN
#define CLASS_SCHED_BIN

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "dps.h"

class sched_bin {
	public:
		sched_bin(Transaction *T,string where_clause,unsigned short b);
		~sched_bin();

		unsigned int size();
		track at(unsigned int index);
		track getRandom();
		track getShorter(track t, unsigned long min_smpl);

	private:
		Result bin;
		unsigned short bin_id;
		track t_null;
};

#endif
