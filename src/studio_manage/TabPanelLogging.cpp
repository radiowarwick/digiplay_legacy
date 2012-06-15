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

#include <QtGui/QTabWidget>
#include <QtGui/QStandardItemModel>
#include <QtGui/QTableView>
#include <QtCore/QString>
#include <QtGui/QIcon>
#include <QtGui/QIconSet>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtCore/QObject>
#include <QtGui/QPushButton>

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
TabPanelLogging::TabPanelLogging(QTabWidget *parent, QString text)
        : TabPanel(parent,text) {
    // Set panel tag
    panelTag = "TabLogging";

    TabPanel::setIcon(QIcon(":/icons/log16.png"));

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
    string artist = txtArtist->text().toStdString();
    string title = txtTitle->text().toStdString();
//    string reclibid = txtReclibID->text().toStdString();

    // Try to log record
    if (logRecord(artist, title) != 0)
        L_ERROR(LOG_TABLOGGING, "Logging failed");
        
    // Reset text fields
    //txtReclibID->setText("");
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
    modLog->removeRows(0,modLog->rowCount());
    modLog->setRowCount(R.size());
    for (unsigned int i = 0; i < R.size(); i++) {
        time_t thetime(atoi(R[i]["datetime"].c_str()));
        dte = localtime(&thetime);
        strftime(date, 30, "%Ex %H:%M", dte);
        modLog->setItem(i,0,new QStandardItem(QString::fromAscii(date)));
	modLog->setItem(i,1,new QStandardItem(QString::fromAscii(R[i]["track_title"].c_str())));
        modLog->setItem(i,2,new QStandardItem(QString::fromAscii(R[i]["track_artist"].c_str())));
	modLog->item(i,0)->setIcon(*icnAudio);
    }
    L_INFO(LOG_TABLOGGING,"List of recently logged tracks updated successfully.");
}


/**
 * Draw the GUI components.
 */
void TabPanelLogging::draw() {

    // do all form drawing here, create widgets, set properties
    //lblReclibID = new QLabel( getPanel() );
    //lblReclibID->setGeometry( QRect( 10, 10, 111, 20 ) );
    icnAudio = new QIcon(":/icons/music16.png");

    lblArtist = new QLabel( getPanel() );
    lblArtist->setGeometry( QRect( 32, 10, 120, 20 ) );

    lblTitle = new QLabel( getPanel() );
    lblTitle->setGeometry( QRect( 39, 37, 68, 20 ) );

    lblRecentlyLogged = new QLabel( getPanel() );
    lblRecentlyLogged->setGeometry( QRect( 10, 58, 121, 21 ) );

    txtArtist = new QLineEdit( getPanel() );
    txtArtist->setGeometry( QRect( 83, 8, 330, 25 ) );

    txtTitle = new QLineEdit( getPanel() );
    txtTitle->setGeometry( QRect( 83, 34, 330, 25 ) );

    btnLog = new QPushButton( getPanel() );
    btnLog->setGeometry( QRect( 419, 8, 100, 50 ) );

    //txtReclibID = new QLineEdit( getPanel() );
    //txtReclibID->setGeometry( QRect( 80, 8, 90, 25 ) );

    modLog = new QStandardItemModel(0,3);
    modLog->setHeaderData(0, Qt::Horizontal, tr("Date/Time"));
    modLog->setHeaderData(1, Qt::Horizontal, tr("Title"));
    modLog->setHeaderData(2, Qt::Horizontal, tr("Artist"));

    lstRecentlyLogged = new QTableView( getPanel() );
    lstRecentlyLogged->setModel(modLog);
    lstRecentlyLogged->setGeometry( QRect( 5, 80, 516, 548 ) );
    lstRecentlyLogged->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    lstRecentlyLogged->setSelectionBehavior(QTableView::SelectRows);
    lstRecentlyLogged->setSelectionMode(QTableView::SingleSelection);
    lstRecentlyLogged->setAlternatingRowColors(true);
    lstRecentlyLogged->setShowGrid(false);
    lstRecentlyLogged->setColumnWidth(0, 130);
    lstRecentlyLogged->setColumnWidth(1, 206);
    lstRecentlyLogged->setColumnWidth(2, 160);
    lstRecentlyLogged->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    lstRecentlyLogged->verticalHeader()->hide();
    lstRecentlyLogged->verticalHeader()->setDefaultSectionSize(20);
    lstRecentlyLogged->setEditTriggers(QTableView::NoEditTriggers);

    //lblReclibID->setText( tr( "Reclib ID:" ) );
    lblArtist->setText( tr( "Artist:" ) );
    lblTitle->setText( tr( "Title:" ) );
    lblRecentlyLogged->setText( tr( "Recently Logged" ) );
    btnLog->setText( tr( "Log" ) );

    //Disable reclib ID logging until data is available....
    //txtReclibID->setEnabled(FALSE);

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
    //delete txtReclibID;
    delete btnLog;
}
