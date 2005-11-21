#include "triggerThread.h"

/* ===========================================
 * Studio trigger derived class
 * This registers a trigger with the database
 */
void studioTrigger::initialise(QWidget *o) {
	receiver = o;
}

void studioTrigger::operator()(int be_pid) {
    QCustomEvent *triggerEvent = new QCustomEvent(30000 + id);
    triggerEvent->setData(&be_pid);
    QApplication::postEvent(receiver, triggerEvent);	
}
// ===========================================

triggerThread::triggerThread(QWidget *o, QString dbstring, int loc, int count) {
	receiver = o;
	C = new Connection(dbstring.ascii());
	enabled = true;
	location = loc;
	trigger_count = count;
}

void triggerThread::run() {
	QString S;
	S = "trig_config_loc" + S.setNum(location);
	studioTrigger *T = new studioTrigger(C,S.ascii(),0);
	T->initialise(receiver);
	cout << T->name() << endl;
	while (enabled) {
		usleep(100000);
		C->get_notifs();
	}
}

void triggerThread::stop() {

}
