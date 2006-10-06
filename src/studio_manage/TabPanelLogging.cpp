#include <qtabwidget.h>
#include <qlistview.h>
#include <qstring.h>
#include <qheader.h>
#include <qobject.h>

#include "Auth.h"
#include "Logger.h"
#include "dps.h"

#include "TabPanelLogging.h"

TabPanelLogging::TabPanelLogging(QTabWidget *parent, string text)
		: TabPanel(parent,text) {
	config *conf = new config("digiplay");
	C = new Connection(conf->getDBConnectString());

	//#######################################################
	//For some reason this doesn't work - getParam returns ""
	//#######################################################
	location = atoi( conf->getParam("LOCATION").c_str() );


	delete conf;
}

// clean up stuff
TabPanelLogging::~TabPanelLogging() {
	if (C && C->is_open()) {
		C->Deactivate();
	}
	delete C;
	delete lstRecentlyLogged;
	delete txtArtist;
	delete txtTitle;
	delete txtReclibID;
	delete btnLog;
}

// this is called whenever the application reconfigures itself,
// usually due to a change in authentication status (login, logoff)
void TabPanelLogging::configure(Auth *authModule) {
	hide();
		
	if (authModule->getUser() != "") {

		string SQL = "SELECT id FROM users WHERE username = '" + authModule->getUser() + "' LIMIT 1;";
		Result R;
		try {
			Transaction *T = new Transaction(*C, "");
			R = T->exec(SQL);
			delete T;
		}
		catch(...) {
			cout << " -> Failed to find username" << endl;
		}
		if ((int)R.size() != 0)
			userid=atoi(R[0]["id"].c_str());
	}
	else {
		userid=location;
	}
	//cout << "Location: " << location << endl;

	if (authModule->isPermitted("TabInfo")) {
		draw();
		getRecentlyLogged();
		show();
	}
}

// This handles drawing the contents of the form, and connecting slots,
// but has little actual implementation
void TabPanelLogging::draw() {
	char* routine = "TabLogging::draw()";

/*	// this deletes the objects if they already exist so to avoid a leak
	if (lstEmail || txtEmailBody) {
		Logger::log(WARNING,routine,"Implicit clear() called",3);
		clear();
	}
*/
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
    lstRecentlyLogged->addColumn( tr( "Artist" ) );
    lstRecentlyLogged->addColumn( tr( "Title" ) );
    lstRecentlyLogged->setGeometry( QRect( 10, 120, 491, 510 ) );

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
	connect( btnLog, SIGNAL( clicked() ), this, SLOT( buttonPressed() ) );
	connect( txtTitle, SIGNAL( returnPressed() ), this, SLOT( buttonPressed() ) );
}

int TabPanelLogging::reclibID(string id) {
        //string artist;
        //string title;
        //return details (user, artist, title);
        return -1;
}

int TabPanelLogging::md5(string hash){
        track t = dps_getTrack(C,hash);
//      trackinfo *trk = new trackinfo(C, *hash);
//      string *artist = new string (trk->artist());
//      string *title = new string (trk->title());
        return logRecord(t.artist, t.title);
}

int TabPanelLogging::logRecord(string artist, string title){
        // Get current time
        int now = (int)time(NULL);

        // Escape the artist and title
        artist = sqlesc(artist);
        title = sqlesc(title);

        // Try and insert into database
        string SQL = "INSERT INTO log "
                "(userid, datetime, track_title, track_artist, location) VALUES ("
                + dps_itoa(userid) + ", " + dps_itoa(now) + ", '"
                + title + "', '" + artist + "', " + dps_itoa(location) + ");";
        try {
                Transaction T(*C,"");
                T.exec(SQL);
                T.commit();
        }
        catch (...) {
                cout << "ERROR: Failed to log record." << endl;
                cout << " -> " << SQL << endl;
                return 1;
        }
        return 0;
}

void TabPanelLogging::getRecentlyLogged() {
        Transaction *T = new Transaction(*C,"");
        QString artist, title, datestr;
        tm *dte;
        char date[30];

        stringstream SQL;
                SQL << "SELECT * FROM log ORDER BY datetime DESC LIMIT 50;";
        lstRecentlyLogged->clear();
        try {
                Result R = T->exec(SQL.str());
                for (int i = ((int)R.size())-1; i > -1; i--) {
                        time_t thetime(atoi(R[i]["datetime"].c_str()));
                        dte = localtime(&thetime);
                        strftime(date, 30, "%Ex %H:%M", dte);
                        artist = R[i]["track_artist"].c_str();
                        title = R[i]["track_title"].c_str();
                        lstRecentlyLogged->insertItem(new QListViewItem(lstRecentlyLogged, date, artist, title));
                }

        }
        catch (...) {
                cout << " -> ERROR: Failed to get recently logged records." << endl;
        }
        delete T;

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

void TabPanelLogging::clear() {
	delete lstRecentlyLogged;
	delete txtArtist;
	delete txtTitle;
	delete txtReclibID;
	delete btnLog;
}
