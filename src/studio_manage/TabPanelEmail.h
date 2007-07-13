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

#include "TabPanel.h"

class QTabWidget;
class QTextBrowser;
class QListView;
class QListViewItem;
class QIconSet;
class Auth;

class DataAccess;
class DbTrigger;

class TabPanelEmail : public TabPanel {
	Q_OBJECT
	public:
		TabPanelEmail(QTabWidget *parent, string text);
		~TabPanelEmail();
		void configure(Auth *authModule);

	public slots:
		virtual void getEmailBody(QListViewItem *current);		
	
  public slots:
        void processEmailUpdate();

	private:
		void markRead(string id);
		void draw();
		void clear();
		void getEmail();
		
        DataAccess* DB;
		bool flagUpdateDisabled;
		DbTrigger* triggerEmail;
		QListView *lstEmail;
		QTextBrowser *txtEmailBody;
		QPixmap *pixEmailNew, *pixEmailOld;
		QIconSet *icsEmailIcons;
		QFont fntBody;
		int pointSize;
};

#endif
