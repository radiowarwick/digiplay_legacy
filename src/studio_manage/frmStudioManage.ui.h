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
#include "TabPanelScript.h"
#include "TabPanelCart.h"
#include "TabPanelFileBrowser.h"
#include "ShowPlanItem.h"

#include "clockThread.h"
#include "triggerThread.h"
#include "track.h"
#include "config.h"
#include "dps.h"

AuthLdap *authModule;
TabPanelInfo *tabPanelInfo;
TabPanelEmail *tabPanelEmail;
TabPanelSearch *tabPanelSearch;
TabPanelFileBrowser *tabPanelFileBrowser;
TabPanelPlaylist *tabPanelPlaylist;
TabPanelLogging *tabPanelLogging;
TabPanelScript *tabPanelScript;
TabPanelCart *tabPanelCart;

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

	sp_audio = new QPixmap(path + "/images/sp_audio.bmp");
	sp_artist = new QPixmap(path + "/images/sp_artist.bmp");
	sp_album = new QPixmap(path + "/images/sp_album.bmp");
		
	lstShowPlan->setColumnWidth(0,lstShowPlan->width() - 5);
	lstShowPlan->setSorting(-1);
	QColor audioItem(128,255,128);
	QColor scriptItem(255,128,128);
	QColor linkItem(128,128,255);
	ShowPlanItem *myAudioItem = new ShowPlanItem( lstShowPlan, NULL,
		"Walking in the Sun","Travis","2:58","14:03.00");
	myAudioItem->setBackColor(audioItem);
	myAudioItem->setPixmap(0,*sp_audio);
	ShowPlanItem *myLinkItem = new ShowPlanItem( lstShowPlan, myAudioItem,
		"Talk about your mum","Dave & Pete","1:02","14:05.58");
	myLinkItem->setBackColor(linkItem);
	myLinkItem->setPixmap(0,*sp_artist);
	ShowPlanItem *myAudioItem2 = new ShowPlanItem( lstShowPlan, myLinkItem,
		"Come back around","Feeder","3:33","14:07:00");
	myAudioItem2->setBackColor(audioItem);
	myAudioItem2->setPixmap(0,*sp_audio);
	ShowPlanItem *myScriptItem = new ShowPlanItem( lstShowPlan, myAudioItem2,
		"My First Radio Play","Me","15:00","14:10:33");
	myScriptItem->setBackColor(scriptItem);
	
	last_item = myScriptItem;
/*	lstShowPlan->setColumnWidth(0,80);
	lstShowPlan->setColumnWidth(1,20);
	//lstShowPlan->setColumnWidth(2,20);
	lstShowPlan->setColumnWidth(2,0);
	lstShowPlan->setColumnWidth(3,60);
	lstShowPlan->setSorting(-1,FALSE);
	*/

	// Load tab panels after removing the orginal info tab.	
	tabManage->removePage(tabManage->currentPage());
	cout << "Loading panels" << endl;
	cout << " -> Info panel...";
	tabPanelInfo = new TabPanelInfo(tabManage,"Info");
	tabPanelInfo->configure(authModule);
	cout << " success." << endl;

	cout << " -> Search panel...";
	tabPanelSearch = new TabPanelSearch(tabManage, this, "Library Search");
	tabPanelSearch->configure(authModule);
	cout << " success." << endl;

	cout << " -> File Browser panel...";
	tabPanelFileBrowser = new TabPanelFileBrowser(tabManage,"File Browser");
	tabPanelFileBrowser->configure(authModule);
	cout << " success." << endl;

	cout << " -> Playlist panel...";
	tabPanelPlaylist = new TabPanelPlaylist(tabManage, this, "Playlist");
	tabPanelPlaylist->configure(authModule);
	cout << " success." << endl;
	
	cout << " -> Email panel...";
	tabPanelEmail = new TabPanelEmail(tabManage,"Email");
	tabPanelEmail->configure(authModule);
	cout << " success." << endl;

	cout << " -> Logging panel...";
	tabPanelLogging = new TabPanelLogging(tabManage,"Logging");
	tabPanelLogging->configure(authModule);
	cout << " success." << endl;

	cout << " -> Cart panel...";
	tabPanelCart = new TabPanelCart(tabManage,"Audio Wall Selection");
	tabPanelCart->configure(authModule);
	cout << " success." << endl;

	cout << " -> Script panel...";
	tabPanelScript = new TabPanelScript(tabManage,"Script");
	tabPanelScript->configure(authModule);
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

void frmStudioManage::playlistAdd(int *id) {
	Transaction *T = new Transaction(*C, "");
	_track *new_track = new _track(T, *id );
	delete T;
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


