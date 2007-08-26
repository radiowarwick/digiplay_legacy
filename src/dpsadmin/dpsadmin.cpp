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
#include "UserManager.h"
#include "GroupManager.h"
#include "MusicManager.h"
#include "LocationManager.h"
#include "Logger.h"
#include "Config.h"

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
    {"upgrade",     required_argument,  0,  'u'},
    {"merge",       required_argument,  0,  'm'},
    {"create",      required_argument,  0,  'c'},
    {"add-to",      required_argument,  0,  't'},
    {"remove-from", required_argument,  0,  'f'},
    {"import",      no_argument,        0,  'i'},
    {"import-md5",  required_argument,  0,  'j'},
    {"purge-deleted", no_argument,      0,  'p'},
    {"set-passwd",  required_argument,  0,  's'},
    {"display",     required_argument,  0,  'b'},
    {"parse-ldap",  no_argument,        0,  'g'},
    // parameters
    {"local-path",  required_argument,  0,  'x'},
	{"remote-path", required_argument,  0,  'y'},
    {"dest-archive",required_argument,  0,  'e'},
    {"with-passwd", required_argument,  0,  'w'},
    {"stdin",       no_argument,        0,  'z'},
    {"username",    required_argument,  0,  'q'},
	{0,0,0,0}
};

static char* short_options = "AMLUGa:d:lm:u:pc:i:se:w:hiv";

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
    Logger::initLogDir();
    Logger::setLogLevel(INFO);
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
            case 'u': options["upgrade"] = optarg; c++; break;
            case 'c': options["create"] = optarg; c++; break;
            case 't': options["add-to"] = optarg; c++; break;
            case 'f': options["remove-from"] = optarg; c++; break;
            case 'i': options["import"] = "yes"; c++; break;
            case 'j': options["import-md5"] = optarg; c++; break;
            case 'p': options["purge-deleted"] = "yes"; c++; break;
            case 's': options["set-passwd"] = optarg; c++; break;
            case 'b': options["display"] = optarg; c++; break;
            case 'g': options["parse-ldap"] = "yes"; c++; break;
            case 'x': options["local-path"] = optarg; break;
            case 'y': options["remote-path"] = optarg; break;
            case 'e': options["dest-archive"] = optarg; break;
            case 'w': options["with-passwd"] = optarg; break;
            case 'q': options["username"] = optarg; break;
            case 'z': options["stdin"] = "yes"; break;
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
"   -m, --merge <name>      merge <name> with a --dest-archive\n"
"   -u, --upgrade <name>    upgrades all INFO files to XML in inbox\n"
"\n"
"Music management commands:\n"
"   -i, --import-all        imports all new audio in all archive\n"
"   --import-md5 <md5>      import <md5> only\n"
"   -p, --purge-deleted     delete audio marked for deletion\n"
"   -x, --export-xml        exports track data to XML for all tracks\n"
"   --export-xml-md5 <md5>  exports track data to XML for <md5>\n"
"   --import-sustainer      imports MD5 ids to set active on sustainer\n"
"   --export-sustainer      exports MD5 ids for tracks on sustainer\n"
"\n"
"Location management commands:\n"
"   -a, --add <number>      add configuration for a new location\n"
"   -d, --drop <number>     remove configuration for a location\n"
"   -l, --list              list the configured locations\n"
"   --display <number>      display a location\n"
"   --set <number>          set a parameter for a location\n"
"\n"
"User management commands:\n"
"   -a, --add <username>    add a new user\n"
"   -d, --drop <username>   drop a user\n"
"   -l, --list              list users on the system\n"
"   --set-passwd <username> set a users password (prompt)\n"
"   --parse-ldap            parse user list from LDAP directory\n"
"\n"
"Group management commands:\n"
"   -a, --add <group>       add a new group\n"
"   -d, --drop <group>      drop a group\n"
"   --add-to <group>        add a user to group as given by --username\n"
"   --remove-from <group>   remove the user given by --username from group\n"
"   -l, --list              list groups on the system\n"
"\n"
"Command parameters:\n"
"   --local-path            the local path of the archive to add/create\n"
"   --remote-path           the remote path of the new archive to add/create\n"
"   --dest-archive          destination archive for archive merge\n"
"   --with-passwd           specify a users password instead of prompt\n"
"   --stdin                 specify a users password will be read from stdin\n"
"   --username              specify a username to add to a group\n"
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
        string name = options["create"];
        if (options["local-path"] == "") {
            L_ERROR(LOG_DB,"No 'local-path' specified");
            exit(-1);
        }
        if (options["remote-path"] == "") {
            L_ERROR(LOG_DB,"No 'remote-path' specified");
            exit(-1);
        }
        L_INFO(LOG_DB,"Creating archive '" + name + "'...");

        if (Sys->atArchive(name)) {
            L_ERROR(LOG_DB,"'" + name + "' already exists");
            exit(-1);
        }
        
        Sys->createArchive(name,options["local-path"],options["remote-path"]);
        L_INFO(LOG_DB,"Complete!");
    
    }

    else if (options["merge"] != "") {
    
    }

    else if (options["upgrade"] != "") {
        string name = options["upgrade"];
        if (!Sys->atArchive(name)) {
            L_ERROR(LOG_DB,"Archive '" + name + "' doesn't exist.");
            exit(-1);
        }

        Sys->atArchive(name)->upgradeInfo();
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
            unsigned int offset = 0;
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
                    try {
                        A->add(offset);
                    }
                    catch (...) {
                        // skip this track
                        offset++;
                    }
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
    char* routine = "dpsadmin::processLocation";

    LocationManager* L = new LocationManager();
    Location l;

    if (options["add"] != "") {
        try {
            L->add(atoi(options["add"].c_str()));
        }
        catch (...) {
            L_ERROR(LOG_DB,"Failed to add location " + options["add"]);
        }
    }
    if (options["drop"] != "") {
        try {
            L->remove(atoi(options["drop"].c_str()));
        }
        catch (...) {
            L_ERROR(LOG_DB,"Failed to drop location " + options["drop"]);
        }
    }
    if (options["list"] != "") {
        cout << "Configured locations: ";
        for (unsigned int i = 0; i < L->count(); ++i) {
            cout << L->get(i) << "  ";
        }
        cout << endl;
    }
    if (options["display"] != "") {
        try {
            l = L->getLocation(atoi(options["display"].c_str()));
            cout << "Location " << l.location << " configuration values";
            cout << endl;
            cout << "           Parameter  Value";
            cout << endl;
            cout << "------------------------------------------------------";
            cout << endl;
            std::map<std::string,std::string>::iterator x;
            for (x = l.data.begin(); x != l.data.end(); x++) {
                cout.width(20);
                cout << x->first << "  ";
                cout << x->second;
                cout << endl;
            }
        }
        catch (...) {
            L_ERROR(LOG_DB,"Failed to display location " + options["display"]);
        }
    }   
}

/**
 * Process user management
 */
void processUser() {
    char* routine = "dpsadmin::processUser";

    UserManager* U = new UserManager();
    User u;

    if (options["add"] != "") {
        u.username = options["add"];
        u.isAdmin = false;
        try {
            U->add(u);
        }
        catch (...) {
            L_ERROR(LOG_DB,"Unable to add user.");
        }
    }
    else if (options["drop"] != "") {
        try {
            u = U->get(options["drop"]);
            U->remove(u);
        }
        catch (...) {
            L_ERROR(LOG_DB,"Unable to remove user.");
        }
    }
    else if (options["list"] != "") {
        cout << "          Username    Admin?" << endl;
        cout << "----------------------------" << endl;
        for (unsigned int i = 0; i < U->count(); i++) {
            u = U->get(i);
            cout.width(18);
            cout << u.username << "    ";
            if (u.isAdmin) cout << "Yes";
            else cout << "No";
            cout << endl;
        }
    }
    else if (options["set-passwd"] != "") {
        try {
            u = U->get(options["set-passwd"]);
            std::string password;
            if (options["with-passwd"] != "") {
                password = options["with-passwd"];
            }
            else if (options["stdin"] != "") {
                cin >> password;
            }
            else {
                cout << "Enter new password: ";
                cin >> password;
            }
            U->setPassword(u,password);
        }
        catch (...) {
            L_ERROR(LOG_DB,"Unable to set password.");
        }
    }
    else if (options["parse-ldap"] != "") {
        Config* C = 0;
        try {
            C = new Config("digiplay");
            std::string host = C->getParam("ldap_host");
            unsigned int port = atoi(C->getParam("ldap_port").c_str());
            std::string dn = C->getParam("ldap_dn");
            std::string filter = C->getParam("ldap_filter");
            std::vector<std::string> userlist;
            userlist = U->parseLdap(host, port, dn, filter);
            for (unsigned int i = 0; i < userlist.size(); ++i) {
                try {
                    User u = U->get(userlist[i]);
                    L_INFO(LOG_DB,"User " + userlist[i] + " already exists.");
                    continue;
                }
                catch (...) {
                    L_INFO(LOG_DB,"Found new LDAP user: " + userlist[i]);
                }
                try {
                    User u;
                    u.username = userlist[i];
                    U->add(u);
                }
                catch (...) {
                    L_ERROR(LOG_DB,"Failed to add new user from LDAP.");
                    throw;
                }
                L_INFO(LOG_DB,"User " + userlist[i] + " created successfully.");
            }
        }
        catch (...) {
            L_ERROR(LOG_DB,"Error occured parsing ldap");
        }
        delete C;
    }
}

/**
 * Process group management
 */
void processGroup() {
    char* routine = "dpsadmin::processGroup";

    GroupManager *G = new GroupManager();
    Group g;

    if (options["add"] != "") {
        g.name = options["add"];
        try {
            G->add(g);
        }
        catch (...) {
            L_ERROR(LOG_DB,"Unable to add group.");
        }
    }
    else if (options["drop"] != "") {
        try {
            g = G->get(options["drop"]);
            G->remove(g);
        }
        catch (...) {
            L_ERROR(LOG_DB,"Unable to remove group.");
        }
    }
    else if (options["list"] != "") {
        cout << "         Groupname" << endl;
        cout << "------------------" << endl;
        for (unsigned int i = 0; i < G->count(); ++i) {
            g = G->get(i);
            cout.width(18);
            cout << g.name;
            cout << endl;
        }
    }
    else if (options["add-to"] != "") {
        if (options["username"] == "") {
            L_ERROR(LOG_DB,"Username to add to group must be supplied.");
            return;
        }
        UserManager *U = new UserManager();
        User u;

        try {
            g = G->get(options["add-to"]);
            u = U->get(options["username"]);
            G->addToGroup(u,g);
        }
        catch (...) {
            L_ERROR(LOG_DB,"Unable to add user to group.");
        }
    }
}
