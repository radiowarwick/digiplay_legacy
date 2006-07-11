#include "triggerThread.h"

/* ===========================================
 * Studio trigger derived class
 * This registers a trigger with the database
 */
void studioTrigger::initialise(QObject *o) {
	receiver = o;
}

void studioTrigger::operator()(int be_pid) {
    QCustomEvent *triggerEvent = new QCustomEvent(30000 + id);
    triggerEvent->setData(&be_pid);
    QApplication::postEvent(receiver, triggerEvent);	
}
// ===========================================

triggerThread::triggerThread(QObject *o, QString dbstring, int t_id) {
	receiver = o;
	db_connect = dbstring;
	
	enabled = true;
	id = t_id;
}

void triggerThread::run() {
	QString S;
	S = "trig_id" + S.setNum(id);
	Connection *C = new Connection(db_connect.ascii());
	studioTrigger *T = new studioTrigger(C,S.ascii(),id);
	T->initialise(receiver);
	while (enabled) {
		usleep(100000);
		C->get_notifs();
	}
}

void triggerThread::stop() {

}
