/*
 * Database Trigger class
 * triggerThread.h
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
