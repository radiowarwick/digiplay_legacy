#include "InputRaw.h"

#include "OutputDsp.h"

Audio::OutputDsp::OutputDsp(string channel) {
	audio = open(channel.c_str(), O_WRONLY, 0);
	if (audio == -1) {
		cout << "FAILED: unable to open " << channel << endl;
		abort();
	}
	threadStart();
}

Audio::OutputDsp::~OutputDsp() {

}

void Audio::OutputDsp::receive(PORT inPort, MESSAGE message) {

}

void Audio::OutputDsp::threadExecute() {
	short int* buffer = new short int[256];
	InputRaw* device = (InputRaw*)connectedDevice(IN0);
	do {
		device->getAudio(buffer,256);
		if (write (audio, buffer, 256) != 256) {
			cout << "Failed to write all of buffer" << endl;
			abort();
		}
	} while (true);
	delete[] buffer;
}

void Audio::OutputDsp::initialise(string device) {

}
