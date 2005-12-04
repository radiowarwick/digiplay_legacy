#include "audiochannel.h"

audiochannel::audiochannel() {
	// first we configure the cache
	Cache_Start = new char[ CACHE_SIZE ];
    if (Cache_Start == NULL) {
        cout << "ERROR: Cannot Allocate Cache." << endl;
        exit (-1);
    }
    Cache_End = Cache_Start + CACHE_SIZE;
    Cache_Read = Cache_Start;
    Cache_Write = Cache_Start;
    Cache_Free = CACHE_SIZE;

	f_pos_byte = 0;
	f_start_byte = 0;
	f_end_byte = 0;
	f_length_byte = 0;
	
	// create the file stream object for reading audio files
	f_handle = new ifstream();

	// create the pthread object for multithreading the caching of audio
	Thread_Cache = new pthread_t;
	
	// allocate memory for the audio output buffer - getAudio()
    audio_buffer = new char[256];

	// we don't want to try to output audio from the cache yet
	// false => zero magnitude samples are output in getAudio()
	// true  => samples from the audio buffer are output
	mode_play = false;

	// Initialise default values
	// By default, channel is used as a "play-once" type so don't auto-reload
	auto_reload = false;
	f_counters = NULL;
	f_obj = NULL;

	fades = new vector<fadeSpecification*>;
	trigs = new vector<triggerSpecification*>;
}

audiochannel::~audiochannel() {
	delete Cache_Start;
	f_handle->close();
	delete f_handle;
	delete Thread_Cache;
	delete[] audio_buffer;
}

/** Loads an audio track into the channel.  The file is not
 * pre-cached until playback is started.
 * @param filename the full path to the file to load
 * @param start_smpl the first sample in the file to commence
 *                   playback with.  allows for skipping bits of
 *                   the track.
 * @param end_smpl the last sample to playback.
*/
void audiochannel::load(string filename, long start_smpl, long end_smpl) {
	if (filename == "") return;
	f_name = filename;
	
	// If we're currently playing, we need to stop and set counter to zero
	mode_play = false;
	mode_cache = false;

	if (f_counters) f_counters(0,f_obj);

	// Delete any fades and triggers that might be still around
	for (unsigned short i = 0; i < fades->size(); i++) {
		delete fades->at(i);
		fades->erase(fades->begin() + i);
	}
	for (unsigned short i = 0; i < trigs->size(); i++) {
		trigs->at(i)->ch->play();
		delete trigs->at(i);
		trigs->erase(trigs->begin() + i);
	}

	// Reset file stream, and load new file
	f_handle->close();
	f_handle->clear();
	f_handle->open(filename.c_str(), ios::in|ios::binary);
	f_handle->seekg(0,ios::end);
	
	// Set file position pointers
	f_length_byte = f_handle->tellg();
    f_start_byte = start_smpl * 4;
    f_end_byte = end_smpl * 4;
    f_pos_byte = f_start_byte;

    // Reset cache
    Cache_Read = Cache_Start;
    Cache_Write = Cache_Start;
    Cache_Free = CACHE_SIZE;

	// Begin new caching thread
	int ret_cache_thread = pthread_create(Thread_Cache, NULL,
                        thread_cache, (void*)this);
    if (ret_cache_thread != 0) {
        cout << "Error creating thread" << endl;
        return;
    }
}

/** Returns true if the channel has an audio track loaded and is good
 * for reading. If the file fails to be readable, or load has not been
 * called on an instance, then this will return false
 * @returns true if a track is loaded and good for reading
 */
bool audiochannel::isLoaded() {
	if (f_handle == NULL) return false;
	return (f_handle->is_open() && f_handle->good());
}

/** This specifies that the output should be from the audio file, as opposed
 * to null samples which are output when not playing
 */
void audiochannel::play() {
	mode_play = true;
}

/** Specifies that null samples should be output instead of audio from file
 * Audio counters are not reset, allowing playback to be resumed from the
 * current position.
 */
void audiochannel::pause() {
	mode_play = false;
}

/** Specifies to resume outputting the audio file from the previous position
 */
void audiochannel::resume() {
	mode_play = true;
}

/** The audio file is no longer output. All counters are reset.
 */
void audiochannel::stop() {
	// Stop playback - don't set mode_cache = false as this would end caching
	mode_play = false;

	// If auto reload is enabled (cd player type application)
	// then reload the track at the start.
	if (auto_reload) {	
		// Reset file and position to start of playback region
		if (f_counters) f_counters((f_pos_byte-f_start_byte)/4,f_obj);
	
		// Reload track
		load(f_name,f_start_byte,f_end_byte);
	}
}

/** Commences reading the audio file at a different position in the file,
 * resetting the cache so new audio begins outputting immediately.
 * @param position The position in samples to seek to
 */
void audiochannel::seek(long position) {
	f_handle->seekg(position * 4, ios::beg);
	f_pos_byte = position * 4;
	Cache_Write = Cache_Read;
	Cache_Free = CACHE_SIZE;
}

/** addCounter
 * @param f_setCounter Pointer to static function for callback
 */
void audiochannel::addCounter(void (*f_setCounter)(long,void*),void *obj) {
	f_counters = f_setCounter;
	f_obj = obj;
	if (f_counters) f_counters((f_pos_byte-f_start_byte)/4,f_obj);
}

/** Fills a user defined buffer with a user specified number of audio bytes
 * @param buffer Pointer to a user-allocated buffer
 * @param bytes The number of bytes to put into the buffer
 * @returns The number of bytes actually output (should match)
 */
short audiochannel::getAudio(char* buffer, unsigned long bytes) {
    char *ptr = buffer;
	short count = 0;
    for (unsigned long i = 0; i < bytes; i++) {
		if (mode_play && CACHE_SIZE - Cache_Free < 1024) {
			stop();
		}
    	if (!mode_play) {
			*ptr = 0;
		}
		else {
			*ptr = *Cache_Read;	
		    Cache_Read++;
        	Cache_Free++;
			f_pos_byte++;
		}
        ptr++;
		count++;
        if (Cache_Read > Cache_End)
            Cache_Read = Cache_Start; 
    }
	if (mode_play && f_counters)
		if ((f_pos_byte - (f_pos_byte % 64)) % 8192 == 0) 
			f_counters((f_pos_byte-f_start_byte)/4,f_obj);

	return count;
}

/** The position in the audio file will be the position at the end of the
 * last getAudio request.
 * @returns Position in samples of the current position in the audio file
 */
unsigned long audiochannel::getPos() {
	if (!mode_play) return 0;
	return f_pos_byte / 4;
}

/** Stores the parameters of a fade, so they can be accounted for in the
 * getVolume routine.
 * @param start_smpl Specifies the sample at which to start the fade
 * @param start_pct Specifies the percentage of maximum amplitude at which to
 * 					start the fade
 * @param end_smpl Specifies the sample at which the fade ends
 * @param end_pct Specifies the percentage of maximum amplitude at end
 */
void audiochannel::scheduleFade(unsigned long start_smpl, float start_pct, unsigned long end_smpl, float end_pct) {
    fadeSpecification *newfade = new fadeSpecification;
    newfade->start_smpl = start_smpl;
    newfade->start_pct = start_pct;
    newfade->end_smpl = end_smpl;
    newfade->end_pct = end_pct;
    newfade->started = false;
    fades->push_back(newfade);
}

/** Stores the parameters of a channel which is to be triggered at the 
 * correct time
 * @param smpl The sample at which to trigger the channel
 * @param ch A pointer to the channel which is to be triggered
 */
void audiochannel::scheduleTrigger(unsigned long smpl, audiochannel *ch) {
	triggerSpecification *newtrig = new triggerSpecification;
	newtrig->ch = ch;
	newtrig->smpl = smpl;
	trigs->push_back(newtrig);
}

/** @param vol The volume to apply
 */
void audiochannel::setVolume(float vol) {
	if (vol > 100.0) vol = 100.0;
	if (vol < 0.0) vol = 0.0;
	volume = vol;
}

/** Computes the intended volume of the channel, based on the current volume
 * and any fades which may have been scheduled. This is usually called by the
 * audiomixer to which the channel belongs when mixing together the audio.
 * @param smpl The sample for which the intended volume is requested
 * @returns The intended volume of the given sample
 */
float audiochannel::getVolume(unsigned long smpl) {
	float vol = volume;
	fadeSpecification *f;
	for (unsigned short k = 0; k < fades->size(); k++) {
    	f = fades->at(k);
        if (f->start_smpl < smpl && f->end_smpl > smpl){
           	vol = ((smpl - f->start_smpl)*(f->end_pct - f->start_pct))
                          /(f->end_smpl - f->start_smpl) + f->start_pct;
        	if (vol > 99.0) vol = 100.0;
        	if (vol < 1.0) vol = 0.0;
			fades->at(k)->started = true;
        }
		else if (f->started) {
			delete f;
			fades->erase(fades->begin() + k);
		}
	}
	volume = vol;
	return vol;
}

/** Determines if any scheduled triggers should trigger and if so, triggers
 * playback on the channel specified.
 * @param smpl The sample at which triggers should be considered
 */
void audiochannel::trigger(unsigned long smpl) {
	for (unsigned short i = 0; i < trigs->size(); i++) {
		if (smpl >= trigs->at(i)->smpl) {
			trigs->at(i)->ch->play();
			delete trigs->at(i);
			trigs->erase(trigs->begin() + i);
		}
	}
}

/** Sleeps (blocks execution of the calling thread) until playback of the
 * current file is complete.
 */
void audiochannel::notify() {
//	while (Cache_Free < CACHE_SIZE)
	while (mode_play)
		usleep(10000);
//	mode_play = false;
}

/** Sleeps (blocks execution of the calling thread) until caching of the
 * current file is complete. This is usually used to destroy the caching thread
 * safely. However, loading a new track before playback is complete will 
 * terminate the output of the current track as all parameters are reset on
 * load.
 */
void audiochannel::notify_cache() {
	if (!Thread_Cache) cout << "Thread is null" << endl;
	pthread_join(*Thread_Cache,NULL);
}

void audiochannel::cache() {
	// Seek to start byte in file
    f_handle->clear();
    f_handle->seekg(f_start_byte, ios::beg);

    // Cache track until cached what we want
    int read_bytes = 256;
    mode_cache = true;
    while (read_bytes == 256 && mode_cache) {
        //If caching has caught up with playback, wait for 100us.
        while (Cache_Free < 1024) {
            usleep(100);
        }
        //Check if we've reached the end point of the section to play
        if (f_end_byte - f_handle->tellg() < 256) {
            read_bytes = f_end_byte - f_handle->tellg();
            if (read_bytes == 0) break;
        }
        else read_bytes = 256;
		
		
        //Read from file into a 256byte buffer and get length read
        f_handle->read(audio_buffer,read_bytes);
        read_bytes = f_handle->gcount();

        //Check we actually read from file
        if (read_bytes == 0 && mode_cache) {
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
    mode_cache = false;
}

void *thread_cache(void *ptr) {
	((audiochannel*)ptr)->cache();
	pthread_exit(NULL);
}


