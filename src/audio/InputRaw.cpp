#include <iostream>
using std::cout;
using std::endl;

#include "Counter.h"
#include "InputRaw.h"
using Audio::InputRaw;

InputRaw::InputRaw(unsigned int cache_size) {
    // default state is stopped, no caching, no cache command
	state = STATE_STOP;
    cacheState = CACHE_STATE_INACTIVE;
    cacheCommand = CACHE_COMMAND_NONE;
    
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

	audioBuffer = new char[2048];
	autoReload = true;
    
    // Start caching thread
    int retval = threadStart();
    if (retval != 0) {
        cout << "ERROR: Error creating thread. Error code: " << retval << endl;
        throw -1;
    }
}

InputRaw::~InputRaw() {
    threadKill();
    threadWait();
    delete[] cacheStart;
    delete[] audioBuffer;
}

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
		if (cacheState == CACHE_STATE_INACTIVE) {
			//cout << "Flushing remainder of cache into buffer." << endl;
			bytes = cacheSize - cacheFree;
		}
		// if we're still caching, the cache has emptied, so stutter.
		else {
			//cout << "STUTTERING!!" << endl;
			cacheRead-=PACKET_BYTES;
			cacheFree-=PACKET_BYTES;
			f_pos_byte-=PACKET_BYTES;
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

	// if cache is completely empty, stop
	if (cacheSize == cacheFree) {
        if (f_end_byte - f_pos_byte > 256) {
            cout << "WARNING: Ran out of cached audio before end of file." << endl;
        }
        // First unlock the cache before we attempt to stop
        cacheLock.unlock();
        
        // Stop the caching and reset
		stop();
	}
	else {
	    // Just unlock the cache
	    cacheLock.unlock();
    }
    
	// if we're playing, update all the attached counters with our current
	// position in terms of stereo samples.
    if (state == STATE_PLAY) {
        updateCounters(pos);
    }

    return;
}

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

	f.close();
	f.clear();

	// Open the new file and check it's good to read
	f.open(filename.c_str(), ios::in|ios::binary);
	if (f.is_open() && f.good() == false) {
        cout << "Failed to open file '" << filename << "'" << endl;
        throw -1;
    }
	
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

void InputRaw::play() {
	state = STATE_PLAY;
	send(OUT0,PLAY);
	updateStates(STATE_PLAY);
}

void InputRaw::stop() {
    stopCaching();
    
    // Change to stopped state.
	state = STATE_STOP;
	send(OUT0,STOP);
	updateStates(STATE_STOP);
    
    // Reload track if required.
    if (autoReload) load(f_filename, f_start_byte/4, f_end_byte/4);
}

void InputRaw::pause() {
	state = STATE_PAUSE;
	send(OUT0,PAUSE);
	updateStates(STATE_PAUSE);
}

void InputRaw::seek(long sample) {
	sample -= (sample % 64);
	f_pos_byte = sample*4;
	f.seekg(f_pos_byte, ios::beg);
	long pos = static_cast<long>((f_pos_byte - f_start_byte) / 4);
	updateCounters(pos);
    
    cacheLock.lock();
	cacheWrite = cacheRead;
	cacheFree = cacheSize;
    cacheLock.unlock();
}

bool InputRaw::isLoaded() {
	return (f.is_open() && f.good());
}

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

void InputRaw::updateCounters(unsigned long sample) {
	for (unsigned int i = 0; i < countersList.size(); i++) {
		countersList.at(i)->setSample(sample);
	}
}

void InputRaw::updateTotals(unsigned long samples) {
	for (unsigned int i = 0; i < countersList.size(); i++) {
		countersList.at(i)->setTotalSamples(samples);
	}
}

void InputRaw::updateStates(enum STATE state) {
	for (unsigned int i = 0; i < countersList.size(); i++) {
		countersList.at(i)->setState(state);
	}
}

void InputRaw::startCaching() {
    cacheStateLock.lock();

    // Check if we're already caching
    if (cacheState == CACHE_STATE_ACTIVE) {
        cout << "Want to start caching, but caching is already active!" << endl;
        cacheStateLock.unlock();
        stopCaching();
    }
    
    // Issue caching start command
    cacheCommand = CACHE_COMMAND_GO;
    
    cacheStateLock.unlock();
    
    // Amount to ensure cache before completing load
    unsigned long preCacheSize = 441000;
    
    // Wait until the cache has preCacheSize audio or all audio,
    // whichever is smaller
    while ( cacheSize - cacheFree < preCacheSize 
            && cacheSize - cacheFree < f_length_byte) {
        usleep(1000);
    }    
}

void InputRaw::stopCaching() {
    cacheStateLock.lock();

    // if we're still caching, instruct to stop caching
    if (cacheState == CACHE_STATE_ACTIVE) {
        cacheCommand = CACHE_COMMAND_STOP;
    }
    
    // Wait until we've actually stopped caching
    while (cacheState == CACHE_STATE_ACTIVE) {
        cacheStateLock.unlock();
        usleep(10000);
        cacheStateLock.lock();
    }
    
    cacheStateLock.unlock();
}

void InputRaw::receiveMessage(PORT inPort, MESSAGE message) {

}

void InputRaw::onConnect(PORT localPort) {

}

void InputRaw::onDisconnect(PORT localPort) {

}

void InputRaw::threadExecute() {
    // Start of the caching thread. Only one thread is run during the
    // lifetime of this object.
    while (!threadTestKill()) {
        cacheStateLock.lock();

        // Wait until we're told to start caching
        while (cacheCommand != CACHE_COMMAND_GO
                && !threadTestKill()) {
            cacheStateLock.unlock();
            usleep(10000);
            cacheStateLock.lock();
        }
        cacheState = CACHE_STATE_ACTIVE;
        cacheCommand = CACHE_COMMAND_NONE;

        cacheStateLock.unlock();
        
        // Start caching open file
    	f.clear();
    	f.seekg(f_start_byte, ios::beg);
    
    	unsigned int READ_PACKET = 2048;
    	unsigned int read_bytes = READ_PACKET;
    	char *ptr;
    
    	while (read_bytes == READ_PACKET              // Not end of file
                && cacheCommand != CACHE_COMMAND_STOP // Not told to stop
                && !threadTestKill()                  // Thread not terminated
                && threadReceive() != STOP) {         // Not told to stop

    		cacheLock.lock();
    		
    		if (cacheFree < READ_PACKET * 2) {
    			cacheLock.unlock();
    			usleep(10000);
    			continue;
    		}
    		
    		if (f_end_byte - f.tellg() < READ_PACKET) {
    			read_bytes = f_end_byte - f.tellg();
    			if (read_bytes == 0) break;
    		}
    
    		f.read(audioBuffer, read_bytes);
    		read_bytes = f.gcount();
    
    		if (read_bytes == 0) {
    			cout << "ERROR: Unable to read from file or unexpected end" 
    				<< endl;
    			break;
    		}
    		
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
    		
    		cacheLock.unlock();
    		
    		//Bandwidth limiting on caching of audio to prevent hanging/stuttering
    		//during caching operations - to be decided on after testing...
    		//Assuming it takes 0 time to cache audio, theoretical thoughput of
    		//2048kbytes/sec is possible.  Since only 176kbytes/sec are
    		//required this should be plenty.
    		//usleep(1000);
    	}
    	cacheLock.unlock();
        
        // Reset cache state to inactive
        cacheStateLock.lock();
        cacheState = CACHE_STATE_INACTIVE;
        cacheCommand = CACHE_COMMAND_NONE;
        cacheStateLock.unlock();
    }
}
