#ifndef CLASS_AUDIO_PROCESS_MIXER
#define CLASS_AUDIO_PROCESS_MIXER

#include <map>
#include <vector>

#include "AudioPacket.h"
using namespace Audio;

#include "Process.h"

struct MixerChannel {
	enum STATE state;
	AudioPacket* data;
	Component* cmpt;
	PORT port;
};

struct ltport {
	bool operator()(PORT s1, PORT s2) const {
	    return (s1<s2);
	}
};

/** Audio mixer for combining audio from multiple audio components.
 * This component retrieves audio from connected input audio components and
 * mixes them using the following formula:
 * \f[ g(t) = \sum_{i=0}^{N-1} \left( f_i(t)\prod_{j=i+1}^{N-1} 
 *  \left(1-\frac{\left|f_j(t)\right|}{M}\right) \right) \f]
 * for \f$N\f$ input signals \f$ f_i(t) \f$, output signal \f$ g(t) \f$ and
 * sample size \f$M\f$.
 */
class Audio::ProcessMixer : public Audio::Process {
    public:
        ProcessMixer();
        ~ProcessMixer();

        virtual void getAudio(AudioPacket* audioData);

        virtual void receiveMessage(PORT inPort, MESSAGE message);

		virtual void onConnect(PORT localPort);
		virtual void onDisconnect(PORT localPort);

        virtual void threadExecute();

    private:
		STATE _state;
        short *audioBuffer, *cacheStart, *cacheEnd, *cacheRead, *cacheWrite;
		std::map<PORT,MixerChannel*> ch_inactive;
		std::map<PORT,MixerChannel*> channels;
		std::map<PORT,MixerChannel*> ch_active;

		pthread_mutex_t channelLock;
};

#endif
