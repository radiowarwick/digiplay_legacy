#ifndef CLASS_AUDIO_OUTPUT_DSP
#define CLASS_AUDIO_OUTPUT_DSP

#include <string>
using namespace std;

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

};

#endif
