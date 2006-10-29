/*
 * Email GUI Module
 * TabPanelEmail.cpp
 * Extracts and displays a list of emails from the central database, and
 * provides the facility to view the email's contents. Updates the database
 * to reflect the read\unread status of the email
 *
 * Copyright (c) 2006 Chris Cantwell
 * Copyright (c) 2006 Ian Liverton
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

#include <qtabwidget.h>
#include <qtextbrowser.h>
#include <qlistview.h>
#include <qstring.h>
#include <qpixmap.h>
#include <qiconset.h>
#include <qfont.h>
#include <qheader.h>
#include <qapplication.h>
#include <qobject.h>

#include "dps.h"
#include "Auth.h"
#include "Logger.h"
#include "config.h"
#include "triggerThread.h"

#include "TabPanelEmail.h"

TabPanelEmail::TabPanelEmail(QTabWidget *parent, string text) 
        : TabPanel(parent,text) {
    panelTag = "TabEmail";

    // Initislise object pointers
    lstEmail = 0;
    txtEmailBody = 0;
    flagUpdateDisabled=0;

    // Create GUI objects and configure
    draw();

    // Connect to database
    config *conf = new config("digiplay");
    C = new Connection(conf->getDBConnectString());
    delete conf;

    // Create a trigger on database for trig_id2
    emailTrigger = new triggerThread(this, 
                        QString(conf->getDBConnectString()), 2);
    emailTrigger->start();

}

// clean up stuff
TabPanelEmail::~TabPanelEmail() {
    if (C && C->is_open()) {
        C->Deactivate();
    }
    delete C;

    delete pixEmailNew;
    delete pixEmailOld;
    delete icsEmailIcons;
}

// this is called whenever the application reconfigures itself,
// usually due to a change in authentication status (login, logoff)
void TabPanelEmail::configure(Auth *authModule) {
    if (authModule->isPermitted(panelTag)) {
        getEmail();
    }
    TabPanel::configure(authModule);
}

// This handles drawing the contents of the form, and connecting slots,
// but has little actual implementation
void TabPanelEmail::draw() {
    char* routine = "TabEmail::draw()";

    // this deletes the objects if they already exist so to avoid a leak
    if (lstEmail || txtEmailBody) {
        L_WARNING(LOG_TABEMAIL,"Implicit clear() called");
        clear();
    }

    // Load icons and create icon set
    QString path = qApp->applicationDirPath();
    pixEmailNew = new QPixmap(path + "/images/email_new16.png");
    pixEmailOld = new QPixmap(path + "/images/email_old16.png");
    icsEmailIcons = new QIconSet(*pixEmailNew, QIconSet::Automatic);
    
    // do all form drawing here, create widgets, set properties
    lstEmail = new QListView(getPanel(), "lstEmail" );
    lstEmail->addColumn( QString::null );
    lstEmail->header()->setResizeEnabled( FALSE, 
                        lstEmail->header()->count() - 1 );
    lstEmail->addColumn( QObject::tr( "From" ) );
    lstEmail->header()->setResizeEnabled( FALSE, 
                        lstEmail->header()->count() - 1 );
    lstEmail->addColumn( QObject::tr( "Subject" ) );
    lstEmail->header()->setResizeEnabled( FALSE, 
                        lstEmail->header()->count() - 1 );
    lstEmail->addColumn( QObject::tr( "Received" ) );
    lstEmail->header()->setResizeEnabled( FALSE, 
                        lstEmail->header()->count() - 1 );
    lstEmail->addColumn( QObject::tr( "ID" ) );
    lstEmail->header()->setResizeEnabled( FALSE, 
                        lstEmail->header()->count() - 1 );
    lstEmail->setGeometry( QRect( 10, 10, 495, 265 ) );
    lstEmail->setVScrollBarMode( QListView::AlwaysOn );
    lstEmail->setAllColumnsShowFocus( TRUE );
    lstEmail->setColumnText(0, *icsEmailIcons, "");
    lstEmail->setColumnWidthMode(1, QListView::Manual); 
    lstEmail->setColumnWidthMode(2, QListView::Manual); 
    lstEmail->setColumnWidthMode(3, QListView::Manual); 
    lstEmail->setColumnWidthMode(4, QListView::Manual); 
    lstEmail->setColumnWidth(0,22); //New
    lstEmail->setColumnWidth(1, 180);   
    lstEmail->setColumnWidth(2, 180);   
    lstEmail->setColumnWidth(3, 93);    
    lstEmail->setColumnWidth(4, 0); 
    lstEmail->header()->setMovingEnabled( FALSE );
    lstEmail->setSorting(-1, FALSE);

    txtEmailBody = new QTextBrowser(getPanel(), "txtEmailBody" );
    txtEmailBody->setGeometry( QRect( 10, 280, 495, 350 ) );
    fntBody = txtEmailBody->currentFont();
    pointSize= txtEmailBody->pointSize();

    // connect signals and slots here
    QObject::connect( lstEmail, SIGNAL( selectionChanged(QListViewItem*) ),
                            this, SLOT( getEmailBody(QListViewItem*) ) );
}


void TabPanelEmail::getEmail(){
    char *routine = "TabPanelEmail::getEmail";
    L_INFO(LOG_TABEMAIL,"Getting emails.");
    
    Transaction *T = new Transaction(*C,"");
    email e;
    tm *dte = 0;
    char date[30];
    QListViewItem *new_email = 0;
    string last_id = "0";

    if (lstEmail->childCount() > 0) {
        last_id = lstEmail->firstChild()->text(4).ascii();
    }

    //Extract the most recent 20 emails
    string SQL = "SELECT * FROM email ORDER BY datetime DESC LIMIT 20;";
    try {
        Result R = T->exec(SQL);
        string flag;
        // If there aren't any, we're done, but warn anyway
        if (R.size() == 0) {
            L_WARNING(LOG_TABEMAIL,"No emails have been returned.");
        }
        else {
            // Iterate over all emails
            for (unsigned int i = 0; i < R.size(); i++) {
                // Examine the emails from the oldest to the newest
                unsigned int j = R.size() - i - 1;
                unsigned int k = atoi(R[j]["id"].c_str());
                // If the email is already shown, just check it's read status
                if (k <= atoi(last_id.c_str())) {
                    QListViewItem *x = lstEmail->findItem(R[j]["id"].c_str(),4);
                    string flag = R[j]["new_flag"].c_str();
                    if ( !flag.compare("t"))
                        x->setPixmap(0,*pixEmailNew);
                    else
                        x->setPixmap(0,*pixEmailOld);
                    continue;
                }
                // if it's a new email, add it to the start of the list
                time_t thetime(atoi(R[j]["datetime"].c_str()));
                dte = localtime(&thetime);
                strftime(date, 30, "%Ex %H:%M", dte);
                new_email = new QListViewItem(lstEmail, 
                                        "",
                                        R[j]["sender"].c_str(),
                                        R[j]["subject"].c_str(),
                                        date,
                                        R[j]["id"].c_str());
                string flag = R[j]["new_flag"].c_str();
                if (  !flag.compare("t")   )
                    new_email->setPixmap(0, *pixEmailNew);
                else
                    new_email->setPixmap(0, *pixEmailOld);
                if (lstEmail->childCount() > 20) {
                    delete lstEmail->lastItem();
                }
            }
        }
    }
    catch (...) {
        L_ERROR(LOG_TABEMAIL,"Failed to get new e-mails.");
    }
    T->abort();
    delete T;

}

void TabPanelEmail::getEmailBody(QListViewItem *current) {
    char *routine = "TabPanelEmail::getEmailBody";
    L_INFO(LOG_TABEMAIL,"Get email body for id " + current->text(4));

    Transaction *T = new Transaction(*C,"");
    string id = current->text(4).ascii();
    string SQL = "SELECT * FROM email WHERE id = " + id;
    try {
        Result R = T->exec(SQL);
        T->abort();
        txtEmailBody->setCurrentFont(fntBody);
        txtEmailBody->setPointSize(pointSize);
        txtEmailBody->setText(R[0]["body"].c_str());
        string flag = R[0]["new_flag"].c_str();
        if ( flag.compare("t") ) {
            markRead(id);
        }
        current->setPixmap(0, *pixEmailOld);

    }
    catch (...) {
        L_ERROR(LOG_TABEMAIL,"Failed to get email body for id "
                                    + current->text(4));
        T->abort();
    }
    delete T;
}

void TabPanelEmail::markRead(string id) {
    char *routine = "TabPanelEmail::markRead";
    L_INFO(LOG_TABEMAIL,"Marking email id " + id + " as read.");

    Transaction *T = new Transaction(*C,"");
    flagUpdateDisabled = TRUE;
    string SQL = "UPDATE email SET new_flag='f' WHERE id=" + id;
    try {
        T->exec(SQL);
        T->commit();
    }
    catch (...) {
        L_ERROR(LOG_TABEMAIL,"Failed to set e-mail as read.");
    }
    T->abort();
    delete T;
}

void TabPanelEmail::customEvent(QCustomEvent *event) {
    char *routine = "TabPanelEmail::customEvent";
    switch (event->type()) {
        case 30002: {
            L_INFO(LOG_TABEMAIL,"A change to the email relation has occured.");
            if (!flagUpdateDisabled)
                getEmail();
            else
                flagUpdateDisabled=FALSE;
            break;
        }
        default: {
            L_WARNING(LOG_TABEMAIL,"Unknown event " + dps_itoa(event->type()));
            break;
        }
    }
}

void TabPanelEmail::clear() {
    delete lstEmail;
    delete txtEmailBody;
}
