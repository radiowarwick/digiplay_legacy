/*
 * DPS Audio Import tool
 * dpsimport.cpp
 * Processes each audio archive in the system and imports the audio into the
 * database
 *
 * Copyright (c) 2006 Chris Cantwell
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
#include "systemmanager.h"
#include "archivemanager.h"
#include "Logger.h"

int main() {
	cout << "Digital Playout System Automated Import" << endl;
	cout << "Copyright (c) 2005-2006 Radio Warwick" << endl;
	char* routine = "dpsimport::main";

    // Configure logging
	Logger::setAppName("dpsimport");
	Logger::setLogLevel(3);
	Logger::setDisplayLevel(2);
	
	L_INFO(LOG_DB,"Import run started.");
	L_INFO(LOG_DB,"Loading music archives");
	systemmanager *Sys = new systemmanager();
	for (unsigned short i = 0; i < Sys->sizeArchive(); i++){
		L_INFO(LOG_DB,"Loading archive '" + Sys->atArchive(i)->spec().name + "'");
		Sys->atArchive(i)->load();
	}
	L_INFO(LOG_DB,"Adding new music");
	for (unsigned short i = 0; i < Sys->sizeArchive(); i++){
		archivemanager *A = Sys->atArchive(i);
		unsigned int count = A->size(DPS_INBOX);
		for (unsigned short j = 0; j < count; j++){
			L_INFO(LOG_DB,"Importing " + A->at(DPS_INBOX,0).md5 + " [" + A->at(DPS_INBOX,0).title + "]");
			A->add(0);
		}
		L_INFO(LOG_DB,"Import complete of archive '" + A->spec().name + "'");
		L_INFO(LOG_DB,dps_itoa(A->size(DPS_DB)) + " tracks in archive");
	}

	L_INFO(LOG_DB,"Cleaning up.");
	delete Sys;
	L_INFO(LOG_DB,"Import complete.");
}
