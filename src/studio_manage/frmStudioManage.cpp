/****************************************************************************
** Form implementation generated from reading ui file 'frmStudioManage.ui'
**
** Created: Sat Nov 6 09:43:05 2010
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include <cstdlib>

#include <QtGui/QApplication>
#include <QtGui/QMessageBox>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include <QtGui/QFrame>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QLayout>
#include <QtGui/QToolTip>
#include <QtGui/QWhatsThis>
#include <QtGui/QImage>
#include <QtGui/QPixmap>
#include <QtGui/QKeyEvent>

#include "dps/DpsObject.h"
#include "Logger.h"
#include "UserConfig.h"
#include "TabPanelInfo.h"
#include "TabPanelEmail.h"
#include "TabPanelSearch.h"
#include "TabPanelPlaylist.h"
#include "TabPanelLogging.h"
//#include "TabPanelScript.h"
//#include "TabPanelFileBrowser.h"
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
#include "frmStudioManage.h"

Auth *authModule;
UserConfig *userConfig;
Showplan *sp;
Nownext *nownext;
TabPanelInfo *tabPanelInfo;
TabPanelEmail *tabPanelEmail;
TabPanelSearch *tabPanelSearch;
//TabPanelFileBrowser *tabPanelFileBrowser;
TabPanelPlaylist *tabPanelPlaylist;
TabPanelLogging *tabPanelLogging;
//TabPanelScript *tabPanelScript;

Config *conf;
clockThread *ck;

/*
 *  Constructs a frmStudioManage as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
frmStudioManage::frmStudioManage( QWidget* parent, Qt::WindowFlags fl )
    : QDialog( parent, fl )
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setMinimumSize( QSize( 1024, 768 ) );
    setMaximumSize( QSize( 1024, 768 ) );
    setBaseSize( QSize( 1024, 768 ) );

    setModal( TRUE );

    tabManage = new QTabWidget( this );
    tabManage->setEnabled( TRUE );
    tabManage->setGeometry( QRect( 10, 40, 530, 660 ) );
    tabManage->setTabShape( QTabWidget::Rounded );

    tabPageInfo = new QWidget( tabManage );
    tabManage->addTab( tabPageInfo, QString::fromLatin1("") );

    mBottomFrame = new QFrame( this );
    mBottomFrame->setProperty("id","BottomFrame");
    mBottomFrame->setProperty("BottomFrame","True");
    mBottomFrame->setGeometry( QRect( 0, 712, 1030, 60 ) );

    pixLogo = new QLabel( mBottomFrame );
    pixLogo->setGeometry( QRect( 0, 0, 250, 60 ) );
    pixLogo->setProperty("BottomFrame","True");
    pixLogo->setProperty("id","Logo");
    pixLogo->setScaledContents( TRUE );

    btnLogin = new QPushButton( mBottomFrame );
    btnLogin->setEnabled( TRUE );
    btnLogin->setProperty("id","LoginButton");
    btnLogin->setGeometry( QRect( 768, 5, 250, 45 ) );
    btnLogin->setAutoDefault( FALSE );

    lblClock = new QLabel( mBottomFrame );
    lblClock->setGeometry( QRect( 260, 0, 140, 35 ) );
    lblClock->setProperty("BottomFrame","True");
    lblClock->setProperty("id","Clock");

    lblDate = new QLabel( mBottomFrame );
    lblDate->setGeometry( QRect( 430, 0, 320, 35 ) );
    lblDate->setProperty("BottomFrame","True");
    lblDate->setProperty("id","Date");
    lblDate->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    lblContactEmail = new QLabel( mBottomFrame );
    lblContactEmail->setGeometry( QRect( 260, 30, 220, 27 ) );
    lblContactEmail->setProperty("BottomFrame","True");
    lblContactEmail->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    lblContactSms = new QLabel( mBottomFrame );
    lblContactSms->setGeometry( QRect( 470, 30, 140, 27 ) );
    lblContactSms->setProperty("BottomFrame","True");
    lblContactSms->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    lblContactPhone = new QLabel( mBottomFrame );
    lblContactPhone->setGeometry( QRect( 610, 30, 140, 25 ) );
    lblContactPhone->setProperty("BottomFrame","True");
    lblContactPhone->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

//    frame10 = new QFrame( this );
//    frame10->setGeometry( QRect( 0, 30, 1030, 6 ) );
//    frame10->setStyleSheet("background-color: rgb(177,240,254);");
//    frame10->setFrameShape( QFrame::StyledPanel );
//    frame10->setFrameShadow( QFrame::Raised );

    languageChange();
    resize( QSize(1024, 768).expandedTo(minimumSizeHint()) );
    ensurePolished();

    // signals and slots connections
    connect( btnLogin, SIGNAL( clicked() ), this, SLOT( btnLoginClicked() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
frmStudioManage::~frmStudioManage()
{
    destroy();
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void frmStudioManage::languageChange()
{
    setWindowTitle( tr( "Digiplay Studio Management Interface" ) );
    //tabManage->changeTab( tabPageInfo, tr( "Starting Tab" ) );
    lblClock->setText( tr( "17:56:56" ) );
    btnLogin->setText( tr( "Log In" ) );
    lblDate->setText( tr( "Wednesday 26th September 2004" ) );
    lblContactPhone->setText( tr( "01234567890" ) );
    lblContactEmail->setText( tr( "studio@example.com" ) );
    lblContactSms->setText( tr( "01234567890" ) );
}

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
    pixLogo->setPixmap(QPixmap(":/images/digiplay.png"));
    lblContactPhone->setText(QString::fromStdString(conf->getParam("contact_phone")));
    lblContactSms->setText(QString::fromStdString(conf->getParam("contact_sms")));
    lblContactEmail->setText(QString::fromStdString(conf->getParam("contact_email")));
    cout << "success." << endl;

    //Load Now/Next widget
    nownext = new Nownext( this );
    nownext->setGeometry( QRect( 0, 0, 1030, 30 ) );
    nownext->configure(authModule);

    // Load tab panels after removing the template tab.
    tabManage->removeTab(tabManage->currentIndex());
    cout << " -> Info panel..." << flush;
    tabPanelInfo = new TabPanelInfo(tabManage,"Info");
    tabPanelInfo->configure(authModule);
    cout << " success." << endl;

    cout << " -> Search panel..." << flush;
    tabPanelSearch = new TabPanelSearch(tabManage, "Library Search");
    tabPanelSearch->configure(authModule);
    cout << " success." << endl;

//    cout << " -> File Browser panel..." << flush;
//    tabPanelFileBrowser = new TabPanelFileBrowser(tabManage, "File Browser");
//    tabPanelFileBrowser->configure(authModule);
//    cout << " success." << endl;

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

//    cout << " -> Script panel..." << flush;
//    tabPanelScript = new TabPanelScript(tabManage,"Script");
//    tabPanelScript->configure(authModule);
//    cout << " success." << endl;

    cout << " -> Showplan..." << flush;
    sp = new Showplan(this);
    sp->setGeometry( QRect( 547, 40, 470, 660) );
    sp->configure(authModule);
    cout << "success." << endl;

    connect ( tabPanelSearch, SIGNAL( audioSelected( const DpsAudioItem& ) ),
                sp, SLOT( append( const DpsAudioItem& ) ) );
    connect ( tabPanelPlaylist, SIGNAL( audioSelected( const DpsAudioItem& ) ),
                sp, SLOT( append( const DpsAudioItem& ) ) );

//    connect ( tabPanelFileBrowser, SIGNAL( audioSelected( const DpsAudioItem& ) ),
//                sp, SLOT( append( const DpsAudioItem& ) ) );
//    connect ( tabPanelFileBrowser, SIGNAL( scriptSelected( const DpsScriptItem& ) ),
//                sp, SLOT( append( const DpsScriptItem& ) ) );
//    connect ( tabPanelFileBrowser, SIGNAL( showplanSelected( const DpsShowPlan& ) ),
//                sp, SLOT( load( const DpsShowPlan& ) ) );
//    connect ( tabPanelFileBrowser, SIGNAL( awsetSelected( QString ) ),
//                this, SLOT( updateAwSet( QString ) ) );

//    connect ( sp, SIGNAL( scriptSelected( const DpsScriptItem& ) ),
//                tabPanelScript, SLOT( loadScript( const DpsScriptItem& ) ) );
//    connect ( sp, SIGNAL( scriptDeselected() ),
//                tabPanelScript, SLOT( clearScript() ) );
//    connect ( tabPanelScript, SIGNAL( scriptDone(const DpsScriptItem&) ),
//                sp, SLOT( scriptDone(const DpsScriptItem&) ) );

    cout << "Interface initialisation complete." << endl;
    cout << "Setting initial configuration values..." << flush;
    conf->setParam("next_on_showplan","");
    cout << "done." << endl;

    losePrivilage();
}

void frmStudioManage::destroy() {
    delete conf;
}

void frmStudioManage::customEvent(QEvent *event) {
    const char *routine = "frmStudioManage::customEvent";
    switch (event->type()) {
    case 20000: {       // Clock update
            QString s = dynamic_cast<ClockUpdateEvent*>(event)->data();
            lblClock->setText(s);
            break;
        }
    case 20001: {       // Date update
            QString s = dynamic_cast<ClockUpdateEvent*>(event)->data();
            lblDate->setText(s);
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
    conf->setParam("user_aw_set",index.toStdString());
}

void frmStudioManage::btnLoginClicked()
{
    if ( !authModule->isAuthenticated() ) {
        dlgLogin *dlg = new dlgLogin(this, 0);
        QString username;
        QString password;
        if ( dlg->exec() == QDialog::Accepted ){
            username = dlg->getUsername();
            password = dlg->getPassword();

            try {
                authModule->authSession(username.toStdString(),
                                        password.toStdString());
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
                    dlgWarn *warning = new dlgWarn(this, 0);
                    warning->setTitle("Failed");
                    warning->setWarning("Incorrect username or password.");
                    warning->setQuestion(false);
                    warning->exec();
                    delete warning;
                }
                else if (e == AUTH_PERMISSION_DENIED ) {
                    dlgWarn *warning = new dlgWarn(this, 0);
                    warning->setTitle("Failed");
                    warning->setWarning("Permission Denied. "
                        "If you believe this is in error, please contact "
                        "the system administrator.");
                    warning->setQuestion(false);
                    warning->exec();
                    delete warning;
                }
                else {
                    dlgWarn *warning = new dlgWarn(this, 0);
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
                dlgWarn *warning = new dlgWarn(this, 0);
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
        dlgWarn *dlg = new dlgWarn(this, 0);
        dlg->setTitle("Logout");
        dlg->setWarning("Are you sure you wish to logout?");
        if ( dlg->exec() == QDialog::Accepted ){
            authModule->closeSession();
            conf->setParam("user_aw_set","0");
            conf->setParam("userid","0");
            sp->clear();
            tabManage->setCurrentIndex(0);
            btnLogin->setText("Log In");
        }
        delete dlg;
    }
    tabPanelInfo->configure(authModule);
    tabPanelSearch->configure(authModule);
    tabPanelPlaylist->configure(authModule);
    tabPanelEmail->configure(authModule);
    tabPanelLogging->configure(authModule);
//    tabPanelScript->configure(authModule);
//    tabPanelFileBrowser->configure(authModule);
}

void frmStudioManage::keyPressEvent(QKeyEvent* e) {
    switch (e->key()) {
        case Qt::Key_Escape: {
            if (conf->isParamDefined("enable_shift_esc")) {
                string confValue = conf->getParam("enable_shift_esc");
                char c = toupper(confValue[0]);
                if (isShiftDown && (c == 'Y' || c == '1')) {
                    exit(0);
                }
            }
            break;
        }
        case Qt::Key_Shift:
            isShiftDown = true;
            break;
        default:
            break;
    }
    e->ignore();
}

void frmStudioManage::keyReleaseEvent(QKeyEvent* e) {
    switch (e->key()) {
        case Qt::Key_Escape:
            break;
        case Qt::Key_Shift:
            isShiftDown = false;
            break;
        default:
            break;
    }
    e->ignore();
}
