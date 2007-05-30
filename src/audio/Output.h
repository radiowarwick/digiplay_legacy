#ifndef CLASS_AUDIO_OUTPUT
#define CLASS_AUDIO_OUTPUT

#include "Component.h"

/** Pure virtual output base class.
 * A base class from which audio output classes are derived.
 */
class Audio::Output : public Audio::Component {
	public:
		virtual ~Output();
		virtual void getAudio(AudioPacket* audioData) {return;}

	protected:
		virtual void receiveMessage(PORT inPort, MESSAGE message) = 0;
		virtual void onConnect(PORT localPort) = 0;
		virtual void onDisconnect(PORT localPort) = 0;
		virtual void threadExecute();

	private:
		char *audioBuffer, *cacheStart, *cacheEnd, *cacheWrite, *cacheRead;
		unsigned long cacheFree;
};

#endif
