#ifndef CLASS_AUDIO_INPUT_RAW
#define CLASS_AUDIO_INPUT_RAW

#include <iostream>
#include <fstream>
using namespace std;

#include "Input.h"
using Audio::Input;

class Audio::Counter;

/** Reads and caches audio from a raw pcm audio file.
 * This class reads and caches audio from a raw PCM audio file, storing the
 * audio in a cyclic cache and passing it out when requested by \c getAudio.
 * The reading of the file into the cache is done in a separate thread.
 */
class Audio::InputRaw : public Input {
	public:
		InputRaw();
		~InputRaw();

        /// Processes a request for a block of audio data
		virtual void getAudio(AudioPacket* audioData);

        /// Load a new audio file and begin caching
		void load(string filename, long start_smpl, long end_smpl);
        /// Set the state to play
		void play();
        /// Set the state to stop
		void stop();
        /// Set the state to pause
		void pause();
        /// Seek to a specific sample within the file and recache
		void seek(long sample);
        /// Check if a file is currently loaded
		bool isLoaded();

        /// Add a counter client to be updated by this object
		void addCounter(Audio::Counter *counter);
        /// Remove a counter client from being updated by this client
		void removeCounter(Audio::Counter *counter);
		
        /// Processes messages received by this component
		void receiveMessage(PORT inPort, MESSAGE message);

        /// Perform any initialisation tasks required on connection
		virtual void onConnect(PORT localPort) {}
        /// Perform any uninitialisation tasks required on disconnection
		virtual void onDisconnect(PORT localPort) {}

        /// Caches the audio in a separate thread
		void threadExecute();

	private:
		ifstream f;
		string f_filename;
		char *audioBuffer, *cacheStart, *cacheEnd, *cacheWrite, *cacheRead;
		unsigned long cacheSize, cacheFree;
		unsigned long f_start_byte, f_end_byte, f_pos_byte, f_length_byte;
		vector<Audio::Counter*> countersList;
		STATE state;

        /// Update the position on all attached counter clients
		void updateCounters(unsigned long sample);
        /// Update the total samples on all attached counter clients
		void updateTotals(unsigned long samples);
        /// Update the state of this component on all attached counter clients
		void updateStates(enum STATE state);
};

#endif
