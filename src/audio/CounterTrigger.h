#ifndef CLASS_COUNTER_TRIGGER
#define CLASS_COUNTER_TRIGGER

#include "InputRaw.h"

#include "Counter.h"

/** Component counter base class.
 * This provides a base class for counter-related components or GUI widgets to
 * derive from and implement their own functionality. When added to an audio
 * component, the \c setSample routine will be called after each audio packet
 * request to update the currentSample.
 */
class Audio::CounterTrigger : public Audio::Counter {
    public:
		CounterTrigger();
        virtual ~CounterTrigger();
        /// Called when the current sample is set
        void onSetSample();
		/// Called when the current state is set
		void onSetState();
        /// Called when the total number of samples is set
        void onSetTotalSamples();

		void setTriggerTarget(InputRaw *I);
		void setTriggerSample(unsigned long sample);
		void waitTrigger();
		void waitStop();
		void waitPlay();

    private:
		InputRaw *_target;
		unsigned long _smpl;
		bool _passed;
};

#endif
