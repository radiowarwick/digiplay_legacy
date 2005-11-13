/* AUDIO MIXER HEADER FILE
 *
 * Takes multiple audio files \ dsp inputs and mixes to a buffered output
 */

#ifndef CLASS_AUDIOMIXER
#define CLASS_AUDIOMIXER

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "fcntl.h"
#include <string>
#include <algorithm>
#include "pthread.h"
using namespace std;

#include "config_reader.h"
#include "audiochannel.h"

#define BUFFER_SIZE 256

/**
 * an audio mixer has a number of channels that supply it with audio.
 * the mixer mixes the samples together as a sum of the input samples.
 */
class audiomixer {
	public:
		audiomixer();
		~audiomixer();
		
		/// Adds a new channel to the audio mixer
		void createChannel();
		
		/// Deletes an existing channel from the audio mixer
		void destroyChannel(unsigned short index);
		
		/// Returns the number of channels in the audio mixer
		short size();
		
		/// Returns an audiochannel object for the requested index
		audiochannel* channel(unsigned short index);
		
		/// Get mixed audio from the mixer
		void getAudio(char* mix_buffer, unsigned int size);

	private:
		/// Vector of channels that comprise this mixer
		vector<audiochannel*>* channels;
		
		/// Vector of input buffers. Each channel has its own input buffer
		/// in the mixer, used to mix the samples.
		vector<char*>* buffers;
};

#endif
