#include <iostream>
using namespace std;
#include <qmutex.h>
#include <qstring.h>
#include <qthread.h>
#include <qapplication.h>
#include <ctime>

class clockThread : public QThread 
{
public:
	clockThread(QWidget *o) : receiver(o), stopped(FALSE) {;}
	void run();
	void stop();
	
private:
	QWidget *receiver;
	QMutex mutex;
	QString getPrettyDate(tm *local);
	bool stopped;
};
