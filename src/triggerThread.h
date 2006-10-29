#ifndef CLASS_TRIGGERTHREAD
#define CLASS_TRIGGERTHREAD

#include <string>
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
		void initialise(QObject *o);
        void operator()(int be_pid);
		
	private:
		QObject *receiver;
		int id;
};
#endif

class triggerThread : public QThread {
	public:
		triggerThread(QObject *o, QString dbstring, int t_id);
		void run();
		void stop();

	private:
		QObject *receiver;
		QString db_connect;
		bool enabled;
		int id;
};

#endif
