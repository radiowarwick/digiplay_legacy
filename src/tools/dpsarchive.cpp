/*
 * DPS Archive Management tool
 * dpsarchive.cpp
 * Tool for adding, dropping and managing DPS archives
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

void displayUsage();
void addArchive(string name, string localPath, string remotePath);
void dropArchive(string name);
void listArchives();

static int verbose;

int main(int argc, char *argv[]) {
    char* routine = "dpsarchive::main";
	int c;
	char task = 0;
	string archiveName;
	string localPath,remotePath;

	static struct option long_options[] = {
		{"verbose",no_argument,&verbose,1},
		{"brief",no_argument,&verbose,0},
		{"add",required_argument,0,'A'},
		{"drop",required_argument,0,'D'},
		{"list",no_argument,0,'L'},
		{"localPath",required_argument,0,'l'},
		{"remotePath",required_argument,0,'r'},
		{0,0,0,0}
	};

	while (1) {
		int option_index = 0;
		c = getopt_long (argc, argv, "A:D:Ll:r:h",long_options, &option_index);
		if (c == -1) break;
		if (task != 0 && c != 'l' && c != 'r' && c != 0) {
			cout << "ERROR: You must specify only one task." << endl;
			displayUsage();
			exit(-1);
		}
		switch (c) {
			case 'A':
				task = 'A';
				archiveName = optarg;
				break;
			case 'D':
				task = 'D';
				archiveName = optarg;
				break;
			case 'L':
				task = 'L';
				break;
			case 'l':
				localPath = optarg;
				break;
			case 'r':
				remotePath = optarg;
				break;
			case 'h':
				cout << "Performs management tasks on a DPS archive." << endl;
				cout << "Select desired task from the options below." << endl;
				displayUsage();
				exit(0);
				break;
		}
	}
	if (verbose) {
	    cout << "Digital Playout System Archive Tool" << endl;
	    cout << "Copyright (c) 2005-2006 Radio Warwick" << endl << endl;
	}
	if (task == 'A') addArchive(archiveName, localPath, remotePath);
	if (task == 'D') dropArchive(archiveName);
	if (task == 'L') listArchives();
	if (task == 0) {
		cout << "ERROR: No task specified" << endl;
		displayUsage();
		exit(-1);
	}
	return 0;
}

void displayUsage() {
	cout << "Usage: dpsarchive [TASK] [NAME] [OPTIONS]" << endl;
	cout << "TASK is one of:" << endl;
	cout << " -A     add/create a new archive." << endl;
	cout << " -D     drop an existing archive. Files are not deleted." << endl;
	cout << " -L     list archives." << endl;
	cout << "For -A, OPTIONS are (all required):" << endl;
	cout << " -l     local path" << endl;
	cout << " -r     remote path" << endl;
	cout << endl;
}

void addArchive(string name, string localPath, string remotePath) {
//	struct stat sbuf;
//	stat(localPath.c_str(),&sbuf);
//	if (verbose) cout << "Checking archive location..." << endl;
//	if (sbuf.st_mode & S_IFMT == S_IFDIR) {
//		cout << "It's a directory" << endl;
//	}

	if (verbose) cout << "Creating archive in system database..." << endl;
	systemmanager *Sys = new systemmanager();
	if (Sys->atArchive(name)) {
		cout << "ERROR: An archive with that name already exists." << endl;
		exit(-1);
	}
	Sys->addArchive(name,localPath,remotePath);
//	if (verbose) cout << "Creating filesystem structure..." << endl;
//	TODO: Add filesystem creation commands
	if (verbose) cout << "Complete!" << endl;
}

void dropArchive(string name) {
	systemmanager *Sys = new systemmanager();
	if (!Sys->atArchive(name)) {
		cout << "ERROR: Archive does not exist." << endl;
		exit(-1);
	}
	for (short i = 0; i < Sys->sizeArchive(); i++) {
		if (Sys->atArchive(i)->spec().name == name) {
			Sys->dropArchive(i);
			break;
		}
	}
}

void listArchives() {
	systemmanager *Sys = new systemmanager();
	archive A;
	cout.setf(ios::left);
	cout.width(20);
	cout << "Name";
	cout.width(30);
	cout << "Local Path";
	cout.width(30);
	cout << "Remote Path";
	cout << endl;
	for (short j = 0; j < 80; j++) cout << "-";
	cout << endl;
	for (short i = 0; i < Sys->sizeArchive(); i++) {
		A = Sys->atArchive(i)->spec();
		cout.width(20);
		cout << A.name;
		cout.width(30);
		cout << A.localPath;
		cout.width(30);
		cout << A.remotePath;
		cout << endl;
	}
}
