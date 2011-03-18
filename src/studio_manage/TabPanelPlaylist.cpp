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
#include <cstdlib>

#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtCore/QString>
#include <QtGui/QIconSet>
#include <QtGui/QHeaderView>
#include <QtGui/QApplication>
#include <QtCore/QObject>
#include <QtGui/QPixmap>
#include <QtGui/QStandardItemModel>
#include <QtGui/QTreeView>

#include "Auth.h"
#include "Logger.h"
#include "DataAccess.h"
#include "QtTrigger.h"
#include "dps.h"

#include "TabPanelPlaylist.h"

/**
 * Constructor.
 */
TabPanelPlaylist::TabPanelPlaylist(QTabWidget *parent, QString text)
		: TabPanel(parent,text) {
    // Set panel tag
	panelTag = "TabPlaylist";

	TabPanel::setIcon(QIcon(":/icons/jingle16.png"));

    // Draw GUI components
    draw();
    
    // Create access to database
	DB = new DataAccess();	
    
    // Create database trigger for playlist updates. 
    triggerPlaylist = new QtTrigger("triggerPlaylist","t_playlists");
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
void TabPanelPlaylist::playlistAdd(const QModelIndex& x) {
    if (!x.parent().isValid())
    {
        return;
    }
    int list = x.parent().row();
    int item = x.row();
    QString vIdx = modPlaylist->item(list,0)->child(item,3)->text();
    DpsAudioItem vAudio(vIdx.toLong());
    emit audioSelected( vAudio );
}


/**
 * Updates the display of the playlist.
 */
void TabPanelPlaylist::processPlaylistUpdate() {
    const char* routine = "TabPanelPlaylist::processPlaylistUpdate";
    L_INFO(LOG_TABPLAYLIST,"Refreshing playlist display.");
    
    QStandardItem *new_playlist;

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

    modPlaylist->removeRows(0,modPlaylist->rowCount());
    // For each playlist, get the items in that playlist
    for (unsigned int j = 0; j < Playlists.size(); j++) {
        QList<QStandardItem*> s;
        s.append(new QStandardItem(*icnExpanded,
                QString::fromStdString(Playlists[j]["name"].c_str())));
        s.append(new QStandardItem);
        s.append(new QStandardItem);
        s.append(new QStandardItem);
        modPlaylist->appendRow(s);
        lstPlaylist->setFirstColumnSpanned(j,modPlaylist->index(-1,0),true);
        SQL = "SELECT * FROM v_playlists WHERE playlistid = "
                + string(Playlists[j]["id"].c_str());
        PqxxResult R;
        try {
            R = DB->exec("PlaylistRetrieve",SQL);

            // Populate this playlist
            for (unsigned int i = 0; i < R.size(); i++) {
                QList<QStandardItem*> s;
                s.append(new QStandardItem(*icnTrack,
                        QString::fromStdString(R[i]["artist"].c_str())));
                s.append(new QStandardItem(QString::fromAscii(R[i]["title"].c_str())));
                s.append(new QStandardItem(QString::fromStdString(dps_prettyTime(atoi(R[i]["length_smpl"].c_str())))));
                s.append(new QStandardItem(QString::fromAscii(R[i]["id"].c_str())));
                s.at(0)->setIcon(*icnTrack);
                modPlaylist->item(j,0)->appendRow(s);
            }
        }
        catch (...) {
            DB->abort("PlaylistRetrieve");
            L_ERROR(LOG_TABPLAYLIST,"Failed to get playlist '"+std::string(Playlists[j][0].c_str())+"'");
            return;
        }
    }
    DB->abort("PlaylistRetrieve");
}


/**
 * Change the icon for an item when it is expanded.
 */
void TabPanelPlaylist::listExpanded(const QModelIndex& x) {
    modPlaylist->item(x.row(),0)->setIcon(*icnExpanded);
}


/**
 * Change the icon for an item when it is collapsed.
 */
void TabPanelPlaylist::listCollapsed(const QModelIndex& x) {
    modPlaylist->item(x.row(),0)->setIcon(*icnCollapsed);
}


/**
 * Draw GUI components.
 */
void TabPanelPlaylist::draw() {
    QString path = DPSDIR;
    icnExpanded = new QIcon(":/icons/expand16.png");
    icnCollapsed = new QIcon(":/icons/contract16.png");
    icnTrack = new QIcon("/icons/music16.png");
    
    // do all form drawing here, create widgets, set properties
    modPlaylist = new QStandardItemModel;
    QStringList vLabels;
    vLabels.append("Artist");
    vLabels.append("Title");
    vLabels.append("Length");
    vLabels.append("ID");
    modPlaylist->setHorizontalHeaderLabels(vLabels);

    lstPlaylist = new QTreeView( getPanel() );
    lstPlaylist->setModel(modPlaylist);
    lstPlaylist->setGeometry( QRect( 10, 10, 510, 620 ) );
    lstPlaylist->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    lstPlaylist->header()->setResizeMode(0, QHeaderView::Fixed);
    lstPlaylist->header()->setResizeMode(1, QHeaderView::Fixed);
    lstPlaylist->header()->setResizeMode(2, QHeaderView::Fixed);
    lstPlaylist->header()->setMovable( FALSE );
    lstPlaylist->header()->setDefaultAlignment(Qt::AlignLeft);
    lstPlaylist->setColumnWidth(0, 190);
    lstPlaylist->setColumnWidth(1, 185);
    lstPlaylist->setColumnWidth(2, 80);
    lstPlaylist->setAllColumnsShowFocus( TRUE );
    lstPlaylist->setColumnHidden(3, true);
    lstPlaylist->setAlternatingRowColors(true);
    lstPlaylist->setEditTriggers(QTreeView::NoEditTriggers);
    lstPlaylist->setSortingEnabled(FALSE);

    // connect signals and slots here
    QObject::connect( lstPlaylist, SIGNAL( doubleClicked(const QModelIndex&) ),
                this, SLOT( playlistAdd(const QModelIndex&) ) );
    QObject::connect( lstPlaylist, SIGNAL( expanded(const QModelIndex&) ),
                this, SLOT( listExpanded(const QModelIndex&) ) );
    QObject::connect( lstPlaylist, SIGNAL( collapsed(const QModelIndex&) ),
                this, SLOT( listCollapsed(const QModelIndex&) ) );
}


/**
 * Delete GUI components.
 */
void TabPanelPlaylist::clear() {
	delete lstPlaylist;
	if (icnAList) delete icnAList;
	if (icnBList) delete icnBList;
	if (icnExpanded) delete icnExpanded;
	if (icnCollapsed) delete icnCollapsed;
	if (icnTrack) delete icnTrack;
}
