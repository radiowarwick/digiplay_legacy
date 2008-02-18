#include "Counter.h"
#include <iostream>
Audio::Counter::Counter() {
    _totalSamples = 0;
    _currentSample = 0;
    _state = STATE_STOP;
}

Audio::Counter::~Counter() {

}

/** 
 * This is used by an audio component (e.g. InputRaw) to set the current
 * sample after each request for an audio block.
 * @param   sample  The most recent sample sent from the parent audio 
 *                  component.
 */
void Audio::Counter::setSample(unsigned long sample) {
    _currentSample = sample;
	onSetSample();
}

/**
 * This is used by an audio component to set the state of the component
 * after it changes (e.g. stop, play, pause).
 * @param   state   The new state of the component.
 */
void Audio::Counter::setState(enum STATE state) {
	_state = state;
	onSetState();
}

/** 
 * This is used by an audio component to set the total number of samples for
 * the current context. This is then available for use by a derived class in
 * the \c _totalSamples class variable. This will be zero for indeterminate
 * audio sources (e.g. InputDsp).
 * @param   sample  The total number of samples in the current audio context.
 */
void Audio::Counter::setTotalSamples(unsigned long sample) {
    _totalSamples = sample;
	onSetTotalSamples();
}
