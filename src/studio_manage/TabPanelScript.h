/*
 * Scripts GUI Module
 * TabPanelScript.cpp
 * Provides facility for managing scripts.
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
#ifndef CLASS_TAB_PANEL_SCRIPT
#define CLASS_TAB_PANEL_SCRIPT

#include <qlabel.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qpushbutton.h>

#include "TabPanel.h"
#include "triggerThread.h"
#include "config.h"

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

class QTabWidget;
class Auth;

class TabPanelScript : public TabPanel {
	Q_OBJECT
	public:
		TabPanelScript(QTabWidget *parent, string text);
		~TabPanelScript();
		void configure(Auth *authModule);

	private:
		void draw();
		void clear();
		
		Connection *C;
	        QLabel *lblScriptName, *lblScriptDuration;
	        QLineEdit *txtScriptName, *txtScriptDuration;
		QTextEdit *txtScriptBody;
        	QPushButton *btnScriptSave;
};

#endif
