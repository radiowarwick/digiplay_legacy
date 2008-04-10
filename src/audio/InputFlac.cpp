#include <iostream>
using std::cout;
using std::endl;

#include "Counter.h"
#include "InputFlac.h"
using Audio::InputFlac;

InputFlac::InputFlac(unsigned int cache_size) 
        : Input(cache_size) {
    // Start caching thread - this must be done from the derived class as
    // this can't be called from the base class - since this derived class
    // won't have been properly constructed yet. Calling threadExecute from
    // the base class Input, would actually call the base class' version.
    int retval = threadStart();
    if (retval != 0) {
        cout << "ERROR: Error creating thread. Error code: " << retval << endl;
        throw -1;
    }
}

InputFlac::~InputFlac() {

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
    
    process_until_end_of_metadata();
    if (sample_rate == 44100) {
        cout << "Samplerate is correct." << endl;
    }
    if (channels == 2) {
        cout << "Channels are correct." << endl;
    }
    if (bps == 16) {
        cout << "Sample bits are correct." << endl;
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

    updateCounters(0);
    updateTotals(f_length_byte/4);

    try {
        startCaching();
    }
    catch (int e) {
        throw -1;
    }
}

void InputFlac::seek(long sample) {
	sample -= (sample % 64);
	bool retval = seek_absolute((FLAC__uint64)(sample));
	if (!retval)
		cout << "Error seeking to stream position " << sample << endl;
	cacheWrite = cacheRead;
	cacheFree = cacheSize;
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
        
        // reset file length if given length doesn't match the actual file
        if (total_samples < f_end_byte || f_end_byte == 0) {
            f_end_byte = total_samples - f_start_byte;
        }
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
/*
        fprintf(stderr, "sample rate    : %u Hz\n", sample_rate);
        fprintf(stderr, "channels       : %u\n", channels);
        fprintf(stderr, "bits per sample: %u\n", bps);
#ifdef _MSC_VER
        fprintf(stderr, "total samples  : %I64u\n", total_samples);
#else
        fprintf(stderr, "total samples  : %llu\n", total_samples);
#endif
*/
    }
}

void InputFlac::error_callback(::FLAC__StreamDecoderErrorStatus status) {
    fprintf(stderr, "Got error callback: %s\n", FLAC__StreamDecoderErrorStatusString[status]);
	return;
}

