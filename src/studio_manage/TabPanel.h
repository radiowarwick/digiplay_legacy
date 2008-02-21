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
#ifndef CLASS_TAB_PANEL
#define CLASS_TAB_PANEL

#include <string>
using namespace std;

#include <qobject.h>

class QWidget;
class QTabWidget;
class Auth;

#include "Thread.h"

/**
 * Base class GUI tab widget from which various GUI components can be derived
 * allowing applications to be built from such components for various
 * purposes.
 */
class TabPanel :    public QObject,
                    public Thread {
	Q_OBJECT
	public:
		/// Constructor
		TabPanel(QTabWidget *parent, string text);
		/// Destructor
		virtual ~TabPanel();
        
		/// Reconfigures the panel
		virtual void configure(Auth *authModule);
		/// Sets the text shown on the tab
		void setText(string text) {tabText = text;}

	protected:
		// Returns a pointer to the actual panel widget
		QWidget *getPanel() {return panel;}
		// Hide the panel
		void hide();
		// Show the panel
		void show();
		// Returns true if the panel is visible
		bool isVisible();
		// Draw the contents of the panel
		virtual void draw() = 0;
		// Clean up the contents of the panel
		virtual void clear() = 0;
        
		string panelTag;

	private:
        void threadExecute() {}
        
		QWidget *panel;
		QTabWidget *tabParent;
		string tabText;
};

#endif
