/*
 * Studio manage main app
 * main.cpp
 * Main application code for studio management application
 *
 * Copyright (c) 2004-2006 Chris Cantwell
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

#include "sys/stat.h"
#include "getopt.h"

#include <qapplication.h>
#include "frmStudioManage.h"
#include "Security.h"
#include "Config.h"
#include "Logger.h"

static int logDebug = 0;
static int logVerbose = 0;
static int logQuiet = 0;

static struct option long_options[] = {
    {"debug",   no_argument,    &logDebug, 1},
    {"verbose", no_argument,    &logVerbose, 1},
    {"quiet",   no_argument,    &logQuiet, 1},
    {"help",    no_argument,    0, 'h'},
    {"version", no_argument,    0, 'v'},
    {0,0,0,0}
};

static const char* short_options = "hv";

int main( int argc, char * argv[] )
{
	const char* routine = "studio_manage::main";

    // Configure logging
    Logger::setAppName("studio_manage");
    Logger::setLogLevel(INFO);
    Logger::setDisplayLevel(ERROR);
    Logger::initLogDir();
    while (1) {
        int v;
        int option_index = 0;
        v = getopt_long (argc, argv, short_options,long_options, &option_index);
        if (v == -1) break;
        switch (v) {
            case 'h': {
                std::cout << "USAGE: " << argv[0]
                        << " [--debug|--verbose|--quiet] [-h|--help]"
                        << " [-v|--version]" << std::endl;
                exit(0);
                break;
            }
            case 'v': {
                std::cout.precision(1);
                std::cout << "DPS Studio Playout Application Version "
                            << VERSION << std::endl;
                exit(0);
                break;
            }
        }
    }
    if (logDebug + logVerbose + logQuiet > 1) {
        L_ERROR(LOG_DB,"Only one verbosity level may be specified");
        exit(-1);
    }
    if (logDebug) Logger::setDisplayLevel(INFO);
    if (logVerbose) Logger::setDisplayLevel(WARNING);
    if (logQuiet) Logger::setDisplayLevel(CRITICAL);

	if (isRoot()) {
		L_INFO(LOG_DB,"Attempting to drop to unprivilaged user.");
		dropPrivilage();
	}

	// Create new application and main window
    QApplication a( argc, argv );
	frmStudioManage w;

	// Show window and run application
    w.show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
