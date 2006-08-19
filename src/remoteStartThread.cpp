#include "remoteStartThread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

#define ADDRESS 0x378

remoteStartThread::remoteStartThread(QObject *o) {
	receiver = o;
	stopped = TRUE;
}

void remoteStartThread::run() {
	mutex.lock();
	stopped = FALSE;
	mutex.unlock();
	while(!stopped) {
		if (ioperm(ADDRESS,2,1)) {
			cout << "Couldn't open port at 0x378" << endl;
		}
		else {
			status = inb(ADDRESS+1);
			if (status != old_status) {
				QCustomEvent *remote;
				if ((status & 0x80) != 0x80) {
					remote = new QCustomEvent(40000);
					QApplication::postEvent(receiver, remote);
				}
				else {
					remote = new QCustomEvent(40001);
					QApplication::postEvent(receiver, remote);
				}
				if ((status & 0x40) == 0x40) {
					remote = new QCustomEvent(40002);
					QApplication::postEvent(receiver, remote);
				}
				else {
					remote = new QCustomEvent(40003);
					QApplication::postEvent(receiver, remote);
				}
				if ((status & 0x20) == 0x20) {
					remote = new QCustomEvent(40004);
					QApplication::postEvent(receiver, remote);
				}
				else {
					remote = new QCustomEvent(40005);
					QApplication::postEvent(receiver, remote);
				}
				old_status = status;
			}
		}
		usleep(100000);
	}
}

void remoteStartThread::stop() {
	mutex.lock();
	stopped = TRUE;
	mutex.unlock();
}
