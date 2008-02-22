/*
 * Sustainer Scheduling application
 * suesched.cpp
 * Schedules music for hour-long periods
 * TODO: Real-time scheduling
 * TODO: A lot more...
 *
 * Copyright (c) 2004-2005 Chris Cantwell
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
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <getopt.h>
#include <fcntl.h>
using namespace std;

#include "Logger.h"
#include "scheduler.h"

static int logDebug = 0;
static int logVerbose = 0;
static int logQuiet = 0;
static int detach = 0;

static struct option long_options[] = {
    {"debug",   no_argument,    &logDebug, 1},
    {"verbose", no_argument,    &logVerbose, 1},
    {"quiet",   no_argument,    &logQuiet, 1},
    {"help",    no_argument,    0, 'h'},
    {"version", no_argument,    0, 'v'},
    {"daemon",  no_argument,    &detach, 1},
    {0,0,0,0}
};

static const char* short_options = "hv";

void processOptions(int argc, char *argv[]) {
    const char* routine = "suesched::processOptions";
    
    while (1) {
        int v;
        int option_index = 0;
        v = getopt_long (argc, argv, short_options,long_options, &option_index);
        if (v == -1) break;
        switch (v) {
            case 'h': {
                std::cout << "USAGE: " << argv[0]
                        << " [--debug|--verbose|--quiet] [-h|--help]"
                        << " [-v|--version] [--daemon]" << std::endl;
                exit(0);
                break;
            }
            case 'v': {
                std::cout.precision(1);
                std::cout << "DPS Sustainer Scheduling Application Version "
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
    if (detach) Logger::setDisplayLevel(CRITICAL);    
}

void signalHandler(int sig) {
    const char* routine = "suesched::signalHandler";
    switch (sig) {
        case SIGHUP:
            L_INFO(LOG_SUEPLAY,"Hangup signal caught");
            break;
        case SIGSEGV:
            L_CRITICAL(LOG_SUEPLAY,"Segmentation fault occured");
            exit(-1);
            break;
        case SIGTERM:
            L_INFO(LOG_SUEPLAY,"Terminate signal caught");
            exit(0);
            break;
        case SIGUSR1:
            L_INFO(LOG_SUEPLAY,"SIGUSR1 caught");
            break;
        case SIGUSR2:
            L_INFO(LOG_SUEPLAY,"SIGUSR2 caught");
            break;
    }
}

void detachProcess() {
    const char* routine = "suesched::detachProcess";
    
    // Check if we're already a daemon
    if (getppid() == 1) return;
    
    pid_t pid = fork();
    
    // Check we fork()-ed correctly
    if (pid < 0) {
        L_CRITICAL(LOG_SUEPLAY, "Unable to fork() daemon.");
        exit(-1);
    }
    // Quite parent process
    if (pid > 0) {
        L_INFO(LOG_SUEPLAY, "Successfully fork()-ed. Daemon process ID is "
                    + dps_itoa(pid));
        exit(0);
    }

    // Child process (daemon)
    setsid();

    // Set file creation mask
    umask(027);

    // Set working directory
    chdir("/var/run");

    // Open lock file, try to lock, write pid
    int lfp=open("suesched.pid",O_RDWR|O_CREAT,0640);
    if (lfp<0) exit(1); /* can not open */
    if (lockf(lfp,F_TLOCK,0)<0) {
        L_CRITICAL(LOG_SUEPLAY, "Daemon already running!");
        exit(0); /* can not lock */
    }
    char str[10];
    sprintf(str,"%d\n",getpid());
    write(lfp,str,strlen(str)); /* record pid to lockfile */

    // Handle signals
    signal(SIGCHLD,SIG_IGN);            // ignore child
    signal(SIGTSTP,SIG_IGN);            // ignore terminal
    signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);
    signal(SIGHUP,signalHandler);      // catch hangup
    signal(SIGTERM,signalHandler);     // catch sigterm
    signal(SIGSEGV,signalHandler);     // catch segfault
    signal(SIGUSR1,signalHandler);     // catch user1
    signal(SIGUSR2,signalHandler);     // catch user2
}


int main(int argc, char *argv []) {
	const char* routine = "suesched::main";
    Logger::setAppName("suesched");
    Logger::setLogLevel(INFO);
    Logger::setDisplayLevel(ERROR);
    Logger::initLogDir();

    processOptions(argc, argv);
    
    if (detach) {
        detachProcess();
    }
	if (!detach && !logQuiet) {
		system("clear");
		cout << "Radio Warwick Sustainer" << endl;
		cout << "-----------------------" << endl;
		cout << "Scheduling service started." << endl;
	}

	scheduler *S = new scheduler();
	while (true) {
		if (S->getPlaylistSize() == 0) {
			//if (!detach) {
                L_CRITICAL(LOG_SUESCHED, "SCH::FATAL:Nothing to schedule!");
            //}
			exit(-1);
		}
		else {
			if (S->getScheduleRemainSize() < 5) {
				S->doSchedule(3600);
                if (!detach && !logQuiet) S->printSchedule();
            }
		}
		sleep(3);
	}
}
