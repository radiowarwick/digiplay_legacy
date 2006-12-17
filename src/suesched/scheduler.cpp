/*
 * Sustainer Scheduler
 * scheduler.cpp
 * Selects tracks from schedule bins and adds them to a schedule calculating
 * timings, etc
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
#include "scheduler.h"

#define DO_CROSSFADES 1
#define DO_FINAL_FADE 1
#define DO_EXPORT 1

/* Creates a connection to database
 */
scheduler::scheduler() {
	// Read configuration from the /etc/digiplay config file
	config *Conf = new config("digiplay");
	try {
	    C = new Connection( Conf->getDBConnectString() );
	}
	catch (...) {
		cout << "Failed to connect to database" << endl;
		exit(-1);
	}

	T = new Transaction( *C, "");
	S = new schedule( T );
}

/* Closes connection to database
 */
scheduler::~scheduler() {
	delete S;
	delete T;
	delete C;
}

/* Initiates scheduling for the required time
 *  long seconds		number of minutes to schedule for
 */
void scheduler::doSchedule(long seconds) {
	cout << " -> Scheduling " << seconds << " seconds of music." << endl;

	// Check we're not aiming to schedule a stupid amount of time
	if (seconds > 86400) {
		cout << "   -> ERROR: max scheduling slot is 24hrs (86400)" << endl;
		return;
	}
	target_length_smpl = seconds * 44100;

	initialise();

	// Process schedule. Only succeeds if the entire chain completes,
	// else it tries again.
	while (!(
		doFill() 
		&& doMinimise()
#if (DO_CROSSFADES == 1)
		&& doCrossfades()
#endif

#if (DO_FINAL_FADE == 1)
		&& doFadeOut()
#endif
		)) {
	}
	S->printToScreen();
	
#if (DO_EXPORT == 1)
	S->exportToDatabase();	
#endif
	
	complete();
	cout << " -> Scheduling complete!" << endl;
	cout << endl;
}

/* Load data from database, create bins, etc
 */
bool scheduler::initialise() {
	bins = new vector<sched_bin*>;
	srand(time(0));
	
	cout << " -> Loading audio data..." << endl;
	bins->push_back(new sched_bin(T,BIN1_SQL,0));
	bins->push_back(new sched_bin(T,BIN2_SQL,1));
	bins->push_back(new sched_bin(T,BIN3_SQL,2));
	bins->push_back(new sched_bin(T,BIN4_SQL,3));
	bins->push_back(new sched_bin(T,BIN5_SQL,4));
	bins->push_back(new sched_bin(T,BIN6_SQL,5));
	bins->push_back(new sched_bin(T,BIN7_SQL,6));

    cout << " -> Getting Weightings..." << endl;
    bin_w[0] = atoi(getConfigParam("bin_weighting_1").c_str());
    bin_w[1] = atoi(getConfigParam("bin_weighting_2").c_str());
    bin_w[2] = atoi(getConfigParam("bin_weighting_3").c_str());
    bin_w[3] = atoi(getConfigParam("bin_weighting_4").c_str());
    bin_w[4] = atoi(getConfigParam("bin_weighting_5").c_str());

	cout << " -> Initialisation complete." << endl;
	return true;
}

bool scheduler::complete() {
	T->commit();
	delete T;
	T = new Transaction(*C,"");

	cout << " -> Cleaning up..." << endl;
	for (unsigned int i = 0; i < bins->size(); i++)
		delete bins->at(i);
	delete bins;
	return true;
}

/* Returns the number of tracks in the playlist
 */
unsigned int scheduler::getPlaylistSize() {
    string SQL = "SELECT count(id) FROM audio WHERE sustainer='t'";
    return atoi(T->exec(SQL)[0][0].c_str());
}   

/* Returns the total length of the tracks in the playlist
 */
unsigned long scheduler::getPlaylistLength() {
    string SQL = "SELECT sum(length_smpl) FROM audio "
        "WHERE sustainer='t'";
    return atoi(T->exec(SQL)[0][0].c_str());
}   

/* Returns the number of tracks in the playout schedule which are still
 * to play
 */
unsigned int scheduler::getScheduleRemainSize() {
    string SQL = "SELECT count(*) FROM sustschedule";
    return atoi(T->exec(SQL)[0][0].c_str());
}

/* Returns the time until the playout engine will reach end of current
 * playout schedule
 */
unsigned long scheduler::getScheduleRemainTime() {
    string SQL = "SELECT sum(audio.length) FROM sustschedule,audio "
        "WHERE sustschedule.audio=audio.id";
    return atoi(T->exec(SQL)[0][0].c_str());
}

/* ====================================================
 * MAIN SCHEDULING ROUTINES
 * ====================================================
 */
/* Fills a specified time frame with music based on weighting and genres
 * TODO: Insert jingles and adverts
 */
bool scheduler::doFill() {
	cout << " -> Filling schedule..." << flush;
    S->newSchedule();
	int bin;
	int checkcount = 0;
	long time_from_last_jingle = 0;
	
	track t;
	//Add tracks until schedule length EXCEEDS required length
	while (S->getLength_smpl() < target_length_smpl) {
		if (time_from_last_jingle > 15*60*ONE_SECOND) {
			time_from_last_jingle = 0;
			bin = 5;
		}
		else {
			// Pick a bin and note down
			bin = (int)((float)bin_w[4] * ((float)rand()/RAND_MAX));
			if (bin <= bin_w[0]) bin = 0;
			if (bin > bin_w[0] && bin <= bin_w[1]) bin = 1;
			if (bin > bin_w[1] && bin <= bin_w[2]) bin = 2;
			if (bin > bin_w[2] && bin <= bin_w[3]) bin = 3;
			if (bin > bin_w[3]) bin = 4;
		}
		
		// Pick a random track out of this bin and check it's not already
		// been selected.
		do {
			t = bins->at(bin)->getRandom();
			checkcount++;
			// give up after 50 attempts (and trying different bins)
			if (checkcount > 50) {
				cout << "failed!" << endl;
				cout << " -> ERROR: Not enough tracks for this duration!" 
					<< endl;
				return false;
			}
			// give up after 10 attempts and hope for a different bin
			if (checkcount > 10) {
				continue;
			}
		} while (S->check(t));
		checkcount = 0;
		
		// Add new track to schedule, -1 => add to back of schedule
		if (!t.isNull) {
			S->add(t,-1);
			time_from_last_jingle += t.length_smpl;
		}
	}
	cout << "done." << endl;
	cout << "   -> Schedule length: " << S->getLength_pretty() << endl;
	return true;
}

/* Minimises the schedule, replacing tracks by shorter ones from same bin
 */
bool scheduler::doMinimise() {
	cout << " -> Minimising schedule...." << flush;
	
	if (S->getLength_smpl() <= target_length_smpl + (90 * ONE_SECOND)) {
		cout << "skipped." << endl;
		cout << "   -> INFO: Current schedule is within tolerance." << endl;
		return true;
	}

	int no_improve_count = 0;
	unsigned long old_length = 0;
	unsigned long excess = 0;

	// Minimise while schedule too long unless we've failed to improve 50 times
	while (S->getLength_smpl() > target_length_smpl + (90 * ONE_SECOND) 
												&& no_improve_count < 50) {
		old_length = S->getLength_smpl();
		excess = old_length - target_length_smpl;
		
		// Remove a randomly selected track
		int i = (int)(S->size() * (rand()/(RAND_MAX+1.0)));
		track t = S->at(i);
		if (t.bin == 5) continue;

		track t_new = bins->at(t.bin)->getShorter(t,t.length_smpl - excess);
	
		// If fails to find a shorter track, returns original track
		// so test to see if we have a shorter track and if so, replace old one
		if (t.audio_id != t_new.audio_id && !(S->check(t_new))) {
			S->remove(i);
			S->add(t_new,i);
			no_improve_count = 0;
		}
		no_improve_count++;
		
		// If we've failed to replace any tracks after 50 attempts, give up!
		if (no_improve_count > 50) {
			cout << "failed." << endl;
			return false;
		}
	}
	// Have successfully minimised schedule to within tolerance
	cout << "done." << endl;
	cout << "   -> Schedule length: " << S->getLength_pretty() << endl;
	return true;
}

/* Inserts crossfading, based on the excess time, and the minimum fade times
 * for each track.
 */
bool scheduler::doCrossfades() {
	cout << " -> Computing Crossfades...";
	track t, t_next, t_previous;
	for (unsigned int i = 0; i < S->size(); i++) {
		t = S->at(i);
		if (i > 0) {
			t_previous = S->at(i-1);
		}
		if (i < S->size() - 1) {
			t_next = S->at(i+1);
		}
		if (t.bin != 5 && t_previous.bin != 5) {
			if (t.length_smpl > 441000 && t_previous.length_smpl > 441000)
				t.fade_in_smpl = t.trim_start_smpl + 220500;
		}
		
		if (t.bin != 5 && t_next.bin != 5) {
			if (t.length_smpl > 441000 && t_next.length_smpl > 441000)
				t.fade_out_smpl = t.trim_end_smpl - 220500;
		}
		S->remove(i);
		S->add(t,i);
	}
	cout << "done." << endl;
	cout << "   -> Schedule length: " << S->getLength_pretty() << endl;
	return true;
}
		
/*bool scheduler::doCrossfade() {
	unsigned short modified_tracks = 0;
	unsigned short modified_previous = 0;
	unsigned long max_fade;
	unsigned long excess_time = getScheduleLength_smpl() - required_length_smpl;
	unsigned long time_per_point = excess_time / getCrossfadePoints();
	track *t;
	track *next;
	
	// Give up straight away if the fade times are ridiculous!
	if (time_per_point > 15000) return false;
	
	cout << endl << "Starting crossfades..." << endl << flush;
	cout << "Excess time before fades: " << excess_time << "ms" << endl;
	cout << "Crossfade points: " << getCrossfadePoints() << endl;

	// Repeatedly scan through playlist allocating the max fade time to
	// tracks whose max fade time is less than time_per_point
	// Adjusts time_per_point after each iteration
	do {
		modified_previous = modified_tracks;
		time_per_point = excess_time / getCrossfadePoints();
		
		for (unsigned short i = 0; i < S->size() - 1; i++) {
			t = S->at(i);
			next = S->at(i+1);
			// If this track or next track isn't music, don't do a fade
			if (next->bin > 3 || t->bin > 3) continue;
			// Only do a fade, if there isn't one there already
			if (t->fade_out == -1) {
				// Gets the max fade time for the pair of tracks
				if (getAudioEndFade(t->bin,t->bin_id) 
						> getAudioStartFade(next->bin, next->bin_id)) {
					max_fade = getAudioStartFade(next->bin, next->bin_id);
				cout << max_fade;}
				else
					max_fade = getAudioEndFade(t->bin,t->bin_id);
				
				// If it's less than time_per_point, then set fade as max_fade
				if (time_per_point > max_fade) {
					t->fade_out = max_fade;
					next->fade_in = max_fade;
					excess_time -= max_fade;
					modified_tracks++;
				}
			}
		}
		// If we've allocated all the fade points, we can't succeed!
		if (modified_tracks == getScheduleCount()) return false;
		//Keep looping unless we never modified any fade points on this go
	} while (modified_tracks - modified_previous == 0);	
	
	cout << "Spreading " << excess_time << "ms between remaining...";
	cout << getCrossfadePoints() << " crossfade points.";

	// If there are fade points to do, we can't do anything for this schedule
	// so return false and we'll try again
	if (getCrossfadePoints() == 0) return false;

    // Now we aren't affecting any more tracks, so allocate remaining excess
	// time between the remaining fade points.
	time_per_point = excess_time / getCrossfadePoints();
	for (unsigned int i = 0; i < S->size() - 1; i++) {
		t = S->at(i);
		next = S->at(i+1);
		if (next->bin > 3 || t->bin > 3) continue;
//		if (getAudioEndFade(t->bin,t->bin_id) < time_per_point)
//			return false;
//		if (getAudioStartFade(next->bin, next->bin_id) < time_per_point)
//			return false;
		if (t->fade_out <= 0) {
			t->fade_out = time_per_point;
			next->fade_in = time_per_point;
			excess_time -= time_per_point;
		}
	}
	cout << "Error time (ms): " << excess_time << endl;
	// We've successfully scheduled, so return true
	return true;
}
*/

/* Fades out the last track to make accurate timing
 */
bool scheduler::doFadeOut() {
	cout << " -> Computing final fade-out..." << flush;
    if (S->getLength_smpl() < target_length_smpl) {
		cout << "failed!" << endl;
        cout << "   -> ERROR: Crossfades made schedule too short!" << endl;
		cout << endl;
        return false;
    }
	unsigned long excess = S->getLength_smpl() - target_length_smpl;
	track t = S->at(S->size() - 1);
	t.trim_end_smpl = t.trim_start_smpl + t.length_smpl - excess;
	t.fade_out_smpl = t.trim_end_smpl - (5 * ONE_SECOND);
	S->remove(S->size() - 1);
	S->add(t,-1);
	cout << "done." << endl;
	return true;
}

/* =================================================
 * HELPER ROUTINES
 * =================================================
 */

/* Gets a configuration parameter value from the database
 */
string scheduler::getConfigParam(string name) {
	string SQL = "SELECT val FROM configuration WHERE parameter='"
		+ name + "'";
	Result R = T->exec(SQL);
	if (R.size() > 0) {
		return R[0][0].c_str();
	}
	else {
		cout << "NO RECORDS!" << flush;
		return "";
	}
}

