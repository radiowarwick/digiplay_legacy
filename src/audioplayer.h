/*
 * Audio Player module
 * audioplayer.h
 * Pulls audio from an audiochannel or audiomixer and passes to soundcard using
 * OSS.
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

#include "config.h"
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
