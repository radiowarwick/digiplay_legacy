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
#include <iostream>
using namespace std;

#include "sys/stat.h"
#include "getopt.h"

#include "systemmanager.h"
#include "archivemanager.h"
#include "Logger.h"

int main(int argc, char* argv[]) {
	cout << "Digital Playout System Audio Import Tool" << endl;
	cout << "Copyright (c) 2005-2006 Chris Cantwell" << endl;
	char* routine = "dpsimport::main";
	string target_md5 = "";

	// Parse command options
	static struct option long_options[] = {
		{"md5",required_argument,0,'m'},
		{0,0,0,0}
	};
	while (1) {
		int c;
		int option_index = 0;
		c = getopt_long (argc, argv, "m:", long_options, &option_index);
		if (c == -1) break;
		if (c == 'm') target_md5 = optarg;
	}
    
	// Configure logging
	Logger::setAppName("dpsimport");
	Logger::setLogLevel(3);
	Logger::setDisplayLevel(2);
	
	// Create a systemmanager class and load each archive in the system
	L_INFO(LOG_DB,"Import run started.");
	L_INFO(LOG_DB,"Loading music archives");
	systemmanager *Sys = new systemmanager();
	for (unsigned short i = 0; i < Sys->sizeArchive(); i++){
		L_INFO(LOG_DB,"Loading archive '" + Sys->atArchive(i)->spec().name + "'");
		Sys->atArchive(i)->load();
	}

	// Add new music from the various archive inboxes into the system
	L_INFO(LOG_DB,"Adding new music");
	bool done_import_flag = false;
	// Process each archive in the system
	for (unsigned short i = 0; i < Sys->sizeArchive(); i++){
		// if we need to import just one md5, and we've done it, stop
		if (target_md5 != "" && done_import_flag) break;

		// get the current archive and process through each track in the inbox
		archivemanager *A = Sys->atArchive(i);
		unsigned int count = A->size(DPS_INBOX);
		for (unsigned short j = 0; j < count; j++){
			// if we're looking for one track, and found it, add it and quit
			// we won't be importing every track, so it will be the j'th entry
			if (target_md5 != "" && target_md5 == A->at(DPS_INBOX,j).md5) {
				L_INFO(LOG_DB,"Importing " + A->at(DPS_INBOX,j).md5 + " [" 
								+ A->at(DPS_INBOX,j).title + "]");
				A->add(j);
				done_import_flag = true;
				break;
			}
			// if we're importing everything, import the first entry in the
			// remaining items. This will be removed and so reduce size by one
			else if (target_md5 == "") {
				L_INFO(LOG_DB,"Importing " + A->at(DPS_INBOX,0).md5 + " [" 
								+ A->at(DPS_INBOX,0).title + "]");
				A->add(0);
			}
		}
		L_INFO(LOG_DB,"Import complete of archive '" + A->spec().name + "'");
		L_INFO(LOG_DB,dps_itoa(A->size(DPS_DB)) + " tracks in archive");
	}

	L_INFO(LOG_DB,"Cleaning up.");
	delete Sys;
	L_INFO(LOG_DB,"Import complete.");
}
