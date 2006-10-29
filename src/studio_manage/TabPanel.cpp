/*
 * GUI Module base class
 * TabPanel.cpp
 * Base class for the TabPanel modules.
 *
 * Copyright (c) 2006 Chris Cantwell
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
#include <qwidget.h>
#include <qtabwidget.h>

#include "dps.h"
#include "Auth.h"
#include "Logger.h"

#include "TabPanel.h"

TabPanel::TabPanel(QTabWidget *parent, string text) {
	tabParent = parent;
	tabText = text;
	panelTag = "Tab";
	panel = new QWidget(0,"tabPanel");
	draw();
}

TabPanel::~TabPanel() {
	delete panel;
}

void TabPanel::configure(Auth *authModule) {
	char* routine = "TabPanel::configure";
	if (!authModule) {
		L_WARNING(LOG_TAB,"authModule isn't defined. Can't configure Tab.");
		return;
	}
	if (authModule->isPermitted(panelTag)) {
		show();
	}
	else {
		hide();
	}
}

void TabPanel::show() {
	int p = tabParent->indexOf(panel);
	if (p == -1) {
		panel->reparent(tabParent,QPoint(0,0),false);
		tabParent->insertTab(panel,tabText);
	}
}

void TabPanel::hide() {
	int p = tabParent->indexOf(panel);
	if (p != -1) {
		tabParent->removePage(panel);
		panel->reparent(0,QPoint(0,0),false);
	}
}

bool TabPanel::isVisible() {
	int p = tabParent->indexOf(panel);
	return (p != -1);
}
