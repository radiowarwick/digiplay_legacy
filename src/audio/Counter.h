#ifndef CLASS_COUNTER
#define CLASS_COUNTER

#include "Audio.h"
#include "Component.h"

/** 
 * Component counter base class.
 * This provides a base class for counter-related components or GUI widgets to
 * derive from and implement their own functionality. When added to an audio
 * component, the \c setSample routine will be called after each audio packet
 * request to update the currentSample.
 */
class Audio::Counter : public virtual Audio::Component {
    public:
        virtual ~Counter();
        /// Set the current sample
        void setSample(unsigned long sample);
		/// Set the current state
		void setState(enum STATE state);
        /// Set the total number of samples
        void setTotalSamples(unsigned long sample);

        /// Overloaded routine called when the sample changes
		virtual void onSetSample() = 0;
        /// Overloaded routine called when the state changes
		virtual void onSetState() = 0;
        /// Overloaded routine called when the total samples changes
		virtual void onSetTotalSamples() = 0;
        
    protected:
        /// Disallow instances of this class
        Counter();
        /// Stores the current playback position of the attached component
        unsigned long _currentSample;
        /// Stores the total samples to playback from the attached component
        unsigned long _totalSamples;
        /// Stores the state of the attached component.
		enum STATE _state;

    private:

};

#endif
