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
#include "QtTrigger.h"
#include "dps.h"

#include "TabPanelPlaylist.h"

/**
 * Constructor.
 */
TabPanelPlaylist::TabPanelPlaylist(QTabWidget *parent, string text)
		: TabPanel(parent,text) {
    // Set panel tag
	panelTag = "TabPlaylist";

    // Draw GUI components
    draw();
    
    // Create access to database
	DB = new DataAccess();	
    
    // Create database trigger for playlist updates. 
    triggerPlaylist = new QtTrigger("triggerPlaylist","trig_id5");
    connect(triggerPlaylist, SIGNAL(trigger()), 
                                    this, SLOT(processPlaylistUpdate()));
}


/**
 * Delete dynamically created objects
 */
TabPanelPlaylist::~TabPanelPlaylist() {
    // Delete GUI components.
    clear();
    
    // Delete database trigger and database access
    delete triggerPlaylist;
    delete DB;
}


/**
 * Update panel based on the current state of the authentication module.
 * @param   authModule      Authentication module reporting current state of auth.
 */
void TabPanelPlaylist::configure(Auth *authModule) {
	if (authModule->isPermitted(panelTag)) {
		processPlaylistUpdate();
	}
	TabPanel::configure(authModule);
}


/**
 * Emits the \a itemSelected signal when a playlist item is selected.
 * @param   current     List item specifying the selected item
 */
void TabPanelPlaylist::playlistAdd(QListViewItem *current) {
	if (current->text(3)) {
        emit itemSelected( current->text(3) );
	}
}


/**
 * Updates the display of the playlist.
 */
void TabPanelPlaylist::processPlaylistUpdate() {
    const char* routine = "TabPanelPlaylist::processPlaylistUpdate";
    L_INFO(LOG_TABPLAYLIST,"Refreshing playlist display.");
    
    QListViewItem *new_playlist = 0, *new_track = 0, *last_track = 0;
    
    // Clear the display
    lstPlaylist->clear();

    // Get list of playlists
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

    // For each playlist, get the items in that playlist
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

            // Populate this playlist
            for (unsigned int i = 0; i < R.size(); i++) {
                new_track = new QListViewItem(new_playlist,last_track,
                            R[i]["artist"].c_str(),
                            R[i]["title"].c_str(),
                            dps_prettyTime(atoi(R[i]["length_smpl"].c_str())),
                            R[i]["md5"].c_str());
                new_track->setPixmap(0,*pixTrack);
                last_track = new_track;
            }
            new_playlist->setOpen(true);
        }
        catch (...) {
            DB->abort("PlaylistRetrieve");
            L_ERROR(LOG_TABPLAYLIST,"Failed to get playlist '"+playlist+"'");
            return;
        }
    }
    DB->abort("PlaylistRetrieve");
}


/**
 * Change the icon for an item when it is expanded.
 */
void TabPanelPlaylist::listExpanded(QListViewItem *x) {
    x->setPixmap(0,*pixExpanded);
}


/**
 * Change the icon for an item when it is collapsed.
 */
void TabPanelPlaylist::listCollapsed(QListViewItem *x) {
    x->setPixmap(0,*pixCollapsed);
}


/**
 * Draw GUI components.
 */
void TabPanelPlaylist::draw() {
    QString path = DPSDIR;
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


/**
 * Delete GUI components.
 */
void TabPanelPlaylist::clear() {
	delete lstPlaylist;
	delete pixAList;
	delete pixBList;
}
