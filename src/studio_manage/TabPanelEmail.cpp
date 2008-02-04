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
#include "QtTrigger.h"
#include "DpsEmail.h"

#include "TabPanelEmail.h"

/**
 * Initialises the panel, creates components, draws the GUI components
 * and initialises the database trigger for the email table.
 */
TabPanelEmail::TabPanelEmail(QTabWidget *parent, string text) 
        : TabPanel(parent,text) {
    // Set panel tag.
    panelTag = "TabEmail";
    
    // Initialise object pointers.
    lstEmail = 0;
    txtEmailBody = 0;
    flagUpdateDisabled=0;

    // Create GUI objects and configure them.
    draw();

    // Email accessor class.
    E = new DpsEmail();

    // Create a trigger on the email table so we update when changes are made.
    triggerEmail = new QtTrigger("triggerEmail","trig_id2");
    
    // Upon triggering, run the getEmail() routine.
    connect(triggerEmail, SIGNAL(trigger()),
                            this, SLOT(getEmail()));
}


/**
 * Clean up dynamically created objects
 */ 
TabPanelEmail::~TabPanelEmail() {
    // Clean up GUI components
    clear();
    
    // Email trigger.
    delete triggerEmail;

    // Email accessor class.
    delete E;
}


/**
 * Reconfigure the panel to reflect the current authentication status.
 */
void TabPanelEmail::configure(Auth *authModule) {
    // If this module is permitted in the current authentication state
    // then get emails, otherwise clear the list.
    if (authModule->isPermitted(panelTag)) {
        getEmail();
    }
    else {
        lstEmail->clear();
    }
    
    // Do base level configuration (hide modules if necessary)
    TabPanel::configure(authModule);
}


/**
 * Retrieves the body of an email, given the QListViewItem from the email
 * list.
 */
void TabPanelEmail::getEmailBody(QListViewItem *current) {
    const char *routine = "TabPanelEmail::getEmailBody";
    L_INFO(LOG_TABEMAIL,"Get email body for id " + current->text(4));

    // Find selected email and display email body
    // TODO: Reimplement using a map.
    for (unsigned int i = 0; i < emails.size(); ++i) {
        if (emails[i].id == string(current->text(4).ascii())) {
            txtEmailBody->setCurrentFont(fntBody);
            txtEmailBody->setPointSize(pointSize);
            txtEmailBody->setText(emails[i].body);
            markRead(emails[i].id);
        }
    }
}


/**
 * Gets the latest emails from the Email accessor, and then redisplays the
 * email list.
 */
void TabPanelEmail::getEmail(){
    const char *routine = "TabPanelEmail::getEmail";
    L_INFO(LOG_TABEMAIL,"Getting emails.");
   
    // If we're not supposed to update, reset the flag and return.
    if (flagUpdateDisabled) {
        flagUpdateDisabled = false;
        return;
    }

    QListViewItem *new_email = 0;
    string last_id = "0";
    int k;

    // Get the message ID of the latest message currently shown
    if (lstEmail->childCount() > 0) {
        last_id = lstEmail->firstChild()->text(4).ascii();
    }

    // Get the latest emails from the email module
    emails = E->getEmails();
    
    // Iterate over the new list of emails
    // TODO: reimplement this when converted to using a map.
    // TODO: use iterators and find
    for (unsigned int i = 0; i < emails.size(); i++) {
        // Examine the emails from the oldest to the newest
        // Get the ID of the ith email
        k = atoi(emails[i].id.c_str());
        
        // If the email is already shown, just check it's read status
        if (k <= atoi(last_id.c_str())) {
            // find this email in the existing list
            QListViewItem *x = lstEmail->findItem(emails[i].id.c_str(),4);

            // check we found an email, and if not, carry on and ignore it
            if ( !x ) continue;
            
            // Set the new flag appropriately
            if ( emails[i].flag )
                x->setPixmap(0,*pixEmailNew);
            else
                x->setPixmap(0,*pixEmailOld);
            continue;
        }
        // Otherwise it's a new email, so add it to the top of the list
        else {
            // if it's a new email, add it to the start of the list
            new_email = new QListViewItem(lstEmail, 
                                "",
                                emails[i].from.c_str(),
                                emails[i].subject.c_str(),
                                emails[i].received.c_str(),
                                emails[i].id.c_str());
            
            // Set the new flag appropriately
            if ( emails[i].flag )
                new_email->setPixmap(0, *pixEmailNew);
            else
                new_email->setPixmap(0, *pixEmailOld);
            
            // If we've now listed over 20 emails, delete the last one
            if (lstEmail->childCount() > 20 && lstEmail->lastItem()) {
                delete lstEmail->lastItem();
            }
        }
    }
}


/**
 * Marks an email with the given message ID as read
 */
void TabPanelEmail::markRead(string id) {
    flagUpdateDisabled = TRUE;
    E->markRead(id);
}


/**
 * This handles drawing the contents of the form, and connecting slots, 
 * but has little actual implementation
 */
void TabPanelEmail::draw() {
    const char* routine = "TabEmail::draw()";

    // this deletes the objects if they already exist so to avoid a leak
    if (lstEmail || txtEmailBody) {
        L_WARNING(LOG_TABEMAIL,"Implicit clear() called");
        clear();
    }

    // Load icons and create icon set
    QString path = DPSDIR;
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
    lstEmail->setColumnWidth(4, 0); // Message ID
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


/**
 * Clean up any objects we created during draw().
 */
void TabPanelEmail::clear() {
    delete txtEmailBody;
    delete lstEmail;
    delete icsEmailIcons;
    delete pixEmailOld;
    delete pixEmailNew;
}
