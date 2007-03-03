#include <iostream>
#include <fstream>
using std::ofstream;
using std::cout;
using std::endl;

#include "OutputDsp.h"
using Audio::OutputDsp;

OutputDsp::OutputDsp(string channel) {
	initialise(channel);
//	threadStart();
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
    cout << "Player start threadExecute()" << endl;
    if (!connectedDevice(IN0)) cout << "CONNECTED DEVICE IS NULL" << endl;
    AudioPacket buffer(512);
    char* d = (char*)&(buffer[0]);
    ofstream f_out("/mnt/dps0-0/audio/output.raw");
	while (audioState == STATE_PLAY) {
		connectedDevice(IN0)->getAudio(buffer);
        for (unsigned int i = 0; i < 1024; i++) f_out << d[i];
		if (write (audio, &(buffer[0]), 1024) != 1024) {
			cout << "Failed to write all of buffer" << endl;
			abort();
		}
	}
    f_out.close();
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
