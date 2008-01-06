/*
 * Library Search GUI Module
 * TabPanelSearch.cpp
 * Allows searching of the music database.
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

#ifndef CLASS_TAB_PANEL_SEARCH
#define CLASS_TAB_PANEL_SEARCH

//#include "frmStudioManage.h"

#include "Showplan.h"
#include "TabPanel.h"
#include "DpsMusicSearch.h"
#include "MessagingInterface.h"
#include "dlgWarn.h"

class QTabWidget;
class QPushButton;
class QListView;
class QLineEdit;
class QLabel;
class QCheckBox;
class QPixmap;

class Auth;
class Config;

/**
 * TabPanel class for providing a music library search.
 */
class TabPanelSearch : 	public TabPanel,
						public MessagingInterface {
	Q_OBJECT
	public:
        /// Constructor
		TabPanelSearch(QTabWidget *parent, string text);
        /// Destructor
		~TabPanelSearch();
        /// ???
		void onMessage();
		
	signals:
        /// Emitted when an item is selected from the search results.
        void itemSelected( QString );

	private slots:
        /// Searches the library.
		virtual void Library_Search();
		void getSearchResults();
        /// Emits the signal indicating an item is selected.
		virtual void playlistAdd(QListViewItem *x);

	private:
        /// Draws the panel.
		void draw();
        /// Clears the panel.
		void clear();
	
		Config *conf;
		vector<track> *SearchResults;
		DpsMusicSearch* library_engine;
		QPushButton *btnLibrarySearch;
		QListView *lstSearchResults;
		QLineEdit *txtLibrarySearchText;
		QLabel *Searchlable;
		QLabel *lblSearch;
		QCheckBox *ArtistCheckBox;
		QCheckBox *AlbumCheckBox;
		QCheckBox *TitleCheckBox;
		QString path;
		QPixmap *pixAudio;
		QPixmap *pixCensored;
};

#endif
