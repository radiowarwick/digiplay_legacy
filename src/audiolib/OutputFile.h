#ifndef CLASS_AUDIO_OUTPUT_FILE
#define CLASS_AUDIO_OUTPUT_FILE

#include <string>

#include "Output.h"

/**
 * Class to read audio from a file.
 * Uses a dynamically loaded implementation.
 */
class Audio::OutputFile : public Audio::Output {
    public:
        OutputFile(std::string filename);
        ~OutputFile();

    protected:
        void receiveMessage(PORT inPort, MESSAGE message);
        virtual void onPatch(PORT localPort);
        virtual void onUnpatch(PORT localPort);

    private:
        Output * pImpl;
        string filename;
        void *dlHandle;
};

#endif
