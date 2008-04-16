/*
 * Email GUI Module
 * TabPanelEmail.h
 * Extracts and displays a list of emails from the central database, and
 * provides the facility to view the email's contents. Updates the database
 * to reflect the read\unread status of the email
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

#ifndef CLASS_TAB_PANEL_EMAIL
#define CLASS_TAB_PANEL_EMAIL

#include <qfont.h>

#include "dps.h"

#include "TabPanel.h"

class QTabWidget;
class QTextBrowser;
class QListView;
class QListViewItem;
class QIconSet;
class Auth;

class QtTrigger;
class DpsEmail;

/**
 * TabPanel class for displaying studio emails.
 */
class TabPanelEmail : public TabPanel {
	Q_OBJECT
	public:
		/// Constructor
		TabPanelEmail(QTabWidget *parent, string text);
		/// Destructor
		~TabPanelEmail();
		/// Reconfigure the panel
		void configure(Auth *authModule);

	public slots:
		/// Get the body of an email and display it
		virtual void getEmailBody(QListViewItem *current);
		/// Check for emails and update the list
		void getEmail();

	private:
		/// Marks an email as read
		void markRead(string id);
		/// Draw the panel
		void draw();
		/// Clear the panel
		void clear();
	
        DataAccess* DB;
        DpsEmail* E;

        std::vector<std::map<std::string,std::string> > emails;

		bool flagUpdateDisabled;
		QtTrigger* triggerEmail;
		QListView *lstEmail;
		QTextBrowser *txtEmailBody;
		QPixmap *pixEmailNew, *pixEmailOld;
		QIconSet *icsEmailIcons;
		QFont fntBody;
		int pointSize;
};

#endif
