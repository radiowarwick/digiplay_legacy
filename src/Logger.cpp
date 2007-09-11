/*
 * System logging Class
 * Logger.h
 * Static routines for logging program information to file
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
#include <sstream>
#include <iostream>
using namespace std;

#include "Logger.h"
#include "Security.h"

ofstream *Logger::logFile = 0;
unsigned short Logger::logLevel = 0;
unsigned short Logger::displayLevel = 0;
string Logger::appName = "";

void Logger::log(LOG_TYPE type, char* routine, string message, 
												MESSAGE_LEVEL level) {
	if (logLevel >= level) {
		if (!logFile) {
			system("mkdir -p /var/log/dps");
			string filename = "/var/log/dps/" + appName + ".log";
			logFile = new ofstream(filename.c_str(), ios::app);
		}
	    time_t current_time;
	    time(&current_time);
	    tm local=*(localtime(&current_time));
	    stringstream outLine;
	    outLine << "[" << 1900 + local.tm_year << "/";
        if (local.tm_mon < 10) outLine << "0";
	    outLine << local.tm_mon << "/";
        if (local.tm_mday < 10) outLine << "0";
	    outLine << local.tm_mday << " ";
        if (local.tm_hour < 10) outLine << "0";
	    outLine << local.tm_hour << ":";
        if (local.tm_min < 10) outLine << "0";
	    outLine << local.tm_min << ":";
        if (local.tm_sec < 10) outLine << "0";
	    outLine << local.tm_sec << "] ";
		switch (level) {
			case INFO:
				outLine << "INFO: ";
				break;
			case WARNING:
				outLine << "WARNING: ";
				break;
			case ERROR:
				outLine << "ERROR: ";
				break;
			case GENERAL:
				outLine << "GENERAL: ";
				break;
			case CRITICAL:
				outLine << "CRITICAL: ";
				break;
			default:
				break;
		}
	    outLine << routine << ": ";
	    outLine << message << endl;
	    (*logFile) << outLine.str() << flush;
	}
	if (displayLevel >= level) {
		switch (level) {
			case INFO:
				cerr << "INFO      > ";
				break;
			case WARNING:
				cerr << "WARNING   > ";
				break;
			case ERROR:
				cerr << "ERROR     > ";
				break;
			case GENERAL:
				cerr << "GENERAL   > ";
				break;
			case CRITICAL:
				cerr << "CRITICAL! > ";
				break;
			default:
				break;
		}
		cerr << message << endl;
	}
}	

void Logger::initLogDir() {
    if (appName == "") {
        cout << "ERROR: Application name not set!" << endl;
        exit(-1);
    }
    if (!logFile) {
	    string filename = "/var/log/dps/" + appName + ".log";
        if (isRoot()) {
	        system("mkdir -p /var/log/dps");
	        system("chown dps:adm /var/log/dps");
	        system("chmod 640 /var/log/dps");
			system(string("touch " + filename).c_str());
	        system(string("chown dps:adm " + filename).c_str());
	        system(string("chmod 640 " + filename).c_str());
		}
/*		else {
            cout << "WARNING: This program is not currently running as root."; 
			cout << endl;
        }
*/	    logFile = new ofstream(filename.c_str(), ios::app);
		if ( ! (logFile->is_open() && logFile->good())) {
			cout << "WARNING: Unable to open log file for writing." << endl;
			cout << "    The current user may not have permissions to" << endl;
			cout << "       /var/log/dps" << endl;
			cout << "    or permission to create this directory." << endl;
		}
    }
}
