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
#ifndef CLOCK_THREAD_H
#define CLOCK_THREAD_H

#include <QtCore/QMutex>
#include <QtCore/QString>
#include <QtCore/QThread>
#include <QtCore/QEvent>
#include <QtGui/QApplication>
#include <ctime>

class clockThread : public QThread
{
public:
	clockThread(QObject *o) : receiver(o), stopped(FALSE) {;}
	void run();
	void stop();

private:
	QObject *receiver;
	QMutex mutex;
	QString getPrettyDate(tm *local);
	bool stopped;
};

class ClockUpdateEvent : public QEvent {
public:
    ClockUpdateEvent(Type type) : QEvent(type) {}
    ClockUpdateEvent(const ClockUpdateEvent& pSrc)
        : QEvent(pSrc), mData(pSrc.mData) {}
    virtual ~ClockUpdateEvent() {}

    QString data() const {return mData;}
    void setData(QString pData) { mData = pData; }

protected:
    QString mData;
};

#endif
