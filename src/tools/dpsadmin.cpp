/*
 * DPS Administration tool
 * dpsadmin.cpp
 * Tool for administering the digital playout system
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
#include <string>
#include <map>
using namespace std;

#include "sys/stat.h"
#include "getopt.h"

#include "systemmanager.h"
#include "archivemanager.h"
#include "Logger.h"

// Global flags
static int verbose;
static map<string,string> options;

static struct option long_options[] = {
    // Be verbose about what we do
	{"verbose",     no_argument,    &verbose,1},
    // Be brief about what we do
	{"brief",       no_argument,    &verbose,0},
    // Display help
    {"help",        no_argument,        0,  'h'},
    // categories
    {"archive",     no_argument,        0,  'A'},
    {"music",       no_argument,        0,  'M'},
    {"location",    no_argument,        0,  'L'},
    {"user",        no_argument,        0,  'U'},
    {"group",       no_argument,        0,  'G'},
    // commands
    {"add",         required_argument,  0,  'a'},
	{"drop",        required_argument,  0,  'd'},
	{"list",        no_argument,        0,  'l'},
    {"merge",       required_argument,  0,  'm'},
    {"purge-deleted", no_argument,      0,  'p'},
    {"create",      required_argument,  0,  'c'},
    {"import",      no_argument,        0,  'i'},
    {"import-md5",  required_argument,  0,  'j'},
    {"set-password",no_argument,        0,  's'},
    // parameters
    {"local-path",   required_argument,  0,  'x'},
	{"remote-path",  required_argument,  0,  'y'},
    {"with-password",required_argument, 0,  'w'},
	{0,0,0,0}
};

static char* short_options = "AMLUGa:d:lm:pc:ij:sx:y:w:h";

// Function prototypes
void parseCommand(int argc, char *argv[]);
void displayUsage();
void process();
void processArchive();
void processMusic();
void processLocation();
void processUser();
void processGroup();

int main(int argc, char *argv[]) {
    char* routine = "dpsadmin::main";
	parseCommand(argc,argv);
    if (options["help"] == "yes") {
        displayUsage();
        exit(0);
    }
    process();
    return 0;
}

/**
 * Parses the command-line options.
 */
void parseCommand(int argc, char *argv[]) {
    int t = 0;
    int c = 0;
	while (1) {
        int v;
		int option_index = 0;
		v = getopt_long (argc, argv, short_options,long_options, &option_index);
		if (v == -1) break;
		switch (v) {
			case 'A': options["archive"] = "yes"; t++; break;
			case 'M': options["music"] = "yes"; t++; break;
			case 'L': options["location"] = "yes"; t++; break;
            case 'U': options["user"] = "yes"; t++; break;
            case 'G': options["group"] = "yes"; t++; break;
            case 'a': options["add"] = optarg; c++; break;
            case 'd': options["drop"] = optarg; c++; break;
            case 'l': options["list"] = "yes"; c++; break;
            case 'm': options["merge"] = optarg; c++; break;
            case 'c': options["create"] = optarg; c++; break;
            case 'i': options["import"] = "yes"; c++; break;
            case 'j': options["import-md5"] = optarg; c++; break;
            case 'p': options["purge-deleted"] = "yes"; c++; break;
            case 's': options["set-password"] = optarg; c++; break;
            case 'x': options["local-path"] = optarg; break;
            case 'y': options["remote-path"] = optarg; break;
            case 'w': options["with-password"] = optarg; break;
            case 'h': options["help"] = "yes"; break;
		}
	}
    if (t > 1) {
        cout << "ERROR: only one task may be specified." << endl;
        exit(-1);
    }
    if (c > 1) {
        cout << "ERROR: only one command may be specified." << endl;
        exit(-1);
    }
}

/**
 * Displays usage information
 */
void displayUsage() {
	cout << "Usage: dpsadmin [TASK] name [COMMAND] {OPTIONS}" << endl;
	cout << "Possible tasks:" << endl;
	cout << " -A, --archive       archive management" << endl;
    cout << " -M, --music         music management" << endl;
    cout << " -L, --location      system location management" << endl;
    cout << " -U, --user          user management" << endl;
    cout << " -G, --group         group management" << endl;
    cout << endl;
    cout << "Archive management commands:" << endl;
    cout << " -a, --add           add an existing archive" << endl;
    cout << " -c, --create        create a new archive and add it" << endl;
    cout << " -d, --drop          remove archive (not deleted)" << endl;
    cout << " -l, --list          list the available archives" << endl;
    cout << endl;
    cout << "Music management commands:" << endl;
    cout << " -i, --import <md5>  imports all new audio in all archive" << endl;
    cout << "                     or just <md5>" << endl;
    cout << " -p, --purge-deleted delete audio marked for deletion" << endl;
    cout << endl;
    cout << "Location management commands:" << endl;
    cout << endl;
    cout << "User management commands:" << endl;
    cout << endl;
    cout << "Group management commands:" << endl;
    cout << endl;
}

/**
 * Processes the command
 */
void process() {
    if (options["archive"] != "") {
        processArchive();
    }
    if (options["music"] != "") {
        processMusic();
    }
    if (options["location"] != "") {
        processLocation();
    }
    if (options["user"] != "") {
        processUser();
    }
    if (options["group"] != "") {
        processGroup();
    }
}

/**
 * Process archive management
 */
void processArchive() {
    if (verbose) cout << "Entering archive mode." << endl;

    // Add archive
    if (options["add"] != "") {
        string name = options["add"];
        if (options["local-path"] == "") {
            cout << "ERROR: no 'local-path' specified" << endl;
            exit(-1);
        }
        if (options["remote-path"] == "") {
            cout << "ERROR: no 'remote-path' specified" << endl;
            exit(-1);
        }
        if (verbose) {
            cout << "Adding existing archive '" << name << "' to database...";
        }

        systemmanager *Sys = new systemmanager();
        if (Sys->atArchive(name)) {
            cout << endl << "ERROR: '" << name << "' already exists" << endl;
            exit(-1);
        }
        Sys->addArchive(name,options["local-path"],options["remote-path"]);
        if (verbose) cout << "Complete!" << endl;
    }

    // Drop archive
    else if (options["drop"] != "") {
        string name = options["drop"];
        if (verbose) {
            cout << "Dropping archive '" << name << "' from database...";
        }

        systemmanager *Sys = new systemmanager();
        if (!Sys->atArchive(name)) {
            cout << endl <<  "ERROR: Archive '" << name << "' does not exist!"
                << endl;
            exit(-1);
        }
        for (short i = 0; i < Sys->sizeArchive(); i++) {
            if (Sys->atArchive(i)->spec().name == name) {
                Sys->dropArchive(i);
                break;
            }
        }
        if (verbose) cout << "Complete!" << endl;
    }

    // List archives
    else if (options["list"] != "") {
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

    // Create archive
    else if (options["create"] != "") {
        cout << "Archive create " << options["create"] << endl;
    }

    else if (options["merge"] != "") {
        cout << "Archive merge " << options["merge"] << endl;
    }

    // Other
    else {
        cout << "Invalid command for Archive" << endl;
    }
}

/**
 * Process music management
 */
void processMusic() {

}

/**
 * Process location management
 */
void processLocation() {

}

/**
 * Process user management
 */
void processUser() {

}

/**
 * Process group management
 */
void processGroup() {

}
