#include <iostream>
using std::cout;
using std::endl;

#include "Counter.h"
#include "InputRaw.h"
using Audio::InputRaw;

#define READ_PACKET 8192

/**
 * Creates a new raw PCM input filereader. The size of the Cache to use may be
 * specified. If not specified, it defaults to 10 seconds.
 * @param   cache_size  Size of cache to use when caching file into memory.
 */
InputRaw::InputRaw(unsigned int cache_size) {
    // default state is stopped, no caching, no cache command
	state = STATE_STOP;
    cacheState = CACHE_STATE_INACTIVE;
    loaded = false;
    autoReload = true;

    // Amount to ensure cache before completing load
    preCacheSize = 441000;
        
	// Configure cache to the appropriate size
	cacheSize = cache_size;
	cacheStart = new char[cacheSize];
	if (cacheStart == 0) {
		cout << "ERROR: Cannot allocate memory for cache" << endl;
		exit(-1);
	}
	cacheEnd = cacheStart + cacheSize;
	cacheRead = cacheStart;
	cacheWrite = cacheStart;
	cacheFree = cacheSize;

	f_pos_byte = 0;
	f_start_byte = 0;
	f_end_byte = 0;
	f_length_byte = 0;

	audioBuffer = new char[READ_PACKET];
    
    // Start caching thread
    int retval = threadStart();
    if (retval != 0) {
        cout << "ERROR: Error creating thread. Error code: " << retval << endl;
        throw -1;
    }
}


/**
 * Terminates the caching thread and cleans up memory used.
 */
InputRaw::~InputRaw() {
    threadKill();
    threadWait();
    delete[] cacheStart;
    delete[] audioBuffer;
}


/**
 * Fills the supplied AudioPacket with audio data from the cache.
 * @param   audioData   AudioPacket to fill.
 */
void InputRaw::getAudio(AudioPacket* audioData) {
    // Fills audioData with the requested number of samples
    char *ptr = (char*)(audioData->getData());
    unsigned long bytes = PACKET_BYTES;
	// pos is in stereo samples
    long pos = static_cast<long>((f_pos_byte - f_start_byte) / 4);
    short count = 0;
    
    // lock the cache while we read a packet from it
	cacheLock.lock();

	// Check if there is enough audio in cache to fill packet	
	if (cacheSize - cacheFree < bytes) {
		// if we've finished caching, just empty the remaining data
		if (f_end_byte - f_pos_byte < bytes) {
			//cout << "Flushing remainder of cache into buffer." << endl;
			bytes = cacheSize - cacheFree;
		}
		// if we're still caching, the cache has emptied, so stutter.
		else {
			//cacheRead-=PACKET_BYTES;
			//cacheFree-=PACKET_BYTES;
			//f_pos_byte-=PACKET_BYTES;
		}
	}
	
	// Transfer the required number of samples to the audio packet
	// Advance cache pointers appropriately.
	for (unsigned long i = 0; i < PACKET_BYTES; i++) {
        if (state == STATE_STOP || bytes == 0) {
            *ptr = 0;
        }
        else {
            *ptr = *cacheRead;
            ++cacheRead;
            ++cacheFree;
            ++f_pos_byte;
			--bytes;
        	if (cacheRead > cacheEnd) {
				cacheRead = cacheStart;
			}
        }
        ++ptr;
        ++count;
    }
    
	// set the absolute position (relative to the start point) of this
	// block of audio in terms of stereo samples.
	audioData->setStart(pos);

    // if we're playing, update all the attached counters with our current
    // position in terms of stereo samples.
    if (state == STATE_PLAY) {
        updateCounters(pos);
    }

	// if cache is completely empty, stop
	if (cacheSize == cacheFree) {
        if (f_end_byte - f_pos_byte > 256) {
            cout << "WARNING: Ran out of cached audio before end of file." << endl;
        }
        // First unlock the cache before we attempt to stop
        cacheLock.unlock();
        
        // Update counters with the end sample position
        updateCounters(f_end_byte/4);
        
        // Stop the caching and reset
		stop();
	}
	else {
	    // Just unlock the cache
	    cacheLock.unlock();
    }
    
    return;
}


/**
 * Loads a new file. If there is a file currently playing, playback is first
 * stopped, and the component state set to STATE_STOP. The cache is then
 * reset, the new file is loaded and caching is started again. Execution is
 * blocked until the cache is filled to a preset level. An exception is thrown
 * if the file cannot be opened or caching does not start.
 * @param   filename    File to load
 * @param   start_smpl  First sample to start loading
 * @param   end_smpl    Last sample to load
 */
void InputRaw::load(string filename, long start_smpl, long end_smpl) {
    if (filename == "") throw -1;

	// If we're not stopped, change to a stopped state
    if (state != STATE_STOP) {
        stopCaching();
        
        // Change to stopped state.
        state = STATE_STOP;
        send(OUT0,STOP);
        updateStates(STATE_STOP);
    }

    // Lock cache to be safe
    cacheLock.lock();

	// Initialise position variables, counters and reset cache
    f_filename = filename;
	f_start_byte = start_smpl * 4;
	f_end_byte = end_smpl * 4;
	f_length_byte = f_end_byte - f_start_byte;
	f_pos_byte = f_start_byte;
	cacheRead = cacheStart;
	cacheWrite = cacheStart;
	cacheFree = cacheSize;

	cacheLock.unlock();

	if (countersList.size() > 0) {
		updateCounters(0);
		updateTotals(f_length_byte/4);
	}

    try {
        startCaching();
    }
    catch (int e) {
        throw -1;
    }
}


/**
 * Change component state to STATE_PLAY. This in turn triggers downstream
 * components to request audio from this component.
 */
void InputRaw::play() {
	state = STATE_PLAY;
	send(OUT0,PLAY);
	updateStates(STATE_PLAY);
}


/**
 * Change component state to STATE_STOP. This will in turn instruct downstream
 * components to stop requesting audio. The caching is then stopped and reset.
 * Subsequent playback will begin from the start of the loaded file. 
 */
void InputRaw::stop() {
    // Change to stopped state.
	state = STATE_STOP;
	send(OUT0,STOP);
	updateStates(STATE_STOP);

    // Stop caching audio    
    stopCaching();
    
    // Reload track if required.
    if (autoReload) {
        load(f_filename, f_start_byte/4, f_end_byte/4);
    }
}


/**
 * Change component state to STATE_PAUSE. This will in turn instruct downstream
 * components to stop requesting audio. Caching is not stopped, and playback
 * can continue from the same point.
 */
void InputRaw::pause() {
	state = STATE_PAUSE;
	send(OUT0,PAUSE);
	updateStates(STATE_PAUSE);
}


/**
 * Jump to another place in the file. The cache is emptied and caching restarts
 * from the new location. The cacheLock prevents the cache from being updated
 * while the change takes place. When the cache has been reset, the lock is
 * released and the new position is updated on all attached counters.
 * @param   sample      Stereo sample to jump to in file
 */
void InputRaw::seek(long sample) {
    cacheLock.lock();

	sample -= (sample % 64);
	f_seek_byte = sample*4;
	long pos = static_cast<long>((f_seek_byte - f_start_byte) / 4);
    updateCounters(pos);
    
    threadSend(SEEK);

    cacheLock.unlock();
}


/**
 * Determines if a file is currently loaded.
 * @returns             true if a file is currently loaded.
 */
bool InputRaw::isLoaded() {
	return loaded;
}


/**
 * Attaches a Counter component to this Component. Counters are updated
 * whenever audio is requested from this component or its state is changed.
 * @param   counter     Audio Counter to attach
 */
void InputRaw::addCounter(Audio::Counter *counter) {
	vector<Audio::Counter *>::iterator i 
		= find(countersList.begin(), countersList.end(), counter);
	if (i == countersList.end()) {
		countersList.push_back(counter);
        counter->setSample(0);
        counter->setTotalSamples(f_length_byte/4);
        counter->setState(state);
	}
}


/**
 * Remove an attached Counter.
 * @param   counter     The Audio Counter to remove
 */
void InputRaw::removeCounter(Audio::Counter *counter) {
	vector<Audio::Counter *>::iterator i 
		= find(countersList.begin(), countersList.end(), counter);
	if (i != countersList.end()) {
		countersList.erase(i);
	}
	else {
		cout << "WARNING: Counter does not exist" << endl;
	}
}


/**
 * Updates the current sample on all attached Counters.
 * @param   sample      The current sample
 */
void InputRaw::updateCounters(unsigned long sample) {
	for (unsigned int i = 0; i < countersList.size(); i++) {
		countersList.at(i)->setSample(sample);
	}
}


/**
 * Updates the total number of samples on all attached Counters.
 * @param   samples     The total number of samples
 */
void InputRaw::updateTotals(unsigned long samples) {
	for (unsigned int i = 0; i < countersList.size(); i++) {
		countersList.at(i)->setTotalSamples(samples);
	}
}


/**
 * Updates the state on all attached Counters.
 * @param   state       The current state.
 */
void InputRaw::updateStates(enum STATE state) {
	for (unsigned int i = 0; i < countersList.size(); i++) {
		countersList.at(i)->setState(state);
	}
}


/**
 * Performs checks and starts caching of audio. If caching is currently
 * active, it is first stopped. Once caching is started, execution is blocked
 * until the cache is filled to a predefined size.
 */
void InputRaw::startCaching() {
    cacheStateLock.lock();
    
    // If the cache is already active, stop the caching
    if (cacheState == CACHE_STATE_ACTIVE) {
        cacheStateLock.unlock();
        stopCaching();
    }
    else {
        cacheStateLock.unlock();
    }
    
    // Start caching
    threadSend(START);
    
    // Wait until the cache has preCacheSize audio or all audio,
    // whichever is smaller
    while ( cacheSize - cacheFree < preCacheSize 
            && cacheSize - cacheFree < f_length_byte) {
        usleep(1000);
    }
}


/**
 * Terminates the caching of audio, and blocks execution until the cache
 * has responded and reaches a CACHE_STATE_INACTIVE state.
 */
void InputRaw::stopCaching() {
    // if we're still caching, instruct to stop caching
    cacheStateLock.lock();
    if (cacheState == CACHE_STATE_ACTIVE) {
        threadSend(STOP);
    }

    // Wait until we've actually stopped caching
    while (cacheState == CACHE_STATE_ACTIVE) {
        cacheStateLock.unlock();
        usleep(10000);
        cacheStateLock.lock();
    }
    cacheStateLock.unlock();
}


/**
 * Processes messages received from other audio components.
 * @param   inPort      Port on which message is received
 * @param   message     The message received
 */
void InputRaw::receiveMessage(PORT inPort, MESSAGE message) {

}


/**
 * Perform tasks when a component connects to this component
 * @param   localPort   Port to which another component connects.
 */
void InputRaw::onPatch(PORT localPort) {

}


/**
 * Perform tasks when a component disconnects from this component
 * @param   localPort   Port on which another component has disconnected
 */
void InputRaw::onUnpatch(PORT localPort) {

}


/**
 * Performs caching of audio. When this component is created, the caching
 * thread is started. It remains idle until a track is loaded at which point
 * the caching of audio begins. When requested to stop caching, the cache is
 * reset and the thread returns to an idle state until requested to start
 * again.
 */
void InputRaw::threadExecute() {
    // Start of the caching thread. Only one thread is run during the
    // lifetime of this object.
    ifstream *f = 0;
    unsigned int read_bytes = READ_PACKET;
    char *ptr = 0;
    
    while (!threadTestKill()) {

        // Wait until told to start caching a file
        while (!threadReceive(START)) {
            // purge any STOP commands while stopped
            threadReceive(STOP);
            usleep(10000);
        }
        
        // Open the file and check it's good to read
        // if not, loop around and wait to be told to start again
        // (hopefully with a new file)
        f = new ifstream(f_filename.c_str(), ios::in|ios::binary);
        if (!f) {
            cout << "Unable to create file object" << endl;
            continue;
        }
        if (f->is_open() && f->good() == false) {
            cout << "Failed to open file '" << f_filename << "'" << endl;
            continue;
        }

        // Set caching state as active
        cacheStateLock.lock();
        cacheState = CACHE_STATE_ACTIVE;
        cacheStateLock.unlock();

        loaded = true;
        
        // Get file length and reset
        f->seekg(0, ios::end);
        if (f->tellg() < f_end_byte || f_end_byte == 0) {
            f_end_byte = f->tellg();
        }

        f->clear();
    	f->seekg(f_start_byte, ios::beg);

        
        /**************************************************
         * CACHE AUDIO FILE
         **************************************************/
    	while ( !threadTestKill() &&            // Thread not terminated
                !threadReceive(STOP)) {         // Not told to stop
            // Lock the cache
    		cacheLock.lock();
            
            // Handle seek requests first
            if (threadReceive(SEEK)) {
                cacheRead = cacheStart;
                cacheWrite = cacheStart;
                cacheFree = cacheSize;
                f_pos_byte = f_seek_byte;
                f->seekg(f_seek_byte, ios::beg);
            }
            
            // Sleep if cache is full
    		if (cacheFree < READ_PACKET * 2) {
    			cacheLock.unlock();
    			usleep(10000);
    			continue;
    		}
    		
            // Default number of bytes to read
            read_bytes = READ_PACKET;
            
            // If we have less than this, work out how many bytes left to read
    		if (f_end_byte - f->tellg() < READ_PACKET) {
    			read_bytes = f_end_byte - f->tellg();
                // If there are in fact no bytes, then we're at the end
                // So just keep sleeping until told to stop
                // This allows the user to seek while it's still playing
    			if (read_bytes == 0) {
                    cacheLock.unlock();
                    usleep(10000);
                    continue;
                }
    		}

            // Read the audio from the file into a temp buffer
    		f->read(audioBuffer, read_bytes);
            
            // See how many bytes we actually read
    		read_bytes = f->gcount();
    
            // If we didn't read any, then sleep (although an error must have occured!)
    		if (read_bytes == 0) {
                cacheLock.unlock();
                usleep(10000);
    			continue;
    		}

            // Copy the read audio into the cache
    		ptr = audioBuffer;
    		for (unsigned int i = 0; i < read_bytes; i++) {
    			*cacheWrite = *ptr;
    			++cacheWrite;
    			++ptr;
    			--cacheFree;
    			if (cacheWrite > cacheEnd) {
    				cacheWrite = cacheStart;
    			}
    		}

            // Unlock the cache to allow audio to be read out
            cacheLock.unlock();
    		
    		//Bandwidth limiting on caching of audio to prevent hanging/stuttering
    		//during caching operations - to be decided on after testing...
    		//Assuming it takes 0 time to cache audio, theoretical thoughput of
    		//2048kbytes/sec is possible.  Since only 176kbytes/sec are
    		//required this should be plenty.
    		//if (cacheSize - cacheFree > preCacheSize) {
            //    usleep(1000);
            //}            
    	}

        // Unlock the cache
        cacheLock.unlock();
        
        // Close the file and delete
        loaded = false;
        f->close();
        delete f;
        
        // Set cache state to inactive
        cacheStateLock.lock();
        cacheState = CACHE_STATE_INACTIVE;
        cacheStateLock.unlock();
    }
}
