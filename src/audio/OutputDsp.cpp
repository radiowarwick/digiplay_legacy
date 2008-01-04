#include <iostream>
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
    //cout << "Message on port " << inPort << ", message " << message << endl;
    if (inPort != IN0) {
        cout << "OutputDsp::receive: only use IN0 on a DSP device" << endl;
        return;
    }
    switch (message) {
        case PLAY:
            audioState = STATE_PLAY;
            if (!isThreadActive()) threadStart();
            break;
        case PAUSE:
            audioState = STATE_PAUSE;
            break;
        default:
            break;
    }
}

void OutputDsp::onConnect(PORT localPort) {

}

void OutputDsp::onDisconnect(PORT localPort) {

}

void OutputDsp::threadExecute() {
    if (!connectedDevice(IN0)) 
		cout << "CONNECTED DEVICE IS NULL" << endl;

    AudioPacket *buffer = new AudioPacket(PACKET_SAMPLES);
    char* d = (char*)(buffer->getData());
	Component *C = connectedDevice(IN0);

	while (audioState != STATE_STOP) {
        if (audioState == STATE_PAUSE) {
            usleep(100);
            continue;
        }
		C->getAudio(buffer);
		for (unsigned int i = 0; i < PACKET_MULTIPLIER; i++) {
			if (write (audio, d+(i*AUDIO_BUFFER), AUDIO_BUFFER) 
													!= AUDIO_BUFFER) {
				cout << "Failed to write all of buffer" << endl;
				abort();
			}
            if (deviceName == "/dev/null") usleep(50);
		}
	}
	delete buffer;
}

void OutputDsp::initialise(string device) {
    // Open audio device
    deviceName = device;
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
    // Set a small buffer to allow accurate control of audio output
    // Must do this BEFORE any read/write/ioctl operations or no effect
    int arg = 0x0002000D;
    if (ioctl (audio, SNDCTL_DSP_SETFRAGMENT, &arg)) {
        cout << "WARNING: " << deviceName
             << ": failed to set audio buffer on dsp device." << endl;
    }

    ioctl(audio, SNDCTL_DSP_SAMPLESIZE, &dsp_sample_size);
    ioctl(audio, SNDCTL_DSP_PROFILE, &dsp_profile);
    ioctl(audio, SNDCTL_DSP_STEREO, &dsp_stereo);
    ioctl(audio, SNDCTL_DSP_SPEED, &dsp_sample_rate);

}
