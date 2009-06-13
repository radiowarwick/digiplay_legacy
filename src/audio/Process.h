#ifndef CLASS_AUDIO_PROCESS
#define CLASS_AUDIO_PROCESS

#include "ComponentAudio.h"
using Audio::ComponentAudio;

/**
 * Pure virtual base class for audio processing components
 */
class Audio::Process : public virtual ComponentAudio {
    public:
        Process();
        virtual ~Process();

        virtual void getAudio(AudioPacket* audioData) =0;

        virtual void receiveMessage(PORT inPort, MESSAGE message) = 0;

        virtual void threadExecute();

    private:
        
};

#endif
