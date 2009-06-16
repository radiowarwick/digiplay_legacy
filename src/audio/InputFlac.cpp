#include <iostream>
using std::cout;
using std::endl;

#include "Counter.h"
#include "CircularCache.h"
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
    allCached = false;
}

InputFlac::~InputFlac() {

}


void InputFlac::load(string filename, long start_smpl, long end_smpl) {
    if (filename == "") throw -1;

    // If we're not stopped, change to a stopped state
    if (state != STATE_STOP) {
        // If all the audio fits into cache, no need to restart caching
        if (!allCached) stopCaching();
        
        // Change to stopped state.
        state = STATE_STOP;
        send(OUT0,STOP);
        updateStates(STATE_STOP);
    }

    if (f.is_open()) {
        f.close();
        f.clear();
    }
    f.open(filename.c_str(), ios::in|ios::binary);

    if (!f.good()) {
        cout << "Failed to open file [" << filename << "]" << endl;
        throw -1;
    }

    set_md5_checking(true);
    if (get_state() == FLAC__STREAM_DECODER_UNINITIALIZED) {
	    FLAC__StreamDecoderInitStatus retval = init();
        if(retval != FLAC__STREAM_DECODER_INIT_STATUS_OK) {
            fprintf(stderr, "ERROR: initializing decoder: %s\n", 
                                FLAC__StreamDecoderInitStatusString[retval]);
            throw -1;
        }
    }
    process_until_end_of_metadata();
    
    if (sample_rate != 44100) {
        cout << "Samplerate is incorrect: " << sample_rate << endl;
        throw -1;
    }
    if (channels != 2) {
        cout << "Number of channels are incorrect: " << channels << endl;
        throw -1;
    }
    if (bps != 16) {
        cout << "Sample bits are incorrect: " << bps << endl;
        throw -1;
    }

    // reset file length if given length doesn't match the actual file
    if (total_samples*4 < f_end_byte || f_end_byte == 0) {
        f_end_byte = total_samples*4 - f_start_byte;
    }

    // Initialise position variables, counters and reset cache
    f_filename = filename;
    f_start_byte = start_smpl * 4;
    f_end_byte = end_smpl * 4;
    f_length_byte = total_samples*4; //f_end_byte - f_start_byte;

    // If we're just resetting after a stop, try to seek to beginning of cache
    try {
        if (mCache->size() > f_length_byte) { 
//                    && mCache->size() != mCache->free()) {
            mCache->seek(-(f_pos_byte - f_start_byte));
        }
        else {
            throw -1;
        }
    }
    catch (int e) {
        // Otherwise clear the cache and start again
        mCache->clear();
    }
    f_pos_byte = f_start_byte;
    
    updateCounters(0);
    updateTotals(f_length_byte / 4);

    try {
        if (!allCached) startCaching();
    }
    catch (int e) {
        throw -1;
    }

    // Flag true if the whole track fits into cache
    // Can then ensure we only cache the audio once.
    allCached = (f_length_byte <= mCache->size()) ? true : false;
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
        if (!threadReceive(START)) {
            // purge any STOP commands while stopped
            threadReceive(STOP);
            usleep(10000);
            continue;
        }

        // Set caching state as active
        cacheStateLock.lock();
        cacheState = CACHE_STATE_ACTIVE;
        cacheStateLock.unlock();

        loaded = true;
        cachedBytes = 0;
        
        if (!seek_absolute((FLAC__uint64)(f_start_byte/4))) {
            cout << "Failed to seek" << endl;
        }
        
        /**************************************************
         * CACHE AUDIO FILE
         **************************************************/
        while ( !threadTestKill() &&            // Thread not terminated
                !threadReceive(STOP)) {         // Not told to stop
            
            // Handle seek requests first
            if (threadReceive(SEEK)) {
                mCache->clear();
                f_pos_byte = f_seek_byte;
                cachedBytes = f_seek_byte;
                seek_absolute((FLAC__uint64)(f_seek_byte/4));
            }

            // get_blocksize() returns number of samples in a frame, so the
            // number of bytes is 4*get_block_size(). We pause caching when
            // free cache drops to below twice this.
            if (mCache->free() < 8*get_blocksize() 
                    || get_state() == FLAC__STREAM_DECODER_END_OF_STREAM
                    || cachedBytes >= f_length_byte) {
                usleep(100);
                continue;
            }
            
            // Process a frame of the FLAC content
            if (!process_single()) {
                cout << "A fatal error occured: "
                        << get_state() << endl;
                flush();
                continue;
            }

            if (mCache->size() - mCache->free() > preCacheSize) {
                usleep(100);
            }            
        }
        finish();

        // Set cache state to inactive
        cacheStateLock.lock();
        cacheState = CACHE_STATE_INACTIVE;
        cacheStateLock.unlock();
    }
}

::FLAC__StreamDecoderReadStatus InputFlac::read_callback(FLAC__byte buffer[], size_t *bytes) {
    if (f.eof()) {
        return FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM;
    }
    if (*bytes != 0) {
        f.read((char*)buffer, *bytes);
        *bytes = f.gcount();
        return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
    }
    return FLAC__STREAM_DECODER_READ_STATUS_ABORT;
}

::FLAC__StreamDecoderSeekStatus InputFlac::seek_callback(FLAC__uint64 absolute_byte_offset) {
    // If we'd finished caching the file, need to reset.
    if (f.eof()) {
        f.clear();
    }
    
    // Seek to the correct position.
    f.seekg(absolute_byte_offset);
    
    // Return state of stream.
    if (f.good()) {
        return FLAC__STREAM_DECODER_SEEK_STATUS_OK;
    }
    return FLAC__STREAM_DECODER_SEEK_STATUS_ERROR;
}

::FLAC__StreamDecoderTellStatus InputFlac::tell_callback (FLAC__uint64 *absolute_byte_offset) {
    *absolute_byte_offset = (FLAC__uint64)(f.tellg());
    return FLAC__STREAM_DECODER_TELL_STATUS_OK;
}

::FLAC__StreamDecoderLengthStatus InputFlac::length_callback (FLAC__uint64 *stream_length) {
    unsigned long pos = f.tellg();
    f.seekg(0,ios::end);
    *stream_length = (FLAC__uint64)(f.tellg());
    f.seekg(pos,ios::beg);
    return FLAC__STREAM_DECODER_LENGTH_STATUS_OK;
}

bool InputFlac::eof_callback () {
    return f.eof();
}
        
::FLAC__StreamDecoderWriteStatus InputFlac::write_callback(
            const::FLAC__Frame *frame, const FLAC__int32 *const buffer[]) {
    size_t i;
    
    char * frameBuffer = new char[frame->header.blocksize*4];

    /* write decoded PCM samples */
    char * ptr = frameBuffer;
    for(i = 0; i < frame->header.blocksize; i++) {
        *(ptr++) = (FLAC__int16)buffer[0][i];
        *(ptr++) = ((FLAC__int16)buffer[0][i]) >> 8;
        *(ptr++) = (FLAC__int16)buffer[1][i];
        *(ptr++) = ((FLAC__int16)buffer[1][i]) >> 8;
    }

    mCache->write(frame->header.blocksize*4, frameBuffer);

    delete[] frameBuffer;
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
    }
}

void InputFlac::error_callback(::FLAC__StreamDecoderErrorStatus status) {
    fprintf(stderr, "Got error callback: %s\n", FLAC__StreamDecoderErrorStatusString[status]);
	return;
}

