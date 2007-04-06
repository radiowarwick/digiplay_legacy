#include <iostream>

#include "CounterTrigger.h"

Audio::CounterTrigger::CounterTrigger() {

}

Audio::CounterTrigger::~CounterTrigger() {

}

/** This is used by an audio component (e.g. InputRaw) to set the current
 * sample after each request for an audio block.
 * @param sample The most recent sample sent from the parent audio component.
 */
void Audio::CounterTrigger::onSetSample() {
	if (_currentSample > _smpl && !_passed) {
		_passed = true;
		_target->play();
	}
}

void Audio::CounterTrigger::onSetState() {

}

void Audio::CounterTrigger::onSetTotalSamples() {

}

void Audio::CounterTrigger::setTriggerTarget(InputRaw *I) {
	_target = I;
}

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

void Audio::CounterTrigger::waitTrigger() {
	while (!_passed) {
		usleep(100);
	}
}

void Audio::CounterTrigger::waitStop() {
	while (_state != STATE_STOP) {
		usleep(100);
	}
}
