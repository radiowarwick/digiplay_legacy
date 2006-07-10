#ifndef CLASS_LOGGER_H
#define CLASS_LOGGER_H

//#ifndef APP_NAME
//#error "Logger:: Must define APP_NAME for this application to use Logger!"
//#endif

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

enum MESSAGE_TYPE {INFO,WARNING,ERROR,FATAL};

class Logger {
	public:
		static void log(MESSAGE_TYPE type, char* routine, string message,
														unsigned short level);
		static void setLogLevel(unsigned short level){logLevel=level;}
		static void setDisplayLevel(unsigned short level){displayLevel=level;}
		static void setAppName(string name){appName=name;}

	private:
		Logger();
		~Logger();
		static ofstream *logFile;
		static unsigned short logLevel;
		static unsigned short displayLevel;
		static string appName;
};

#endif
