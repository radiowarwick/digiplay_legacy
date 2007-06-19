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

#include "SystemManager.h"
#include "ArchiveManager.h"
#include "Logger.h"

#define VERSION 0.95

// Global flags
static int verbose = 0;
static int quiet = 0;
static map<string,string> options;

static struct option long_options[] = {
    // Be verbose about what we do
	{"verbose",     no_argument,    &verbose,1},
    // Be brief about what we do
	{"quiet",       no_argument,    &quiet,  1},
    // Display help
    {"help",        no_argument,        0,  'h'},
    {"version",     no_argument,        0,  'v'},
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
    {"set-password",required_argument,  0,  's'},
    // parameters
    {"local-path",   required_argument, 0,  'x'},
	{"remote-path",  required_argument, 0,  'y'},
    {"dest-archive", required_argument, 0,  'e'},
    {"with-password",required_argument, 0,  'w'},
	{0,0,0,0}
};

static char* short_options = "AMLUGa:d:lm:pc:i:se:w:hiv";

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
    // Parse the command line parameters
	parseCommand(argc,argv);
    if (verbose && quiet) {
        cerr << "ERROR     > Can't be verbose and quiet!" << endl;
        exit(-1);
    }

    // configure logging
    Logger::setAppName("dpsadmin");
    Logger::setLogLevel(3);
    Logger::setDisplayLevel(WARNING);
    if (verbose) Logger::setDisplayLevel(INFO);
    if (quiet) Logger::setDisplayLevel(CRITICAL);

    // Display version if requested
    if (options["version"] == "yes") {
        cout << "Digital Playout System Administration Tool" << endl;
        cout << "Copyright (c) 2005-2007 Chris Cantwell" << endl;
        cout << "Version " << VERSION << endl;
        exit(0);
    }

    // Display help if requested
    if (options["help"] == "yes") {
        displayUsage();
        exit(0);
    }

    // Perform the action
    process();
    return 0;
}

/**
 * Parses the command-line options.
 */
void parseCommand(int argc, char *argv[]) {
    char* routine = "dpsadmin::parseCommand";
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
            case 'e': options["dest-archive"] = optarg; break;
            case 'w': options["with-password"] = optarg; break;
            case 'h': options["help"] = "yes"; break;
            case 'v': options["version"] = "yes"; break;
		}
	}
    if (t > 1) {
        L_ERROR(LOG_DB,"Only one task may be specified.");
        exit(-1);
    }
    if (c > 1) {
        L_ERROR(LOG_DB,"Only one command may be specified.");
        exit(-1);
    }
}

/**
 * Displays usage information
 */
void displayUsage() {
cout <<
"Usage: dpsadmin [TASK] [COMMAND] {OPTIONS}\n"
"   --verbose               be verbose about what is being done\n"
"   --quiet                 do not print anything to stdout\n"
"   --version               print the copyright and version info\n"
"   --help                  print this help\n"
"\n"
"Possible tasks:\n"
"   -A, --archive           archive management\n"
"   -M, --music             music management\n"
"   -L, --location          system location management\n"
"   -U, --user              user management\n"
"   -G, --group             group management\n"
"\n"
"Archive management commands:\n"
"   -a, --add <name>        add an existing archive\n"
"   -c, --create <name>     create a new archive and add it\n"
"   -d, --drop <name>       remove archive (not deleted)\n"
"   -l, --list              list the available archives\n"
"\n"
"Music management commands:\n"
"   -i, --import            imports all new audio in all archive\n"
"   --import-md5 <md5>      import <md5> only\n"
"   -p, --purge-deleted     delete audio marked for deletion\n"
"\n"
"Location management commands:\n"
"   -a, --add <number>      add configuration for a new location\n"
"   -d, --drop <number>     remove configuration for a location\n"
"   -l, --list              list the configured locations\n"
"   --set <number>          set a parameter for a location\n"
"\n"
"User management commands:\n"
"   -a, --add <username>    add a new user\n"
"   -d, --drop <username>   drop a user\n"
"   -l, --list              list users on the system\n"
"   --set-passwd <username> set a users password (prompt)\n"
"\n"
"Group management commands:\n"
"   -a, --add <group>       add a new group\n"
"   -d, --drop <group>      drop a group\n"
"   -l, --list              list groups on the system\n"
"\n"
"Command parameters:\n"
"   --local-path            the local path of the archive to add/create\n"
"   --remote-path           the remote path of the new archive to add/create\n"
"   --dest-archive          destination archive for archive merge\n"
"   --with-passwd           specify a users password instead of prompt\n"
<< endl;
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
    char* routine = "dpsadmin::processArchive";

    L_INFO(LOG_DB,"Entering archive mode.");
    SystemManager *Sys = new SystemManager();

    // Add archive
    if (options["add"] != "") {
        string name = options["add"];
        if (options["local-path"] == "") {
            L_ERROR(LOG_DB,"No 'local-path' specified");
            exit(-1);
        }
        if (options["remote-path"] == "") {
            L_ERROR(LOG_DB,"No 'remote-path' specified");
            exit(-1);
        }
        L_INFO(LOG_DB,"Adding existing archive '" + name + "' to database...");

        if (Sys->atArchive(name)) {
            L_ERROR(LOG_DB,"'" + name + "' already exists");
            exit(-1);
        }
        Sys->addArchive(name,options["local-path"],options["remote-path"]);
        L_INFO(LOG_DB,"Complete!");
    }

    // Drop archive
    else if (options["drop"] != "") {
        string name = options["drop"];
        L_INFO(LOG_DB,"Dropping archive '" + name + "' from database...");

        if (!Sys->atArchive(name)) {
            L_ERROR(LOG_DB,"Archive '" + name + "' does not exist!");
            exit(-1);
        }
        for (short i = 0; i < Sys->sizeArchive(); i++) {
            if (Sys->atArchive(i)->spec().name == name) {
                Sys->dropArchive(i);
                break;
            }
        }
        L_INFO(LOG_DB,"Complete!");
    }

    // List archives
    else if (options["list"] != "") {
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
    
    }

    else if (options["merge"] != "") {
    
    }

    // Other
    else {
        L_ERROR(LOG_DB,"No valid command supplied for archive operation");
    }
}

/**
 * Process music management
 */
void processMusic() {
    char* routine = "dpsadmin::processMusic";

    SystemManager *Sys = new SystemManager();

    // Import music
    if (options["import"] != "" || options["import-md5"] != "") {
        string target_md5 = options["import-md5"];

        // Load the archives
        L_INFO(LOG_DB,"Import run started.");
        L_INFO(LOG_DB,"Loading music archives");
        for (unsigned short i = 0; i < Sys->sizeArchive(); i++){
            L_INFO(LOG_DB,"Loading archive '" 
                            + Sys->atArchive(i)->spec().name + "'");
            Sys->atArchive(i)->load();
        }

        // Add new music from the various archive inboxes into the system
        L_INFO(LOG_DB,"Adding new music");
        bool done_import_flag = false;

        // Process each archive in the system
        for (unsigned short i = 0; i < Sys->sizeArchive(); i++){
            // if we need to import just one md5, and we've done it, stop
            if (target_md5 != "" && done_import_flag) break;
    
            // get the current archive and process each track in the inbox
            ArchiveManager *A = Sys->atArchive(i);
            unsigned int count = A->size(DPS_INBOX);
            for (unsigned short j = 0; j < count; j++){
                // if we're looking for one track, and found it, add it and quit
                // we won't be importing every track, so it'll be the j'th entry
                if (target_md5 != "" && target_md5 == A->at(DPS_INBOX,j).md5) {
                    L_INFO(LOG_DB,"Importing " + A->at(DPS_INBOX,j).md5 + " ["
                                    + A->at(DPS_INBOX,j).title + "]");
                    A->add(j);
                    done_import_flag = true;
                    break;
                }
                // if we're importing everything, import the first entry in the
                // remaining items. This is then removed so reduce size by one
                else if (target_md5 == "") {
                    L_INFO(LOG_DB,"Importing " + A->at(DPS_INBOX,0).md5 + " ["
                                    + A->at(DPS_INBOX,0).title + "]");
                    A->add(0);
                }
            }
            L_INFO(LOG_DB,"Finished importing from '" + A->spec().name + "'");
            L_INFO(LOG_DB,dps_itoa(A->size(DPS_DB)) + " tracks in archive");
        }

        L_INFO(LOG_DB,"Cleaning up.");
        delete Sys;
        L_INFO(LOG_DB,"Import complete.");

    }
    
    // Purge deleted tracks
    else if (options["purge-deleted"] != "") {

    }
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
