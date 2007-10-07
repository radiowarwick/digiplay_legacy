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
using namespace std;

#include "audio/Audio.h"
#include "audio/InputRaw.h"
#include "audio/OutputDsp.h"
#include "audio/ProcessMixer.h"
#include "audio/ProcessFader.h"
#include "audio/CounterTrigger.h"
using namespace Audio;

#include "Config.h"
#include "dps.h"
#include "Logger.h"
#include "DataAccess.h"

#define min(a,b) (((a)<(b))?(a):(b))

int main(int argc, char *argv) {
    Logger::setAppName("sueplay");
    Logger::setLogLevel(INFO);
    Logger::setDisplayLevel(ERROR);
    Logger::initLogDir();

    const char* routine = "sueplay::main";
	system("clear");
	cout << "Radio Warwick Sustainer" << endl;
	cout << "-----------------------" << endl;
	cout << "Playback service started." << endl;
	
	string SQL_Item,SQL_Remove;
	PqxxResult R;
	
	L_INFO(LOG_SUEPLAY, " -> Reading configuration file");
	Config *Conf = new Config("digiplay");
	
    L_INFO(LOG_SUEPLAY, " -> Connecting to Database...");
    DataAccess* DB = new DataAccess();
	
	SQL_Item = "SELECT archives.localpath AS path, audio.md5 AS md5, audio.title AS title, audio.length_smpl AS length_smpl, sustschedule.id AS id, sustschedule.trim_start_smpl AS start, sustschedule.trim_end_smpl AS end, sustschedule.fade_in AS fade_in, sustschedule.fade_out AS fade_out, v_audio_music.artist FROM sustschedule, audio, archives, v_audio_music WHERE sustschedule.audioid = audio.id AND archives.id = audio.archive AND audio.id = v_audio_music.id ORDER BY sustschedule.id LIMIT 1";
	L_INFO(LOG_SUEPLAY, "done.");

	// Create components
	InputRaw* ch[] = {new InputRaw(), new InputRaw()};
	ProcessFader* fader[] = {new ProcessFader(), new ProcessFader()};
	CounterTrigger* trig[] = {new CounterTrigger(), new CounterTrigger()};
	ProcessMixer* mixer = new ProcessMixer();
	OutputDsp* player = new OutputDsp(Conf->getParam("channel_1").c_str());

	ch[0]->connect(OUT0,fader[0],IN0);
	ch[1]->connect(OUT0,fader[1],IN0);
	fader[0]->connect(OUT0,mixer,IN0);
	fader[1]->connect(OUT0,mixer,IN1);
	mixer->connect(OUT0,player,IN0);
	
	trig[0]->setTriggerTarget(ch[1]);
	trig[1]->setTriggerTarget(ch[0]);
	ch[0]->addCounter(trig[0]);
	ch[1]->addCounter(trig[1]);

	string md5, path, title, artist;
	long start = 0, end = 0, fade_in = 0, fade_out = 0;
	long length_smpl = 0;
	unsigned short active = 0, inactive = 1;
	bool warn_flag = true;
	
	// Process schedule table until empty
	while (true) {
		//L_INFO(LOG_SUEPLAY, "BEGIN LOOP");
		// Keep trying until successfully loaded a file that exists!
		do {
			// Query database for next track to play
			R = DB->exec("SuePlay",SQL_Item);

			// If no results, then schedule must have been depleated! Doh!
			if (R.size() == 0) {
				if (warn_flag) {
					warn_flag = false;
					L_WARNING(LOG_SUEPLAY, "WARNING: Schedule is depleated!");
				}
				continue;
			}
			warn_flag = true;
			
			// Load the required data from database
			path = R[0]["path"].c_str();
			md5 = R[0]["md5"].c_str();
			title = R[0]["title"].c_str();
			artist = R[0]["artist"].c_str();
			start = atoi(R[0]["start"].c_str());
			end = atoi(R[0]["end"].c_str());
			fade_in = atoi(R[0]["fade_in"].c_str());
			fade_out = atoi(R[0]["fade_out"].c_str());
			length_smpl = atoi(R[0]["length_smpl"].c_str());
			//L_INFO(LOG_SUEPLAY, "DB START: " + dps_itoa(start));
			//L_INFO(LOG_SUEPLAY, "DB END: " + dps_itoa(end));
			//L_INFO(LOG_SUEPLAY, "DB FADEIN: " + dps_itoa(fade_in));
			//L_INFO(LOG_SUEPLAY, "DB FADEOUT: " + dps_itoa(fade_out));
			// Remove the entry from schedule once we've tried to load it
			SQL_Remove = "DELETE FROM sustschedule WHERE id="
			                        + (string)R[0]["id"].c_str();
	        DB->exec("SuePlay",SQL_Remove);
			DB->commit("SuePlay");
			
			path += "/" + md5.substr(0,1) + "/";
			L_INFO(LOG_SUEPLAY, "Attempting to load channel " +
                    dps_itoa(active) + ": " + artist + " - " + title);
			L_INFO(LOG_SUEPLAY, " -> Start: " + dps_itoa(start));
			L_INFO(LOG_SUEPLAY, " -> End: " + dps_itoa(end));
			// Try and load the track
			try {
				ch[active]->load( path + md5, start, end );
				break;
			}
			catch (...) {
				L_ERROR(LOG_SUEPLAY, "Error loading track");
			}
			sleep(1);
		} while (1);
		
		if (R.size() == 0) break;

		// positions are specified in terms of STEREO samples
		// database positions are in terms of STEREO samples
		fader[active]->clearNodes();
		unsigned long offset = start;

		if (fade_in > start)
			fade_in = fade_in - offset;
		else
			fade_in = 256;
		//L_INFO(LOG_SUEPLAY, "Fade in length: " + dps_itoa(fade_in));
		fader[active]->addNode(0,0.0);
		fader[active]->addNode(fade_in,1.0);
	
		//L_INFO(LOG_SUEPLAY, "BEFORE fadeout computation: ");
		L_INFO(LOG_SUEPLAY, " -> Fadeout: " + dps_itoa(fade_out));
		//L_INFO(LOG_SUEPLAY, "End = " + dps_itoa(end));
		if (fade_out < end)
			fade_out = fade_out - offset;
		else
			fade_out = end - 256 - offset;
		end = end - offset;
		L_INFO(LOG_SUEPLAY, " -> Fade out length: " + dps_itoa(end - fade_out));
		fader[active]->addNode(fade_out,1.0);
		fader[active]->addNode(end,0.0);
		//L_INFO(LOG_SUEPLAY, "Added fades");

		trig[active]->setTriggerSample(min(fade_out,end));
		//L_INFO(LOG_SUEPLAY, "Added trigger");
		// Wait until last track has been played before we load the next
		if (ch[inactive]->isLoaded()) {
			L_INFO(LOG_SUEPLAY, "Waiting for channel " + dps_itoa(inactive));
			trig[inactive]->waitStop();
			L_INFO(LOG_SUEPLAY, "Finished waiting");
		}
		else {
			L_INFO(LOG_SUEPLAY, "Playing channel " + dps_itoa(active));
			ch[active]->play();
		}

		//const char* routine = "sueplay::main";
		int now = (int)time(NULL);
		artist = DB->esc(artist);
		title = DB->esc(title);
		string SQL_Insert = "INSERT INTO log "
			"(userid, datetime, track_title, track_artist, location) "
			"VALUES (" + dps_itoa(1) + ", " + dps_itoa(now) + ", '"
			+ title + "', '" + artist + "', " + dps_itoa(0) + ");";
		try {
			DB->exec("SuePlayLog",SQL_Insert);
			DB->commit("SuePlayLog");
		}
		catch (...) {
            DB->abort("SuePlayLog");
			L_ERROR(LOG_TABLOGGING,"Failed to log record " + artist + " - " + title + ".");
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
