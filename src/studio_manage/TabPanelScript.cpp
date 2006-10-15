#include <qtabwidget.h>
#include <qtextbrowser.h>
#include <qlistview.h>
#include <qstring.h>
#include <qpixmap.h>
#include <qiconset.h>
#include <qheader.h>
#include <qapplication.h>
#include <qobject.h>

#include "Auth.h"
#include "Logger.h"
#include "dps.h"

#include "TabPanelScript.h"

TabPanelScript::TabPanelScript(QTabWidget *parent, string text)
		: TabPanel(parent,text) {
	config *conf = new config("digiplay");
	C = new Connection(conf->getDBConnectString());
	delete conf;
}

// clean up stuff
TabPanelScript::~TabPanelScript() {
	if (C && C->is_open()) {
		C->Deactivate();
	}
	delete C;
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
	char* routine = "TabScript::draw()";

/*	// this deletes the objects if they already exist so to avoid a leak
	if (lstEmail || txtEmailBody) {
		Logger::log(WARNING,routine,"Implicit clear() called",3);
		clear();
	}
*/
	// do all form drawing here, create widgets, set properties

    lblScriptName = new QLabel( getPanel(), "lblScriptName" );
    lblScriptName->setGeometry( QRect( 10, 11, 151, 16 ) );
    QFont lblScriptName_font(  lblScriptName->font() );
    lblScriptName_font.setPointSize( 12 );
    lblScriptName_font.setBold( FALSE );
    lblScriptName->setFont( lblScriptName_font );
    lblScriptName->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignLeft ) );

    txtScriptBody = new QTextEdit( getPanel(), "txtScriptBody" );
    txtScriptBody->setGeometry( QRect( 9, 68, 490, 560 ) );

    lblScriptDuration = new QLabel( getPanel(), "lblScriptDuration" );
    lblScriptDuration->setGeometry( QRect( 240, 11, 60, 16 ) );
    QFont lblScriptDuration_font(  lblScriptDuration->font() );
    lblScriptDuration_font.setPointSize( 12 );
    lblScriptDuration_font.setBold( FALSE );
    lblScriptDuration->setFont( lblScriptDuration_font );
    lblScriptDuration->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignLeft ) );

    btnScriptSave = new QPushButton( getPanel(), "btnScriptSave" );
    btnScriptSave->setGeometry( QRect( 330, 26, 171, 30 ) );
    QFont btnScriptSave_font(  btnScriptSave->font() );
    btnScriptSave_font.setPointSize( 12 );
    btnScriptSave_font.setBold( FALSE );
    btnScriptSave->setFont( btnScriptSave_font );

    txtScriptName = new QLineEdit( getPanel(), "txtScriptName" );
    txtScriptName->setGeometry( QRect( 10, 30, 220, 21 ) );

    txtScriptDuration = new QLineEdit( getPanel(), "txtScriptDuration" );
    txtScriptDuration->setGeometry( QRect( 238, 30, 70, 21 ) );

    lblScriptName->setText( tr( "Item Name:" ) );
    lblScriptDuration->setText( tr( "Duration:" ) );
    btnScriptSave->setText( tr( "Save Changes" ) );


}

void TabPanelScript::clear() {
	delete lblScriptName;
	delete lblScriptDuration;
	delete txtScriptName;
	delete txtScriptDuration;
	delete txtScriptBody;
	delete btnScriptSave;
}
