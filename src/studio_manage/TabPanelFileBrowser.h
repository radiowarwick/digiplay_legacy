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
#ifndef CLASS_TAB_PANEL_FILEBROWSER
#define CLASS_TAB_PANEL_FILEBROWSER

#include "TabPanel.h"
#include "DpsObject.h"

class QTabWidget;
class QListViewItem;

class Auth;
class DirectoryView;
class Directory;

class TabPanelFileBrowser : public TabPanel {
	Q_OBJECT
	public:
		TabPanelFileBrowser(QTabWidget *parent, string text);
		~TabPanelFileBrowser();
        void configure(Auth *authModule);

    signals:
        void trackSelected( QString md5 );
        void jingleSelected( QString md5 );
        void advertSelected( QString md5 );
        void scriptSelected( DpsShowScript& S );
        void cartsetSelected( QString index );
        void showplanSelected( DpsShowplan& s );

    protected slots:
        void handleLoad(QListViewItem* x);

	private:
		void draw();
		void clear();
        
		DirectoryView *lstFileBrowser;
		Directory *root;
};

#endif
