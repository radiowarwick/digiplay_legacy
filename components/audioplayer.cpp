
#include "audioplayer.h"

/** Instantiates an \c audioplayer class.
 * Reads configuration using a \c config_reader and then initilises the 
 * audio output hardware
 * @param Channel String specifying the parameter in the config file
 * 					which specifies the output device to use
 */
audioplayer::audioplayer(string Channel) {
    config *Conf = new config("digiplay");
    DEVICE = Conf->getParam(Channel).c_str();
    delete Conf;
    InitialiseHardware(DEVICE);
}

audioplayer::~audioplayer() {

}

/** Attaches a mixer to this playout device. Allows the \c audioplayer to
 * retrieve audio samples from the \c audiomixer. This routine creates a new 
 * thread which reads from the \c audiomixer and outputs to the sound device.
 * @param mixer Pointer to an \c audiomixer
 */
void audioplayer::attachMixer(audiomixer *mixer) {
	amix = mixer;
    int Ret_Output = pthread_create(&Thread_Output, NULL,
	                                thread_output, (void*)this);
	if (Ret_Output != 0) {
		cout << "Error creating playout thread!" << endl;
		return;
	}
}

/** This routine is for internal use only
 */
void audioplayer::output() {
	char *buffer = new char[256];
	do {
		amix->getAudio(buffer, 256);
		if (write (audio, buffer, 256) != 256) {
            cout << "FATAL: Failed to write all of buffer" << endl;
            abort();
        }
		if (DEVICE == "/dev/null") usleep(150);
	} while (true);
	delete[] buffer;
		
}

/** Opens the specified audio device and initialises it to the correct
 * sample rate, etc
 * @param Device Location of output device e.g. \c /dev/dsp0
 */
void audioplayer::InitialiseHardware(string Device) {
    cout << " -> Initialising audio hardware for " << Device << "..." << endl;
    dsp_speed = 44100;
    int dsp_sample_size = 16;
    int dsp_stereo = 1;
    int dsp_profile = APF_NORMAL;

    int audio_buffer_size = 2048;
    //open audio device
    audio = open (Device.c_str(), O_WRONLY, 0);
    if (audio == -1) {
        cout << "   -> FATAL: Unable to open device " << Device << endl;
        exit (-1);
    }
    //configure audio device
    int tmp = dsp_sample_size;
    ioctl(audio, SNDCTL_DSP_SAMPLESIZE, &dsp_sample_size);
    if (tmp != dsp_sample_size) {
        cout << "   -> WARNING: " << DEVICE 
			<< ": Unable to set sample size" << endl;
    }
    ioctl(audio, SNDCTL_DSP_PROFILE, &dsp_profile);

    if (ioctl (audio, SNDCTL_DSP_STEREO, &dsp_stereo)==-1) {
        cout << "   -> WARNING: " << DEVICE
			<< ": Unable to set Stereo flag" << endl;
    }

    if (ioctl (audio, SNDCTL_DSP_SPEED, &dsp_speed) == -1) {
        cout << "   -> WARNING: " << DEVICE
			<< ": Unable to set DSP speed" << endl;
    }

    ioctl (audio, SNDCTL_DSP_GETBLKSIZE, &audio_buffer_size);
    if (audio_buffer_size < 1) {
        cout << "   -> WARNING: " << DEVICE
			<< ": Unable to get block size" << endl;
    }

    int arg = 0x0002000B;
    if (ioctl (audio, SNDCTL_DSP_SETFRAGMENT, &arg)) {
        cout << "   -> ERROR: " << DEVICE
			<< ": occured setting buffer!" << endl;
    }

    ioctl (audio, SNDCTL_DSP_GETBLKSIZE, &audio_buffer_size);
    if (audio_buffer_size < 1) {
        cout << "   -> WARNING: " << DEVICE
			<< ": Unable to get block size" << endl;
    }
	cout << "   -> Hardware Initialisation complete." << endl;
}


void *thread_output(void *ptr) {
	audioplayer *p = (audioplayer*)ptr;
	p->output();
	pthread_exit(NULL);
}
