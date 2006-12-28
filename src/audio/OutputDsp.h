#ifndef CLASS_AUDIO_OUTPUT_DSP
#define CLASS_AUDIO_OUTPUT_DSP

#include <string>
#include <iostream>
#include "fcntl.h"
using namespace std;

#include <sys/soundcard.h>
#include <sys/ioctl.h>

#include "Output.h"

class Audio::OutputDsp : public Audio::Output {
	public:
		OutputDsp(string channel);
		~OutputDsp();

		void receive(PORT inPort, MESSAGE message);

		void threadExecute();

	private:
		void initialise(string device);

		string deviceName;
		int audio;
};

#endif
