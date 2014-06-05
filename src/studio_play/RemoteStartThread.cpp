/*
 * Remote Starts module
 * remoteStartThread.cpp
 * Provides triggering of audio players through the ALSA MIDI port
 *
 * Copyright (c) 2014 Jonty Sewell
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
#include "RemoteStartThread.h"
#include "Logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <alsa/asoundlib.h>

#include "Security.h"

#define MIDI_DEVICE "Digiplay"

RemoteStartThread::RemoteStartThread() {
	const char* routine = "RemoteStartThread::RemoteStartThread";

	stopped = TRUE;

	int portid;

	if (snd_seq_open(&seq_handle, "default", SND_SEQ_OPEN_INPUT, 0) < 0) {
		fprintf(stderr, "Error opening ALSA sequencer.\n");
		exit(1);
	}
	snd_seq_set_client_name(seq_handle, MIDI_DEVICE);
	if ((portid = snd_seq_create_simple_port(seq_handle, MIDI_DEVICE,
	 SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE,
	 SND_SEQ_PORT_TYPE_APPLICATION)) < 0) {
		fprintf(stderr, "Error creating sequencer port.\n");
		exit(1);
	}

}


RemoteStartThread::~RemoteStartThread() {
	snd_seq_close(seq_handle);
	threadKill();
	threadWait();
}

		
void RemoteStartThread::threadExecute() {
	const char* routine = "RemoteStartThread::run";
	mutex.lock();
	stopped = FALSE;
	mutex.unlock();

	int npfd;
	struct pollfd *pfd;

	npfd = snd_seq_poll_descriptors_count(seq_handle, POLLIN);
	pfd = (struct pollfd *)alloca(npfd * sizeof(struct pollfd));
	snd_seq_poll_descriptors(seq_handle, pfd, npfd, POLLIN);

	while(!stopped) {

		if (poll(pfd, npfd, 100000) > 0) {
			snd_seq_event_t *ev;

			do {
				snd_seq_event_input(seq_handle, &ev);
				switch (ev->type) {
					case SND_SEQ_EVENT_NOTEON:
						switch (ev->data.control.channel) {
							case 0:
								emit player1_play();
								break;
							case 1:
								emit player2_play();
								break;
							case 2:
								emit player3_play();
								break;
						}
						break;
					case SND_SEQ_EVENT_NOTEOFF: 
						switch (ev->data.control.channel) {
							case 0:
								emit player1_pause();
								break;
							case 1:
								emit player2_pause();
								break;
							case 2:
								emit player3_pause();
								break;
						}
						break;
				}
				snd_seq_free_event(ev);
			} while (snd_seq_event_input_pending(seq_handle, 0) > 0);

		}
		usleep(100000);
	}
}

void RemoteStartThread::start() {
	threadStart();    
}

void RemoteStartThread::stop() {
	mutex.lock();
	stopped = TRUE;
	mutex.unlock();
}
