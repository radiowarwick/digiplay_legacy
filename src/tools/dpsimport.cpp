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
	
	Logger::log(INFO,routine,"Import run started.",1);
	Logger::log(INFO,routine,"Loading music archives",1);
	systemmanager *Sys = new systemmanager();
	for (unsigned short i = 0; i < Sys->sizeArchive(); i++){
		Logger::log(INFO,routine,"Loading archive '" + Sys->atArchive(i)->spec().name + "'",1);
		Sys->atArchive(i)->load();
	}
	Logger::log(INFO,routine,"Adding new music",1);
	for (unsigned short i = 0; i < Sys->sizeArchive(); i++){
		archivemanager *A = Sys->atArchive(i);
		unsigned int count = A->size(DPS_INBOX);
		for (unsigned short j = 0; j < count; j++){
			Logger::log(INFO,routine,"Importing " + A->at(DPS_INBOX,0).md5 + " [" + A->at(DPS_INBOX,0).title + "]",2);
			A->add(0);
		}
		Logger::log(INFO,routine,"Import complete of archive '" + A->spec().name + "'",1);
		Logger::log(INFO,routine,dps_itoa(A->size(DPS_DB)) + " tracks in archive",1);
	}

	Logger::log(INFO,routine,"Cleaning up.",1);
	delete Sys;
	Logger::log(INFO,routine,"Import complete.",1);
}
