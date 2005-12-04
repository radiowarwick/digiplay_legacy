#ifndef CLASS_TRIGGERTHREAD
#define CLASS_TRIGGERTHREAD

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/trigger"
using namespace pqxx;

#include <qmutex.h>
#include <qstring.h>
#include <qthread.h>
#include <qapplication.h>

#ifndef CLASS_STUDIOTRIGGER
#define CLASS_STUDIOTRIGGER
class studioTrigger : public trigger {
    public:
        studioTrigger(Connection *C, string name, int config_id) 
			: trigger(*C,name), id(config_id) {;}
		void initialise(QWidget *o);
        void operator()(int be_pid);
		
	private:
		QWidget *receiver;
		int id;
};
#endif

class triggerThread : public QThread {
	public:
		triggerThread(QWidget *o, QString dbstring, int loc, int count);
		void run();
		void stop();

	private:
		QWidget *receiver;
		QString db_connect;
		bool enabled;
		int location;
		int trigger_count;
};

#endif
