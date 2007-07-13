/*
 * Scripts GUI Module
 * TabPanelScript.cpp
 * Provides facility for managing scripts.
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
#include <qheader.h>
#include <qapplication.h>
#include <qobject.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qpushbutton.h>

#include "Auth.h"
#include "Logger.h"
#include "DataAccess.h"
#include "dps.h"

#include "TabPanelScript.h"

TabPanelScript::TabPanelScript(QTabWidget *parent, string text)
            : TabPanel(parent,text) {
    DB = new DataAccess();
}

// clean up stuff
TabPanelScript::~TabPanelScript() {
    delete DB;
}

// this is called whenever the application reconfigures itself,
// usually due to a change in authentication status (login, logoff)
void TabPanelScript::configure(Auth *authModule) {
	hide();
	if (authModule->isPermitted("TabScript")) {
		draw();
		show();
	}
}

// This handles drawing the contents of the form, and connecting slots,
// but has little actual implementation
void TabPanelScript::draw() {
	// do all form drawing here, create widgets, set properties
    lblScriptName = new QLabel( getPanel(), "lblScriptName" );
    lblScriptName->setGeometry( QRect( 10, 11, 151, 16 ) );
    QFont lblScriptName_font(  lblScriptName->font() );
    lblScriptName_font.setPointSize( 12 );
    lblScriptName_font.setBold( FALSE );
    lblScriptName->setFont( lblScriptName_font );
    lblScriptName->setAlignment( int( QLabel::AlignVCenter 
                                            | QLabel::AlignLeft ) );

    txtScriptBody = new QTextEdit( getPanel(), "txtScriptBody" );
    txtScriptBody->setGeometry( QRect( 9, 68, 490, 560 ) );
	txtScriptBody->setReadOnly(true);

    lblScriptDuration = new QLabel( getPanel(), "lblScriptDuration" );
    lblScriptDuration->setGeometry( QRect( 240, 11, 60, 16 ) );
    QFont lblScriptDuration_font(  lblScriptDuration->font() );
    lblScriptDuration_font.setPointSize( 12 );
    lblScriptDuration_font.setBold( FALSE );
    lblScriptDuration->setFont( lblScriptDuration_font );
    lblScriptDuration->setAlignment( int( QLabel::AlignVCenter 
                                            | QLabel::AlignLeft ) );

    btnScriptDone = new QPushButton( getPanel(), "btnScriptDone" );
    btnScriptDone->setGeometry( QRect( 330, 26, 171, 30 ) );
    QFont btnScriptDone_font(  btnScriptDone->font() );
    btnScriptDone_font.setPointSize( 12 );
    btnScriptDone_font.setBold( FALSE );
    btnScriptDone->setFont( btnScriptDone_font );

    txtScriptName = new QLineEdit( getPanel(), "txtScriptName" );
    txtScriptName->setGeometry( QRect( 10, 30, 220, 21 ) );
	txtScriptName->setReadOnly(true);

    txtScriptDuration = new QLineEdit( getPanel(), "txtScriptDuration" );
    txtScriptDuration->setGeometry( QRect( 238, 30, 70, 21 ) );
	txtScriptDuration->setReadOnly(true);

    lblScriptName->setText( tr( "Item Name:" ) );
    lblScriptDuration->setText( tr( "Duration:" ) );
    btnScriptDone->setText( tr( "Finished" ) );
	connect( btnScriptDone, SIGNAL( clicked() ), 
	         this, SLOT( btnScriptDoneClicked() ) );
}

void TabPanelScript::loadScript( int id ) {
	//gets the id of a script when clicked on in the 
	//showplan and shoul then load it.
	string SQL = "SELECT name, contents, length FROM scripts " 
				 "WHERE id=" + dps_itoa(id) +" LIMIT 1;";
	PqxxResult R;
	try {
		R = DB->exec("ScriptLoad", SQL);
	}
	catch(...) {
		//Fuck up put an error here!
	}
    DB->abort("ScriptLoad");
	if ( R.size() != 0 ) {
		txtScriptBody->setText( R[0]["contents"].c_str() );
		txtScriptName->setText( R[0]["name"].c_str() );
		txtScriptDuration->setText( R[0]["length"].c_str() );
		btnScriptDone->setEnabled( true );
	}
	else {
		//toss wank.  Something fucked up good.
	}
}

void TabPanelScript::clearScript() {
        txtScriptBody->setText( "" );
		txtScriptName->setText( "" );
		txtScriptDuration->setText( "" );
		btnScriptDone->setEnabled( false );

}

void TabPanelScript::btnScriptDoneClicked() {
	emit scriptDone();
}

void TabPanelScript::clear() {
	delete lblScriptName;
	delete lblScriptDuration;
	delete txtScriptName;
	delete txtScriptDuration;
	delete txtScriptBody;
	delete btnScriptDone;
}
