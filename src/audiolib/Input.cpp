#include <iostream>
#include <algorithm>
#include <unistd.h>
using namespace std;

#include <cstring>
#include "Input.h"
#include "CircularCache.h"
#include "Counter.h"
using namespace Audio;

/**
 * Constructor. Initialises the cache and audio parameters for input source.
 */
Input::Input(unsigned int cache_size) {
    // default state is stopped, no caching, no cache command
    state = STATE_STOP;
    cacheState = CACHE_STATE_INACTIVE;
    loaded = false;
    autoReload = true;

    // Amount to ensure cache before completing load
    preCacheSize = 441000;

    // Configure cache to the appropriate size
    mCache = new CircularCache(cache_size);

    f_pos_byte = 0;
    f_start_byte = 0;
    f_end_byte = 0;
    f_length_byte = 0;
}


/**
 * Destructor. Terminates the caching thread, and deletes the cache.
 */
Input::~Input() {
    threadKill();
    threadWait();
    delete mCache;
}


/**
 * Fills the supplied AudioPacket with audio data from the cache.
 * @param   audioData   AudioPacket to fill.
 */
void Input::getAudio(AudioPacket* audioData) {
    // Fills audioData with the requested number of samples
    char *ptr = (char*)(audioData->getData());
    unsigned long bytes = PACKET_BYTES;
    unsigned long bytes_out = bytes;
    
    // pos is in stereo samples
    long pos = static_cast<long>((f_pos_byte - f_start_byte) / 4);

    if ((bytes_out = mCache->read(bytes, ptr)) != bytes) {
        // Failed to read a full packet from cache.
		memset(ptr + bytes_out, 0, bytes-bytes_out);
    }
    f_pos_byte += bytes_out;

    // block of audio in terms of stereo samples.
    audioData->setStart(pos);

    // if we're playing, update all the attached counters with our current
    // position in terms of stereo samples.
    if (state == STATE_PLAY) {
        updateCounters(pos);
    }

    // if cache is completely empty, stop
    if (mCache->free() == mCache->size()) {
        if (long(f_end_byte) - long(f_pos_byte) > 256) {
            cout << "WARNING: Ran out of cached audio before end of file." 
                 << long(f_end_byte) - long(f_pos_byte) << endl;
        }
        
        // Update counters with the end sample position
        updateCounters(f_length_byte/4);
        
        // Stop the caching and reset
        stop();
    }
    
    return;
}

void Input::receiveMessage(PORT inPort, MESSAGE message) {
    cout << "Input::receive" << endl;
}

/**
 * Change component state to STATE_PLAY. This in turn triggers downstream
 * components to request audio from this component.
 */
void Input::play() {
    state = STATE_PLAY;
    send(OUT0,PLAY);
    updateStates(STATE_PLAY);
}


/**
 * Change component state to STATE_STOP. This will in turn instruct downstream
 * components to stop requesting audio. The caching is then stopped and reset.
 * Subsequent playback will begin from the start of the loaded file. 
 */
void Input::stop() {
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
void Input::pause() {
    state = STATE_PAUSE;
    send(OUT0,PAUSE);
    updateStates(STATE_PAUSE);
}


/**
 * Jump to another place in the file. The cache is emptied and caching restarts
 * from the new location.
 * @param   sample      Stereo sample to jump to in file
 */
void Input::seek(long sample) {
    // Round sample to nearest 64.
    sample -= (sample % 64);
    
    // Compute the file offset.
    f_seek_byte = sample*4 + f_start_byte;
    
    // Update counters.
    long pos = static_cast<long>(sample);
    updateCounters(pos);
    
    // Seek audio stream.
    try {
        // Try and seek within the currently cached audio.
        mCache->seek(f_seek_byte - f_pos_byte);
        f_pos_byte = f_seek_byte;
    }
    catch (int e) {
        // Otherwise do a hard seek and reread from file.
        threadSend(SEEK);
    }
}


/**
 * Determines if a file is currently loaded.
 * @returns             true if a file is currently loaded.
 */
bool Input::isLoaded() {
    return loaded;
}


/**
 * Attaches a Counter component to this Component. Counters are updated
 * whenever audio is requested from this component or its state is changed.
 * @param   counter     Audio Counter to attach
 */
void Input::addCounter(Audio::Counter *counter) {
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
void Input::removeCounter(Audio::Counter *counter) {
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
void Input::updateCounters(unsigned long sample) {
    for (unsigned int i = 0; i < countersList.size(); i++) {
        countersList.at(i)->setSample(sample);
    }
}


/**
 * Updates the total number of samples on all attached Counters.
 * @param   samples     The total number of samples
 */
void Input::updateTotals(unsigned long samples) {
    for (unsigned int i = 0; i < countersList.size(); i++) {
        countersList.at(i)->setTotalSamples(samples);
    }
}


/**
 * Updates the state on all attached Counters.
 * @param   state       The current state.
 */
void Input::updateStates(enum STATE state) {
    for (unsigned int i = 0; i < countersList.size(); i++) {
        countersList.at(i)->setState(state);
    }
}


/**
 * Performs checks and starts caching of audio. If caching is currently
 * active, it is first stopped. Once caching is started, execution is blocked
 * until the cache is filled to a predefined size.
 */
void Input::startCaching() {
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
    while ( mCache->size() - mCache->free() < preCacheSize 
            && mCache->size() - mCache->free() < f_length_byte) {
        usleep(1000);
    }
}


/**
 * Terminates the caching of audio, and blocks execution until the cache
 * has responded and reaches a CACHE_STATE_INACTIVE state.
 */
void Input::stopCaching() {
    // if we're still caching, instruct to stop caching
    cacheStateLock.lock();

    threadSend(STOP);

    // Wait until we've actually stopped caching
    while (cacheState == CACHE_STATE_ACTIVE) {
        cacheStateLock.unlock();
        usleep(10000);
        cacheStateLock.lock();
    }
    cacheStateLock.unlock();
}


/**
 * Pure virtual function placeholder for implementing caching in derived class.
 */
void Input::threadExecute() {

}
