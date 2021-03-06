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
#include <cstdlib>

#include <qapplication.h>
#include <qmessagebox.h>

#include "dps/DpsObject.h"
#include "Logger.h"
#include "UserConfig.h"
#include "TabPanelInfo.h"
#include "TabPanelEmail.h"
#include "TabPanelSearch.h"
#include "TabPanelPlaylist.h"
#include "TabPanelLogging.h"
#include "TabPanelScript.h"
#include "TabPanelFileBrowser.h"
#include "Nownext.h"
#include "Showplan.h"
#include "dlgLogin.h"
#include "dlgWarn.h"
#include "Auth.h"
#include "AuthLdap.h"
#include "AuthPsql.h"
#include "Security.h"

#include "clockThread.h"
#include "Config.h"
#include "dps.h"

Auth *authModule;
UserConfig *userConfig;
Showplan *sp;
Nownext *nownext;
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
    isShiftDown = false;

    // Connect to database
    cout << "Processing configuration..." << flush;
    conf = new Config("digiplay");
    cout << "complete!" << endl;
    
    cout << "Resetting playout engine..." << flush;
    conf->setParam("user_aw_set","0");
    conf->setParam("userid","0");
    cout << "done." << endl;
    
    // Initialise modules
    cout << "Initialising Core Modules..." << endl;

    cout << " -> Authentication subsystem...";
    btnLogin->setEnabled(true);
    // Load the appropriate authentication module as per config
    if (conf->getParam("auth_method") == "LDAP") {
        authModule = new AuthLdap(conf->getParam("ldap_host"),
                                atoi(conf->getParam("ldap_port").c_str()),
                                conf->getParam("ldap_dn"),
                                conf->getParam("ldap_filter"));
    }
    else if (conf->getParam("auth_method") == "PSQL") {
        authModule = new AuthPsql();
    }
    else {
        cout << "unknown authentication method: ";
        cout << conf->getParam("auth_method") << endl;
        throw -1;
    }
    userConfig = new UserConfig(authModule);
    cout << "success." << endl;

    cout << " -> Clock...";
    ck = new clockThread(this);
    ck->start();
    cout << "success." << endl;
    cout << "All modules loaded." << endl;

    // Initialise interface
    cout << "Initialising Interface..." << endl;
    QString path = DPSDIR;

    //Load Images
    cout << " -> Loading Images and setting contact information... ";
//  pixFade->setPixmap(QPixmap(path + "/images/fade.png"));
    pixLogo->setPixmap(QPixmap(path + "/images/rawdigiplay.png"));
        lblContactPhone->setText(QString(conf->getParam("contact_phone")));
        lblContactSms->setText(QString(conf->getParam("contact_sms")));
        lblContactEmail->setText(QString(conf->getParam("contact_email")));
    cout << "success." << endl;

    //Load Now/Next widget
    nownext = new Nownext( this, "Nownext");
    nownext->setGeometry( QRect( 0, 0, 1030, 30 ) );
    nownext->configure(authModule);

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

    cout << " -> Script panel..." << flush;
    tabPanelScript = new TabPanelScript(tabManage,"Script");
    tabPanelScript->configure(authModule);
    cout << " success." << endl;

    cout << " -> Showplan..." << flush;
    sp = new Showplan(this,"sp");
    sp->setGeometry( QRect( 550, 40, 470, 670) );
    sp->configure(authModule);
    cout << "success." << endl;

    connect ( tabPanelSearch, SIGNAL( audioSelected( const DpsAudioItem& ) ),
                sp, SLOT( append( const DpsAudioItem& ) ) );
    connect ( tabPanelPlaylist, SIGNAL( audioSelected( const DpsAudioItem& ) ),
                sp, SLOT( append( const DpsAudioItem& ) ) );

    connect ( tabPanelFileBrowser, SIGNAL( audioSelected( const DpsAudioItem& ) ),
                sp, SLOT( append( const DpsAudioItem& ) ) );
    connect ( tabPanelFileBrowser, SIGNAL( scriptSelected( const DpsScriptItem& ) ),
                sp, SLOT( append( const DpsScriptItem& ) ) );
    connect ( tabPanelFileBrowser, SIGNAL( showplanSelected( const DpsShowPlan& ) ),
                sp, SLOT( load( const DpsShowPlan& ) ) );
    connect ( tabPanelFileBrowser, SIGNAL( awsetSelected( QString ) ),
                this, SLOT( updateAwSet( QString ) ) );
//    connect ( sp, SIGNAL( scriptSelected( int ) ),
//                tabPanelScript, SLOT( loadScript( int ) ) );
//    connect ( sp, SIGNAL( scriptDeselected() ),
//                tabPanelScript, SLOT( clearScript() ) );
//    connect ( tabPanelScript, SIGNAL( scriptDone() ),
//                sp, SLOT( scriptDone() ) );

    cout << "Interface initialisation complete." << endl;
    cout << "Setting initial configuration values..." << flush;
    conf->setParam("next_on_showplan","");
    cout << "done." << endl;

    losePrivilage();
}

void frmStudioManage::destroy() {
    delete conf;
}

void frmStudioManage::customEvent(QCustomEvent *event) {
    const char *routine = "frmStudioManage::customEvent";
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

/*void frmStudioManage::processConfigUpdate() {
    AuthLdap* a;
    if ((a = dynamic_cast<AuthLdap*>(authModule)) != 0) {
        conf->requery();
        std::string host = conf->getParam("ldap_host");
        unsigned int port = atoi(conf->getParam("ldap_port").c_str());
        std::string baseDn = conf->getParam("ldap_dn");
        std::string filter = conf->getParam("ldap_filter");
        a->reconnect(host, port, baseDn, filter);
    }
}
*/
void frmStudioManage::updateAwSet( QString index ) {
    conf->setParam("user_aw_set",index.ascii());
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
                    userConfig = new UserConfig(authModule);
                    conf->setParam("user_aw_set",
                                    userConfig->get("default_aw_set"));
                    delete userConfig;
                    btnLogin->setText("Log Out");
                }
            }
            catch (int e) {
                if ( e==AUTH_INVALID_CREDENTIALS ) {
                    dlgWarn *warning = new dlgWarn(this, "");
                    warning->setTitle("Failed");
                    warning->setWarning("Incorrect username or password.");
                    warning->setQuestion(false);
                    warning->exec();
                    delete warning;
                }
                else if (e == AUTH_PERMISSION_DENIED ) {
                    dlgWarn *warning = new dlgWarn(this, "");
                    warning->setTitle("Failed");
                    warning->setWarning("Permission Denied. "
                        "If you believe this is in error, please contact "
                        "the system administrator.");
                    warning->setQuestion(false);
                    warning->exec();
                    delete warning;
                }
                else {
                    dlgWarn *warning = new dlgWarn(this, "");
                    warning->setTitle("Error");
                    warning->setWarning("Problem authenticating with server. "
                                        "Please check your settings.");
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
            conf->setParam("user_aw_set","0");
            conf->setParam("userid","0");
            sp->clear();
            tabManage->setCurrentPage(0);
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

void frmStudioManage::keyPressEvent(QKeyEvent* e) {
    switch (e->key()) {
        case Key_Escape: {
            if (conf->isParamDefined("enable_shift_esc")) {
                string confValue = conf->getParam("enable_shift_esc");
                char c = toupper(confValue[0]);
                if (isShiftDown && (c == 'Y' || c == '1')) {
                    exit(0);
                }
            }
            break;
        }
        case Key_Shift:
            isShiftDown = true;
            break;
        default:
            break;
    }
    e->ignore();
}

void frmStudioManage::keyReleaseEvent(QKeyEvent* e) {
    switch (e->key()) {
        case Key_Escape:
            break;
        case Key_Shift:
            isShiftDown = false;
            break;
        default:
            break;
    }
    e->ignore();
}
