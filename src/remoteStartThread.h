#include <iostream>
using namespace std;
#include <qmutex.h>
#include <qthread.h>
#include <qapplication.h>
#include <qobject.h>

#include "triggerThread.h"

class remoteStartThread : public QThread 
{
public:
	remoteStartThread(QObject *o);
	void run();
	void stop();
	
private:
	QMutex mutex;
	QObject *receiver;
	
	bool stopped;
	int status;
	int old_status;
	studioTrigger *T;
};
