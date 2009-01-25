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
#include "dps/Dps.h"

class QTabWidget;
class QListViewItem;

class Auth;
class DirectoryView;
class Directory;

/**
 * TabPanel class for displaying a virtual filesystem browser.
 * This provides access to the DPS virtual filesystem structure.
 */
class TabPanelFileBrowser : public TabPanel {
	Q_OBJECT
	public:
		/// Constructor
		TabPanelFileBrowser(QTabWidget *parent, string text);
		/// Destructor
		~TabPanelFileBrowser();
		/// Reconfigure the panel
        void configure(Auth *authModule);

    signals:
    	/// Emitted when an audio item is selected
    	void audioSelected( const DpsAudioItem& pAudio );
        /// Emitted when a script is selected from the browser.
        void scriptSelected( const DpsScriptItem& pScript );
        /// Emitted when a audiowall set is selected from the browser.
        void awsetSelected( QString index );
        /// Emitted when a showplan is selected from the browser.
        void showplanSelected( const DpsShowPlan& s );

    protected slots:
    	/// Handle load events from the FileBrowser object and emit signals.
        void handleLoad(QListViewItem* x);

	private:
		/// Draw the panel
		void draw();
		/// Clear the panel
		void clear();
        
		DirectoryView *lstFileBrowser;
		Directory *root;
};

#endif
