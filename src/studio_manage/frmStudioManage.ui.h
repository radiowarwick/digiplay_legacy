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
#include <qmessagebox.h>

#include "Logger.h"
#include "AuthLdap.h"
#include "TabPanelInfo.h"
#include "TabPanelEmail.h"
#include "TabPanelSearch.h"
#include "TabPanelPlaylist.h"
#include "TabPanelLogging.h"
#include "TabPanelScript.h"
#include "TabPanelFileBrowser.h"
#include "ShowPlanItem.h"
#include "ShowPlanAudio.h"
#include "ShowPlanScript.h"
#include "dlgLogin.h"
#include "dlgWarn.h"

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

triggerThread *dbTrigger;
config *conf;
Connection *C;
clockThread *ck;
vector<track> *SearchResults;
//vector<track> *Playlist = new vector<_track*>;
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
	authModule = new AuthLdap("ldapserver",389,"ou=People,dc=radio,dc=warwick,dc=ac,dc=uk");
	
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

	//Load Images
	cout << " -> Loading Images... ";
	pixFade->setPixmap(QPixmap(path + "/images/fade.png"));
	pixLogo->setPixmap(QPixmap(path + "/images/rawdigiplay.png"));

	btnMoveUp->setPixmap(QPixmap(path + "/images/moveup32.png"));
	btnMoveDown->setPixmap(QPixmap(path + "/images/movedown32.png"));
	btnMoveTop->setPixmap(QPixmap(path + "/images/movetop32.png"));
	btnMoveBottom->setPixmap(QPixmap(path + "/images/movebottom32.png"));
	btnDelete->setPixmap(QPixmap(path + "/images/delete48.png"));
	btnClear->setPixmap(QPixmap(path + "/images/clear32.png"));
	
	cout << "success." << endl;
	
	
	lstShowPlan->setColumnWidth(0,lstShowPlan->width() - 5);
	lstShowPlan->setSorting(-1);

	// Load tab panels after removing the template tab.	
	tabManage->removePage(tabManage->currentPage());
	cout << "Loading panels" << endl;
	cout << " -> Info panel..." << flush;
	tabPanelInfo = new TabPanelInfo(tabManage,"Info");
	tabPanelInfo->configure(authModule);
	cout << " success." << endl;

	cout << " -> Search panel..." << flush;
	tabPanelSearch = new TabPanelSearch(tabManage, this, "Library Search");
	tabPanelSearch->configure(authModule);
	cout << " success." << endl;

	cout << " -> File Browser panel..." << flush;
	tabPanelFileBrowser = new TabPanelFileBrowser(tabManage,"File Browser");
	tabPanelFileBrowser->configure(authModule);
	cout << " success." << endl;

	cout << " -> Playlist panel..." << flush;
	tabPanelPlaylist = new TabPanelPlaylist(tabManage, this, "Playlist");
	tabPanelPlaylist->configure(authModule);
	cout << " success." << endl;
	
	cout << " -> Email panel..." << flush;
	tabPanelEmail = new TabPanelEmail(tabManage,"Email");
	tabPanelEmail->configure(authModule);
	cout << " success." << endl;

	cout << " -> Logging panel..." << flush;
	tabPanelLogging = new TabPanelLogging(tabManage,"Logging");
	tabPanelLogging->configure(authModule);
	cout << " success." << endl;

	cout << " -> Script panel..." << flush;
	tabPanelScript = new TabPanelScript(tabManage,"Script");
	tabPanelScript->configure(authModule);
	cout << " success." << endl;

	btnLogin->setEnabled(true);
	cout << "Interface initialisation complete." << endl;

	// Create trigger for configuration
	cout << "Creating database triggers..." << endl;
	dbTrigger = new triggerThread(this, QString(conf->getDBConnectString()), 1); 
	dbTrigger->start();
	cout << "Triggers active." << endl;	
}

void frmStudioManage::destroy() {
//	for (unsigned int i = 0; i < Playlist->size(); i++)
//		delete Playlist->at(i);
//	delete Playlist;
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
			if (conf->getParam("next_on_showplan") == "" 
								&& lstShowPlan->childCount() > 0) {
				delete lstShowPlan->firstChild();
				updateNextTrack();
			}
			break;
		}
	default: {
			qWarning("Unknown event type: %d", event->type());
			break;
		}
	}
}

void frmStudioManage::playlistAdd(QString md5) {
	track t = dps_getTrack(C,md5);
	ShowPlanAudio *audio_item = new ShowPlanAudio( lstShowPlan, last_item, t); 
	last_item = audio_item;
	updateNextTrack();
}

bool frmStudioManage::isDefined(QString *name) {
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

void frmStudioManage::btnLoginClicked()
{
    if ( !authModule->isAuthenticated() ) {
		dlgLogin *dlg = new dlgLogin(this, "");
		QString username;
		QString password;
		if ( dlg->exec() == QDialog::Accepted ){
		    username = dlg->getUsername();
		    password = dlg->getPassword();
		    
		    cout << " -> Trying login... ";
		    try {
			    authModule->authSession(username, password);
			    if ( authModule->isAuthenticated() ) {
				cout << "success." << endl;
				btnLogin->setText("Log Out");
			    }
			}
			catch (int e) {
			    if ( e==AUTH_INVALID_CREDENTIALS ) {
					cout << "failed: Incorrect username or password." << endl;
					dlgWarn *warning = new dlgWarn(this, "");
					warning->setTitle("Error");
					warning->setWarning("Incorrect username or password.");
					warning->setQuestion(false);
					warning->exec();
					delete warning;
			    }
			    else {
					cout << "failed: Error code " << e << endl;
					dlgWarn *warning = new dlgWarn(this, "");
					warning->setTitle("Error");
					warning->setWarning("Problem connecting to the server. Please check your settings.");
				warning->setQuestion(false);
				warning->exec();
				delete warning;
			    }
			}
			catch (...) {
			    cout << "failed: reason unknown." << endl;
			    dlgWarn *warning = new dlgWarn(this, "");
			    warning->setTitle("Error");
			    warning->setWarning("An unknown error occurred.");
			    warning->setQuestion(false);
			    warning->exec();
			    delete warning;
			}
		}
		delete dlg;
    }
    else {
		dlgWarn *dlg = new dlgWarn(this, "");
		dlg->setTitle("Logout");
		dlg->setWarning("Are you sure you wish to logout?");
		if ( dlg->exec() == QDialog::Accepted ){
		    authModule->closeSession();
		    btnLogin->setText("Log In");
		}
		delete dlg;
	}
	tabPanelInfo->configure(authModule);
	tabPanelSearch->configure(authModule);
	tabPanelPlaylist->configure(authModule);
	tabPanelEmail->configure(authModule);
	tabPanelLogging->configure(authModule);
	tabPanelScript->configure(authModule);
	tabPanelFileBrowser->configure(authModule);
}


void frmStudioManage::btnMoveTopClicked() {
    if ( lstShowPlan->selectedItem() ) {
		QListViewItem *temp;
		temp = lstShowPlan->selectedItem();
		lstShowPlan->takeItem(temp);
		lstShowPlan->insertItem(temp);
		updateNextTrack();
    }
}


void frmStudioManage::btnMoveUpClicked() {
    if ( lstShowPlan->selectedItem() ) {
		if (lstShowPlan->selectedItem() 
					== lstShowPlan->firstChild()->itemBelow() ) {
		    QListViewItem *temp;
		    temp = lstShowPlan->selectedItem();
		    lstShowPlan->takeItem(temp);
		    lstShowPlan->insertItem(temp);
		}
		else {
		    lstShowPlan->selectedItem()->moveItem(
					lstShowPlan->selectedItem()->itemAbove()->itemAbove());
		}
    }
}


void frmStudioManage::btnDeleteClicked() {
    if ( lstShowPlan->selectedItem() )
		delete lstShowPlan->selectedItem();
}

void frmStudioManage::btnClearClicked() {
    dlgWarn *dlg = new dlgWarn(this, "");
    dlg->setTitle("Clear All");
    dlg->setWarning("Are you sure you wish to clear the show plan?");
    if ( dlg->exec() == QDialog::Accepted ){
		authModule->closeSession();
		btnLogin->setText("Log In");
		lstShowPlan->clear();
		updateNextTrack();
    }
    delete dlg;
}

void frmStudioManage::btnMoveDownClicked() {
    if ( lstShowPlan->selectedItem() ) {
		lstShowPlan->selectedItem()->moveItem(
				lstShowPlan->selectedItem()->itemBelow());
	}
}

void frmStudioManage::btnMoveBottomClicked() {
    if ( lstShowPlan->selectedItem() ) {
		lstShowPlan->selectedItem()->moveItem(lstShowPlan->lastItem());
    }
}


void frmStudioManage::updateNextTrack() {
	if (lstShowPlan->childCount() > 0) {
		ShowPlanItem *item = (ShowPlanItem*)lstShowPlan->firstChild();
		do
			if (item->getType() == 0) {
				ShowPlanAudio *audio = (ShowPlanAudio*)item;
				track t = audio->getTrack();
				conf->setParam("next_on_showplan",t.md5);
				return;
			}
		while ((item = (ShowPlanItem*)item->nextSibling()) != 0);
	}
	conf->setParam("next_on_showplan","");
}
