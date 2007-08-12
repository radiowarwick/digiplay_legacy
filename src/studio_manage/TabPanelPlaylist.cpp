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

#include <qtabwidget.h>
#include <qtextbrowser.h>
#include <qstring.h>
#include <qiconset.h>
#include <qheader.h>
#include <qapplication.h>
#include <qobject.h>
#include <qpixmap.h>
#include <qlistview.h>

#include "Auth.h"
#include "Logger.h"
#include "DataAccess.h"
#include "DbTrigger.h"
#include "dps.h"

#include "TabPanelPlaylist.h"

TabPanelPlaylist::TabPanelPlaylist(QTabWidget *parent, string text)
		: TabPanel(parent,text) {
	panelTag = "TabPlaylist";
	DB = new DataAccess();	
    
    triggerPlaylist = new DbTrigger("triggerPlaylist","trig_id5");
    triggerPlaylist->start();
    connect(triggerPlaylist, SIGNAL(trigger()), 
                                    this, SLOT(processPlaylistUpdate()));

	draw();
}

// clean up stuff
TabPanelPlaylist::~TabPanelPlaylist() {
    triggerPlaylist->stop();
    delete triggerPlaylist;
    delete DB;
}

// this is called whenever the application reconfigures itself,
// usually due to a change in authentication status (login, logoff)
void TabPanelPlaylist::configure(Auth *authModule) {
	if (authModule->isPermitted(panelTag)) {
		getPlaylist();
	}
	TabPanel::configure(authModule);
}

// This handles drawing the contents of the form, and connecting slots,
// but has little actual implementation
void TabPanelPlaylist::draw() {
	QString path = qApp->applicationDirPath();
	pixExpanded = new QPixmap(path+"/images/expand16.png");
	pixCollapsed = new QPixmap(path+"/images/contract16.png");
	pixTrack = new QPixmap(path+"/images/music16.png");
	
	// do all form drawing here, create widgets, set properties
	lstPlaylist = new QListView(getPanel(), "lstEmail" );

	lstPlaylist->setGeometry( QRect( 20, 20, 480, 610 ) );
	lstPlaylist->setVScrollBarMode( QListView::AlwaysOn );
	lstPlaylist->setAllColumnsShowFocus( TRUE );
	lstPlaylist->setColumnWidthMode(3, QListView::Manual);
	lstPlaylist->setColumnWidth(3, 0);
	lstPlaylist->header()->setMovingEnabled( FALSE );
	lstPlaylist->addColumn( tr( "Artist" ) );
	lstPlaylist->header()->setResizeEnabled( FALSE,
			lstPlaylist->header()->count() -1);
	lstPlaylist->addColumn( tr( "Title" ) );
	lstPlaylist->header()->setResizeEnabled( FALSE,
			lstPlaylist->header()->count() -1);
	lstPlaylist->addColumn( tr( "Length" ) );
	lstPlaylist->header()->setResizeEnabled( FALSE,
			lstPlaylist->header()->count() -1);
	lstPlaylist->addColumn( tr( "ID" ) );
	lstPlaylist->header()->setResizeEnabled( FALSE,
			lstPlaylist->header()->count() -1);
	lstPlaylist->setColumnWidthMode(0, QListView::Manual);
	lstPlaylist->setColumnWidthMode(1, QListView::Manual);
	lstPlaylist->setColumnWidthMode(2, QListView::Manual);
	lstPlaylist->setColumnWidthMode(3, QListView::Manual);
	lstPlaylist->setColumnWidth(0, 190);
	lstPlaylist->setColumnWidth(1, 185);
	lstPlaylist->setColumnWidth(2, 80);
	lstPlaylist->setColumnWidth(3, 0);
	lstPlaylist->header()->setMovingEnabled( FALSE );
	lstPlaylist->setSorting(-1,FALSE);

	// connect signals and slots here
	QObject::connect( lstPlaylist, SIGNAL( doubleClicked(QListViewItem*) ),
				this, SLOT( playlistAdd(QListViewItem*) ) );
	QObject::connect( lstPlaylist, SIGNAL( expanded(QListViewItem*) ),
				this, SLOT( listExpanded(QListViewItem*) ) );
	QObject::connect( lstPlaylist, SIGNAL( collapsed(QListViewItem*) ),
				this, SLOT( listCollapsed(QListViewItem*) ) );
}


void TabPanelPlaylist::getPlaylist(){
	char *routine = "TabPanelPlaylist::getPlaylist";
	QListViewItem *new_playlist = 0, *new_track = 0, *last_track = 0;
	string SQL = "SELECT id,name FROM playlists ORDER BY name DESC";

	PqxxResult Playlists;
	try {
		Playlists = DB->exec("PlaylistRetrieve", SQL);
	}
	catch (...) {
		DB->abort("PlaylistRetrieve");
		L_ERROR(LOG_TABPLAYLIST,"Failed to get list of playlists");
		return;
	}

	lstPlaylist->clear();


	for (unsigned int j = 0; j < Playlists.size(); j++) {
		last_track = 0;
		string playlist = Playlists[j]["name"].c_str();
		new_playlist = new QListViewItem(lstPlaylist, playlist);
		new_playlist->setPixmap (0, *pixExpanded);
		SQL = "SELECT * FROM v_playlists WHERE playlistid = "
				+ string(Playlists[j]["id"].c_str());
		PqxxResult R;
		try {
			R = DB->exec("PlaylistRetrieve",SQL);

			for (unsigned int i = 0; i < R.size(); i++) {
				new_track = new QListViewItem(new_playlist,last_track,
							R[i]["artist"].c_str(),
							R[i]["title"].c_str(),
							dps_prettyTime(atoi(R[i]["length_smpl"].c_str())),
							R[i]["md5"].c_str());
				new_track->setPixmap(0,*pixTrack);
				last_track = new_track;
			}
            L_INFO(LOG_TABPLAYLIST,"Before open");
			new_playlist->setOpen(true);
            L_INFO(LOG_TABPLAYLIST,"After open");
		}
		catch (...) {
	        DB->abort("PlaylistRetrieve");
			L_ERROR(LOG_TABPLAYLIST,"Failed to get playlist '"+playlist+"'");
            return;
		}
	}
    DB->abort("PlaylistRetrieve");
}

void TabPanelPlaylist::playlistAdd(QListViewItem *current) {
	if (current->text(3)) {
        emit itemSelected( current->text(3) );
	}
}

void TabPanelPlaylist::clear() {
	delete lstPlaylist;
	delete pixAList;
	delete pixBList;
}

void TabPanelPlaylist::processPlaylistUpdate() {
    char* routine = "TabPanelPlaylist::processPlaylistUpdate";
    L_INFO(LOG_TABPLAYLIST,"Playlist table updated.");
    getPlaylist();
}

void TabPanelPlaylist::listExpanded(QListViewItem *x) {
	x->setPixmap(0,*pixExpanded);
}

void TabPanelPlaylist::listCollapsed(QListViewItem *x) {
	x->setPixmap(0,*pixCollapsed);
}
