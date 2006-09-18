#include <qtabwidget.h>
#include <qtextbrowser.h>
#include <qstring.h>
#include <qiconset.h>
#include <qheader.h>
#include <qapplication.h>
#include <qobject.h>

#include "Auth.h"
#include "Logger.h"
#include "dps.h"
#include "track.h"

#include "TabPanelPlaylist.h"

TabPanelPlaylist::TabPanelPlaylist(QTabWidget *parent, frmStudioManage *parent2, string text)
		: TabPanel(parent,text) {
	parentForm = parent2;
	
	config *conf = new config("digiplay");
	C = new Connection(conf->getDBConnectString());
	delete conf;

	playlistTrigger = new triggerThread(this, 
		QString(conf->getDBConnectString()), 2);
	playlistTrigger->start();
}

// clean up stuff
TabPanelPlaylist::~TabPanelPlaylist() {
	if (C && C->is_open()) {
		C->Deactivate();
	}
	delete C;

	delete pixAList;
	delete pixBList;
}

// this is called whenever the application reconfigures itself,
// usually due to a change in authentication status (login, logoff)
void TabPanelPlaylist::configure(Auth *authModule) {
	hide();
	if (authModule->isPermitted("TabInfo")) {
		draw();
		getPlaylist();
		show();
	}
}

// This handles drawing the contents of the form, and connecting slots,
// but has little actual implementation
void TabPanelPlaylist::draw() {
	char* routine = "TabPlaylist::draw()";

/*	// this deletes the objects if they already exist so to avoid a leak
	if (lstEmail || txtEmailBody) {
		Logger::log(WARNING,routine,"Implicit clear() called",3);
		clear();
	}
*/
	// do all form drawing here, create widgets, set properties
	lstPlaylist = new QListView(getPanel(), "lstEmail" );

	lstPlaylist->setGeometry( QRect( 20, 20, 480, 610 ) );
	lstPlaylist->setVScrollBarMode( QListView::AlwaysOn );
	lstPlaylist->setAllColumnsShowFocus( TRUE );

	// connect signals and slots here
	QObject::connect( lstPlaylist, SIGNAL( doubleClicked(QListViewItem*) ),
				this, SLOT( playlistAdd(QListViewItem*) ) );
}


void TabPanelPlaylist::getPlaylist(){
	Transaction *T = new Transaction(*C,"");
	stringstream SQL;
	track t;
	QListViewItem *new_playlist = NULL;
	QString path = qApp->applicationDirPath();
	QPixmap pixExpand(path+"/images/expand16.png");
	QPixmap pixContract(path+"/images/contract16.png");
	QPixmap pixTrack(path+"/images/audiofile16.png");

	lstPlaylist->clear();

	lstPlaylist->addColumn( tr( "Title" ) );
	lstPlaylist->addColumn( tr( "Artist" ) );
	lstPlaylist->addColumn( tr( "Length" ) );
	lstPlaylist->addColumn( tr( "ID" ) );

	SQL << "SELECT DISTINCT ON (playlist)  playlist FROM playlist ORDER BY playlist;";

	Result Playlists = T->exec(SQL.str());
	T->abort();
	delete T;
 	
	for (int j = 0; j < (int)Playlists.size(); j++) {

		string playlist = Playlists[j]["playlist"].c_str();
		string playlist_name = playlist + " List";
		new_playlist = new QListViewItem(lstPlaylist, playlist_name);
		new_playlist->setPixmap (0, pixContract);
		SQL << "SELECT playlist.audio, audio.md5 FROM playlist, audio  WHERE playlist = '" << Playlists[j]["playlist"].c_str() << "' AND audio.id = playlist.audio;";
		Result R;
		try {
			Transaction *T = new Transaction(*C,"");
			R = T->exec(SQL.str());
			T->abort();
			delete T;
		}
		catch (...) {
			cout << " -> ERROR: Failed to get " << playlist_name << "." << endl;
		}
	
		for (int i = (int)R.size()-1; i > -1; i--) {
			t = dps_getTrack(C, R[i]["md5"].c_str());
			QListViewItem *new_track = new QListViewItem(new_playlist,
       	             		 t.title, t.artist, getTime(t.length_smpl),  R[i]["audio"].c_str());
			new_track->setPixmap(0,pixTrack);
		}
		new_playlist->setOpen(true);

	}

}

void TabPanelPlaylist::customEvent(QCustomEvent *event) {
	char *routine = "TabPanelPlaylist::customEvent";
	switch (event->type()) {
		case 40001: { //Some kind of change to the playlist table
			getPlaylist();
			break;
		}
		default: {
			Logger::log(WARNING,routine,"Unknown event",2);
//			qWarning("Unknown event type: %d", event->type());
			break;
		}
	}
}

void TabPanelPlaylist::playlistAdd(QListViewItem *current) {
	if (current->text(3)) {
//		int id = atoi(current->text(3).ascii());
//		parentForm->playlistAdd(&id);
	}
}

QString TabPanelPlaylist::getTime( long smpl ) {
        QString S;
        int mil, sec, min;

        mil = smpl/441;
	sec = (int)(mil / 100);
	mil = mil%100;
	min = (int)(sec / 60);
	sec = sec%60;
        if (min < 10) S += "0";
        S += QString::number(min) + ":";
        if (sec < 10) S += "0";
        S += QString::number(sec);
        return S;
}


void TabPanelPlaylist::clear() {
	delete lstPlaylist;
}
