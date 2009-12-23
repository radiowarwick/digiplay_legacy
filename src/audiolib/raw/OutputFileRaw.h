#ifndef CLASS_AUDIO_OUTPUT_FILE_RAW
#define CLASS_AUDIO_OUTPUT_FILE_RAW

#include <string>

#include "Output.h"

/** Class to output audio to a DSP device.
 * This class reads audio from it's connected component and writes it to the
 * specified dsp device.
 */
class Audio::OutputFileRaw : public Audio::Output {
    public:
        /// Create an output component to write to a file
        OutputFileRaw(std::string filename, Output * facade = 0);
        /// Destructor
        ~OutputFileRaw();

    protected:
        /// Process messages received from other components
        void receiveMessage(PORT inPort, MESSAGE message);

        /// Perform tasks when a component is connected
        virtual void onPatch(PORT localPort);
        /// Perform tasks when a component is disconnected
        virtual void onUnpatch(PORT localPort);

        /// Thread to process audio into file
        void threadExecute();

    private:
        /// Filename to write to.
        string filename;
        /// Audio state of component.
        enum STATE audioState;
        int audio;

        /// Pointer to OutputFile facade.
        Audio::Output * facade;
};

#endif
