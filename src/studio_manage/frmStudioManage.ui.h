/*
 * Studio Management Application
 * frmStudioManage.ui.h
 * Provides implementation of routines used by the main GUI for the Studio
 * Management application.
 *
 * Copyright (c) 2004-2006 Chris Cantwell
 * Copyright (c) 2004-2006 Ian Liverton
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
#include <qapplication.h>
#include <qmessagebox.h>
#include <qmutex.h>

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
QMutex activePointLock;
ShowPlanItem *activePoint;		// the first item in plan currently loaded

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

	// Initialise modules
	cout << "Initialising Core Modules..." << endl;
	cout << " -> Authentication subsystem...";
	authModule = new AuthLdap("ldapserver",389,
								"ou=People,dc=radio,dc=warwick,dc=ac,dc=uk");
	cout << "success." << endl;
	
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
	lstShowPlan->header()->hide();

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
	tabPanelFileBrowser = new TabPanelFileBrowser(tabManage, this, "File Browser");
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

//	cout << " -> Script panel..." << flush;
//	tabPanelScript = new TabPanelScript(tabManage,"Script");
//	tabPanelScript->configure(authModule);
//	cout << " success." << endl;

	btnLogin->setEnabled(true);
	cout << "Interface initialisation complete." << endl;

	// Create trigger for configuration
	cout << "Creating database triggers..." << endl;
	dbTrigger = new triggerThread(this, QString(conf->getDBConnectString()), 1); 
	dbTrigger->start();
	cout << "Triggers active." << endl;	

	activePoint = 0;
}

void frmStudioManage::destroy() {
//	for (unsigned int i = 0; i < Playlist->size(); i++)
//		delete Playlist->at(i);
//	delete Playlist;
}

void frmStudioManage::customEvent(QCustomEvent *event) {
    char *routine = "frmStudioManage::customEvent";
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
            L_INFO(LOG_DB,"Triggering configuration refresh");
			conf->requery();
			if (conf->getParam("next_on_showplan") == "" 
								&& lstShowPlan->childCount() > 0
                                && activePoint != lstShowPlan->lastItem()) {
                activePointLock.lock();
                L_INFO(LOG_DB,"Processing track load event");
				if (activePoint == 0) {
					activePoint = (ShowPlanItem*)lstShowPlan->firstChild();
				}
				else {
					activePoint->setState(SHOWPLAN_STATE_FINISHED);
					activePoint = (ShowPlanItem*)activePoint->nextSibling();
				}
                if (!activePoint) cout << "NULL ACTIVE POINT!" << endl;
				activePoint->setState(SHOWPLAN_STATE_LOADED);
				lstShowPlan->ensureItemVisible(activePoint);
				if (lstShowPlan->selectedItem()) {
					lstShowPlanSelectionChanged(lstShowPlan->selectedItem());
				}
                L_INFO(LOG_DB,"Triggering update of next_on_showplan entry");
                activePointLock.unlock();
				updateNextTrack();
			}
            L_INFO(LOG_DB,"Configuration refresh complete.");
			break;
		}
	default: {
			qWarning("Unknown event type: %d", event->type());
            L_WARNING(LOG_DB,"Unknown event type: " + dps_itoa(event->type()));
			break;
		}
	}
}

void frmStudioManage::playlistAdd(QString md5) {
    char *routine = "frmStudioManage::playlistAdd";
    L_INFO(LOG_SHOWPLAN,"Adding to showplan " + md5);
	track t = dps_getTrack(C,md5);
    if (t.isNull) return;
	new ShowPlanAudio( lstShowPlan,	lstShowPlan->lastItem(), t); 
    L_INFO(LOG_DB,"Triggering update of next_on_showplan entry");
	updateNextTrack();
    L_INFO(LOG_DB,"Playlist add complete.");
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
		    
		    try {
			    authModule->authSession(username, password);
			    if ( authModule->isAuthenticated() ) {
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
//	tabPanelScript->configure(authModule);
//	tabPanelFileBrowser->configure(authModule);
}


void frmStudioManage::btnMoveTopClicked() {
	if (lstShowPlan->childCount() == 0) return;
	QListViewItem *x = lstShowPlan->selectedItem();
    if ( x && x != lstShowPlan->firstChild()) {
        if (!activePoint) {
    		lstShowPlan->takeItem(x);
    		lstShowPlan->insertItem(x);
        }
        else {
    		x->moveItem(activePoint);
        }
		lstShowPlan->setSelected(x,true);
		lstShowPlanSelectionChanged(x);
		updateNextTrack();
    }
}


void frmStudioManage::btnMoveUpClicked() {
	if (lstShowPlan->childCount() == 0) return;
	QListViewItem *x = lstShowPlan->selectedItem();
    if ( x ) {
		if (x == lstShowPlan->firstChild()->itemBelow() ) {
		    lstShowPlan->takeItem(x);
		    lstShowPlan->insertItem(x);
		    lstShowPlan->setSelected(x,true);
		}
		else if (x != lstShowPlan->firstChild()) {
			x->moveItem(x->itemAbove()->itemAbove());
		}
		lstShowPlanSelectionChanged(x);
		updateNextTrack();
    }
}


void frmStudioManage::btnDeleteClicked() {
	if (lstShowPlan->childCount() == 0) return;
	QListViewItem *x = lstShowPlan->selectedItem();
	QListViewItem *y;
    if ( x ) {
		y = x->nextSibling();
		delete x;
		if ( y ) {
			lstShowPlan->setSelected(y,true);
		}
        else {
            y = lstShowPlan->lastItem();
            lstShowPlan->setSelected(y,true);
        }
		lstShowPlanSelectionChanged(y);            

	}
	updateNextTrack();
}

void frmStudioManage::btnClearClicked() {
	if (lstShowPlan->childCount() == 0) return;
    dlgWarn *dlg = new dlgWarn(this, "");
    dlg->setTitle("Clear All");
    dlg->setWarning("Are you sure you wish to clear the show plan?");
    if ( dlg->exec() == QDialog::Accepted ){
		lstShowPlan->clear();
		lstShowPlanSelectionChanged(0);
		activePoint = 0;
		updateNextTrack();
    }
    delete dlg;
}

void frmStudioManage::btnMoveDownClicked() {
	if (lstShowPlan->childCount() == 0) return;
	QListViewItem *x = lstShowPlan->selectedItem();
    if ( x ) {
		if (x != lstShowPlan->lastItem() ) {
			x->moveItem(x->itemBelow());
			lstShowPlan->setSelected(x,true);
			lstShowPlanSelectionChanged(x);
			updateNextTrack();
		}
	}
}

void frmStudioManage::btnMoveBottomClicked() {
	if (lstShowPlan->childCount() == 0) return;
	QListViewItem *x = lstShowPlan->selectedItem();
    if ( x ) {
		x->moveItem(lstShowPlan->lastItem());
		lstShowPlan->setSelected(lstShowPlan->lastItem(),true);
		lstShowPlanSelectionChanged(x);
		updateNextTrack();
    }
}


void frmStudioManage::updateNextTrack() {
	ShowPlanItem *x = 0;
	if (lstShowPlan->childCount() == 0) return;
    activePointLock.lock();
	if ( ! activePoint ) {
		x = (ShowPlanItem*)lstShowPlan->firstChild();
	}
	else {
		x = (ShowPlanItem*)activePoint->nextSibling();
	}
    activePointLock.unlock();
	if ( x ) {
		do
			if (x->getType() == 0) {
				ShowPlanAudio *audio = (ShowPlanAudio*)x;
				track t = audio->getTrack();
				conf->setParam("next_on_showplan",t.md5);
				return;
			}
		while ((x = (ShowPlanItem*)x->nextSibling()) != 0);
	}
}


void frmStudioManage::lstShowPlanSelectionChanged(QListViewItem *x) {
	ShowPlanItem *y = (ShowPlanItem*)x;
	if ( y && y->getState() == SHOWPLAN_STATE_UNLOADED ) {
		ShowPlanItem *z = (ShowPlanItem*)y->itemAbove();
		if ( z && z->getState() == SHOWPLAN_STATE_UNLOADED) {
			btnMoveUp->setEnabled(true);
			btnMoveTop->setEnabled(true);
		}
		else {
			btnMoveUp->setEnabled(false);
			btnMoveTop->setEnabled(false);
		}
		if ( y == (ShowPlanItem*)lstShowPlan->lastItem() ) {
			btnMoveBottom->setEnabled(false);
			btnMoveDown->setEnabled(false);
		}
		else {
			btnMoveBottom->setEnabled(true);
			btnMoveDown->setEnabled(true);
		}
		btnDelete->setEnabled(true);
		return;
	}
	btnMoveBottom->setEnabled(false);
	btnMoveDown->setEnabled(false);
	btnMoveUp->setEnabled(false);
	btnMoveTop->setEnabled(false);
	btnDelete->setEnabled(false);
}
