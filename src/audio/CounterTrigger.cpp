#include <iostream>

#include "CounterTrigger.h"

/**
 * Creates a new CounterTrigger
 */
Audio::CounterTrigger::CounterTrigger() {

}


/**
 * Destructor
 */
Audio::CounterTrigger::~CounterTrigger() {

}


/** 
 * This is used by an audio component (e.g. InputRaw) to set the current
 * sample after each request for an audio block.
 */
void Audio::CounterTrigger::onSetSample() {
	if (_currentSample > _smpl && !_passed) {
		_passed = true;
		_target->play();
	}
}


/**
 * This is run when the audio component to which this counter is attached
 * updates its state.
 */
void Audio::CounterTrigger::onSetState() {

}


/**
 * This is run when the audio component to which this counter is attached
 * updates the total number of samples in the current track.
 */
void Audio::CounterTrigger::onSetTotalSamples() {

}


/**
 * Sets the target which will receive actions from this trigger.
 * @param   I           InputRaw component to receive actions
 */
void Audio::CounterTrigger::setTriggerTarget(InputRaw *I) {
	_target = I;
}


/**
 * Set the sample at which this CounterTrigger triggers.
 * @param   sample      Stereo sample at which to trigger.
 */
void Audio::CounterTrigger::setTriggerSample(unsigned long sample) {
	if (sample > _totalSamples) {
		std::cout << "Sample is beyond end of file!" << std::endl;
		std::cout << "Total samples: " << _totalSamples << std::endl;
		std::cout << "Trigger sample: " << sample << std::endl;
		throw;
	}
	_passed = (_currentSample > sample);
	_smpl = sample;
}


/**
 * Block execution of the calling thread until the trigger sample has been
 * passed.
 */
void Audio::CounterTrigger::waitTrigger() {
	while (!_passed) {
		usleep(1000);
	}
}


/**
 * Block execution of the calling thread until the associated component
 * reaches the STATE_STOP state.
 */
void Audio::CounterTrigger::waitStop() {
	while (_state != STATE_STOP) {
		usleep(1000);
	}
}


/**
 * Block execution of the calling thread until the associated component
 * reaches the STATE_PLAY state.
 */
void Audio::CounterTrigger::waitPlay() {
    while (_state != STATE_PLAY) {
        usleep(1000);
    }    
}
