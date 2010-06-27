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

#include "TabPanel.h"
#include "dps/Dps.h"

class QTabWidget;
class QPixmap;
class QListView;
class QListViewItem;

class Auth;
class DataAccess;
class QtTrigger;

/**
 * TabPanel class for providing access to a music playlist.
 */
class TabPanelPlaylist : public TabPanel {
	Q_OBJECT
	public:
        /// Constructor.
		TabPanelPlaylist(QTabWidget *parent, string text);
        /// Destructor.
		~TabPanelPlaylist();
        /// Reconfigures the panel.
		void configure(Auth *authModule);

    signals:
        /// Emitted when a playlist item is selected.
        void audioSelected( const DpsAudioItem& pSrc );

	private slots:
        /// Refreshes the contents of the playlist.
        void processPlaylistUpdate();
        /// Processes when a playlist item is selected and emits signal.
		virtual void playlistAdd(QListViewItem *current);
        /// Changes the icon when a playlist is expanded.
		virtual void listExpanded(QListViewItem *x);
        /// Changes the icen when a playlist is collapsed.
		virtual void listCollapsed(QListViewItem *x);

	private:
        /// Draws the panel.
		void draw();
        /// Clears the panel.
		void clear();

        DataAccess* DB;
        QtTrigger* triggerPlaylist;
		QListView *lstPlaylist;
		QPixmap *pixAList, *pixBList;
		QPixmap *pixExpanded, *pixCollapsed, *pixTrack;
};

#endif
