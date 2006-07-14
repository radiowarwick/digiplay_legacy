#include <qtabwidget.h>
#include <qtextbrowser.h>

#include "Auth.h"
#include "Logger.h"

#include "TabPanelInfo.h"

TabPanelInfo::~TabPanelInfo() {

}

void TabPanelInfo::configure(Auth *authModule) {
	hide();
	if (authModule->isPermitted("TabInfo")) {
		draw();
		show();
	}
}

void TabPanelInfo::draw() {
	char* routine = "TabInfo::draw()";
	
	if (txtInfoPanel) {
		Logger::log(WARNING,routine,"Implicit clear() called",3);
		clear();
	}
	
	txtInfoPanel = new QTextBrowser(getPanel(), "txtInfoPanel");
	txtInfoPanel->setGeometry( QRect( 10, 10, 500, 610 ) );
	txtInfoPanel->setVScrollBarMode( QTextBrowser::AlwaysOn );
	txtInfoPanel->setHScrollBarMode( QTextBrowser::AlwaysOff );
	txtInfoPanel->setTextFormat( QTextBrowser::RichText );

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

void TabPanelInfo::clear() {
	delete txtInfoPanel;
}
