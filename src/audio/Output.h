#ifndef CLASS_AUDIO_OUTPUT
#define CLASS_AUDIO_OUTPUT

#include "ComponentAudio.h"

/** Pure virtual output base class.
 * A base class from which audio output classes are derived.
 */
class Audio::Output : public virtual Audio::ComponentAudio {
	public:
		virtual ~Output();
		virtual void getAudio(AudioPacket* audioData);
		virtual void receiveMessage(PORT inPort, MESSAGE message) = 0;
		virtual void onPatch(PORT localPort) = 0;
		virtual void onUnpatch(PORT localPort) = 0;
		virtual void threadExecute();
};

 /// Dynamic module entry point function type and name
typedef Audio::Output * (* OutputSO_Entry)(const char *, Audio::Output *);
#define OUTPUT_SO_ENTRY	_OutputEntry
#define OUTPUT_SO_SYM "_OutputEntry"

#endif
