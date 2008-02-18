#ifndef CLASS_COUNTER_TRIGGER
#define CLASS_COUNTER_TRIGGER

#include "InputRaw.h"

#include "Counter.h"

/** 
 * Counter-trigger class for triggering an event based on the current sample.
 * This component is derived from the Counter base class, and blocks execution
 * of calling threads until certain conditions are satisfied. These conditions
 * are usually based on the current sample, but may also include conditions on
 * the state of the audio component this is attached to.
 */
class Audio::CounterTrigger : public Audio::Counter {
    public:
        /// Construct a new CounterTrigger
		CounterTrigger();
        /// Destructor
        virtual ~CounterTrigger();
        /// Called when the current sample is set
        void onSetSample();
		/// Called when the current state is set
		void onSetState();
        /// Called when the total number of samples is set
        void onSetTotalSamples();

        /// Set the InputRaw component to trigger when conditions are met.
		void setTriggerTarget(InputRaw *I);
        /// Set the sample at which the event should trigger
		void setTriggerSample(unsigned long sample);
        /// Blocks execution until the trigger sample has passed
		void waitTrigger();
        /// Blocks execution until the attached component is stopped
		void waitStop();
        /// Blocks execution until the attached component plays
		void waitPlay();

    private:
		InputRaw *_target;
		unsigned long _smpl;
		bool _passed;
};

#endif
