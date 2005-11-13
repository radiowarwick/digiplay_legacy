#include "schedule.h"

schedule::schedule(Transaction *T_new) {
	T = T_new;
	S = new vector<track>;
}

schedule::~schedule() {

}

void schedule::newSchedule() {
	delete S;
	S = new vector<track>;
}

/* Inserts a track into the schedule.
 */
void schedule::add(track t, short position) {
    if (position == -1) {
        S->push_back(t);
    }
    else {
        S->insert(S->begin() + position,1,t);
    }
}

/* Removes an item from the schedule
 */
void schedule::remove(unsigned short position) {
    if (position >= S->size()) {
        cout << "Invalid ID to remove" << endl;
        exit(-1);
    }
    S->erase(S->begin() + position);
}

/* Checks if a track is already scheduled
 */
bool schedule::check(track t) {
    for (unsigned short i = 0; i < S->size(); i++)
        if (S->at(i).md5 == t.md5)
            return true;
    return false;
}

/* Returns the track in the given position
 */
track schedule::at(unsigned short position) {
	return S->at(position);
}

/* Gets the length of the currently proposed schedule
 * TODO: Check this works properly when fade in \ fade out times don't match
 */
unsigned long schedule::getLength_smpl() {
    unsigned long length_smpl = 0;
    for (unsigned int i = 0; i < S->size(); i++) {
        length_smpl += (S->at(i).fade_out_smpl - S->at(i).trim_start_smpl);
    }
	if (S->size() > 0) {
		length_smpl += S->at(S->size() - 1).trim_end_smpl 
							- S->at(S->size() - 1).fade_out_smpl;
	}
    return length_smpl;
}

/* Gets the number of entries in the schedule
 */
unsigned int schedule::size() {
    return (unsigned int)(S->size());
}

/* Creates a string showing the schedule length in pretty format
 */
string schedule::getLength_pretty() {
    unsigned long length_smpl = getLength_smpl();
    unsigned short hrs = (length_smpl - (length_smpl % (44100*60*60))) / (44100*60*60);
    length_smpl = length_smpl - (44100*60*60*hrs);
    unsigned short mins = (length_smpl - (length_smpl % (44100*60))) / (44100*60);
    length_smpl = length_smpl - (44100*60*mins);
    unsigned short secs = (length_smpl - (length_smpl % 44100)) / 44100;
    length_smpl = length_smpl - (44100*secs);
    stringstream S;
    S << hrs << "hrs " << mins << "mins " << secs << "secs (" << length_smpl << ")";
    return S.str();
}

/* Returns the number of points in the schedule still requiring allocation
 * of fade times
 */
unsigned int schedule::getCrossfadePoints() {
    unsigned int points = 0;
    for (unsigned short i = 0; i < S->size() - 1; i++) {
        if (S->at(i).fade_out_smpl == S->at(i).trim_end_smpl) points++;
    }
    return points;
}

void schedule::printToScreen() {
	track t;
	cout << " -> Schedule length: " << getLength_pretty() << endl << endl;
	cout << "    Title                                               "
		<< "Length       ID" << endl;
	cout << "--------------------------------------------------------"
		<< "--------------------" << endl;
	for (unsigned short i = 0; i < S->size(); i++) {
		t = S->at(i);
		string desc = t.title + " (" + t.artist + ")";
		printf("%02i) %-50.50s [%10i] {%6i}\n",
				(int)i, desc.c_str(), (int)t.length_smpl, (int)t.audio_id);
	}
    cout << "--------------------------------------------------------"
		        << "--------------------" << endl;
}

/* Exports the generated schedule to the database
 */
void schedule::exportToDatabase() {
    track t;
    for (unsigned short i = 0; i < S->size(); i++) {
        t = S->at(i);
        stringstream SQL;
        SQL << "INSERT INTO sust_sched (audio,source_type,start_date,start_time,trim_start_smpl,trim_end_smpl,fade_in,fade_out)"
            << " VALUES ("
            << t.audio_id << ","			// Audio ID
            << "0" << ",'"					// Source type
            << "01-01-2000" << "','"		// Start date
            << "00:00" << "',"				// Start time
            << t.trim_start_smpl << ","		// Start trim
            << t.trim_end_smpl << ","		// End trim
            << t.fade_in_smpl << "," 		// End point of fade in
            << t.fade_out_smpl << ")";		// Start point of fade out
        T->exec(SQL);
    }
}

