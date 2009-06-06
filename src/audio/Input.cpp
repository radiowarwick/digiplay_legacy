#include <iostream>
#include <algorithm>
using namespace std;

#include "Input.h"
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
    cacheSize = cache_size;
    cacheStart = new char[cacheSize];
    if (cacheStart == 0) {
        cout << "ERROR: Cannot allocate memory for cache" << endl;
        throw -1;
    }
    cacheEnd = cacheStart + cacheSize;
    cacheRead = cacheStart;
    cacheWrite = cacheStart;
    cacheFree = cacheSize;

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
    delete[] cacheStart;
}


/**
 * Fills the supplied AudioPacket with audio data from the cache.
 * @param   audioData   AudioPacket to fill.
 */
void Input::getAudio(AudioPacket* audioData) {
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
        // if we're still caching, the cache has emptied, oops!
        else {
            cout << "WARNING: buffer seems to be empty, yet we haven't reached end of file!" << endl;
            cout << "Audio length: " << f_length_byte << endl;
            cout << "Current pos:  " << f_pos_byte - f_start_byte << endl;
            bytes = cacheSize - cacheFree;
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
    if (cacheFree >= cacheSize) {
        if (f_end_byte - f_pos_byte > 256) {
            cout << "WARNING: Ran out of cached audio before end of file." << endl;
        }
        // First unlock the cache before we attempt to stop
        cacheLock.unlock();
        
        // Update counters with the end sample position
        updateCounters(f_length_byte/4);
        
        // Stop the caching and reset
        stop();
    }
    else {
        // Just unlock the cache
        cacheLock.unlock();
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
 * from the new location. The cacheLock prevents the cache from being updated
 * while the change takes place. When the cache has been reset, the lock is
 * released and the new position is updated on all attached counters.
 * @param   sample      Stereo sample to jump to in file
 */
void Input::seek(long sample) {
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
    while ( cacheSize - cacheFree < preCacheSize 
            && cacheSize - cacheFree < f_length_byte) {
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
    //if (cacheState == CACHE_STATE_ACTIVE) {
        threadSend(STOP);
    //}

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
