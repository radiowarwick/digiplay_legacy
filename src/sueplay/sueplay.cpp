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

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "audioplayer.h"
#include "audiomixer.h"
#include "audiochannel.h"

#include "config.h"

#define min(a,b) (((a)<(b))?(a):(b))

config *Conf;

int main(int argc, char *argv) {
	system("clear");
	cout << "Radio Warwick Sustainer" << endl;
	cout << "-----------------------" << endl;
	cout << "Playback service started." << endl;
	
	string SQL_Item,SQL_Remove;
	Result R;
	
	cout << " -> Reading configuration file" << endl;
    Conf = new config("digiplay");
	
	cout << " -> Connecting to Database...";
	Connection *C;
	Transaction *T = NULL;
	//Connect to database and get the first item on schedule
	try {
		C = new Connection( Conf->getDBConnectString() );
	}
	catch (...) {
		cout << "Failed to connect to database" << endl;
		exit(-1);
	}
	SQL_Item = "SELECT archives.localpath AS path, audio.md5 AS md5, audio.title AS title, audio.length_smpl AS length_smpl, sustschedule.id AS id, sustschedule.trim_start_smpl AS start, sustschedule.trim_end_smpl AS end, sustschedule.fade_in AS fade_in, sustschedule.fade_out AS fade_out FROM sustschedule, audio, archives WHERE sustschedule.audio = audio.id AND archives.id = audio.archive ORDER BY sustschedule.id LIMIT 1";
	cout << "done." << endl << " -> Creating audio mixer..." << flush;
	
	// Create and configure audio mixer
	audiomixer *mixer = new audiomixer;
	mixer->createChannel();
	mixer->createChannel();
	mixer->channel(0)->setVolume(0.0);
	mixer->channel(1)->setVolume(0.0);
	cout << "done." << endl;
	audioplayer *P = new audioplayer("channel_1");
	P->attachMixer(mixer);

	string md5, path;
	long start = 0, end = 0, fade_in = 0, fade_out = 0;
	long length_smpl = 0, trigger = 0;
	unsigned short active = 0, inactive = 1;
	bool warn_flag = true;
	
	// Process schedule table until empty
	while (true) {
		// Keep trying until successfully loaded a file that exists!
		do {
			// Query database for next track to play
			T = new Transaction(*C,"");
			R = T->exec(SQL_Item);

			// If no results, then schedule must have been depleated! Doh!
			if (R.size() == 0) {
				if (warn_flag) {
					warn_flag = false;
					cout << "WARNING: Schedule is depleated!" << endl;
				}
				continue;
			}
			warn_flag = true;
			
			// Load the required data from database
			path = R[0]["path"].c_str();
			md5 = R[0]["md5"].c_str();
			start = atoi(R[0]["start"].c_str());
			end = atoi(R[0]["end"].c_str());
			fade_in = atoi(R[0]["fade_in"].c_str());
			fade_out = atoi(R[0]["fade_out"].c_str());
			length_smpl = atoi(R[0]["length_smpl"].c_str());
			
			// Remove the entry from schedule once we've tried to load it
			SQL_Remove = "DELETE FROM sustschedule WHERE id="
			                        + (string)R[0]["id"].c_str();
	        T->exec(SQL_Remove);
			T->commit();
			delete T;
			
			path += "/" + md5.substr(0,1) + "/";
			cout << "Attempting to load channel " << active << ": " 
					<< R[0]["title"].c_str() << endl;
			// Try and load the track
			mixer->channel(active)->load( path + md5, start, end );
			sleep(1);
		} while (!mixer->channel(active)->isLoaded());
		
		if (R.size() == 0) break;

		trigger = min(end,fade_out);

		if (fade_in > start)
		mixer->channel(active)->scheduleFade(start, 0.0, fade_in, 100.0);
		else
		mixer->channel(active)->scheduleFade(start, 0.0, start+256, 100.0);
		
		if (fade_out < end)
		mixer->channel(active)->scheduleFade(fade_out, 100.0, end, 0.0);
		else
		mixer->channel(active)->scheduleFade(end-256, 100.0, end, 0.0);
		
		mixer->channel(active)->scheduleTrigger(trigger, mixer->channel(inactive));
		
		// Wait until last track has been played before we load the next
		if (mixer->channel(inactive)->isLoaded()) {
			cout << "Waiting for channel " << inactive << endl << endl;
			mixer->channel(inactive)->notify_cache();
			mixer->channel(inactive)->notify();
		}
		else {
			cout << "Playing channel " << active << endl << endl;
			mixer->channel(active)->play();
		}
		
		active = abs(active - 1);
		inactive = abs(inactive - 1);
	}
	delete P;
	delete mixer;
	delete Conf;
}
