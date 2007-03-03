#include "Counter.h"

Audio::Counter::Counter() {

}

Audio::Counter::~Counter() {

}

/** This is used by an audio component (e.g. InputRaw) to set the current
 * sample after each request for an audio block.
 * @param sample The most recent sample sent from the parent audio component.
 */
void Audio::Counter::setSample(unsigned long sample) {
    _currentSample = sample;
}

/** This is used by an audio component to set the total number of samples for
 * the current context. This is then available for use by a derived class in
 * the \c _totalSamples class variable. This will be zero for indeterminate
 * audio sources (e.g. InputDsp).
 * @param sample The total number of samples in the current audio context.
 */
void Audio::Counter::setTotalSamples(unsigned long sample) {
    _totalSamples = sample;
}
