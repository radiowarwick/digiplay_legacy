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
#include <QtGui/QWidget>
#include <QtGui/QTabWidget>

#include "dps.h"
#include "Auth.h"
#include "Logger.h"

#include "TabPanel.h"


/**
 * Constructs the base panel widget and sets the parent and text variables as
 * passed from the derived class's constructor. Nothing is drawn on the widget
 * at the base level, hence draw() and clean() are pure virtual functions.
 */
TabPanel::TabPanel(QTabWidget *parent, QString text) {
    // Set parent, tab label and tab tag
	tabParent = parent;
	tabText = text;
	panelTag = "Tab";

    // Create base panel widget
	panel = new QWidget(0);
}


/**
 * Clean up the base panel widget
 */
TabPanel::~TabPanel() {
	delete panel;
}


/**
 * Reconfigures the widget based on the state of the authentication module.
 * At the base class level, these merely controls the visibility of the
 * widget based on whether the associated \a panelTag should be active
 * for the current authentication state.
 */
void TabPanel::configure(Auth *authModule) {
	const char* routine = "TabPanel::configure";
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


/**
 * Checks if the panel isn't already visible, and then makes it visible by
 * inserting the base panel as a new tab in the parent QTabWidget.
 */
void TabPanel::show() {
	int p = tabParent->indexOf(panel);
	if (p == -1) {
		panel->setParent(tabParent);
		tabParent->insertTab(-1,panel,tabText);
	}
}


/**
 * Checks that the panel is currently visible, then removes it from the
 * parent QTabWidget.
 */
void TabPanel::hide() {
	int p = tabParent->indexOf(panel);
	if (p != -1) {
		tabParent->removeTab(p);
		panel->setParent(0);
	}
}


/**
 * Checks if the panel is currently associated with the parent QTabWidget.
 */
bool TabPanel::isVisible() {
	int p = tabParent->indexOf(panel);
	return (p != -1);
}
