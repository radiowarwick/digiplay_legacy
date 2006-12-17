/*
 * Audio Mixer module
 * audiomixer.h
 * Pulls audio off multiple audiochannel modules and mixes to a single cached
 * audio stream. Currently only supports cumulative mixing; this will be fixed
 * in the newer AudioLib library modules.
 * NOTE: audio distortion may occur as a result.
 *
 * Copyright (c) 2004-2005 Chris Cantwell
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
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
		audiochannel* createChannel();
		
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
