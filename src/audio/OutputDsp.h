#ifndef CLASS_AUDIO_OUTPUT_DSP
#define CLASS_AUDIO_OUTPUT_DSP

#include <string>
using std::string;

#include "fcntl.h"
#include <sys/soundcard.h>
#include <sys/ioctl.h>

#include "Output.h"

/** 
 * Class to output audio to a DSP device.
 * This class reads audio from it's connected component and writes it to the
 * specified dsp device.
 */
class Audio::OutputDsp : public Audio::Output {
	public:
        /// Output to a DSP device
		OutputDsp(string channel);
        /// Destructor
		~OutputDsp();

        /// Process messages received from other components
		void receiveMessage(PORT inPort, MESSAGE message);
		
        /// Perform tasks when a component is connected
		virtual void onPatch(PORT localPort);
        /// Perform tasks when a component is disconnected
		virtual void onUnpatch(PORT localPort);

        /// Write audio to output device in a separate thread
		void threadExecute();

	private:
        /// Initialises the output device
		void initialise(string device);

		string deviceName;
        enum STATE audioState;
		int audio;
};

#endif
