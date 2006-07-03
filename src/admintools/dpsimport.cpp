#include "systemmanager.h"
#include "archivemanager.h"

int main() {
	cout << "Digital Playout System Automated Import" << endl;
	cout << "Copyright (c) 2005-2006 Radio Warwick" << endl;
	cout << " -> Loading music archives" << flush;
	systemmanager *Sys = new systemmanager();
	for (unsigned short i = 0; i < Sys->sizeArchive(); i++){
		Sys->atArchive(i)->load();
		cout << "." << flush;
	}
	cout << endl << " -> Adding new music..." << endl;
	for (unsigned short i = 0; i < Sys->sizeArchive(); i++){
		archivemanager *A = Sys->atArchive(i);
		for (unsigned short j = 0; j < A->size(DPS_INBOX); j++){
			cout << "   -> " << A->at(DPS_INBOX,j).title << endl; 
//			A->add(0);
		}
		cout << " -> Import complete of archive " << i+1 << endl;
		cout << "   -> " << A->size(DPS_DB) << " tracks in archive" << endl;
	}
	cout << " -> Import complete. " << endl;
	cout << " -> Cleaning up..." << endl;
	delete Sys;
	cout << "done." << endl;
}
