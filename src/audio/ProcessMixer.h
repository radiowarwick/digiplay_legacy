#ifndef CLASS_AUDIO_PROCESS_MIXER
#define CLASS_AUDIO_PROCESS_MIXER

#include "Process.h"

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

        virtual void getAudio(short *audioData, unsigned long samples);

        virtual void receiveMessage(PORT inPort, MESSAGE message);

        virtual void threadExecute();

    private:
        short *audioBuffer, *cacheStart, *cacheEnd, *cacheRead, *cacheWrite;
        vector<int> channelFlags;
        vector<short*> channelBuffers;
};

#endif
