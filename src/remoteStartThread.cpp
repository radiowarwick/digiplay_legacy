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
#include "remoteStartThread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

#include "Config.h"
#include "Security.h"

#define ADDRESS 0x378

remoteStartThread::remoteStartThread(QObject *o) {
	receiver = o;
	stopped = TRUE;
}

void remoteStartThread::run() {
	// Look up normal user in config and drop privilages
	Config *conf = new Config("digiplay");
	mutex.lock();
	stopped = FALSE;
	mutex.unlock();
	gainPrivilage();
	showPrivilage();
	if (ioperm(ADDRESS,2,1)) {
	    dropPrivilage(conf->getParam("user"));
		delete conf;
		cout << "Couldn't open port at address ";
		printf("%x\n",ADDRESS);
	}
	else {
	    dropPrivilage(conf->getParam("user"));
		delete conf;
		while(!stopped) {
			status = inb(ADDRESS+1);
			if (status != old_status) {
				int changed = status^old_status;
				QCustomEvent *remote;
				if ((changed & 0x80) == 0x80) {
					if ((status & 0x80) == 0x80) {
						remote = new QCustomEvent(40000);
						QApplication::postEvent(receiver, remote);
					}
					else {
						remote = new QCustomEvent(40001);
						QApplication::postEvent(receiver, remote);
					}
				}
				if ((changed & 0x40) == 0x40) {
					if ((status & 0x40) != 0x40) {
						remote = new QCustomEvent(40002);
						QApplication::postEvent(receiver, remote);
					}
					else {
						remote = new QCustomEvent(40003);
						QApplication::postEvent(receiver, remote);
					}
				}
				if ((changed & 0x20) == 0x20) {
					if ((status & 0x20) != 0x20) {
						remote = new QCustomEvent(40004);
						QApplication::postEvent(receiver, remote);
					}
					else {
						remote = new QCustomEvent(40005);
						QApplication::postEvent(receiver, remote);
					}
				}
				old_status = status;
			}

		usleep(100000);
		}
	}

	cout << "Finished thread" << endl;
}

void remoteStartThread::stop() {
	mutex.lock();
	stopped = TRUE;
	mutex.unlock();
}
