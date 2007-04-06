#ifndef CLASS_AUDIO_INPUT
#define CLASS_AUDIO_INPUT

#include "Component.h"

class Audio::Input : public Audio::Component {
	public:
		virtual ~Input();
		virtual void getAudio(AudioPacket* audioData);
		virtual void play();		// play track
		virtual void stop();		// stop track and seek to start
		virtual void pause();		// pause track
		virtual void seek(long sample);
		virtual void onConnect(PORT localPort) {}
		virtual void onDisconnect(PORT localPort) {}

	protected:
		virtual void receiveMessage(PORT inPort, MESSAGE message);
		virtual void threadExecute();

	private:
		char *audioBuffer, *cacheStart, *cacheEnd, *cacheWrite, *cacheRead;
		unsigned long cacheFree;
};

#endif
