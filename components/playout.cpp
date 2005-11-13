/* Audio Playout Handler Object
 * playout.cpp
 *
 * Handles playback of audio from file or Line In sources, providing
 * crossfading facilities.
 * (c) Copyright Chris Cantwell 2004
 */
#include "playout.h"

/* Keeps pointer to a dynamic playlist. Then proceeds to initialise the
 * audio hardware.
 * TODO: Take dsp device as a parameter for multiple soundcards.
 */
playout::playout(string Channel) {
	config_reader *Conf = new config_reader("digiplay");
	string Device;

	DB_CONNECT = "";
    if (Conf->isDefined("DB_HOST"))
        DB_CONNECT += "hostaddr=" + Conf->getParam("DB_HOST") + " ";
    if (Conf->isDefined("DB_NAME"))
        DB_CONNECT += "dbname=" + Conf->getParam("DB_NAME") + " ";
    if (Conf->isDefined("DB_USER"))
        DB_CONNECT += "user=" + Conf->getParam("DB_USER") + " ";
    if (Conf->isDefined("AUDIO_PATH"))
        AUDIO_PATH = Conf->getParam("AUDIO_PATH");
    if (Conf->isDefined("CACHE_SIZE"))
        CACHE_SIZE = atoi(Conf->getParam("CACHE_SIZE").c_str());
	if (Conf->isDefined("DSP_SPEED"))
        DSP_SPEED = atoi(Conf->getParam("DSP_SPEED").c_str());
	
	if (Conf->isDefined(Channel))
		Device = Conf->getParam(Channel).c_str();
	else {
		cout << "Channel: " << Channel 
			<< " has not been defined in /etc/digiplay config file!" << endl;
		exit(-1);
	}
	
	if (AUDIO_PATH == "" || DSP_SPEED == 0 || CACHE_SIZE == 0) {
		cout << "FATAL: Missing or invalid configuration information" << endl;
		cout << "  -> Check /etc/digiplay is correct" << endl;
		exit(-1);
	}
	if (DB_CONNECT == "") {
		cout << "FATAL: No database connection defined" << endl;
		cout << "  -> Check /etc/digiplay defined database connection" << endl;
		exit(-1);
	}
	delete Conf;

	Initialise_Hardware(Device);

	//Initialise database access
	cout << "Connecting to database...";
	C = new Connection( DB_CONNECT );
	cout << "done." << endl << "Creating transaction..." << flush;
	T = new Transaction(*C,"");
	cout << "done." << endl;
	
    //Set up Cache
    Cache_Start = new char[ CACHE_SIZE ];
	if (Cache_Start == NULL) {
	    cout << "ERROR: Cannot Allocate Cache." << endl;
        exit (-1);
    }
    Cache_End = Cache_Start + CACHE_SIZE;
    Cache_Read = Cache_Start;
    Cache_Write = Cache_Start;
    Cache_Free = CACHE_SIZE;
	mode_play = false;	// no track loaded yet so won't be trying to play!

	f_counters = NULL;  // by default, no counter is going to be updated

	//Create playback thread and execute
	int Ret_Play;
	pthread_t Thread_Play;
    Ret_Play = pthread_create(&Thread_Play, NULL,
								thread_play_cache, (void*)this);
	cout << "Created Playback thread." << endl;
	cout << "Playout engine ready." << endl << endl;
}

playout::~playout() {
	T->Abort();
	delete Cache_Start;
	delete C;
	delete T;
}

/* Opens dsp device and configures sample rate, sample size, stereo, etc
 */
void playout::Initialise_Hardware(string Device) {
	cout << "Initialising audio hardware for " << Device << "..." << endl;
	dsp_speed = DSP_SPEED;
	int dsp_sample_size = 16;
	int dsp_stereo = 1;
	int dsp_profile = APF_NORMAL;
	int dsp_frag_size = 0;
	
	int dsp_block_size = 0;
	int audio_buffer_size;
	//open audio device
    audio = open (Device.c_str(), O_WRONLY, 0);
    if (audio == -1) {
        cout << "FATAL: Unable to open device " << Device << endl;
        exit (-1);
    }
	//configure audio device
	int tmp = dsp_sample_size;
    ioctl(audio, SNDCTL_DSP_SAMPLESIZE, &dsp_sample_size);
    if (tmp != dsp_sample_size) {
		cout << "WARNING: Unable to set sample size" << endl;
    }
    ioctl(audio, SNDCTL_DSP_PROFILE, &dsp_profile);

	if (ioctl (audio, SNDCTL_DSP_STEREO, &dsp_stereo)==-1) {
        cout << "WARNING: Unable to set Stereo flag" << endl;
	}

	if (ioctl (audio, SNDCTL_DSP_SPEED, &dsp_speed) == -1) {
		cout << "WARNING: Unable to set DSP speed" << endl;
    }

    ioctl (audio, SNDCTL_DSP_GETBLKSIZE, &audio_buffer_size);
	cout << "Initial Buffer size: " << audio_buffer_size << endl;
    if (audio_buffer_size < 1) {
		cout << "WARNING: Unable to get block size" << endl;
    }

	int arg = 0x0002000B;
	if (ioctl (audio, SNDCTL_DSP_SETFRAGMENT, &arg)) {
		cout << "Error occured setting buffer!" << endl;
	}

    ioctl (audio, SNDCTL_DSP_GETBLKSIZE, &audio_buffer_size);
    cout << "New Buffer size: " << audio_buffer_size << endl;
    if (audio_buffer_size < 1) {
        cout << "WARNING: Unable to get block size" << endl;
	}		
}

void playout::load(string *md5) {
	string filename = AUDIO_PATH;
	filename += "/" + *md5;

	//stop();

    //Open the track
    current_file_handle = new ifstream(filename.c_str(),
                                            ios::in|ios::binary|ios::ate);
	current_file_handle->seekg(0,ios::end);
	b_current_length = current_file_handle->tellg();
	b_current_pos = 0;
	
	cout << "Loaded " << getFileTitle(md5) << " ("
			<< long(b_current_length / 176.4) << "ms)" << endl;
}
	
/* Plays a track as specified by MD5 hash
 * Works from back of vector popping the last item off when read.
 * The scheduler inserts items at the front when run.
 */
void playout::play(long start_smpl, long end_smpl) {

	//Cache current file
	current_start_byte = start_smpl * 4;
	current_end_byte = end_smpl * 4;
	b_current_pos = current_start_byte;
    
	int Ret_Cache = pthread_create(&Thread_Cache, NULL,
                                thread_fill_cache, (void*)this);
	mode_play = true;
}

/* Sets up the crossfading between two tracks
 */
void playout::play_crossfade(string *md5_1, string *md5_2,
						long start1_ms, long start2_ms, long length_ms) {

    string filename1 = AUDIO_PATH;
	string filename2 = AUDIO_PATH;
    filename1 += "/" + *md5_1;
	filename2 += "/" + *md5_2;

    //Open the tracks
    current_file_handle1 = new ifstream(filename1.c_str(), 
										ios::in|ios::binary|ios::ate);
	current_file_handle2 = new ifstream(filename2.c_str(), 
										ios::in|ios::binary|ios::ate);

	//Set file segment to cache
	current_start1_byte = (long)(start1_ms * 176.4);
	current_start2_byte = (long)(start2_ms * 176.4);
	current_length_byte = (long)(length_ms * 176.4);

	//Create thread and run the caching routine
	int Ret_Cache = pthread_create(&Thread_Cache_Crossfade, NULL,
								thread_fill_cache_crossfade, (void*)this);
}

/* Stops playback
 */
void playout::stop() {
	mode_play = false;
	mode_cache = false;
	usleep(100000);
	b_current_pos = current_start_byte;
	if (f_counters)	f_counters(getPosition_ms(),f_obj);
	Cache_Read = Cache_Start;
	Cache_Write = Cache_Start;
	Cache_Free = CACHE_SIZE;
}

/* Pauses playback
 */
void playout::pause() {
	mode_play = false;
}

/* Resume playback from pause
 */
void playout::resume() {
	mode_play = true;
}

/* Jumps to a position within the track
 */
void playout::seek(long position) {
	position = (long)(position * 176.4);
	position -= position%4;
	current_file_handle->seekg(position,ios::beg);
	b_current_pos = position;
	if (f_counters) f_counters(getPosition_ms(),f_obj);
	Cache_Write = Cache_Read;
	Cache_Free = CACHE_SIZE;
}

/* Notify when the playback thread has flushed the cache
 */
void playout::notify() {
	while (Cache_Free < CACHE_SIZE)
		usleep(10000);
}

/* Waits until the caching thread terminates then returns
 * One of the more simpler functions :D
 */
void playout::notify_cache() {
	pthread_join(Thread_Cache,NULL);
}

/* Stores a pointer to a counter-update function.
 * This function is called only when the current position in the audio 
 * changes. The supplied pointer should reference a static function which 
 * accepts a const char array, and a void pointer. The void pointer is to 
 * pass a pointer to the instance of the client object for use by it's static
 * function when setting the returned value.
 */
void playout::addCounter(void (*f_setCounter)(long,void*), void *obj) {
	f_counters = f_setCounter;
	f_obj = obj;
	if (f_counters) f_counters(getPosition_ms(),f_obj);
}

/* ==============================================
 * PSEUDO PUBLIC CODE
 * This code, while public, is for the benefit of loopback
 * multithreading. Not to be called by other objects.
 * Yes, this is all a bit of a bodge...but it works perfectly
 * =============================================
 */

/* Reads the designated portion of an audio track into Cache
 * (as specified by global variables)
 */
void playout::cache() {
	// Calculate portion of track to cache and initialise variables
//	long count = current_end_byte - b_current_pos;
	long offset;
	char *audio_buffer = new char[256];
	int read_bytes = 256;
	
	// Seek to start offset in file
	current_file_handle->clear();
	current_file_handle->seekg(b_current_pos,ios::beg);
	
	// Cache track until cached what we want
	mode_cache = true;
	while (read_bytes == 256 && mode_cache) {
		//If caching has caught up with playback, wait for 100us.
		while (Cache_Free < 1024) {	
			usleep(100);
		}
	
		//Check if we've reached the end point of the section to play
		if (current_end_byte - current_file_handle->tellg() < 256) {
			read_bytes = current_end_byte - current_file_handle->tellg();
			if (read_bytes == 0) break;
		}
		else read_bytes = 256;
		
		//Read from file into a 256byte buffer and get length read
		current_file_handle->read(audio_buffer,read_bytes);
		read_bytes = current_file_handle->gcount();
		
		//Check we actually read from file
		if (read_bytes == 0) {
	    	cout << "ERROR: Unable to read from file or unexpected end" << endl;
			break; //File messed up, continue onto next track...
		}
		
		//Put buffer into Cache - this could quite easily be tidied up a bit!
		char *ptr = audio_buffer;
		for (int i = 0; i < read_bytes; i++) {
			*Cache_Write = *ptr;
			Cache_Write++;
			ptr++;
			Cache_Free--;
			if (Cache_Write > Cache_End) // circular cache
				Cache_Write = Cache_Start;
		}
	}
	delete audio_buffer;
	mode_cache = false;
	cout << "mode_cache end: " << mode_cache << endl;	
}

/* Reads from two audio tracks and crossfades
 * TODO: Write this so it works and test it
 */
void playout::cache_crossfade() {
    char *audio_buffer_pri = new char [256];
    char *audio_buffer_sec = new char [256];
    long count = current_length_byte;
    long write_count;
    float ratio;
								    
    current_file_handle1->seekg(current_start1_byte);
	current_file_handle2->seekg(current_start2_byte);
    while (count && mode_cache) {
        //read in next block
        current_file_handle1->read (audio_buffer_pri, 256);
        current_file_handle2->read (audio_buffer_sec, 256);
        if (current_file_handle1->gcount() < count)
	        write_count = current_file_handle1->gcount();
		else
            write_count = count;

		if (write_count == 0) {
	        cout << "ERROR: Unable to read from file or unexpected end" << endl;
            exit (-1);
        }   

		ratio = (float)count / (float)current_length_byte;

		//perform dsp.....badly
		unsigned short pri, sec, temp;
		char *ptr = audio_buffer_pri;
		for (int i = 0; i < write_count; i++ ) {
            audio_buffer_pri[i] = (char)((float)audio_buffer_pri[i] 
                                                        * ratio);
            audio_buffer_pri[i] += (char)((float)audio_buffer_sec[i] 
                                                        * (1.0-ratio));
		}

		*Cache_Write = *ptr;
        Cache_Write++;
        ptr++;
        Cache_Free--;
        if (Cache_Write > Cache_End) // circular cache
            Cache_Write = Cache_Start;

        count -= write_count; //deduct what we've now read and cached
	}          
	delete audio_buffer_pri;
	delete audio_buffer_sec;
	delete current_file_handle1;
	delete current_file_handle2;
}

/* Plays out the contents of a Cache until empty then waits.
 * This is designed to run in its own thread, and initialised
 * when the object is created.
 *
 * It will sleep until the cache contains audio data.
 * TODO: Put stop \ pause conditions in.
 */
void playout::play_cache() {
	long write_count = 64;
	long updateCount = 0;
	char *audio_buffer = new char[64];
	do {
// 		cout << Cache_Free << endl;
		//Don't play when paused
        while (!mode_play)
            usleep(1000);

		//Sleep and keep checking cache every 10ms for data
		while (Cache_Free > CACHE_SIZE - 512) {
			if (mode_play) stop();
			usleep(1000);
		}
		
		// Do counters
        b_current_pos += 64;
    	if (f_counters) {		// only update a counter if we have one!
			if (updateCount == 50) {  // update roughly every 1/50 sec
		        updateCount = 0;
			    f_counters(getPosition_ms(),f_obj);
			}		// callback function using function pointers
			updateCount++;
		}
		
		//Read the 64byte chunk into a separate buffer.
		//Again, this can be easily shortened. But can't dump straight from
		//cache as things become messy at ends (unless make cache n*256bytes)
		char *ptr = audio_buffer;
		for (int i = 0; i < 64; i++) {
			*ptr = *Cache_Read;
			ptr++;
			Cache_Read++;
			Cache_Free++;
			if (Cache_Read > Cache_End)
				Cache_Read = Cache_Start;
			if (Cache_Free == CACHE_SIZE) break;
		}
		
		//If can't output to the soundcard, we have a problem!
		if (write (audio, audio_buffer, write_count) != write_count) {
			cout << "FATAL: Failed to write all of buffer" << endl;
			exit(-1);
		}
		
	} while(true); // just keep on going...
	delete audio_buffer;
}

/* Returns the current playback position in milliseconds
 */
long playout::getPosition_ms() {
    return (long)(floor(b_current_pos / 176.4));
}

long playout::getLength_ms() {
	return (long)(floor(b_current_length / 176.4));
}

/* ========================================
 * DUMMY FUNCTIONS
 * This is to allow multithreading in the object
 * ========================================
 */

/* Dummy function to initialise the thread for caching audio
 * NOTE: This is not currently used. Only playback runs on a separate thread
 */
void *thread_fill_cache(void *ptr) {
	playout *P = (playout*)ptr;	
	P->cache();
	pthread_exit(NULL);
}

/* Dummy function to initialise the thread for playing back.
 */
void *thread_play_cache(void *ptr) {
	playout *P = (playout*)ptr;
	P->play_cache();
	pthread_exit(NULL);
}

/* Dummy function to initialise the thread for caching crossfade
 */
void *thread_fill_cache_crossfade(void *ptr) {
	playout *P = (playout*)ptr;
	P->cache_crossfade();
	pthread_exit(NULL);
}


/* ======================================
 * HELPFUL FUNCTIONS
 * Useful functions such as getting file length and pretty time
 * ======================================
 */

/* Returns the file length of given file
 * TODO: Implement
 */
long playout::getFileLength(string *md5) {

}

/* Returns the length of a file in ms
 * TODO: Implement
 */
long playout::getFileLength_ms(string *md5) {

}

/* Returns the title of a given md5
 */
string playout::getFileTitle(string *md5) {
	string SQL;
	Result R;
	
	SQL = "SELECT title FROM audio WHERE md5='" + *md5 + "'";
	R = T->exec(SQL);
	if (R.size() > 0) return (string)(R[0][0].c_str());
//	SQL = "SELECT title FROM jingles WHERE md5='" + *md5 + "'";
//	R = T->exec(SQL);
//	if (R.size() > 0) return (string)(R[0][0].c_str());
//	SQL = "SELECT title FROM adverts WHERE md5='" + *md5 + "'";
//	R = T->exec(SQL);
//	if (R.size() > 0) return (string)(R[0][0].c_str());
	return "Unknown";
}
