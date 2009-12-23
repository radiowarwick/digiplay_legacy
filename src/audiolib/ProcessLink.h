#ifndef CLASS_AUDIO_PROCESS_LINK
#define CLASS_AUDIO_PROCESS_LINK

#include <fstream>
#include <vector>
#include <map>
using std::vector;
using std::map;

#include "Process.h"
#include "Counter.h"

/** 
 * Audio link module.
 * 
 * This module simply acts as a link between two audio modules (say an input
 * and another processing module). It is primarily intended as an audio
 * interface for other classes to inherit and use to allow audio modules
 * outside the class to access audio modules inside the class which may change
 * throughout the lifetime of the derived class.
 */
class Audio::ProcessLink : public Audio::Process {
    public:
        /// Create a new link
        ProcessLink();
        /// Destructor
        ~ProcessLink();

        /// Retrieve a packet of audio from the component connected to IN0
        virtual void getAudio(AudioPacket* audioData);
        /// Process a message received from another component
        virtual void receiveMessage(PORT inPort, MESSAGE message);
		
        /// Perform tasks when a component is connected
		virtual void onPatch(PORT localPort __attribute__((unused))) {}
        /// Perform tasks when a component is disconnected
		virtual void onUnpatch(PORT localPort __attribute__((unused))) {}

   private:

};

#endif
