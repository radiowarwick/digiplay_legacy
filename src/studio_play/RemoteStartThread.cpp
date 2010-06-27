/*
 * Remote Starts module
 * remoteStartThread.cpp
 * Provides triggering of audio players through the parallel port
 *
 * Copyright (c) 2005-2006 Ian Liverton
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
#include <sys/io.h>

#include "Security.h"

#define ADDRESS 0x378

RemoteStartThread::RemoteStartThread() {
    const char* routine = "RemoteStartThread::RemoteStartThread";
    char *error = new char[256];

	stopped = TRUE;

	gainPrivilage();
	
	//Open the parallel port
	if (ioperm(ADDRESS,2,1)) {
		//If the port cannot be opened log an error
        sprintf(error, "Couldn't open parallel port at address %x\n", ADDRESS);
	    L_ERROR(LOG_AUDIOHW, error);
	    dropPrivilage();
	    delete[] error;
	    throw -1;
	}
	else {
		//If the port has been opened, log a confirmation message
        sprintf(error, "Succesfully opened parallel port at address %x\n", ADDRESS);
	    L_INFO(LOG_AUDIOHW, error);
	    dropPrivilage();
	}
	delete[] error;
}


RemoteStartThread::~RemoteStartThread() {
	threadKill();
	threadWait();
}

		
void RemoteStartThread::threadExecute() {
    const char* routine = "RemoteStartThread::run";
	mutex.lock();
	stopped = FALSE;
	mutex.unlock();
	
	while(!stopped) {
		//Read in a byte from the parallel port status register
		status = inb(ADDRESS+1);
		//Check to see if the value has changed
		if (status != old_status) {
			//If it has, extract the bits that have changed (XOR)
			int changed = status^old_status;
			//Check to see if it was the "Busy" line which changed
			if ((changed & 0x80) == 0x80) {
				//Check to see whether it was a play or pause command
				//NOTE:  This line is "hardware inverted" in the port
				//so the software logic for this line is swapped - 
				//(status & 0x80) != 0x80 as opposed to
				//(status & 0x80) == 0x80 as all the other lines
				if ((status & 0x80) != 0x80) {
					//Play player 1
					emit player1_play();
				}
				else {
					//Pause player 1
					emit player1_pause();
				}
			}
			//Check to see if it was the "Ack" line which changed
			if ((changed & 0x40) == 0x40) {
				//Check to see whether it was a play or pause command
				if ((status & 0x40) == 0x40) {
					//Play player 2
					emit player2_play();
				}
				else {
					//Pause player 2
					emit player2_pause();
				}
			}
			//Check to see if it was the "Paper Out" line which changed
			if ((changed & 0x20) == 0x20) {
				//Check to see whether it was a play or pause command
				if ((status & 0x20) == 0x20) {
					//Play player 3
					emit player3_play();
				}
				else {
					//Pause player 3
					emit player3_pause();
				}
			}
			old_status = status;
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
