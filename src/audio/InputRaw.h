#ifndef CLASS_AUDIO_INPUT_RAW
#define CLASS_AUDIO_INPUT_RAW

#include <iostream>
#include <fstream>

#include "Input.h"

/** Reads and caches audio from a raw pcm audio file.
 * This class reads and caches audio from a raw PCM audio file, storing the
 * audio in a cyclic cache and passing it out when requested by \c getAudio.
 * The reading of the file into the cache is done in a separate thread.
 */
class Audio::InputRaw : public Audio::Input {
	public:
		/// Create a new raw PCM input file reader
		InputRaw(unsigned int cache_size = 1760000);
        /// Destructor
		virtual ~InputRaw();

        /// Load a new audio file and begin caching
		void load(string filename, long start_smpl, long end_smpl);

        /// Processes messages received by this component
		void receiveMessage(PORT inPort, MESSAGE message);

        /// Perform any initialisation tasks required on connection
		virtual void onPatch(PORT localPort);
        /// Perform any uninitialisation tasks required on disconnection
		virtual void onUnpatch(PORT localPort);

		
	private:
        /// Caches the audio in a separate thread
        void threadExecute();
        
		char *audioBuffer;        
};

#endif
