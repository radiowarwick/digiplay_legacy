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
#include "MessagingInterface.h"

class QTabWidget;
class QStandardItemModel;
class QTableView;
class QLineEdit;
class QIcon;
class QIconSet;
class QLabel;
class QPushButton;

class Auth;
class DataAccess;
class QtTrigger;

/**
 * TabPanel class for logging records which are played on the system.
 */
class TabPanelLogging : public TabPanel,
						public MessagingInterface {
    Q_OBJECT
    public:
        /// Constructor
        TabPanelLogging(QTabWidget *parent, QString text);
        /// Destructor
        ~TabPanelLogging();
        /// Reconfigure the panel
        void configure(Auth *authModule);
        /// ???
        void onMessage();

    public slots:
        virtual void buttonPressed();		
        void processLogUpdate();

	private:
        /// Draw the panel
        void draw();
        /// Clear the panel
        void clear();
        /// Log a record for the given artist/title
        int logRecord(string artist, string title);
		
        DataAccess* DB;
        QtTrigger* triggerLog;
		int location, userid;
		QStandardItemModel *modLog;
		QTableView *lstRecentlyLogged;
		QLineEdit *txtArtist, *txtTitle;
		QLabel *lblArtist, *lblTitle, *lblRecentlyLogged;
		QPushButton *btnLog;
		QIcon *icnAudio;
};

#endif
