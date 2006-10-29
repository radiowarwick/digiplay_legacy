#include <sstream>
#include <iostream>
using namespace std;

#include "Logger.h"

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
	    outLine << "[" << 1900 + local.tm_year;
	    outLine << "/" << local.tm_mon;
	    outLine << "/" << local.tm_mday;
	    outLine << " " << local.tm_hour;
	    outLine << ":" << local.tm_min;
	    outLine << ":" << local.tm_sec << "] ";
	    outLine << routine << ": " << endl << " -> ";
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
	    outLine << message << endl;
	    (*logFile) << outLine.str() << flush;
	}
	if (displayLevel >= level) {
		switch (level) {
			case INFO:
				cout << "INFO      > ";
				break;
			case WARNING:
				cout << "WARNING   > ";
				break;
			case ERROR:
				cout << "ERROR     > ";
				break;
			case GENERAL:
				cout << "GENERAL   > ";
				break;
			case CRITICAL:
				cout << "CRITICAL! > ";
				break;
			default:
				break;
		}
		cout << message << endl;
	}
}	
