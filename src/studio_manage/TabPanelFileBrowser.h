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
#include "triggerThread.h"
#include "config.h"
#include "FileBrowser.h"
#include "frmStudioManage.h"

#include <qlistview.h>


#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

class QTabWidget;
class Auth;

class TabPanelFileBrowser : public TabPanel {
	Q_OBJECT
	public:
		TabPanelFileBrowser(QTabWidget *parent, frmStudioManage *parent2, string text);
		~TabPanelFileBrowser();

    protected slots:
        void playlistAdd(QListViewItem* x);

	private:
		void draw();
		void clear();
        
        frmStudioManage *parentForm;
		Connection *C;
		DirectoryView *lstFileBrowser;
		Directory *root;
};

#endif
