#ifndef CLASS_COUNTER
#define CLASS_COUNTER

#include "Audio.h"

/** Component counter base class.
 * This provides a base class for counter-related components or GUI widgets to
 * derive from and implement their own functionality. When added to an audio
 * component, the \c setSample routine will be called after each audio packet
 * request to update the currentSample.
 */
class Audio::Counter {
    public:
        virtual ~Counter();
        /// Set the current sample
        void setSample(unsigned long sample);
		/// Set the current state
		void setState(enum STATE state);
        /// Set the total number of samples
        void setTotalSamples(unsigned long sample);

		virtual void onSetSample() = 0;
		virtual void onSetState() = 0;
		virtual void onSetTotalSamples() = 0;

    protected:
        Counter();
        unsigned long _currentSample;
        unsigned long _totalSamples;
		enum STATE _state;

    private:

};

#endif
