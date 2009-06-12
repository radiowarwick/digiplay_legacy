#ifndef CLASS_AUDIO_INPUT
#define CLASS_AUDIO_INPUT

#include <iostream>
#include <fstream>

#include "Component.h"

class Counter;


/** 
 * Pure virtual base class for file input reader components.
 * This class provides a base class and the infrastructure for passing
 * audio onto the next component in the chain. It also provides the handling
 * of attached counter components and updating position and state variables. 
 */
class Audio::Input : public virtual Audio::Component {
	public:
        /// Destructor
		virtual ~Input();
        /// Fills AudioPacket with data
		virtual void getAudio(AudioPacket* audioData);
        /// Load a new audio file and begin caching
        virtual void load(string filename, long start_smpl, long end_smpl) = 0;
        /// Changes to STATE_PLAY
		virtual void play();
        /// Changes to STATE_STOP
		virtual void stop();
        /// Changes to STATE_PAUSE
		virtual void pause();
        /// Seeks to a position in an input source
		virtual void seek(long sample);
        /// Process when a component is connected
		virtual void onPatch(PORT localPort) = 0;
        /// Process when a component is disconnected
		virtual void onUnpatch(PORT localPort) = 0;
        /// Add a counter client to be updated by this object
        void addCounter(Audio::Counter *counter);
        /// Remove a counter client from being updated by this client
        void removeCounter(Audio::Counter *counter);
        /// Set that the track should be reloaded when stopped
        void setAutoReload(bool flag) {autoReload = flag;}
        /// Check if a file is currently loaded
        bool isLoaded();

	protected:
        /// Only allow derived classes to be created
        Input(unsigned int cache_size);
        /// Process messages received from other components
		virtual void receiveMessage(PORT inPort, MESSAGE message);
        /// Update the position on all attached counter clients
        virtual void updateCounters(unsigned long sample);
        /// Update the total samples on all attached counter clients
        virtual void updateTotals(unsigned long samples);
        /// Update the state of this component on all attached counter clients
        virtual void updateStates(enum STATE state);
        /// Starts caching and waits for cache to be pre-filled
        virtual void startCaching();
        /// stop caching and wait for cache to become inactive
        virtual void stopCaching();
        /// Caches the audio in a separate thread
        virtual void threadExecute() = 0;

        // Cache related variables
        CircularCache *mCache;
        CACHE_STATE cacheState;
        ThreadMutex cacheStateLock;

        // Position variables
        unsigned long f_start_byte, f_end_byte, f_pos_byte, f_length_byte;
        unsigned long f_seek_byte;

        // Component state
        STATE state;
        bool loaded;
        string f_filename;
        bool autoReload;
        unsigned long preCacheSize;
        
	private:
        // Counters
        vector<Audio::Counter*> countersList;
        
        

};

#endif
