/**
 * OSS output module for RaW Digiplay (the original OutputDsp.cpp really)
 * @author Phil Ashby
 * @date June-2009
 *
 */

#include "Output.h"

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#include <fcntl.h>
#include <sys/soundcard.h>
#include <sys/ioctl.h>

namespace Audio {
    /**
     * Local sub-class of Output to implement OSS interface
     */
    class OutputDspOss : public Output {
        public:
            OutputDspOss(string device, Audio::Output *facade);
            virtual ~OutputDspOss();

            virtual void receiveMessage(PORT inPort, MESSAGE message);
            virtual void onPatch(PORT localPort);
            virtual void onUnpatch(PORT localPort);
            virtual void threadExecute();

        private:
            void initialise(string device);

            Audio::Output *facade;
            enum STATE audioState;
            string deviceName;
            int audio;
    };
};

/************************ implementation ***************************/
using Audio::Output;
using Audio::OutputDspOss;

/**
 * Dynamic loader entry point
 */
extern "C" {
    Output * OUTPUT_SO_ENTRY(const char *device, Output *facade) {
        string deviceName = device;
        return new OutputDspOss(deviceName, facade);
    }
};

OutputDspOss::OutputDspOss(string channel, Output *facade) {
    initialise(channel);
    this->facade = facade;
}

OutputDspOss::~OutputDspOss() {
    if (audio >= 0)
        close(audio);
}

void OutputDspOss::receiveMessage(PORT inPort, MESSAGE message) {
    if (inPort != IN0) {
        cout << "OutputDspOss::receive: only use IN0 on a DSP device" << endl;
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
            break;
        default:
            break;
    }
}

void OutputDspOss::onPatch(PORT localPort) {

}

void OutputDspOss::onUnpatch(PORT localPort) {

}

void OutputDspOss::threadExecute() {
   if (!facade->connectedDevice(IN0))
        cout << "CONNECTED DEVICE IS NULL" << endl;

    AudioPacket *buffer = new AudioPacket(PACKET_SAMPLES);
    char *d = (char *)buffer->getData();

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

      if (!(C = dynamic_cast<ComponentAudio *>(facade->connectedDevice(IN0)))) {
          usleep(10000);
          continue;
      }

        C->getAudio(buffer);
        for (unsigned int i = 0; i < PACKET_MULTIPLIER; i++) {
            if (write (audio, d+(i*AUDIO_BUFFER), AUDIO_BUFFER) != AUDIO_BUFFER) {
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
void OutputDspOss::initialise(string device) {
    // Open audio device
    deviceName = device;
    audio = open(device.c_str(), O_WRONLY, 0);
    if (audio == -1) {
        cout << "FAILED: unable to open " << deviceName << endl;
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
