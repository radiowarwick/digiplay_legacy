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
#include <qtabwidget.h>
#include <qlistview.h>
#include <qstring.h>
#include <qheader.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qobject.h>
#include <qpushbutton.h>

#include "Auth.h"
#include "Logger.h"
#include "dps.h"
#include "DbTrigger.h"
#include "Config.h"
#include "DataAccess.h"

#include "TabPanelLogging.h"

TabPanelLogging::TabPanelLogging(QTabWidget *parent, string text)
        : TabPanel(parent,text) {
    panelTag = "TabLogging";
    Config *conf = new Config("digiplay");
		DB = new DataAccess();
    location = atoi( conf->getParam("LOCATION").c_str() );
    delete conf;

		triggerLog = new DbTrigger("triggerLog","trig_id4");
	  triggerLog->start();

    draw();
}

// clean up stuff
TabPanelLogging::~TabPanelLogging() {
    delete DB;
    delete lstRecentlyLogged;
    delete txtArtist;
    delete txtTitle;
    delete txtReclibID;
    delete btnLog;
}

// this is called whenever the application reconfigures itself,
// usually due to a change in authentication status (login, logoff)
void TabPanelLogging::configure(Auth *authModule) {
		string usrnme = authModule->getUser();
		char *routine = "TabPanelLogging::configure";

		if (usrnme=="")
				usrnme = "Guest";
	  string SQL = "SELECT id FROM users WHERE username = '" 
                        + usrnme + "' LIMIT 1";
    Result R = DB->exec(SQL);
    
    if (R.size() != 0) {
        userid=atoi(R[0]["id"].c_str());
    }
	  else {
			L_ERROR(LOG_TABLOGGING,"Oh no! No user ID matching "
											  + usrnme + ".  What screwed up?");
	  }
    getRecentlyLogged();
    TabPanel::configure(authModule);
}

// This handles drawing the contents of the form, and connecting slots,
// but has little actual implementation
void TabPanelLogging::draw() {

    // do all form drawing here, create widgets, set properties
    lblReclibID = new QLabel( getPanel(), "lblReclibID" );
    lblReclibID->setGeometry( QRect( 10, 10, 111, 20 ) );
    QFont lblReclibID_font(  lblReclibID->font() );
    lblReclibID_font.setPointSize( 12 );
    lblReclibID_font.setBold( FALSE );
    lblReclibID->setFont( lblReclibID_font );

    lblArtist = new QLabel( getPanel(), "lblArtist" );
    lblArtist->setGeometry( QRect( 32, 40, 120, 20 ) );
    QFont lblArtist_font(  lblArtist->font() );
    lblArtist_font.setPointSize( 12 );
    lblArtist_font.setBold( FALSE );
    lblArtist->setFont( lblArtist_font );

    lblTitle = new QLabel( getPanel(), "lblTitle" );
    lblTitle->setGeometry( QRect( 39, 70, 68, 20 ) );
    QFont lblTitle_font(  lblTitle->font() );
    lblTitle_font.setPointSize( 12 );
    lblTitle_font.setBold( FALSE );
    lblTitle->setFont( lblTitle_font );

    lblRecentlyLogged = new QLabel( getPanel(), "lblRecentlyLogged" );
    lblRecentlyLogged->setGeometry( QRect( 10, 98, 121, 21 ) );
    QFont lblRecentlyLogged_font(  lblRecentlyLogged->font() );
    lblRecentlyLogged_font.setPointSize( 12 );
    lblRecentlyLogged->setFont( lblRecentlyLogged_font );

    txtArtist = new QLineEdit( getPanel(), "txtArtist" );
    txtArtist->setGeometry( QRect( 80, 40, 260, 21 ) );

    txtTitle = new QLineEdit( getPanel(), "txtTitle" );
    txtTitle->setGeometry( QRect( 80, 70, 260, 22 ) );

    btnLog = new QPushButton( getPanel(), "btnLog" );
    btnLog->setGeometry( QRect( 401, 10, 100, 50 ) );
    QFont btnLog_font(  btnLog->font() );
    btnLog_font.setPointSize( 12 );
    btnLog_font.setBold( FALSE );
    btnLog->setFont( btnLog_font );

    txtReclibID = new QLineEdit( getPanel(), "txtReclibID" );
    txtReclibID->setGeometry( QRect( 80, 10, 90, 21 ) );

    lstRecentlyLogged = new QListView( getPanel(), "lstRecentlyLogged" );
    lstRecentlyLogged->addColumn( tr( "Date/Time" ) );
    lstRecentlyLogged->header()->setResizeEnabled( FALSE,
            lstRecentlyLogged->header()->count() -1 );
    lstRecentlyLogged->addColumn( tr( "Artist" ) );
    lstRecentlyLogged->header()->setResizeEnabled( FALSE,
            lstRecentlyLogged->header()->count() -1 );
    lstRecentlyLogged->addColumn( tr( "Title" ) );
    lstRecentlyLogged->header()->setResizeEnabled( FALSE,
            lstRecentlyLogged->header()->count() -1 );
    lstRecentlyLogged->setGeometry( QRect( 10, 120, 491, 510 ) );
    lstRecentlyLogged->setAllColumnsShowFocus( TRUE );
    lstRecentlyLogged->setVScrollBarMode( QListView::AlwaysOn );
    lstRecentlyLogged->setColumnWidth(0,90);
    lstRecentlyLogged->setColumnWidth(1,194);
    lstRecentlyLogged->setColumnWidth(2,194);
    lstRecentlyLogged->header()->setMovingEnabled( FALSE );
    lstRecentlyLogged->setSorting(-1, FALSE);

    lblReclibID->setText( tr( "Reclib ID:" ) );
    lblArtist->setText( tr( "Artist:" ) );
    lblTitle->setText( tr( "Title:" ) );
    lblRecentlyLogged->setText( tr( "Recently Logged" ) );
    btnLog->setText( tr( "Log" ) );
    lstRecentlyLogged->header()->setLabel( 0, tr( "Date/Time" ) );
    lstRecentlyLogged->header()->setLabel( 1, tr( "Artist" ) );
    lstRecentlyLogged->header()->setLabel( 2, tr( "Title" ) );

    //Disable reclib ID logging until data is available....
    txtReclibID->setEnabled(FALSE);


    // connect signals and slots here
    connect( btnLog, SIGNAL( clicked() ), 
                this, SLOT( buttonPressed() ) );
    connect( txtTitle, SIGNAL( returnPressed() ), 
                this, SLOT( buttonPressed() ) );
    connect(triggerLog, SIGNAL(trigger()),
		                                this, SLOT(processLogUpdate()));

}

int TabPanelLogging::logRecord(string artist, string title){
    // Get current time
    int now = (int)time(NULL);

    // Escape the artist and title
    artist = sqlesc(artist);
    title = sqlesc(title);

    // Try and insert into database
    string SQL = "INSERT INTO log "
                "(userid, datetime, track_title, track_artist, location) "
                "VALUES (" + dps_itoa(userid) + ", " + dps_itoa(now) + ", '"
                + title + "', '" + artist + "', " + dps_itoa(location) + ");";
    DB->exec(SQL);
		return 0;
}

void TabPanelLogging::getRecentlyLogged() {
    QString artist, title, datestr;
    tm *dte;
    char date[30];

    string SQL = "SELECT * FROM log ORDER BY datetime DESC LIMIT 50;";
    lstRecentlyLogged->clear();
    Result R = DB->exec(SQL);
    for (unsigned int i = 0; i < R.size(); i++) {
        time_t thetime(atoi(R[i]["datetime"].c_str()));
        dte = localtime(&thetime);
        strftime(date, 30, "%Ex %H:%M", dte);
        artist = R[i]["track_artist"].c_str();
        title = R[i]["track_title"].c_str();
        lstRecentlyLogged->insertItem(
                new QListViewItem(  lstRecentlyLogged, 
                                    lstRecentlyLogged->lastItem(), 
                                    date, artist, title   ));
        }
}

void TabPanelLogging::buttonPressed() {
    string artist = txtArtist->text().ascii();
    string title = txtTitle->text().ascii();
    string reclibid = txtReclibID->text().ascii();

    if (logRecord(artist, title) != 0)
        cout << "Logging failed" << endl;
    txtReclibID->setText("");
    txtArtist->setText("");
    txtTitle->setText("");
    getRecentlyLogged();
}

void TabPanelLogging::processLogUpdate() {
    char *routine = "TabPanelLogging::processLogUpdate";

    L_INFO(LOG_TABLOGGING,"A change to the log relation has occured.");
    getRecentlyLogged();
    L_INFO(LOG_TABLOGGING,"Change to log relation processed.");
    
}

void TabPanelLogging::clear() {
    delete lstRecentlyLogged;
    delete txtArtist;
    delete txtTitle;
    delete txtReclibID;
    delete btnLog;
}
