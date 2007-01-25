#ifndef CLASS_AUDIO_PROCESS_MIXER
#define CLASS_AUDIO_PROCESS_MIXER

#include "Process.h"

/** Audio mixer for combining audio from multiple audio components.
 * This component retrieves audio from connected input audio components and
 * mixes them using the following formula:
 * \f[ g(t) = \sum_{i=0}^{n} \left( f_i(t)\prod_{j=i+1}^n (1-f_j(t)) \right) \f]
 * for \f$n\f$ input signals \f$ f_i(t) \f$ and output signal \f$ g(t) \f$.
 */
class Audio::ProcessMixer : public Audio::Process {
    public:
        ProcessMixer();
        ~ProcessMixer();

        virtual void receiveMessage(PORT inPort, MESSAGE message);

        virtual void threadExecute();

    private:
        short *audioBuffer, *cacheStart, *cacheEnd, *cacheRead, *cacheWrite;
        vector<int> channelFlags;
};

#endif
