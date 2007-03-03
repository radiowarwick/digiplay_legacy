#ifndef CLASS_AUDIO_OUTPUT_DSP
#define CLASS_AUDIO_OUTPUT_DSP

#include <string>
using std::string;

#include "fcntl.h"
#include <sys/soundcard.h>
#include <sys/ioctl.h>

#include "Output.h"

class Audio::OutputDsp : public Audio::Output {
	public:
		OutputDsp(string channel);
		~OutputDsp();

		void receiveMessage(PORT inPort, MESSAGE message);

		void threadExecute();

	private:
		void initialise(string device);

		string deviceName;
        enum STATE audioState;
		int audio;
};

#endif
