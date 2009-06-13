#include <iostream>
using std::cout;
using std::endl;

#include "Security.h"

#include "OutputDsp.h"
using Audio::OutputDsp;

/**
 * Creates a new output object to write to a DSP device
 * @param   channel     DSP device to use
 */
OutputDsp::OutputDsp(string channel) {
	initialise(channel);
}


/**
 * Destructor
 */
OutputDsp::~OutputDsp() {

}


/**
 * Process messages received from other connected components.
 * @param   inPort      Port on which message is received.
 * @param   message     Message received.
 */
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
        case STOP:
            audioState = STATE_STOP;
            //if (isThreadActive()) {
            //    cout << "Kill thread" << endl;
            //    threadKill();
            //    cout << "Wait for thread" << endl;
            //    threadWait();
            //    cout << "Thread stopped" << endl;
            //}
            break;
        default:
            break;
    }
}


/**
 * Perform tasks when a component is connected to this component
 * @param   localPort   Port on which component is connected.
 */
void OutputDsp::onPatch(PORT localPort) {

}


/**
 * Perform tasks when a component is disconnected from this component.
 * @param   localPort   Port from which this component is disconnected.
 */
void OutputDsp::onUnpatch(PORT localPort) {

}


/**
 * Writes audio to a DSP device. An AudioPacket is created, which the
 * Component attached to the first input port is asked to fill. This
 * audio is then written to the output device.
 */
void OutputDsp::threadExecute() {
    if (!connectedDevice(IN0)) 
		cout << "CONNECTED DEVICE IS NULL" << endl;

    AudioPacket *buffer = new AudioPacket(PACKET_SAMPLES);
    char* d = (char*)(buffer->getData());
	ComponentAudio *C;

	while (!threadTestKill()) {
        if (audioState == STATE_STOP) {
            usleep(10000);
            continue;
        }
        
        if (audioState == STATE_PAUSE) {
            usleep(1000);
            continue;
        }
        
        if (!(C = dynamic_cast<ComponentAudio*>(connectedDevice(IN0)))) {
            usleep(10000);
            continue;
        }

		C->getAudio(buffer);

		for (unsigned int i = 0; i < PACKET_MULTIPLIER; i++) {
			if (write (audio, d+(i*AUDIO_BUFFER), AUDIO_BUFFER) 
													!= AUDIO_BUFFER) {
				cout << "Failed to write all of buffer" << endl;
				throw -1;
			}
            if (deviceName == "/dev/null") usleep(50);
		}
	}

	delete buffer;
}


/**
 * Opens and initialises an output DSP device.
 * @param   device      The DSP device to initialise.
 */
void OutputDsp::initialise(string device) {
    // Open audio device
    deviceName = device;
    gainPrivilage();
	audio = open(device.c_str(), O_WRONLY, 0);
	dropPrivilage();
	if (audio == -1) {
		cout << "FAILED: unable to open " << device << endl;
		throw audio;
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
