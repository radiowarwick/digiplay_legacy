/*
 * Logging GUI Module
 * TabPanelLogging.cpp
 * Provides the ability to logged played tracks into the central database.
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

#ifndef CLASS_TAB_PANEL_LOGGING
#define CLASS_TAB_PANEL_LOGGING

#include "TabPanel.h"

class QTabWidget;
class QListView;
class QLineEdit;
class QLabel;
class QPushButton;

class Auth;
class DataAccess;
class DbTrigger;

class TabPanelLogging : public TabPanel {
	Q_OBJECT
	public:
		TabPanelLogging(QTabWidget *parent, string text);
		~TabPanelLogging();
		void configure(Auth *authModule);

	public slots:
		virtual void buttonPressed();		
	
	private:
        void processLogUpdate();
		void draw();
		void clear();
		int logRecord(string artist, string title);
		void getRecentlyLogged();
		
        DataAccess* DB;
        DbTrigger* triggerLog;
		int location, userid;
		QListView *lstRecentlyLogged;
		QLineEdit *txtArtist, *txtTitle, *txtReclibID;
		QLabel *lblArtist, *lblTitle, *lblReclibID, *lblRecentlyLogged;
		QPushButton *btnLog;
};

#endif
