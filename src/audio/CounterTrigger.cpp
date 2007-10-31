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
		cout << "TRriggering on sample " << _currentSample << endl;
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
    cout << "setTriggerSample(): sample = " << sample << endl;
	if (sample > _totalSamples) {
		std::cout << "Sample is beyond end of file!" << std::endl;
		std::cout << "Total samples: " << _totalSamples << std::endl;
		std::cout << "Trigger sample: " << sample << std::endl;
		throw;
	}
	_passed = (_currentSample > sample);
    cout << "setTriggerSample(): _passed = " << _passed << endl;
	_smpl = sample;
}

void Audio::CounterTrigger::waitTrigger() {
    cout << "waitTrigger(): _passed = " << _passed << endl;
    cout << "waitTrigger(): _totalSamples = " << _totalSamples << endl;
    cout << "waitTrigger(): _currentSample = " << _currentSample << endl;
	while (!_passed) {
		usleep(1000);
	}
}

void Audio::CounterTrigger::waitStop() {
    cout << "waitStop(): _state = " << _state << endl;
    cout << "STATE_STOP is " << STATE_STOP << endl;
	while (_state != STATE_STOP) {
		usleep(1000);
	}
	cout << "Trigger found stop" << endl;
}
