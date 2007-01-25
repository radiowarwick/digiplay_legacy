/*
 * Database Trigger class
 * triggerThread.cpp
 * Listens on a database trigger and sends a QCustomEvent on activity
 *
 * Copyright (c) 2005-2006 Chris Cantwell
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
    if (C && C->is_open()) {
        C->Disconnect();
    }
    delete C;
}

void triggerThread::stop() {
    enabled = false;
}
