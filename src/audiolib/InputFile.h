#ifndef CLASS_AUDIO_INPUT_FILE
#define CLASS_AUDIO_INPUT_FILE

#include <string>
using std::string;

#include "Input.h"
#include "Counter.h"

/**
 * Class to read audio from a file.
 * Uses a dynamically loaded implementation.
 */
class Audio::InputFile : public Audio::Input {
    public:
        InputFile(unsigned int cache_size = 1760000);
        ~InputFile();

        virtual void load(string filename, long start_smpl, long end_smpl);

        virtual void getAudio(AudioPacket* audioData);
        /// Changes to STATE_PLAY
        virtual void play();
        /// Changes to STATE_STOP
        virtual void stop();
        /// Changes to STATE_PAUSE
        virtual void pause();
        /// Seeks to a position in an input source
        virtual void seek(long sample);
        /// Add a counter client to be updated by this object
        virtual void addCounter(Audio::Counter *counter);
        /// Remove a counter client from being updated by this client
        virtual void removeCounter(Audio::Counter *counter);
        /// Set that the track should be reloaded when stopped
        virtual void setAutoReload(bool flag);
        /// Check if a file is currently loaded
        virtual bool isLoaded();

    protected:
        void receiveMessage(PORT inPort, MESSAGE message);
        virtual void onPatch(PORT localPort);
        virtual void onUnpatch(PORT localPort);

    private:
        /// Caches the audio in a separate thread
        void threadExecute();

        Input * pImpl;
        vector<Audio::Counter *>  facadeCounters;
        unsigned int cache_size;
        void *dlHandle;
};

#endif
