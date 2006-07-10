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

#include "clockThread.h"
#include "triggerThread.h"
#include "libsearch.h"
#include "track.h"
#include "config.h"
#include "recordLog.h"
#include "modEmail.h"
#include "dps.h"

AuthLdap *authModule;
TabPanelInfo *tabPanelInfo;
TabPanelEmail *tabPanelEmail;

libsearch *library_engine;
triggerThread *dbTrigger;
triggerThread *emailTrigger;
config *conf;
recordLog *log; 
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
	cout << " -> Library Search...";
	library_engine = new libsearch();
	cout << "success." << endl;
	cout << " -> Logging...";
	log = new recordLog(C,1);
	cout << "success." << endl;
	cout << " -> Email...";
	cout << "success." << endl;
	cout << " -> Clock...";
	ck = new clockThread(this);
	ck->start();
	cout << "success." << endl;
	cout << "All modules loaded." << endl;
	
	// Initialise interface
	cout << "Initialising Interface..." << endl;
	path = qApp->applicationDirPath();
	tblLibrarySearchResults->setColumnWidth(3,0);
	lstShowPlan->setColumnWidth(0,80);
	lstShowPlan->setColumnWidth(1,20);
	//lstShowPlan->setColumnWidth(2,20);
	lstShowPlan->setColumnWidth(2,0);
	lstShowPlan->setColumnWidth(3,60);
	lstShowPlan->setSorting(-1,FALSE);
	
	lstRecentlyLogged->setColumnWidth(0,101);
	lstRecentlyLogged->setColumnWidth(1,193);
	lstRecentlyLogged->setColumnWidth(2,193);
	lstRecentlyLogged->setSorting(-1,FALSE);
	txtReclibLogBox->setEnabled(FALSE);
	log->getRecentlyLogged(lstRecentlyLogged);
	
	sp_audio = new QPixmap(path + "/images/sp_audio.bmp");
	sp_artist = new QPixmap(path + "/images/sp_artist.bmp");
	sp_album = new QPixmap(path + "/images/sp_album.bmp");
	
	last_item = NULL;
	
	tabPanelInfo = new TabPanelInfo(tabManage,"Info");
	tabPanelInfo->configure(authModule);
	tabPanelEmail = new TabPanelEmail(tabManage,"Email");
	tabPanelEmail->configure(authModule);
	tabPanelEmail->getEmail(C);	
	//tabPageScripts->setEnabled(false);
	//tabPageAudiowall->setEnabled(false);
	//tabPageSchedule->setEnabled(false);
	//tabPagePlaylist->setEnabled(false);
	btnLogin->setEnabled(false);
	cout << "Interface initialisation complete." << endl;

	// Create triggers for configuration and email
	cout << "Creating database triggers..." << endl;
	dbTrigger = new triggerThread(this, QString(conf->getDBConnectString()), 1); 
	dbTrigger->start();
	emailTrigger = new triggerThread(this, QString(conf->getDBConnectString()), 2); 
	emailTrigger->start();
	cout << "Trigger active." << endl;	
}

void frmStudioManage::destroy() {
	for (unsigned int i = 0; i < Playlist->size(); i++)
		delete Playlist->at(i);
	delete Playlist;
	delete log;
	delete library_engine;
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
	case 30002: { //Email
			tabPanelEmail->getEmail(C);
			break;
		}
	default: {
			qWarning("Unknown event type: %d", event->type());
			break;
		}
	}
}

void frmStudioManage::Library_Search() {
	cout << "Searching audio library..." << endl;
	library_engine->searchLimit(50);
	if (TitleCheckBox->isChecked()) {
		cout << " -> Search Title: true" << endl;
	}
	if (ArtistCheckBox->isChecked()) {
		cout << " -> Search Artist: true" << endl;
	}
	if (AlbumCheckBox->isChecked()) {
		cout << " -> Search Album: true" << endl;
	}
	library_engine->searchTitle(TitleCheckBox->isChecked());
	library_engine->searchArtist(ArtistCheckBox->isChecked());
	library_engine->searchAlbum(AlbumCheckBox->isChecked());
	if (SearchResults)
		for (unsigned int i = 0; i < SearchResults->size(); i++)
			delete SearchResults->at(i);
	delete SearchResults;
	SearchResults = library_engine->query(txtLibrarySearchText->text());
	cout << " -> Criteria: " << library_engine->lastQuery() << endl;
	cout << " -> Found: " << SearchResults->size() << " matches." << endl;
	tblLibrarySearchResults->setNumRows(SearchResults->size());
	for (unsigned int i = 0; i < SearchResults->size(); i++) {
		tblLibrarySearchResults->setItem(i,0,
										 new QTableItem( tblLibrarySearchResults, QTableItem::Never, SearchResults->at(i)->title()));
		tblLibrarySearchResults->setItem(i,1,
										 new QTableItem( tblLibrarySearchResults, QTableItem::Never, SearchResults->at(i)->artist()));
		tblLibrarySearchResults->setItem(i,2,
										 new QTableItem( tblLibrarySearchResults, QTableItem::Never, SearchResults->at(i)->album()));
		tblLibrarySearchResults->setItem(i,3,
										 new QTableItem( tblLibrarySearchResults, QTableItem::Never, SearchResults->at(i)->id()));
	}
	tblLibrarySearchResults->adjustColumn(0);
	tblLibrarySearchResults->adjustColumn(1);
	tblLibrarySearchResults->adjustColumn(2);
	tblLibrarySearchResults->setColumnWidth(3,0);
}

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

void frmStudioManage::LogRecord() {
	string artist = txtArtistLogBox->text().ascii();
	string title = txtTitleLogBox->text().ascii();
	string reclibid = txtReclibLogBox->text().ascii();

	if (log->details(0, artist, title) != 0)
		cout << "Logging failed" << endl;
	txtReclibLogBox->setText("");
	txtArtistLogBox->setText("");
	txtTitleLogBox->setText("");
	log->getRecentlyLogged(lstRecentlyLogged);
}

bool frmStudioManage::isDefined(QString *name) {
	//	for (unsigned short i = 0; i < names->size(); i++) {
	//		if (names->at(i) == name)
	//			return true;
	//	}
	return false;
}


void frmStudioManage::displayEmailBody( QListViewItem *current )
{
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
