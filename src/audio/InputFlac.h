#ifndef CLASS_AUDIO_INPUT_RAW
#define CLASS_AUDIO_INPUT_RAW

#include <iostream>
using namespace std;

#include "FLAC++/decoder.h"
using namespace FLAC::Decoder;

#include "Input.h"

class Audio::Counter;

/** Reads and caches audio from a FLAC encoded audio file.
 * This class reads and caches audio from a FLAC encoded audio file, storing 
 * the audio in a cyclic cache. The reading of the file into the cache is 
 * done in a separate thread.
 */
class Audio::InputFlac :    public FLAC::Decoder::File, 
                            public Audio::Input {
	public:
        /// Constructor
		InputFlac(unsigned int cache_size = 1760000);
        /// Destructor
		virtual ~InputFlac();

        /// Load a new FLAC encoded audio file and begin caching
		void load(string filename, long start_smpl, long end_smpl);
        /// Seeks to a position in an input source
        virtual void seek(long sample);
		/// Processes messages received by this component
        virtual void receiveMessage(PORT inPort, MESSAGE message);
        /// Perform any initialisation tasks required on connection
        virtual void onPatch(PORT localPort);
        /// Perform any uninitialisation tasks required on disconnection
        virtual void onUnpatch(PORT localPort);

	protected:
        /// Handle reading of a single FLAC frame into cache
		virtual ::FLAC__StreamDecoderWriteStatus write_callback(const::FLAC__Frame *frame, const FLAC__int32 *const buffer[]);
        /// FLAC metadata callback
        virtual void metadata_callback(const::FLAC__StreamMetadata *metadata);
        /// FLAC error callback
        virtual void error_callback(::FLAC__StreamDecoderErrorStatus status);

	private:
        /// Caches the audio in a separate thread
        void threadExecute();

        FLAC__uint64 total_samples;
        unsigned sample_rate;
        unsigned channels;
        unsigned bps;
};

#endif
