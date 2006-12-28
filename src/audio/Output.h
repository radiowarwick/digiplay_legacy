#ifndef CLASS_AUDIO_OUTPUT
#define CLASS_AUDIO_OUTPUT

#include "Component.h"

class Audio::Output : public Audio::Component {
	public:
		virtual ~Output();
		virtual void getAudio(short *audioData, int samples) {return;}

	protected:
		virtual void receive(PORT inPort, MESSAGE message);
		virtual void threadExecute();

	private:
		char *audioBuffer, *cacheStart, *cacheEnd, *cacheWrite, *cacheRead;
		unsigned long cacheFree;
};

#endif
