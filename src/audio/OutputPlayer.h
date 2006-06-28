#ifndef CLASS_AUDIO_OUTPUT_PLAYER
#define CLASS_AUDIO_OUTPUT_PLAYER

#include "Output.h"

class Audio::OutputPlayer : public Audio::Output {
	public:
		OutputPlayer(string channel);
		~OutputPlayer();

		void receive(PORT inPort, MESSAGE message);

		void threadExecute();

	private:
		void initialise(string device);

		string deviceName;

};

#endif
