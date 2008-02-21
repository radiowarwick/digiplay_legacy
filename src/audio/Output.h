#ifndef CLASS_AUDIO_OUTPUT
#define CLASS_AUDIO_OUTPUT

#include "Component.h"

/** Pure virtual output base class.
 * A base class from which audio output classes are derived.
 */
class Audio::Output : public virtual Audio::Component {
	public:
		virtual ~Output();
		virtual void getAudio(AudioPacket* audioData);

	protected:
		virtual void receiveMessage(PORT inPort, MESSAGE message) = 0;
		virtual void onPatch(PORT localPort) = 0;
		virtual void onUnpatch(PORT localPort) = 0;
		virtual void threadExecute();

	private:
		char *audioBuffer, *cacheStart, *cacheEnd, *cacheWrite, *cacheRead;
		unsigned long cacheFree;
};

#endif
