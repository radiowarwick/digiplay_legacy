#include "InputRaw.h"

#include "OutputDsp.h"

Audio::OutputDsp::OutputDsp(string channel) {
	initialise(channel);
//	threadStart();
}

Audio::OutputDsp::~OutputDsp() {

}

void Audio::OutputDsp::receiveMessage(PORT inPort, MESSAGE message) {
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

void Audio::OutputDsp::threadExecute() {
	short int* buffer = new short int[256];
	Component* device = connectedDevice(0);
	while (audioState == STATE_PLAY) {
		device->getAudio(buffer,64);
		if (write (audio, buffer, 256) != 256) {
			cout << "Failed to write all of buffer" << endl;
			abort();
		}
	}
	delete[] buffer;
}

void Audio::OutputDsp::initialise(string device) {
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
