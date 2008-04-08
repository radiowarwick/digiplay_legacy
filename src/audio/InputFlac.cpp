#include <iostream>
using std::cout;
using std::endl;

#include "Counter.h"
#include "InputFlac.h"
using Audio::InputFlac;

InputFlac::InputFlac() {
    state = STATE_STOP;
    cacheState = CACHE_STATE_INACTIVE;
    loaded = false;
    autoReload = true;

	// Configure cache
	cacheSize = 1760000;
	cacheStart = new char[cacheSize];
	if (cacheStart == 0) {
		cout << "ERROR: Cannot allocate memory for cache" << endl;
		exit(-1);
	}
	cacheEnd = cacheStart + cacheSize;
	cacheRead = cacheStart;
	cacheWrite = cacheStart;
	cacheFree = cacheSize;

    // Start caching thread
    int retval = threadStart();
    if (retval != 0) {
        cout << "ERROR: Error creating thread. Error code: " << retval << endl;
        throw -1;
    }
}

InputFlac::~InputFlac() {

}

void InputFlac::getAudio(AudioPacket* audioData) {
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

void InputFlac::load(string filename, long start_smpl, long end_smpl) {
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

	FLAC__StreamDecoderInitStatus retval = init(filename);
    if(retval != FLAC__STREAM_DECODER_INIT_STATUS_OK) {
        fprintf(stderr, "ERROR: initializing decoder: %s\n", FLAC__StreamDecoderInitStatusString[retval]);
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

void InputFlac::play() {
	state = STATE_PLAY;
	send(OUT0,PLAY);
}

void InputFlac::stop() {
	state = STATE_STOP;
	send(OUT0,STOP);
}

void InputFlac::pause() {
	state = STATE_PAUSE;
	send(OUT0,PAUSE);
}

void InputFlac::seek(long sample) {
	sample -= (sample % 64);		//WTF is this?
	bool retval = seek_absolute((FLAC__uint64)(sample));
	if (!retval)
		cout << "Error seeking to stream position " << sample << endl;
	cacheWrite = cacheRead;
	cacheFree = cacheSize;
}

void InputFlac::addCounter(Audio::Counter *counter) {
	vector<Audio::Counter *>::iterator i 
		= find(countersList.begin(), countersList.end(), counter);
	if (i == countersList.end()) {
		countersList.push_back(counter);
	}
}

void InputFlac::removeCounter(Audio::Counter *counter) {
	vector<Audio::Counter *>::iterator i 
		= find(countersList.begin(), countersList.end(), counter);
	if (i != countersList.end()) {
		countersList.erase(i);
	}
	else {
		cout << "Counter does not exist" << endl;
	}
}

/**
 * Updates the current sample on all attached Counters.
 * @param   sample      The current sample
 */
void InputFlac::updateCounters(unsigned long sample) {
    for (unsigned int i = 0; i < countersList.size(); i++) {
        countersList.at(i)->setSample(sample);
    }
}


/**
 * Updates the total number of samples on all attached Counters.
 * @param   samples     The total number of samples
 */
void InputFlac::updateTotals(unsigned long samples) {
    for (unsigned int i = 0; i < countersList.size(); i++) {
        countersList.at(i)->setTotalSamples(samples);
    }
}


/**
 * Updates the state on all attached Counters.
 * @param   state       The current state.
 */
void InputFlac::updateStates(enum STATE state) {
    for (unsigned int i = 0; i < countersList.size(); i++) {
        countersList.at(i)->setState(state);
    }
}

/**
 * Performs checks and starts caching of audio. If caching is currently
 * active, it is first stopped. Once caching is started, execution is blocked
 * until the cache is filled to a predefined size.
 */
void InputFlac::startCaching() {
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
void InputFlac::stopCaching() {
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
void InputFlac::receiveMessage(PORT inPort, MESSAGE message) {

}


/**
 * Perform tasks when a component connects to this component
 * @param   localPort   Port to which another component connects.
 */
void InputFlac::onPatch(PORT localPort) {

}


/**
 * Perform tasks when a component disconnects from this component
 * @param   localPort   Port on which another component has disconnected
 */
void InputFlac::onUnpatch(PORT localPort) {

}


void InputFlac::threadExecute() {

    while (!threadTestKill()) {
        // Wait until told to start caching a file
        while (!threadReceive(START)) {
            // purge any STOP commands while stopped
            threadReceive(STOP);
            usleep(10000);
        }

        // Set caching state as active
        cacheStateLock.lock();
        cacheState = CACHE_STATE_ACTIVE;
        cacheStateLock.unlock();

        loaded = true;
        
        seek_absolute((FLAC__uint64)(f_start_byte/4));
        
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
                seek_absolute((FLAC__uint64)(f_seek_byte/4));
            }
            
            if (cacheFree < 128000) {
                cacheLock.unlock();
                usleep(10000);
                continue;
            }
            
            // Process a frame of the FLAC content
            if (!process_single()) {
                cout << "A fatal error occured.  Its now dead." <<endl;
                cacheLock.unlock();
                continue;
            }


            // Unlock the cache to allow audio to be read out
            cacheLock.unlock();
            
        }

        // Unlock the cache
        cacheLock.unlock();
        
        // Set cache state to inactive
        cacheStateLock.lock();
        cacheState = CACHE_STATE_INACTIVE;
        cacheStateLock.unlock();
    }
}

::FLAC__StreamDecoderWriteStatus InputFlac::write_callback(
            const::FLAC__Frame *frame, const FLAC__int32 *const buffer[]) {
    size_t i;
                    
    /* write decoded PCM samples */
    for(i = 0; i < frame->header.blocksize; i++) {
        *(cacheWrite++) = (FLAC__int16)buffer[0][i];
        cacheFree--;
        if (cacheWrite > cacheEnd) {
            cacheWrite = cacheStart;
        }
        *(cacheWrite++) = ((FLAC__int16)buffer[0][i]) >> 8;
        cacheFree--;
        if (cacheWrite > cacheEnd) {
            cacheWrite = cacheStart;
        }
        *(cacheWrite++) = (FLAC__int16)buffer[1][i];
        cacheFree--;
        if (cacheWrite > cacheEnd) {
            cacheWrite = cacheStart;
        }
        *(cacheWrite++) = ((FLAC__int16)buffer[1][i]) >> 8;
        cacheFree--;
        if (cacheWrite > cacheEnd) {
            cacheWrite = cacheStart;
        }
    }
    
    return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

void InputFlac::metadata_callback(const::FLAC__StreamMetadata *metadata) {
    /* print some stats */
    if(metadata->type == FLAC__METADATA_TYPE_STREAMINFO) {
        /* save for later */
        total_samples = metadata->data.stream_info.total_samples;
        sample_rate = metadata->data.stream_info.sample_rate;
        channels = metadata->data.stream_info.channels;
        bps = metadata->data.stream_info.bits_per_sample;

        fprintf(stderr, "sample rate    : %u Hz\n", sample_rate);
        fprintf(stderr, "channels       : %u\n", channels);
        fprintf(stderr, "bits per sample: %u\n", bps);
#ifdef _MSC_VER
        fprintf(stderr, "total samples  : %I64u\n", total_samples);
#else
        fprintf(stderr, "total samples  : %llu\n", total_samples);
#endif
    }
}

void InputFlac::error_callback(::FLAC__StreamDecoderErrorStatus status) {
    fprintf(stderr, "Got error callback: %s\n", FLAC__StreamDecoderErrorStatusString[status]);
	return;
}

