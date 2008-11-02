/*
 * Sustainer Playout application
 * sueplay.cpp
 * This provides the playback engine for the sustainer service
 * It reads the schedule from the database, and controls the 
 * playback object accordingly.
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
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>
#include <signal.h>
#include <fcntl.h>
using namespace std;

#include "audio/Audio.h"
#include "audio/InputRaw.h"
#include "audio/InputFlac.h"
#include "audio/OutputDsp.h"
#include "audio/OutputRaw.h"
#include "audio/ProcessMixer.h"
#include "audio/ProcessFader.h"
#include "audio/CounterTrigger.h"
using namespace Audio;

#include "Config.h"
#include "dps.h"
#include "Logger.h"
#include "DataAccess.h"

#define min(a,b) (((a)<(b))?(a):(b))

static int logDebug = 0;
static int logVerbose = 0;
static int logQuiet = 0;
static int detach = 0;
static int print_info = 0;

static struct option long_options[] = {
    {"debug",   	no_argument,    &logDebug, 1},
    {"verbose", 	no_argument,    &logVerbose, 1},
    {"quiet",   	no_argument,    &logQuiet, 1},
    {"help",    	no_argument,    0, 'h'},
    {"version", 	no_argument,    0, 'v'},
	{"daemon",		no_argument,	&detach, 1},
	{"now-playing",  no_argument,	&print_info, 1},
    {0,0,0,0}
};

static const char* short_options = "hv";

void processOptions(int argc, char *argv []) {
    const char* routine = "sueplay::getOptions";
    
    // Process options
    while (1) {
        int v;
        int option_index = 0;
        v = getopt_long (argc, argv, short_options,long_options, &option_index);
        if (v == -1) break;
        switch (v) {
            case 'h': {
                std::cout << "USAGE: " << argv[0]
                        << " [--debug|--verbose|--quiet] [-h|--help]"
                        << " [-v|--version] [--daemon] [--now-playing]" << std::endl;
                throw -1;
                break;
            }
            case 'v': {
                std::cout.precision(1);
                std::cout << "DPS Sustainer Playout Application Version "
                            << VERSION << std::endl;
                exit(0);
                break;
            }
        }
    }
    if (detach && print_info) {
        L_ERROR(LOG_DB,"Printed output only available when attached to the console");
        throw -1;
    }

    if (logDebug + logVerbose + logQuiet > 1) {
        L_ERROR(LOG_DB,"Only one verbosity level may be specified");
        throw -1;
    }
    if (logDebug) Logger::setDisplayLevel(INFO);
    if (logVerbose) Logger::setDisplayLevel(WARNING);
    if (logQuiet) Logger::setDisplayLevel(CRITICAL);    
}

void signalHandler(int sig) {
    const char* routine = "sueplay::signalHandler";
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
    const char* routine = "sueplay::detachProcess";
    
    // Check if we're already a daemon
    if (getppid() == 1) return;
    
    pid_t pid = fork();
    
    // Check we fork()-ed correctly
    if (pid < 0) {
        L_CRITICAL(LOG_SUEPLAY, "Unable to fork() daemon.");
        throw -1;
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
    int lfp=open("sueplay.pid",O_RDWR|O_CREAT,0640);
    if (lfp<0) exit(1); /* can not open */
    if (lockf(lfp,F_TLOCK,0)<0) {
        L_CRITICAL(LOG_SUEPLAY,"Daemon already running!"); 
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
    // Configure logging module
    const char* routine = "sueplay::main";
    Logger::setAppName("sueplay");
    Logger::setLogLevel(INFO);
    Logger::setDisplayLevel(ERROR);
    Logger::initLogDir();

    // Process command-line options
    processOptions(argc, argv);

    // Create daemon process if running detached
    if (detach) {
        detachProcess();
    }

	string SQL_Item,SQL_Detail,SQL_Remove;
	PqxxResult R;
	
	L_INFO(LOG_SUEPLAY, " -> Reading configuration file");
	Config *Conf = new Config("digiplay");
	
    L_INFO(LOG_SUEPLAY, " -> Connecting to Database...");
    DataAccess* DB = new DataAccess();
	
	SQL_Item = "SELECT audioid FROM sustschedule ORDER BY id LIMIT 1"; 
    SQL_Detail = "SELECT filetype, archives.localpath AS path, v_audio.md5 AS md5, v_audio.title AS title, v_audio.length_smpl AS length_smpl, sustschedule.id AS id, sustschedule.trim_start_smpl AS start, sustschedule.trim_end_smpl AS end, sustschedule.fade_in AS fade_in, sustschedule.fade_out AS fade_out, v_audio.artist FROM sustschedule, archives, v_audio WHERE sustschedule.audioid = v_audio.id AND archives.id = v_audio.archiveid";
	L_INFO(LOG_SUEPLAY, "done.");

	// Create components
	Input* ch[] = {0,0};
	ProcessFader* fader[] = {new ProcessFader(), new ProcessFader()};
	CounterTrigger* trig[] = {new CounterTrigger(), new CounterTrigger()};
	ProcessMixer* mixer = new ProcessMixer();
	OutputDsp* player = new OutputDsp(Conf->getParam("channel_1").c_str());

	fader[0]->patch(OUT0,mixer,IN0);
	fader[1]->patch(OUT0,mixer,IN1);
	mixer->patch(OUT0,player,IN0);
	
	string md5, id, path, title, artist, ext;
	long start = 0, end = 0, fade_in = 0, fade_out = 0;
	long length_smpl = 0;
	unsigned short active = 0, inactive = 1;
	bool warn_flag = true;
	
	// Process schedule table until empty
	while (true) {
		L_INFO(LOG_SUEPLAY, "BEGIN LOOP");
		// Keep trying until successfully loaded a file that exists!
		do {
			// Query database for next track to play
            L_INFO(LOG_SUEPLAY, "Retrieving next track from database.");
			R = DB->exec("SuePlay",SQL_Item);
            id = R[0]["audioid"].c_str();
            R = DB->exec("SuePlay",SQL_Detail + " AND v_audio.id=" + id);
             
			// If no results, then schedule must have been depleated! Doh!
			if (R.size() == 0) {
				if (warn_flag) {
					warn_flag = false;
					L_WARNING(LOG_SUEPLAY, "Schedule is depleated!");
				}
                // Let's not batter the psql server while we poll for new tracks to play
                sleep(1);
				continue;
			}
			warn_flag = true;
			
			// Load the required data from database
			id = R[0]["id"].c_str();
			path = R[0]["path"].c_str();
			md5 = R[0]["md5"].c_str();
			title = R[0]["title"].c_str();
			artist = R[0]["artist"].c_str();
			start = atoi(R[0]["start"].c_str());
			end = atoi(R[0]["end"].c_str());
			fade_in = atoi(R[0]["fade_in"].c_str());
			fade_out = atoi(R[0]["fade_out"].c_str());
			length_smpl = atoi(R[0]["length_smpl"].c_str());
			
			path += "/" + md5.substr(0,1) + "/";
			L_INFO(LOG_SUEPLAY, "Attempting to load channel " +
                    dps_itoa(active) + ": " + artist + " - " + title);
			L_INFO(LOG_SUEPLAY, " -> Start: " + dps_itoa(start));
			L_INFO(LOG_SUEPLAY, " -> End: " + dps_itoa(end));
			// Try and load the track
			try { 
                if (ch[active]) {
                    ch[active]->unpatch(OUT0);
                    delete ch[active];
                }
                if (string(R[0]["filetype"].c_str()) == "raw") {
                    ch[active] = new InputRaw();
                    ext = "";
                }
                else if (string(R[0]["filetype"].c_str()) == "flac") {
                    ch[active] = new InputFlac();
                    ext = ".flac";
                }
                ch[active]->setAutoReload(false);
                ch[active]->patch(OUT0, fader[active], IN0);
                trig[inactive]->setTriggerTarget(ch[active]);
                ch[active]->addCounter(trig[active]);
                
				ch[active]->load( path + md5 + ext, start, end );
                L_INFO(LOG_SUEPLAY, "Successfully loaded track.");
				break;
			}
			catch (...) {
				L_ERROR(LOG_SUEPLAY, "Error loading track");
			}
		} while (1);
		
        DB->abort("SuePlay");
		if (R.size() == 0) break;

		// positions are specified in terms of STEREO samples
		// database positions are in terms of STEREO samples
		fader[active]->clearNodes();
		unsigned long offset = start;

		if (fade_in > start)
			fade_in = fade_in - offset;
		else
			fade_in = 256;
		L_INFO(LOG_SUEPLAY, " -> Fadein: " + dps_itoa(fade_in));
		fader[active]->addNode(0,0.0);
		fader[active]->addNode(fade_in,1.0);
	
		L_INFO(LOG_SUEPLAY, " -> Fadeout: " + dps_itoa(fade_out));
		if (fade_out < end)
			fade_out = fade_out - offset;
		else
			fade_out = end - 256 - offset;
		end = end - offset;
		L_INFO(LOG_SUEPLAY, " -> Fade out length: " + dps_itoa(end - fade_out));

		fader[active]->addNode(fade_out,1.0);
		fader[active]->addNode(end,0.0);
		trig[active]->setTriggerSample(min(fade_out,end));
        
        // Wait until last track has been played before we load the next
		if (ch[inactive] && ch[inactive]->isLoaded()) {
			L_INFO(LOG_SUEPLAY, "Waiting for channel " + dps_itoa(inactive));
			trig[inactive]->waitStop();
			if (print_info) {
				cout << "Now playing: " << artist << " - " << title << endl;
			}
			L_INFO(LOG_SUEPLAY, "Finished waiting");
		}
		else {
			L_INFO(LOG_SUEPLAY, "Playing channel " + dps_itoa(active));
			ch[active]->play();
			if (print_info) {
				cout << "Now playing: " << artist << " - " << title << endl;
			}
		}

		int now = (int)time(NULL);
		artist = DB->esc(artist);
		title = DB->esc(title);
		string SQL_Insert = "INSERT INTO log "
			"(userid, datetime, track_title, track_artist, location) "
			"VALUES (" + dps_itoa(1) + ", " + dps_itoa(now) + ", '"
			+ title + "', '" + artist + "', " + dps_itoa(0) + ");";
		try {
            L_INFO(LOG_SUEPLAY,"Writing log entry for " + artist
                    + " - " + title + ".");
			DB->exec("SuePlayLog",SQL_Insert);
			DB->commit("SuePlayLog");
		}
		catch (...) {
            DB->abort("SuePlayLog");
			L_ERROR(LOG_TABLOGGING,"Failed to log record " + artist 
                    + " - " + title + ".");
		}
			
            // Remove the entry from schedule once we've tried to load it
            L_INFO(LOG_SUEPLAY, "Removing track from sustainer playlist.");
			SQL_Remove = "DELETE FROM sustschedule WHERE id=" + id;
		try{
	        	DB->exec("SuePlay",SQL_Remove);
			DB->commit("SuePlay");
		} catch (...) {
            		L_INFO(LOG_SUEPLAY, "Failed to remove track from sustainer playlist.");
		}

		active = abs(active - 1);
		inactive = abs(inactive - 1);
	}
	delete ch[0];
	delete ch[1];
	delete fader[0];
	delete fader[1];
	delete mixer;
	delete player;
	delete Conf;
	delete DB;
}
