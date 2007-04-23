#ifndef CLASS_AUDIO_OUTPUT_DSP
#define CLASS_AUDIO_OUTPUT_DSP

#include <string>
using std::string;

#include "fcntl.h"
#include <sys/soundcard.h>
#include <sys/ioctl.h>

#include "Output.h"

/** Class to output audio to a DSP device.
 * This class reads audio from it's connected component and writes it to the
 * specified dsp device.
 */
class Audio::OutputDsp : public Audio::Output {
	public:
		OutputDsp(string channel);
		~OutputDsp();

		void receiveMessage(PORT inPort, MESSAGE message);
		
		virtual void onConnect(PORT localPort) {}
		virtual void onDisconnect(PORT localPort) {}

		void threadExecute();

	private:
		void initialise(string device);

		string deviceName;
        enum STATE audioState;
		int audio;
};

#endif
