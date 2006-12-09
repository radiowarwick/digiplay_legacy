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

#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qtable.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtooltip.h>

#include "frmStudioManage.h"

#include "Showplan.h"
#include "TabPanel.h"
#include "config.h"
#include "libsearch.h"
#include "dlgWarn.h"

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

class QTabWidget;
class Auth;

class TabPanelSearch : public TabPanel {
	Q_OBJECT
	public:
		TabPanelSearch(QTabWidget *parent, string text);
		~TabPanelSearch();

	signals:
        void itemSelected( QString );

	private slots:
		virtual void Library_Search();
		virtual void playlistAdd(QListViewItem *x);

	private:
		void draw();
		void clear();
		
		Connection *C;
		vector<track> *SearchResults;
		libsearch *library_engine;
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
};

#endif
