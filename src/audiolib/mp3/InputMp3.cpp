#include "Counter.h"
#include "CircularCache.h"
#include "InputMp3.h"
using Audio::Input;
using Audio::InputMp3;
using std::cout;
using std::endl;

extern "C" {
    Input * INPUT_SO_ENTRY(unsigned int cache_size, Input *facade) {
        return new InputMp3(cache_size, facade);
    }
}

#define READ_PACKET 8192

/**
 * Creates a new MP3 input filereader. The size of the Cache to use may be
 * specified. If not specified, it defaults to 10 seconds.
 * @param   cache_size  Size of cache to use when caching file into memory.
 */
InputMp3::InputMp3(unsigned int cache_size, Input *facade) 
        : Input(cache_size) {

    readBuffer = new unsigned char[READ_PACKET];

    if(mpg123_init()!=MPG123_OK || !(mh=mpg123_new(NULL, &error)) ||
       mpg123_format_none(mh)!=MPG123_OK ||
       mpg123_format(mh, 44100, MPG123_STEREO, MPG123_ENC_SIGNED_16)!=MPG123_OK) {
        cout << "ERROR: MP3 decoder init failed" << endl;
        throw -1;
    }

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
    this->facade = facade;
}

/**
 * Closes MPG123 library, terminates cache thread
 */
InputMp3::~InputMp3() {
    mpg123_close(mh);
    mh = NULL;
    mpg123_exit();
    delete[] readBuffer;
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
void InputMp3::load(string filename, long start_smpl, long end_smpl) {
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

    // Close input stream, [re]open new file
    mpg123_close(mh);
    if (mpg123_open(mh, (char *)filename.c_str())!=MPG123_OK) {
        cout << "ERROR: Failed to open file: " << filename << endl;
        throw -1;
    }

    // Check format is acceptable (S16,44.1kHz,stereo)
    long rate;
    int chan, enc;
    if (mpg123_getformat(mh, &rate, &chan, &enc)!=MPG123_OK ||
       rate != 44100 || chan != 2 || enc != MPG123_ENC_SIGNED_16) {
       cout << "ERROR: MP3 not in acceptable format (S16,44.1kHz,stereo)" << endl;
       throw -1;
    }

    // Scan file to enable seeking and measure size
    off_t size;
    if (mpg123_scan(mh)!=MPG123_OK || (size=mpg123_length(mh))==MPG123_ERR) {
        cout << "ERROR: Unable to scan MP3 file" << endl;
        throw -1;
    }

    // Initialise position variables, counters and reset cache
    f_filename = filename;
    f_start_byte = start_smpl * 4;
    f_end_byte = end_smpl * 4;
    if (size*4 < (off_t)f_end_byte || f_end_byte==0) f_end_byte = size*4;
    f_length_byte = f_end_byte - f_start_byte;

    // If we're just resetting after a stop, try to seek to beginning of cache
    try {
        if (mCache->size() > f_length_byte) { 
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
    updateTotals(f_length_byte/4);
    
    try {
        // If first load or the whole track doesn't fit into cache then
        // start caching it
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
void InputMp3::receiveMessage(PORT inPort, MESSAGE message) {

}


/**
 * Perform tasks when a component connects to this component
 * @param   localPort   Port to which another component connects.
 */
void InputMp3::onPatch(PORT localPort) {

}


/**
 * Perform tasks when a component disconnects from this component
 * @param   localPort   Port on which another component has disconnected
 */
void InputMp3::onUnpatch(PORT localPort) {

}

/**
 * Cache thread
 */
void InputMp3::threadExecute() {
    while (!threadTestKill()) {
        bool atEnd = false;

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

        // Seek to requested start byte
        if (mpg123_seek(mh, f_start_byte/4, SEEK_SET)==MPG123_ERR) {
            cout << "WARNING: Failed to seek in InputMp3::threadExecute: " <<
                mpg123_plain_strerror(error) << endl;
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
                mpg123_seek(mh, f_seek_byte/4, SEEK_SET);
                atEnd = false;
            }

            // We pause caching when free cache drops to below twice READ_PACKET,
            // or we have reached the end of file
            if (mCache->free() < 2*READ_PACKET || atEnd) {
                usleep(100);
                continue;
            }

            // Read a block of decoded MP3 data and add to cache
            size_t len;
            if (mpg123_read(mh, readBuffer, READ_PACKET, &len)!=MPG123_OK)
                atEnd = true;
            else
                mCache->write(len, (const char *)readBuffer);

            if (mCache->size() - mCache->free() > preCacheSize) {
                usleep(100);
            }            
        }

        // Set cache state to inactive
        cacheStateLock.lock();
        cacheState = CACHE_STATE_INACTIVE;
        cacheStateLock.unlock();
    }
}
