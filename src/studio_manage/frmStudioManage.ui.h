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

#include "DpsObject.h"
#include "Logger.h"
#include "UserConfig.h"
#include "TabPanelInfo.h"
#include "TabPanelEmail.h"
#include "TabPanelSearch.h"
#include "TabPanelPlaylist.h"
#include "TabPanelLogging.h"
#include "TabPanelScript.h"
#include "TabPanelFileBrowser.h"
#include "Showplan.h"
#include "dlgLogin.h"
#include "dlgWarn.h"
#include "Auth.h"
#ifdef AUTH_LDAP
	#include "AuthLdap.h"
#endif
#ifdef AUTH_PSQL
	#include "AuthPsql.h"
#endif

#include "clockThread.h"
#include "Config.h"
#include "dps.h"

Auth *authModule;
UserConfig *userConfig;
Showplan *sp;
TabPanelInfo *tabPanelInfo;
TabPanelEmail *tabPanelEmail;
TabPanelSearch *tabPanelSearch;
TabPanelFileBrowser *tabPanelFileBrowser;
TabPanelPlaylist *tabPanelPlaylist;
TabPanelLogging *tabPanelLogging;
TabPanelScript *tabPanelScript;

Config *conf;
clockThread *ck;

void frmStudioManage::init() {
    // Configure logging
    Logger::setAppName("studio_manage");
    Logger::setLogLevel(5);
    Logger::setDisplayLevel(0);
    
	// Connect to database
	cout << "Connecting to database..." << endl;
	conf = new Config("digiplay");
    DpsObject::dbInit();
	cout << "Connected." << endl;

	// Initialise modules
	cout << "Initialising Core Modules..." << endl;
	cout << " -> Authentication subsystem...";
	btnLogin->setEnabled(true);
#ifdef AUTH_LDAP
	authModule = new AuthLdap(conf->getParam("ldap_host"),
								atoi(conf->getParam("ldap_port").c_str()),
								conf->getParam("ldap_dn"));
#endif
#ifdef AUTH_PSQL
	authModule = new AuthPsql();
#endif
    userConfig = new UserConfig(authModule);
	cout << "success." << endl;
	
	cout << " -> Clock...";
	ck = new clockThread(this);
	ck->start();
	cout << "success." << endl;
	cout << "All modules loaded." << endl;
	
	// Initialise interface
	cout << "Initialising Interface..." << endl;
	QString path = qApp->applicationDirPath();

	//Load Images
	cout << " -> Loading Images... ";
	pixFade->setPixmap(QPixmap(path + "/images/fade.png"));
	pixLogo->setPixmap(QPixmap(path + "/images/rawdigiplay.png"));
	cout << "success." << endl;
	
	// Load tab panels after removing the template tab.	
	tabManage->removePage(tabManage->currentPage());
	cout << " -> Info panel..." << flush;
	tabPanelInfo = new TabPanelInfo(tabManage,"Info");
	tabPanelInfo->configure(authModule);
	cout << " success." << endl;

	cout << " -> Search panel..." << flush;
	tabPanelSearch = new TabPanelSearch(tabManage, "Library Search");
	tabPanelSearch->configure(authModule);
	cout << " success." << endl;

	cout << " -> File Browser panel..." << flush;
	tabPanelFileBrowser = new TabPanelFileBrowser(tabManage, "File Browser");
	tabPanelFileBrowser->configure(authModule);
	cout << " success." << endl;

	cout << " -> Playlist panel..." << flush;
	tabPanelPlaylist = new TabPanelPlaylist(tabManage, "Playlist");
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

	cout << " -> Showplan..." << flush;
	sp = new Showplan(this,"sp");
    sp->setGeometry( QRect( 550, 40, 470, 670) );
    sp->configure(authModule);
	cout << "success." << endl;

    connect ( tabPanelSearch, SIGNAL( itemSelected( QString ) ),
                sp, SLOT( addTrack( QString ) ) );
    connect ( tabPanelPlaylist, SIGNAL( itemSelected( QString ) ),
                sp, SLOT( addTrack( QString ) ) );

    connect ( tabPanelFileBrowser, SIGNAL( trackSelected( QString ) ),
                sp, SLOT( addTrack( QString ) ) );
    connect ( tabPanelFileBrowser, SIGNAL( jingleSelected( QString ) ),
                sp, SLOT( addJingle( QString ) ) );
    connect ( tabPanelFileBrowser, SIGNAL( advertSelected( QString ) ),
                sp, SLOT( addAdvert( QString ) ) );
    connect ( tabPanelFileBrowser, SIGNAL( scriptSelected( DpsShowScript& ) ),
                sp, SLOT( addScript( DpsShowScript& ) ) );
    connect ( tabPanelFileBrowser, SIGNAL( showplanSelected( DpsShowplan& ) ),
                sp, SLOT( loadShowplan( DpsShowplan& ) ) );
    connect ( tabPanelFileBrowser, SIGNAL( cartsetSelected( QString ) ),
                this, SLOT( updateCartset( QString ) ) );

	cout << "Interface initialisation complete." << endl;
}

void frmStudioManage::destroy() {

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
	default: {
			qWarning("Unknown event type: %d", event->type());
            L_WARNING(LOG_DB,"Unknown event type: " + dps_itoa(event->type()));
			break;
		}
	}
}

void frmStudioManage::updateCartset( QString index ) {
    conf->setParam("user_cartset",index.ascii());
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
                    delete userConfig;
                    userConfig = new UserConfig(authModule);
                    conf->setParam("user_cartset",
                                    userConfig->get("default_cartset"));
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
	tabPanelFileBrowser->configure(authModule);
}
