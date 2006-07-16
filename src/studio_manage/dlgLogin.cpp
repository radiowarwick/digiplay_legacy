/****************************************************************************
** Form implementation generated from reading ui file 'dlgLogin.ui'
**
** Created: Fri Jul 14 09:38:04 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.5   edited Aug 31 12:13 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "dlgLogin.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

/*
 *  Constructs a dlgLogin as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
dlgLogin::dlgLogin( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "dlgLogin" );
    setSizeGripEnabled( TRUE );

    textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setGeometry( QRect( 40, 10, 431, 61 ) );
    QFont textLabel1_font(  textLabel1->font() );
    textLabel1_font.setFamily( "Sans Serif" );
    textLabel1_font.setPointSize( 36 );
    textLabel1->setFont( textLabel1_font ); 
    textLabel1->setAlignment( int( QLabel::AlignCenter ) );

    QWidget* privateLayoutWidget = new QWidget( this, "Layout1" );
    privateLayoutWidget->setGeometry( QRect( 20, 190, 476, 33 ) );
    Layout1 = new QHBoxLayout( privateLayoutWidget, 0, 6, "Layout1"); 
    Horizontal_Spacing2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( Horizontal_Spacing2 );

    buttonOk = new QPushButton( privateLayoutWidget, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    buttonCancel = new QPushButton( privateLayoutWidget, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    Layout1->addWidget( buttonCancel );

    lblLoginUsername = new QLabel( this, "lblLoginUsername" );
    lblLoginUsername->setGeometry( QRect( 20, 100, 70, 21 ) );
    lblLoginUsername->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignLeft ) );

    lblLoginPassword = new QLabel( this, "lblLoginPassword" );
    lblLoginPassword->setGeometry( QRect( 20, 140, 70, 21 ) );
    lblLoginPassword->setLineWidth( 1 );
    lblLoginPassword->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignLeft ) );

    txtLoginPassword = new QLineEdit( this, "txtLoginPassword" );
    txtLoginPassword->setGeometry( QRect( 100, 140, 391, 21 ) );
    txtLoginPassword->setMargin( 0 );
    txtLoginPassword->setEchoMode( QLineEdit::Password );

    txtLoginUsername = new QLineEdit( this, "txtLoginUsername" );
    txtLoginUsername->setGeometry( QRect( 100, 100, 390, 21 ) );
    languageChange();
    resize( QSize(517, 238).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
dlgLogin::~dlgLogin()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */

void dlgLogin::init() {
}

QString dlgLogin::getUsername() {
    return txtLoginUsername->text();
}

QString dlgLogin::getPassword() {
    return txtLoginPassword->text();
}

void dlgLogin::languageChange()
{
    setCaption( tr( "RaW // Digiplay // Login" ) );
    textLabel1->setText( tr( "Digiplay Login" ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
    lblLoginUsername->setText( tr( "Username:" ) );
    lblLoginPassword->setText( tr( "Password:" ) );
}

