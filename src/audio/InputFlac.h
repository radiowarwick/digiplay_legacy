#ifndef CLASS_AUDIO_INPUT_RAW
#define CLASS_AUDIO_INPUT_RAW

#include <iostream>
#include <fstream>
#include "FLAC++/decoder.h"

using namespace std;
using namespace FLAC::Decoder;

#include "Input.h"

class Audio::Counter;

class Audio::InputFlac :    public FLAC::Decoder::File, 
                            public Audio::Input {
	public:
		InputFlac();
		virtual ~InputFlac();

		virtual void getAudio(AudioPacket* audioData);

		void load(string filename, long start_smpl, long end_smpl);
		void play();		// play track
		void stop();		// stop track and seek to start
		void pause();		// pause track
		void seek(long sample);

		void addCounter(Audio::Counter *counter);
		void removeCounter(Audio::Counter *counter);
		
		void receiveMessage(PORT inPort, MESSAGE message);

        /// Perform any initialisation tasks required on connection
        virtual void onPatch(PORT localPort);
        /// Perform any uninitialisation tasks required on disconnection
        virtual void onUnpatch(PORT localPort);

		void threadExecute();

	protected:
		virtual ::FLAC__StreamDecoderWriteStatus write_callback(const::FLAC__Frame *frame, const FLAC__int32 *const buffer[]);
        virtual void metadata_callback(const::FLAC__StreamMetadata *metadata);
        virtual void error_callback(::FLAC__StreamDecoderErrorStatus status);

	private:
        /// Lock on read/write operations to cache
        ThreadMutex cacheLock;
        /// Lock on read/write operations to caching action
        ThreadMutex cacheStateLock;
        
        bool loaded;
        string f_filename;
        char *audioBuffer, *cacheStart, *cacheEnd, *cacheWrite, *cacheRead;
        unsigned long cacheSize, cacheFree;
        unsigned long f_start_byte, f_end_byte, f_pos_byte, f_length_byte;
        unsigned long f_seek_byte;
        unsigned long preCacheSize;
        vector<Audio::Counter*> countersList;
        STATE state;
        CACHE_STATE cacheState;
        bool autoReload;

        FLAC__uint64 total_samples;
        unsigned sample_rate;
        unsigned channels;
        unsigned bps;

        /// Update the position on all attached counter clients
        void updateCounters(unsigned long sample);
        /// Update the total samples on all attached counter clients
        void updateTotals(unsigned long samples);
        /// Update the state of this component on all attached counter clients
        void updateStates(enum STATE state);
        
        /// Starts caching and waits for cache to be pre-filled
        void startCaching();
        /// stop caching and wait for cache to become inactive
        void stopCaching();
};

#endif
