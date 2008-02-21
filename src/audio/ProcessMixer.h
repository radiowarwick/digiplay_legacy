#ifndef CLASS_AUDIO_PROCESS_MIXER
#define CLASS_AUDIO_PROCESS_MIXER

#include <map>
#include <vector>

#include "AudioPacket.h"
using namespace Audio;

#include "Process.h"

/**
 * Associates an source audio component, its state, the port on which it is
 * connected to the mixer and an AudioPacket to buffer audio received from
 * this component.
 */
struct MixerChannel {
	enum STATE state;
	AudioPacket* data;
	Component* cmpt;
	PORT port;
};

/*
struct ltport {
	bool operator()(PORT s1, PORT s2) const {
	    return (s1<s2);
	}
};
*/

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
        /// Creates a new mixer
        ProcessMixer();
        /// Destructor
        ~ProcessMixer();

        /// Processes a packet of Audio from each source
        virtual void getAudio(AudioPacket* audioData);

        /// Process messages received from attached components
        virtual void receiveMessage(PORT inPort, MESSAGE message);

        /// Perform tasks when a component is connected
		virtual void onPatch(PORT localPort);
        /// Perform tasks when a component is disconnected
		virtual void onUnpatch(PORT localPort);

    private:
		STATE _state;
        short *audioBuffer;
        std::map<PORT,MixerChannel*> channels;
		std::map<PORT,MixerChannel*> ch_inactive;
		std::map<PORT,MixerChannel*> ch_active;

		pthread_mutex_t channelLock;
};

#endif
