/**
 * ALSA output module for Digiplay (based on the original OutputDsp.cpp)
 * @author Phil Ashby
 * @date June-2009
 *
 */

#include <iostream>
#include <string.h>
using namespace std;

#include "OutputDspAlsa.h"

namespace Audio {
    /**
     * Dynamic loader entry point
     */
    extern "C" {
        Output * OUTPUT_SO_ENTRY(const char *device) {
            string deviceName = device;
            return new OutputDspAlsa(deviceName);
        }
    };

    OutputDspAlsa::OutputDspAlsa(string channel) {
        audio = NULL;
        initialise(channel);
    }

    OutputDspAlsa::~OutputDspAlsa() {
        if (audio)
            snd_pcm_close(audio);
    }

    void OutputDspAlsa::receiveMessage(PORT inPort, MESSAGE message) {
        if (inPort != IN0) {
            cout << "OutputDspAlsa::receive: only use IN0 on a DSP device"
                 << endl;
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

    void OutputDspAlsa::onPatch(PORT localPort) {

    }

    void OutputDspAlsa::onUnpatch(PORT localPort) {

    }

    void OutputDspAlsa::threadExecute() {
       if (!connectedDevice(IN0))
            cout << "CONNECTED DEVICE IS NULL" << endl;

        AudioPacket *buffer = new AudioPacket(PACKET_SAMPLES);
        SAMPLEVAL *d = buffer->getData();

        ComponentAudio *C;

        while (!threadTestKill()) {
            if (audioState != STATE_PLAY) {
                snd_pcm_state_t s = snd_pcm_state(audio);
                if (s == SND_PCM_STATE_RUNNING || s == SND_PCM_STATE_XRUN) {
                    snd_pcm_drain(audio);
                    snd_pcm_prepare(audio);
                }
            }

          if (audioState == STATE_STOP) {
              usleep(10000);
              continue;
          }

          if (audioState == STATE_PAUSE) {
              usleep(1000);
              continue;
          }

          if (!(C = dynamic_cast<ComponentAudio *>(connectedDevice(IN0)))) {
              usleep(10000);
              continue;
          }

            C->getAudio(buffer);
            int r = snd_pcm_writei (audio, d, PACKET_SAMPLES/2);
            if (r != PACKET_SAMPLES/2) {
                if (r == -EPIPE) {
                    cout << "XRUN" << endl;
                    snd_pcm_prepare(audio);
                } else {
                    cout << "Failed to write all of buffer" << endl;
                    throw -1;
                }
            }
        }
        delete buffer;
    }


    /**
     * Opens and initialises an output DSP device.
     * @param   device      The DSP device to initialise.
     */
    void OutputDspAlsa::initialise(string device) {
		int err;

        // Open audio device
        if ((err = snd_pcm_open(	&audio, 
									device.c_str(), 
									SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
            cout << "FAILED: unable to open " << device << endl;
			cout << "Error: " << snd_strerror(err) << endl;
            throw 0;
        }

		if ((err = snd_pcm_set_params(audio,
									SND_PCM_FORMAT_S16_LE,
									SND_PCM_ACCESS_RW_INTERLEAVED,
									2,
									44100,
									1,
									100000)) < 0) {
			cout << "FAILED: unable to set ALSA parameters." << endl;
			cout << "Error: " << snd_strerror(err) << endl;
			throw 0;
		}
        
		if ((err = snd_pcm_prepare(audio)) < 0) {
            cout << "FAILED: unable to prepare device: " << device << endl;
			cout << "Error: " << snd_strerror(err) << endl;
            throw 0;
        }
    }

}
