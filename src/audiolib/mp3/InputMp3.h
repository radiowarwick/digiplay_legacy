#ifndef CLASS_AUDIO_INPUT_MP3
#define CLASS_AUDIO_INPUT_MP3

#include <iostream>
#include <fstream>
using namespace std;

#include <mpg123.h>
#include "Input.h"

/** Reads and caches audio from an MP3 encoded audio file.
 * This class reads and caches audio from a MP3 encoded audio file, storing 
 * the audio in a cyclic cache. The reading of the file into the cache is 
 * done in a separate thread.
 */
class Audio::InputMp3: public Audio::Input {

    public:
        /// Constructor
        InputMp3(unsigned int cache_size = 1760000, Input * facade = 0);
        /// Destructor
        virtual ~InputMp3();

        /// Load a new MP3 encoded audio file and begin caching
        void load(string filename, long start_smpl, long end_smpl);
        /// Processes messages received by this component
        virtual void receiveMessage(PORT inPort, MESSAGE message);
        /// Perform any initialisation tasks required on connection
        virtual void onPatch(PORT localPort);
        /// Perform any uninitialisation tasks required on disconnection
        virtual void onUnpatch(PORT localPort);

    private:
        /// Caches the audio in a separate thread
        void threadExecute();
        mpg123_handle *mh;
        int error;
        unsigned char *readBuffer;

        Audio::Input * facade;
};

#endif
