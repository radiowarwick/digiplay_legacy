/*
 * Virtual Directory Browser GUI Module
 * TabPanelFileBrowser.cpp
 * Provides a tree structure to allow navigation of the virtual directory
 * hierarchy within the central database.
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
#include <qheader.h>
#include <qapplication.h>
#include <qobject.h>
#include <string.h>

#include "Auth.h"
#include "Logger.h"
#include "dps.h"

#include "TabPanelFileBrowser.h"

TabPanelFileBrowser::TabPanelFileBrowser(QTabWidget *parent, frmStudioManage *parent2, string text)
		: TabPanel(parent, text) {
    panelTag = "TabFileBrowser";
    parentForm = parent2;
	conf = new config("digiplay");
	C = new Connection(conf->getDBConnectString());
    draw();
}

// clean up stuff
TabPanelFileBrowser::~TabPanelFileBrowser() {
	if (C && C->is_open()) {
		C->Deactivate();
	}
	delete C;
    delete conf;
}

// This handles drawing the contents of the form, and connecting slots,
// but has little actual implementation
void TabPanelFileBrowser::draw() {
	// do all form drawing here, create widgets, set properties
    lstFileBrowser = new DirectoryView( getPanel() );
    lstFileBrowser->addColumn( tr( "Name" ) );
    lstFileBrowser->header()->setResizeEnabled( FALSE,
                    lstFileBrowser->header()->count() - 1 );
    lstFileBrowser->setColumnWidthMode(0, QListView::Manual);
    lstFileBrowser->addColumn( tr( "Type" ) );
    lstFileBrowser->header()->setResizeEnabled( FALSE,
                    lstFileBrowser->header()->count() - 1 );
    lstFileBrowser->setColumnWidthMode(1, QListView::Manual);
    lstFileBrowser->setTreeStepSize( 20 );
    lstFileBrowser->setGeometry( QRect( 10, 10, 491, 620 ) );
    lstFileBrowser->setCaption( tr( "File Browser" ) );
    lstFileBrowser->setAllColumnsShowFocus( TRUE );
    lstFileBrowser->setVScrollBarMode( QListView::AlwaysOn );
    lstFileBrowser->setColumnWidth(0, 360);
    lstFileBrowser->setColumnWidth(1, 100);
    lstFileBrowser->header()->setMovingEnabled( FALSE );
    lstFileBrowser->setSorting(1, TRUE);

    connect( lstFileBrowser, SIGNAL( doubleClicked(QListViewItem*) ),
                this, SLOT( handleLoad(QListViewItem*) ) );
    lstFileBrowser->show();
}

void TabPanelFileBrowser::clear() {
	delete lstFileBrowser;
}

void TabPanelFileBrowser::handleLoad(QListViewItem* x) {
    if (x) {
        if (x->text(1) == "Audio file") {
            parentForm->playlistAdd(x->text(2));
        }
        if (x->text(1) == "Cartset") {
            conf->setParam("user_cartset",x->text(2).ascii());
        }
    }
}
