#ifndef CLASS_AUDIO_OUTPUT
#define CLASS_AUDIO_OUTPUT

#include "Component.h"

class Audio::Output : public Audio::Component {
	public:
		virtual ~Output();
//		virtual void getAudio(short *audioData, int samples);
//		virtual void play();		// play track
//		virtual void stop();		// stop track and seek to start
//		virtual void pause();		// pause track
//		virtual void seek(long sample);

	protected:
		virtual void receive(PORT inPort, MESSAGE message);
		virtual void threadExecute();

	private:
		char *audioBuffer, *cacheStart, *cacheEnd, *cacheWrite, *cacheRead;
		unsigned long cacheFree;
};

#endif
