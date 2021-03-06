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
#include <cstdlib>

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
#include "QtTrigger.h"
#include "Config.h"
#include "DataAccess.h"

#include "TabPanelLogging.h"

/**
 * Constructs a new logging panel.
 */
TabPanelLogging::TabPanelLogging(QTabWidget *parent, string text)
        : TabPanel(parent,text) {
    // Set panel tag
    panelTag = "TabLogging";

    // Create GUI components
    draw();
    
    // Create a DataAccess class for database access
    DB = new DataAccess();
    
    // Create a config class and determine location
    Config *conf = new Config("digiplay",this);
    location = atoi( conf->getParam("LOCATION").c_str() );
    delete conf;

    // Create a database trigger and run the update routine when triggered
    triggerLog = new QtTrigger("triggerLog","t_log");
    connect(triggerLog, SIGNAL(trigger()),
              this, SLOT(processLogUpdate()));
    
}

/**
 * Delete any dynamically created objects.
 */
TabPanelLogging::~TabPanelLogging() {
    // Delete GUI components
    clear();
    
    // Release database access
    delete DB;
}


/**
 * Reconfigure the tab based on a change in authentication state.
 * @param   authModule  Authentication module indicating authentication state.
 */
void TabPanelLogging::configure(Auth *authModule) {
    const char *routine = "TabPanelLogging::configure";

    // Get the user id and store it
    string SQL = "SELECT id FROM users WHERE username = '" 
                        + authModule->getUser() + "' LIMIT 1";
    PqxxResult R; 
    try {
        R = DB->exec("LoggingGetUser", SQL);
        DB->abort("LoggingGetUser");
    }
    catch (...) {
        DB->abort("LoggingGetUser");
        L_ERROR(LOG_TABLOGGING,"Failed to query user ID in database.");        
    }
    if (R.size() != 0) {
        userid=atoi(R[0]["id"].c_str());
    }
    else {
        L_ERROR(LOG_TABLOGGING,"No user ID matching username.");
    }
    
    // Populate the list with recently logged items.
    processLogUpdate();
    TabPanel::configure(authModule);
}


/**
 * MessagingInterface routine
 */
void TabPanelLogging::onMessage() {
	
}


/**
 * Logs a record in the database.
 * @param   artist      Artists name
 * @param   title       Title of the track
 * @returns             0 if completes successfully
 */
int TabPanelLogging::logRecord(string artist, string title){
    const char *routine="TabPanelLogging::logRecord";
    
    // Get current time
    int now = (int)time(NULL);

    // Escape the artist and title
    artist = DB->esc(artist);
    title = DB->esc(title);

    // Try and insert into database
    string SQL = "INSERT INTO log "
                "(userid, datetime, track_title, track_artist, location) "
                "VALUES (" + dps_itoa(userid) + ", " + dps_itoa(now) + ", '"
                + title + "', '" + artist + "', " + dps_itoa(location) + ");";
    try {
        DB->exec("LoggingRecord", SQL);
        DB->commit("LoggingRecord");
    }
    catch (...) {
        L_ERROR(LOG_TABLOGGING,"Failed to insert record " + artist +
								" - " + title + ".");
        return -1;
    }
    return 0;
}


/**
 * Code run when the log button is pressed.
 */
void TabPanelLogging::buttonPressed() {
    const char *routine = "TabPanelLogging::buttonPressed";
    
    // Retrieve values from text fields
    string artist = txtArtist->text().ascii();
    string title = txtTitle->text().ascii();
    string reclibid = txtReclibID->text().ascii();

    // Try to log record
    if (logRecord(artist, title) != 0)
        L_ERROR(LOG_TABLOGGING, "Logging failed");
        
    // Reset text fields
    txtReclibID->setText("");
    txtArtist->setText("");
    txtTitle->setText("");
    
    // Repopulate the list to reflect changes
    processLogUpdate();
}


/**
 * Update the list of logged tracks.
 */
void TabPanelLogging::processLogUpdate() {
    const char *routine = "TabPanelLogging::processLogUpdate";

    L_INFO(LOG_TABLOGGING,"Updating list of recently logged tracks.");
    QString artist, title, datestr;
    tm *dte;
    char date[30];
    
    // Clear the list
    lstRecentlyLogged->clear();

    // Retrieve the last 50 tracks logged.
    // TODO - Change the 1 in this SQL query to the System Define
    string SQL = "SELECT * FROM log WHERE userid != 1 ORDER BY datetime DESC LIMIT 50;";
    PqxxResult R;
    try {
        R=DB->exec("LoggingGet", SQL);
        DB->abort("LoggingGet");
    }
    catch (...) {
        DB->abort("LoggingGet");
        L_ERROR(LOG_TABLOGGING,"Couldn't get logged records from DB.");
    }
    
    // Populate the list with the retrieved tracks.
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
    L_INFO(LOG_TABLOGGING,"List of recently logged tracks updated successfully.");
}


/**
 * Draw the GUI components.
 */
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
}


/**
 * Delete the GUI components
 */
void TabPanelLogging::clear() {
    delete lstRecentlyLogged;
    delete txtArtist;
    delete txtTitle;
    delete txtReclibID;
    delete btnLog;
}
