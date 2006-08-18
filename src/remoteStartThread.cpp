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
	T->initialise(receiver);
	while(!stopped) {
		if (ioperm(ADDRESS,2,1))
			cout << "Couldn't open port at 0x378" << endl;
	status = inb(ADDRESS+1);
	if (status != old_status) {
		QCustomEvent *remote;
		if ((status & 0x80) != 0x80) {
			remote = new QCustomEvent(40000);
			QApplication::postEvent(receiver, remote);
		}
		else if ((status & 0x80) == 0x80) {
			remote = new QCustomEvent(40001);
			QApplication::postEvent(receiver, remote);
		}
		
	}
	usleep(10000);
	}
}

void remoteStartThread::stop() {
	mutex.lock();
	stopped = TRUE;
	mutex.unlock();
}
