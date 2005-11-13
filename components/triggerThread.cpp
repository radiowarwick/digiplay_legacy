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
	vector<studioTrigger*> *T = new vector<studioTrigger*>;
	for (int i = 0; i < trigger_count; i++) {
		QString S, temp;
		temp.setNum(i,10);
		if (i < 10) temp = "0" + temp;
		S = "trig" + S.setNum(location) + temp;
		T->push_back(new studioTrigger(C,S.ascii(),i));
		T->at(i)->initialise(receiver);
		cout << "Added trigger: " << T->at(i)->name() << endl;
	}
	while (enabled) {
		usleep(100000);
		C->get_notifs();
	}
}

void triggerThread::stop() {

}
