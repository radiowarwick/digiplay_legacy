#include <iostream>
#include <fstream>
using std::ofstream;
using std::cout;
using std::endl;

#include "OutputDsp.h"
using Audio::OutputDsp;

OutputDsp::OutputDsp(string channel) {
	initialise(channel);
}

OutputDsp::~OutputDsp() {

}

void OutputDsp::receiveMessage(PORT inPort, MESSAGE message) {
    cout << "Message on port " << inPort << ", message " << message << endl;
    if (inPort != IN0) {
        cout << "OutputDsp::receive: only use IN0 on a DSP device" << endl;
        return;
    }
    switch (message) {
        case PLAY:
            audioState = STATE_PLAY;
            if (!isThreadActive()) threadStart();
            break;
        default:
            break;
    }
}

void OutputDsp::threadExecute() {
    if (!connectedDevice(IN0)) 
		cout << "CONNECTED DEVICE IS NULL" << endl;

    AudioPacket *buffer = new AudioPacket(PACKET_SAMPLES);
    char* d = (char*)(buffer->getData());
	Component *C = connectedDevice(IN0);

	while (audioState == STATE_PLAY) {
		C->getAudio(buffer);
		for (unsigned int i = 0; i < PACKET_MULTIPLIER; i++) {
			if (write (audio, d+(i*AUDIO_BUFFER), AUDIO_BUFFER) 
													!= AUDIO_BUFFER) {
				cout << "Failed to write all of buffer" << endl;
				abort();
			}
		}
	}
	delete buffer;
}

void OutputDsp::initialise(string device) {
    // Open audio device
	audio = open(device.c_str(), O_WRONLY, 0);
	if (audio == -1) {
		cout << "FAILED: unable to open " << device << endl;
		abort();
	}

    // Output settings
    int dsp_sample_rate = 44100;
    int dsp_sample_size = 16;
    int dsp_stereo = 1;
    int dsp_profile = APF_NORMAL;

    // Configure DSP device
    ioctl(audio, SNDCTL_DSP_SAMPLESIZE, &dsp_sample_size);
    ioctl(audio, SNDCTL_DSP_PROFILE, &dsp_profile);
    ioctl(audio, SNDCTL_DSP_STEREO, &dsp_stereo);
    ioctl(audio, SNDCTL_DSP_SPEED, &dsp_sample_rate);
}
