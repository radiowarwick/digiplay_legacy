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

#include "clockThread.h"
#include "triggerThread.h"
#include "libsearch.h"
#include "track.h"
#include "config.h"
#include "recordLog.h"

libsearch *library_engine = new libsearch();
triggerThread *dbTrigger;
config *conf;
recordLog *log = new recordLog(1); 
Connection *C;
clockThread *ck;
vector<track*>* SearchResults;
vector<track*>* Playlist = new vector<track*>;
QPixmap *sp_audio, *sp_artist, *sp_album;
QString path;
QListViewItem *last_item;

void frmSearch::init() {
    cout << "Connecting to database..." << endl;
    conf = new config("digiplay");
    C = new Connection(conf->getDBConnectString());
    cout << "Connected." << endl;
    
	cout << "Initialising Interface..." << endl;
	path = qApp->applicationDirPath();
        tblLibrarySearchResults->setColumnWidth(3,0);
	lstShowPlan->setColumnWidth(0,80);
	lstShowPlan->setColumnWidth(1,20);
	lstShowPlan->setColumnWidth(2,20);
	lstShowPlan->setColumnWidth(3,60);
	lstShowPlan->setSorting(-1,FALSE);
	sp_audio = new QPixmap(path + "/images/sp_audio.bmp");
	sp_artist = new QPixmap(path + "/images/sp_artist.bmp");
	sp_album = new QPixmap(path + "/images/sp_album.bmp");
	last_item = NULL;
	ck = new clockThread(this);
	ck->start();
    cout << "Interface initialisation complete." << endl;
	
	cout << "Creating trigger on configuration settings..." << endl;
    dbTrigger = new triggerThread(this, QString(conf->getDBConnectString()), 1, 5); 
    dbTrigger->start();
    cout << "Trigger active." << endl;

}

void frmSearch::destroy() {
    for (unsigned int i = 0; i < Playlist->size(); i++)
        delete Playlist->at(i);
    delete Playlist;
}

void frmSearch::customEvent(QCustomEvent *event) {
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
	case 30000: {       // Configuration changed trigger
            conf->requery();
            cout << "Configuration data refreshed!" << endl;
			if (conf->getParam("next_on_showplan") == "" && lstShowPlan->childCount() > 0) {
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

void frmSearch::Library_Search() {
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

void frmSearch::PlaylistAdd(int row, int col, int button, const QPoint& mousepos) {
	if (mousepos.isNull()) {button = 0; row = 0; col = 0;}
    track *new_track = new track(*(SearchResults->at(row)));
    Playlist->push_back(new_track);
	QListViewItem *track_title = new QListViewItem( lstShowPlan,last_item, new_track->title(), "3:00", "00:00:00", "");
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
	
void frmSearch::LogRecord() {
    int retval;
    QString *artst = new QString(txtArtistLogBox->text());
    QString *ttle = new QString(txtTitleLogBox->text());
    QString *rclbid = new QString(txtReclibLogBox->text());
    string *artist  = new string(artst->ascii());
    string *title = new string(ttle->ascii());
    string *reclibid = new string (rclbid->ascii());
    
    if (isDefined(rclbid)) {
	retval=log->reclibid(C, 1, reclibid);
	txtReclibLogBox->setText("");
	txtArtistLogBox->setText("");
	txtTitleLogBox->setText("");
    }
    else {
	log->details(C, 1, artist, title);
	txtReclibLogBox->setText("");
	txtArtistLogBox->setText("");
	txtTitleLogBox->setText("");
    }
}

bool frmSearch::isDefined(QString *name) {
//	for (unsigned short i = 0; i < names->size(); i++) {
//		if (names->at(i) == name)
//			return true;
//	}
	return false;
}
