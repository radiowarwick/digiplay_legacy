/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
#include <qapplication.h>

#include "Logger.h"
#include "AuthLdap.h"
#include "TabPanelInfo.h"
#include "TabPanelEmail.h"
#include "TabPanelSearch.h"
#include "TabPanelPlaylist.h"
#include "TabPanelLogging.h"

#include "clockThread.h"
#include "triggerThread.h"
#include "track.h"
#include "config.h"
#include "dps.h"

AuthLdap *authModule;
TabPanelInfo *tabPanelInfo;
TabPanelEmail *tabPanelEmail;
TabPanelSearch *tabPanelSearch;
TabPanelPlaylist *tabPanelPlaylist;
TabPanelLogging *tabPanelLogging;

triggerThread *dbTrigger;
config *conf;
Connection *C;
clockThread *ck;
vector<_track*> *SearchResults;
vector<_track*> *Playlist = new vector<_track*>;
QPixmap *sp_audio, *sp_artist, *sp_album;
QString path;
QListViewItem *last_item;

void frmStudioManage::init() {
    // Configure logging
    Logger::setAppName("studio_manage");
    Logger::setLogLevel(5);
    Logger::setDisplayLevel(0);
    
	// Connect to database
	cout << "Connecting to database..." << endl;
	conf = new config("digiplay");
	C = new Connection(conf->getDBConnectString());
	cout << "Connected." << endl;

	// Initialise Authentication mechanism
	authModule = new AuthLdap("localhost",389,"ou=People,dc=radio,dc=warwick,dc=ac,dc=uk");
	
	// Initialise modules
	cout << "Initialising Modules..." << endl;
	cout << " -> Clock...";
	ck = new clockThread(this);
	ck->start();
	cout << "success." << endl;
	cout << "All modules loaded." << endl;
	
	// Initialise interface
	cout << "Initialising Interface..." << endl;
	path = qApp->applicationDirPath();
	lstShowPlan->setColumnWidth(0,80);
	lstShowPlan->setColumnWidth(1,20);
	//lstShowPlan->setColumnWidth(2,20);
	lstShowPlan->setColumnWidth(2,0);
	lstShowPlan->setColumnWidth(3,60);
	lstShowPlan->setSorting(-1,FALSE);
	
	sp_audio = new QPixmap(path + "/images/sp_audio.bmp");
	sp_artist = new QPixmap(path + "/images/sp_artist.bmp");
	sp_album = new QPixmap(path + "/images/sp_album.bmp");
	
	last_item = NULL;
	
	// Load tab panels	
	cout << "Loading panels" << endl;
	cout << " -> Info panel...";
	tabPanelInfo = new TabPanelInfo(tabManage,"Info");
	tabPanelInfo->configure(authModule);
	cout << " success." << endl;

	cout << " -> Search panel...";
	tabPanelSearch = new TabPanelSearch(tabManage,"Library Search");
	tabPanelSearch->configure(authModule);
	cout << " success." << endl;

	cout << " -> Email panel...";
	tabPanelEmail = new TabPanelEmail(tabManage,"Email");
	tabPanelEmail->configure(authModule);
	cout << " success." << endl;

	cout << " -> Playlist panel...";
	tabPanelPlaylist = new TabPanelPlaylist(tabManage,"Playlist");
	tabPanelPlaylist->configure(authModule);
	cout << " success." << endl;

	cout << " -> Logging panel...";
	tabPanelLogging = new TabPanelLogging(tabManage,"Logging");
	tabPanelLogging->configure(authModule);
	cout << " success." << endl;

	btnLogin->setEnabled(false);
	cout << "Interface initialisation complete." << endl;

	// Create trigger for configuration
	cout << "Creating database triggers..." << endl;
	dbTrigger = new triggerThread(this, QString(conf->getDBConnectString()), 1); 
	dbTrigger->start();
	cout << "Triggers active." << endl;	
}

void frmStudioManage::destroy() {
	for (unsigned int i = 0; i < Playlist->size(); i++)
		delete Playlist->at(i);
	delete Playlist;
}

void frmStudioManage::customEvent(QCustomEvent *event) {
	switch (event->type()) {
	case 20000: {       // Clock update
			QString *s = (QString *) event->data();
			lblClock->setText(*s);
			break;
		}
	case 20001: {       // Date update
			QString *s = (QString *) event->data();
			lblDate->setText(*s);
			break;
		}
	case 30001: {       // Configuration changed trigger
			conf->requery();
			cout << "Configuration data refreshed!" << endl;
			if (conf->getParam("next_on_showplan") == "" 
								&& lstShowPlan->childCount() > 0) {
				Playlist->erase(Playlist->begin());
				delete lstShowPlan->firstChild();
				if (Playlist->size() > 0) {
					cout << "Notifying next track" << endl;
					conf->setParam("next_on_showplan",Playlist->at(0)->md5());
				}
			}
			break;
		}
	default: {
			qWarning("Unknown event type: %d", event->type());
			break;
		}
	}
}

/*
  ####################################
  This function needs moving into the TabPanelSearch class
  ####################################
  
void frmStudioManage::PlaylistAdd(int row, int col, int button, const QPoint& mousepos) {
	if (mousepos.isNull()) {button = 0; row = 0; col = 0;}
	_track *new_track = new _track(*(SearchResults->at(row)));
	Playlist->push_back(new_track);
	QListViewItem *track_title = new QListViewItem( lstShowPlan,last_item, new_track->title(), getTime(new_track->length_smpl()), "00:00:00", "");
	track_title->setPixmap( 0, *sp_audio );
	QListViewItem *track_artist = new QListViewItem( track_title, "Artist: " + new_track->artist());
	track_artist->setPixmap(0, *sp_artist );
	QListViewItem *track_album = new QListViewItem( track_title, "Album: " + new_track->album());
	track_album->setPixmap(0, *sp_album );
	track_title->setOpen(false);
	last_item = track_title;
	if (Playlist->size() == 1) {
		conf->setParam("next_on_showplan",new_track->md5());
	}
}
*/

bool frmStudioManage::isDefined(QString *name) {
	//	for (unsigned short i = 0; i < names->size(); i++) {
	//		if (names->at(i) == name)
	//			return true;
	//	}
	return false;
}

QString frmStudioManage::getTime( long smpl ) {
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
