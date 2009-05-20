#ifndef CLASS_AUDIO_PROCESS
#define CLASS_AUDIO_PROCESS

#include "Component.h"
using Audio::Component;

/**
 * Pure virtual base class for audio processing components
 */
class Audio::Process : public virtual Component {
    public:
        Process();
        virtual ~Process();

        virtual void getAudio(AudioPacket* audioData) =0;

        virtual void receiveMessage(PORT inPort, MESSAGE message) = 0;

        virtual void threadExecute();

    private:
        
};

#endif
