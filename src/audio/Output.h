#ifndef CLASS_AUDIO_OUTPUT
#define CLASS_AUDIO_OUTPUT

#include "Component.h"

class Audio::Output : public Audio::Component {
	public:
		virtual ~Output();
		virtual void getAudio(AudioPacket* audioData) {return;}

	protected:
		virtual void receiveMessage(PORT inPort, MESSAGE message);
		virtual void onConnect(PORT localPort) {}
		virtual void onDisconnect(PORT localPort) {}
		virtual void threadExecute();

	private:
		char *audioBuffer, *cacheStart, *cacheEnd, *cacheWrite, *cacheRead;
		unsigned long cacheFree;
};

#endif
