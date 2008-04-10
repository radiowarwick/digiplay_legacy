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
InputRaw::InputRaw(unsigned int cache_size) 
        : Input(cache_size) {
            
	audioBuffer = new char[READ_PACKET];

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


/**
 * Terminates the caching thread and cleans up memory used.
 */
InputRaw::~InputRaw() {
    delete[] audioBuffer;
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

    updateCounters(0);
	updateTotals(f_length_byte/4);

    try {
        startCaching();
    }
    catch (int e) {
        throw -1;
    }
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
            f_end_byte = (unsigned long)f->tellg() - f_start_byte;
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
