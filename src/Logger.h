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
#ifndef CLASS_LOGGER_H
#define CLASS_LOGGER_H

//#ifndef APP_NAME
//#error "Logger:: Must define APP_NAME for this application to use Logger!"
//#endif

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

//#include "dps.h"

// Error types
enum LOG_TYPE {
	LOG_DB = 0,
	LOG_AUDIOHW = 1,
	LOG_AUDIOPROC = 2,
	LOG_PLAYOUT = 4,
	LOG_CONFIG = 8,
	LOG_AUTH = 16,
	LOG_SHOWPLAN = 32,
	LOG_TAB = 64,
	LOG_TABINFO = 128,
	LOG_TABSEARCH = 256,
	LOG_TABEMAIL = 512,
	LOG_TABLOGGING = 1024,
	LOG_TABPLAYLIST = 2048,
	LOG_TABFILES = 4096,
	LOG_TABSCRIPT = 8192,
	LOG_XML = 16384,
    LOG_ARCHIVE = 32768,
    LOG_SECURITY = 65536
};

// Define Logging macros based on DEBUG level (0...4)
// First set default value for DEBUG
#ifndef DEBUG
#define DEBUG 0
#endif

enum MESSAGE_LEVEL {CRITICAL,GENERAL,ERROR,WARNING,INFO};
#define L_CRITICAL(x,y)		Logger::log((x),routine,y,CRITICAL)

#if DEBUG > 0
#define L_GENERAL(x,y)		Logger::log((x),routine,y,GENERAL)
#else
#define L_GENERAL(x,y)
#endif

#if DEBUG > 1
#define L_ERROR(x,y)		Logger::log((x),routine,y,ERROR)
#else
#define L_ERROR(x,y)
#endif

#if DEBUG > 2
#define L_WARNING(x,y)		Logger::log((x),routine,y,WARNING)
#else
#define L_WARNING(x,y)
#endif

#if DEBUG > 3
#define L_INFO(x,y)			Logger::log((x),routine,y,INFO)
#else
#define L_INFO(x,y)
#endif

/**
 * Provides a centralised logging system for DPS applications.
 * This class provides static functions allowing any class to log events into a
 * log file. The log file is named based on the application name, which should
 * be set before the class is used.
 *
 * Log levels for file and display logs may be specified so only appropriate
 * messages are sent to each output location.
 */
class Logger {
	public:
		static void log(LOG_TYPE type, char* routine, string message,
														MESSAGE_LEVEL level);
		static void setLogLevel(unsigned short level){logLevel=level;}
		static void setDisplayLevel(unsigned short level){displayLevel=level;}
		static void setAppName(string name){appName=name;}
        static void initLogDir();

	private:
		Logger();
		~Logger();
		static ofstream *logFile;
		static unsigned short logLevel;
		static unsigned short displayLevel;
		static string appName;
};

#endif
