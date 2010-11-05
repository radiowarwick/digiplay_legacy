/*
 * Remote Starts module
 * remoteStartThread.h
 * Provides triggering of audio players through the parallel port
 *
 * Copyright (c) 2005-2006 Ian Liverton
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
#ifndef CLASS_REMOTE_START_THREAD
#define CLASS_REMOTE_START_THREAD

#include <QtGui/QApplication>
#include <QtCore/QObject>

#include "Thread.h"

class RemoteStartThread : public QObject,
						  public Thread {
	
	Q_OBJECT
	
	public:
		RemoteStartThread();
		~RemoteStartThread();
		void threadExecute();
        void start();
		void stop();

	signals:
		void player1_play();
		void player1_pause();
		void player2_play();
		void player2_pause();
		void player3_play();
		void player3_pause();
	
	private:
		ThreadMutex mutex;
		QObject *receiver;
		
		bool stopped;
		int status;
		int old_status;
};

#endif
