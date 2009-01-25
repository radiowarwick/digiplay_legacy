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
#include <cstdlib>

#include <qtabwidget.h>
#include <qheader.h>
#include <qapplication.h>
#include <qobject.h>
#include <string.h>
#include <qlistview.h>

#include "Auth.h"
#include "Logger.h"
#include "dps.h"
#include "FileBrowser.h"

#include "TabPanelFileBrowser.h"

/**
 * Initialises the TabPanel and draws the panels GUI components.
 */
TabPanelFileBrowser::TabPanelFileBrowser(QTabWidget *parent, string text)
		: TabPanel(parent, text) {
    // Set panel tag
    panelTag = "TabFileBrowser";
    
    // Draw GUI components
    draw();
}

/**
 * Cleans up dynamically created objects.
 */
TabPanelFileBrowser::~TabPanelFileBrowser() {
    clear();
}

void TabPanelFileBrowser::configure(Auth *authModule) {
    if (lstFileBrowser) {
        lstFileBrowser->setUser(authModule->getUser());
    }
    TabPanel::configure(authModule);
}


/**
 * This handles drawing the contents of the form, and connecting slots, 
 * but has little actual implementation.
 */
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


/**
 * Cleans up the GUI components.
 */
void TabPanelFileBrowser::clear() {
	delete lstFileBrowser;
}


/**
 * Emits the appropriate signal when an item is selected in the filebrowser.
 */
void TabPanelFileBrowser::handleLoad(QListViewItem* x) {
    if (x) {
        if (x->text(1) == "Audio File") {
        	DpsAudioItem vNew(x->text(2));
            emit audioSelected( vNew );
        }
        if (x->text(1) == "Audio Ident") {
        	DpsAudioItem vNew(x->text(2));
            emit audioSelected( vNew );
        }
        if (x->text(1) == "Audio Advert") {
        	DpsAudioItem vNew(x->text(2));
            emit audioSelected( vNew );
        }
        if (x->text(1) == "Script") {
            DpsScriptItem S(atoi(x->text(2).ascii()));
            emit scriptSelected( S );
        }
        if (x->text(1) == "AudioWall Set") {
            emit awsetSelected( x->text(2) );
        }
        if (x->text(1) == "Showplan") {
            DpsShowPlan s;
            s.load(atoi(x->text(2).ascii()));
            emit showplanSelected( s );
        }
    }
}