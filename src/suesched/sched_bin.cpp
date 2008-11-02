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
#include <cstdlib>

#include "Logger.h"

#include "sched_bin.h"

sched_bin::sched_bin(string SQL, unsigned short b) {
    const char* routine = "sched_bin::sched_bin";
    
    DB = new DataAccess();
	bin = DB->exec("Sched_bin",SQL);
    DB->abort("Sched_bin");
	if (bin.size() == 0) {
        L_WARNING(LOG_SUESCHED,"Bin " + dps_itoa(b) + " is empty!");
        L_WARNING(LOG_SUESCHED,"SQL: " + SQL);
	}
	bin_id = b;
	t_null.isNull = true;
}

sched_bin::~sched_bin() {

}

unsigned int sched_bin::size() {
	return bin.size();
}

track sched_bin::at(unsigned int index) {
    const char* routine = "sched_bin::at";
    
	track t;
	if (index > size() - 1 || index < 0) {
        L_ERROR(LOG_SUESCHED,"Index " + dps_itoa(index) + " out of range");
		return t_null;
	}
	t.isNull = false;
	t.bin = bin_id;
	t.index = index;
	t.audio_id = atoi(bin[index]["id"].c_str());
	t.md5 = bin[index]["md5"].c_str();
	t.title = bin[index]["title"].c_str();
	if (bin_id < 5) t.artists.push_back(bin[index]["artist"].c_str());
	t.trim_start_smpl = atoi(bin[index]["start_smpl"].c_str());
	t.trim_end_smpl = atoi(bin[index]["end_smpl"].c_str());
	t.length_smpl = t.trim_end_smpl - t.trim_start_smpl;
	t.fade_in_smpl = atoi(bin[index]["intro_smpl"].c_str());
	t.fade_out_smpl = atoi(bin[index]["extro_smpl"].c_str());
	if (t.fade_out_smpl > t.trim_end_smpl)
		t.fade_out_smpl = t.trim_end_smpl;
	return t;
}

track sched_bin::getRandom() {
	if (size() > 0) {
		int x = (int)((float)bin.size() * rand()/(RAND_MAX+1.0));
		return at(x);
	}
	else {
		return t_null;
	}
}

track sched_bin::getShorter(track t_old, unsigned long min_smpl) {
	track t;
	unsigned short count = 0;
	do {
		t = getRandom();
		count++;
		if (count > 100) return t_old;
	} while (t.length_smpl > t_old.length_smpl || t.length_smpl < min_smpl);
	return t;
}
