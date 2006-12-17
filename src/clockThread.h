/*
 * Clock module
 * clockThread.h
 * Provides date/time in a separate QThread 
 *
 * Copyright (c) 2004-2005 Chris Cantwell
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
