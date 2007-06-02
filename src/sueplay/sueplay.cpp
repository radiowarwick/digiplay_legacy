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

#include "audio/Audio.h"
#include "audio/InputRaw.h"
#include "audio/OutputDsp.h"
#include "audio/ProcessMixer.h"
#include "audio/ProcessFader.h"
#include "audio/CounterTrigger.h"
using namespace Audio;

#include "Config.h"

#define min(a,b) (((a)<(b))?(a):(b))

int main(int argc, char *argv) {
	system("clear");
	cout << "Radio Warwick Sustainer" << endl;
	cout << "-----------------------" << endl;
	cout << "Playback service started." << endl;
	
	string SQL_Item,SQL_Remove;
	Result R;
	
	cout << " -> Reading configuration file" << endl;
    Config *Conf = new Config("digiplay");

	cout << " -> Connecting to Database..." << flush;
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
	SQL_Item = "SELECT archives.localpath AS path, audio.md5 AS md5, audio.title AS title, audio.length_smpl AS length_smpl, sustschedule.id AS id, sustschedule.trim_start_smpl AS start, sustschedule.trim_end_smpl AS end, sustschedule.fade_in AS fade_in, sustschedule.fade_out AS fade_out FROM sustschedule, audio, archives WHERE sustschedule.audioid = audio.id AND archives.id = audio.archive ORDER BY sustschedule.id LIMIT 1";
	cout << "done." << endl;

	// Create components
	InputRaw* ch[] = {new InputRaw(), new InputRaw()};
	ProcessFader* fader[] = {new ProcessFader(), new ProcessFader()};
	CounterTrigger* trig[] = {new CounterTrigger(), new CounterTrigger()};
	ProcessMixer* mixer = new ProcessMixer();
	OutputDsp* player = new OutputDsp("/dev/dsp");

	ch[0]->connect(OUT0,fader[0],IN0);
	ch[1]->connect(OUT0,fader[1],IN0);
	fader[0]->connect(OUT0,mixer,IN0);
	fader[1]->connect(OUT0,mixer,IN1);
	mixer->connect(OUT0,player,IN0);
	
	trig[0]->setTriggerTarget(ch[1]);
	trig[1]->setTriggerTarget(ch[0]);
	ch[0]->addCounter(trig[0]);
	ch[1]->addCounter(trig[1]);

	string md5, path;
	long start = 0, end = 0, fade_in = 0, fade_out = 0;
	long length_smpl = 0;
	unsigned short active = 0, inactive = 1;
	bool warn_flag = true;
	
	// Process schedule table until empty
	while (true) {
		cout << "BEGIN LOOP" << endl;
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
			cout << "DB START: " << start << endl;
			cout << "DB END: " << end << endl;
			cout << "DB FADEIN: " << fade_in << endl;
			cout << "DB FADEOUT: " << fade_out << endl;
			// Remove the entry from schedule once we've tried to load it
			SQL_Remove = "DELETE FROM sustschedule WHERE id="
			                        + (string)R[0]["id"].c_str();
	        T->exec(SQL_Remove);
			T->commit();
			delete T;
			
			path += "/" + md5.substr(0,1) + "/";
			cout << "Attempting to load channel " << active << ": " 
					<< R[0]["title"].c_str() << endl;
			cout << " -> Start: " << start << endl;
			cout << " -> End: " << end << endl;
			// Try and load the track
			try {
				ch[active]->load( path + md5, start, end );
				break;
			}
			catch (...) {
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
		cout << "Fade in length: " << fade_in << endl;
		fader[active]->addNode(0,0.0);
		fader[active]->addNode(fade_in,1.0);
	
		cout << "BEFORE fadeout computation: " << endl;
		cout << "Fadeout = " << fade_out << endl;
		cout << "End = " << end << endl;
		if (fade_out < end)
			fade_out = fade_out - offset;
		else
			fade_out = end - 256 - offset;
		end = end - offset;
		cout << "Fade out length: " << end - fade_out << endl;
		fader[active]->addNode(fade_out,1.0);
		fader[active]->addNode(end,0.0);
		cout << "Added fades" << endl;

		trig[active]->setTriggerSample(min(fade_out,end));
		cout << "Added trigger" << endl;
		// Wait until last track has been played before we load the next
		if (ch[inactive]->isLoaded()) {
			cout << "Waiting for channel " << inactive << endl << endl;
			trig[inactive]->waitStop();
			cout << "Finished waiting" << endl;
		}
		else {
			cout << "Playing channel " << active << endl << endl;
			ch[active]->play();
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
}
