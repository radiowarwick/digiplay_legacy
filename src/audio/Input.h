#ifndef CLASS_AUDIO_INPUT
#define CLASS_AUDIO_INPUT

#include "Component.h"

/** Pure virtual base class for input components.
 * This class provides a base class from which to derive input components.
 */
class Audio::Input : public Audio::Component {
	public:
		virtual ~Input();
		virtual void getAudio(AudioPacket* audioData) = 0;
		virtual void play() = 0;
		virtual void stop() = 0;
		virtual void pause() = 0;
		virtual void seek(long sample) = 0;
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
