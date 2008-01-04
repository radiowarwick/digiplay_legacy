/*
 * Information Panel GUI Module
 * TabPanelInfo.cpp
 * Provides an information area.
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
#ifndef CLASS_TAB_PANEL_INFO
#define CLASS_TAB_PANEL_INFO

#include "TabPanel.h"

class QTabWidget;
class QTextBrowser;
class Auth;

/**
 * TabPanel class for displaying a simple information panel.
 */
class TabPanelInfo : public TabPanel {
	public:
		/// Constructor
		TabPanelInfo(QTabWidget *parent, string text);
		/// Destructor 
		~TabPanelInfo();

	private:
		/// Draw the panel
		void draw();
		/// Clear the panel
		void clear();

		QTextBrowser *txtInfoPanel;
};

#endif
