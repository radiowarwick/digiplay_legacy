#define APP_NAME "Logtest"

#include <sstream>
#include <iostream>
using namespace std;

#include "Logger.h"

void Logger::write(string srcObject, string srcMethod, string srcMessage) {
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
    outLine << srcObject << "::" << srcMethod << ": ";
    outLine << srcMessage << endl;
    (*logFile) << outLine.str();
}

Logger::Logger(string filename) {
	logFile = new ofstream(filename.c_str(), ios::app);
}

Logger::~Logger() {
	logFile->close();
	delete logFile;
}

