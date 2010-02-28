/**
 * JACK output module for RaW Digiplay
 * @author Phil Ashby
 * @date June-2009
 *
 * TODO: Better typing for entry point (including extern "C" prototype)
 */

#include "Output.h"

#include <iostream>
#include <string.h>
using namespace std;

#include <jack/jack.h>

#include "OutputDspJack.h"

namespace Audio {

    /**
     * Dynamic loader entry point
     */
    extern "C" {
        Output * OUTPUT_SO_ENTRY(const char *device) {
            string deviceName = device;
            return new OutputDspJack(deviceName);
        }
    };

    OutputDspJack::OutputDspJack(string channel) {
        initialise(channel);
    }

    OutputDspJack::~OutputDspJack() {
        if (client) {
            jack_deactivate(client);
            if (left)
                jack_port_unregister(client, left);
            if (right)
                jack_port_unregister(client, right);
            jack_client_close(client);
        }
    }

    void OutputDspJack::receiveMessage(PORT inPort, MESSAGE message) {
        if (inPort != IN0) {
            cout << "OutputDspJack::receive: only use IN0 on a DSP device" << endl;
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

    void OutputDspJack::onPatch(PORT localPort) {

    }

    void OutputDspJack::onUnpatch(PORT localPort) {

    }

    void OutputDspJack::threadExecute() {
       if (!connectedDevice(IN0))
            cout << "CONNECTED DEVICE IS NULL" << endl;

        AudioPacket *buffer = new AudioPacket(PACKET_SAMPLES);
        SAMPLEVAL *d = buffer->getData();
        SAMPLE size = buffer->getSize();
        dbuf = new jack_default_audio_sample_t[bufSize*2];

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

          if (!(C = dynamic_cast<ComponentAudio *>(connectedDevice(IN0)))) {
              usleep(10000);
              continue;
          }

            jack_nframes_t samples = 0;
            while (samples < bufSize) {
                C->getAudio(buffer);
                // Pre-process 16-bit interleaved audio into two blocks of floats for JACK
                for(SAMPLE n=0; n<size; n+=2) {
                    dbuf[samples] = (float)d[n]/32768.0;
                    dbuf[samples+bufSize] = (float)d[n+1]/32768.0;
                    samples++;
                }
            }
            bufReady = 1;
            pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
            pthread_cond_wait(sync, &mutex);
        }
        delete dbuf;
        delete buffer;
    }


    /**
     * Opens and initialises an output DSP device.
     * @param   device      The DSP device to initialise.
     */
    int OutputDspJack::jack_callback(jack_nframes_t nframes, void *arg) {
        OutputDspJack *me = (OutputDspJack *)arg;
        return me->process(nframes);
    }

    int OutputDspJack::process(jack_nframes_t nframes) {
        jack_default_audio_sample_t *lbuf =
            (jack_default_audio_sample_t *)jack_port_get_buffer(left, nframes);
        jack_default_audio_sample_t *rbuf =
            (jack_default_audio_sample_t *)jack_port_get_buffer(right, nframes);
        if (bufReady && dbuf && nframes == bufSize) {
            // Copy out pre-processed blocks
            memcpy(lbuf, dbuf, nframes * sizeof(jack_default_audio_sample_t));
            memcpy(rbuf, dbuf+bufSize,
                nframes * sizeof(jack_default_audio_sample_t));
            bufReady = 0;
        } else {
            for(jack_nframes_t n=0; n<nframes; n++) {
                lbuf[n] = 0.0;
                rbuf[n] = 0.0;
            }
        }
        pthread_cond_signal(sync);
        return 0;
    }

    void OutputDspJack::initialise(string device) {
        client = jack_client_open(device.c_str(), (jack_options_t)0, NULL);
        if (!client) {
            cerr << "FAILED: unable to open JACK as " << device << endl;
            throw 0;
        }
        // Check sample rate is valid (44k1 only)
        jack_nframes_t sr = jack_get_sample_rate(client);
        if (sr != 44100) {
            cerr << "FAILED: sample rate != 44100: " << sr << endl;
            throw sr;
        }
        // Read buffer size, check it's a multiple of PACKET_SAMPLES/2
        bufSize = jack_get_buffer_size(client);
        cout << "OutputDspJack: buffer size " << bufSize << endl;
        if (bufSize < PACKET_SAMPLES/2 || (bufSize/(PACKET_SAMPLES/2))*(PACKET_SAMPLES/2) != bufSize) {
            cerr << "FAILED: jack buffer size not a multiple of " << PACKET_SAMPLES << endl;
            throw bufSize;
        }
        // Create ports for sending audio to JACK
        left = jack_port_register(
            client, "left", JACK_DEFAULT_AUDIO_TYPE,
            JackPortIsOutput | JackPortIsTerminal, 0);
        right = jack_port_register(
            client, "right", JACK_DEFAULT_AUDIO_TYPE,
            JackPortIsOutput | JackPortIsTerminal, 0);
        if (!left || !right) {
            cerr << "FAILED: unable to register a JACK port" << endl;
            throw 0;
        }
        // Create buffer synchronisation object
        sync = new pthread_cond_t;
        pthread_cond_init(sync, NULL);
        bufReady = 0;
        // Set our callback method and tell JACK we're ready to rumble
        jack_set_process_callback(client, jack_callback, this);
        jack_activate(client);
    }

}
