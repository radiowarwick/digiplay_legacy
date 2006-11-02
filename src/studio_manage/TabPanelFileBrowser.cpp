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

TabPanelFileBrowser::TabPanelFileBrowser(QTabWidget *parent, string text)
		: TabPanel(parent, text) {
    panelTag = "TabFileBrowser";
	config *conf = new config("digiplay");
	C = new Connection(conf->getDBConnectString());
	delete conf;
    draw();
}

// clean up stuff
TabPanelFileBrowser::~TabPanelFileBrowser() {
	if (C && C->is_open()) {
		C->Deactivate();
	}
	delete C;
}

// This handles drawing the contents of the form, and connecting slots,
// but has little actual implementation
void TabPanelFileBrowser::draw() {
	// do all form drawing here, create widgets, set properties
    lstFileBrowser = new DirectoryView( getPanel() );
    lstFileBrowser->addColumn( tr( "Name" ) );
    lstFileBrowser->addColumn( tr( "Type" ) );
    lstFileBrowser->setTreeStepSize( 20 );
    lstFileBrowser->setGeometry( QRect( 10, 10, 491, 620 ) );
    lstFileBrowser->setCaption( tr( "File Browser" ) );
    lstFileBrowser->setAllColumnsShowFocus( TRUE );
//    root = new Directory( lstFileBrowser, "/" );
//    root->setOpen( TRUE );
    lstFileBrowser->show();
}

void TabPanelFileBrowser::clear() {
	delete lstFileBrowser;
}
