/*
 * Playlist GUI Module
 * TabPanelPlaylist.cpp
 * Provides a TabPanel which extracts and displays the playlist from the
 * central database.
 *
 * Copyright (c) 2006 Chris Cantwell
 * Copyright (c) 2006 Ian Liverton
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

#ifndef CLASS_TAB_PANEL_PLAYLIST
#define CLASS_TAB_PANEL_PLAYLIST

#include <qpixmap.h>
#include <qstring.h>
#include <qlistview.h>

#include "TabPanel.h"
#include "triggerThread.h"
#include "config.h"

#include "frmStudioManage.h"

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

class QTabWidget;
class Auth;

class TabPanelPlaylist : public TabPanel {
	Q_OBJECT
	public:
		TabPanelPlaylist(QTabWidget *parent, frmStudioManage *parent2, string text);
		~TabPanelPlaylist();
		void configure(Auth *authModule);
		void customEvent(QCustomEvent *event);

	public slots:
		virtual void playlistAdd(QListViewItem *current);
		virtual void listExpanded(QListViewItem *x);
		virtual void listCollapsed(QListViewItem *x);

	private:
		void draw();
		void clear();
		void getPlaylist();		
//		QString getTime( long smpl );
		frmStudioManage *parentForm;
		Connection *C;
		triggerThread *playlistTrigger;
		QListView *lstPlaylist;
		QPixmap *pixAList, *pixBList;
		QPixmap *pixExpanded, *pixCollapsed, *pixTrack;
};

#endif
