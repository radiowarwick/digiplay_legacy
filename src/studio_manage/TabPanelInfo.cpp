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
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>

#include "dps.h"
#include "Auth.h"
#include "Logger.h"

#include "TabPanelInfo.h"

/**
 * Initialise the panal and draw the GUI components.
 */
TabPanelInfo::TabPanelInfo(QTabWidget *parent, QString text)
		: TabPanel(parent,text) {
    // Set panel tag.
	panelTag = "TabInfo";

	TabPanel::setIcon(QIcon(":/icons/info16.png"));

    // Initialise pointers.
	txtInfoPanel = 0;

    // Draw GUI components.
	draw();
}


/**
 * Deletes any dynamically assigned objects.
 */
TabPanelInfo::~TabPanelInfo() {
	clear();
}


/**
 * Creates the GUI components for this panel.
 */
void TabPanelInfo::draw() {
	const char* routine = "TabInfo::draw()";

	if (txtInfoPanel) {
		L_WARNING(LOG_TABINFO,"Implicit clear() called");
		clear();
	}

	txtInfoPanel = new QTextBrowser( getPanel() );
	txtInfoPanel->setGeometry( QRect( 10, 10, 500, 610 ) );
	txtInfoPanel->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	txtInfoPanel->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

	//##############################################
	//TODO: Add SQL to get info from DB by location#
	//##############################################

	txtInfoPanel->setText( tr( "<H2>Quick Start</H2>\n"
		"<P>On the touch screen are three 'Audio Players' which correspond to three channels on the Broadcast Desk. These function just like a normal CD player.</P>\n"
		"<P>There is also an audio wall that contains jingles and beds that you can play without searching the library. To start them, just press their button, and it will come out of the fourth channel on the desk. In the future the bottom wall will be fully customisable, while the top wall will contain the station jingles, adverts and promotions.<p>\n"
		"<H3>Library Search</H3>\n"
		"<P>The third tab above is an Audio Library search engine. It allows you to find music in the audio library to add to your playlist. Enter criteria for the track you are looking for and click search. Double click on a track to add it to the bottom of the show plan.</P>\n"
		"<H3>Playing Music out</H3>\n"
		"<P>Click the load button on any of the three players to load the top track in the show plan. Use the play \\ stop \\ pause buttons like a normal CD player. You can jump through the track by dragging the position bar when in pause or stop mode. Click the time button to toggle between the Elapsed and Remaining time display.\n"
		"<H3>Problems or Suggestions?</H3>\n"
		"If the software \"Crashes\" or \"Locks up\", please send an email to: <b>digiplay@radio.warwick.ac.uk</b> and say what you'd done just before it crashed and what the software was doing at the time. This will help us improve the software which will in turn help you.\n"
		"If you have any suggestions for features you'd like to see in RaW Digiplay, please send an email to the same address above.</p><p>Thanks,</p><P>RaW Digiplay Development Team</p>" ) );
}


/**
 * Clean up the GUI components.
 */
void TabPanelInfo::clear() {
	delete txtInfoPanel;
}
