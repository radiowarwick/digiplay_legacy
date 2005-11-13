#ifndef CLASS_AUDIOPLAYER
#define CLASS_AUDIOPLAYER

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "pthread.h"
using namespace std;

#include <sys/soundcard.h>
#include <sys/ioctl.h>

#include "config_reader.h"
#include "audiomixer.h"

/** An \c audioplayer takes audio from an \c audiomixer and outputs it
 * to a DSP device, given by the configuration.
 */
class audioplayer {
	public:
		/// Creates a new \c audioplayer for the given channel
		audioplayer(string Channel);

		/// Destructor
		~audioplayer();

		/// Attaches a mixer device to this \c audioplayer
		void attachMixer(audiomixer *mixer);
		
		// Outputs audio samples to sound device
		void output();

	private:
		void InitialiseHardware(string Device);

		audiomixer *amix;
		pthread_t Thread_Output;

		string DEVICE;
		string AUDIO_PATH;
		int DSP_SPEED;
		int audio;
		int dsp_speed;
};

void *thread_output(void *ptr);

#endif
