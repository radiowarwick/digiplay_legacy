/****************************************************************************
** Form implementation generated from reading ui file 'dlgLogin.ui'
**
** Created: Sat Nov 6 09:42:43 2010
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QLayout>
#include <QtGui/QToolTip>
#include <QtGui/QWhatsThis>
#include <QtGui/QImage>
#include <QtGui/QPixmap>

#include "dlgLogin.h"

/*
 *  Constructs a dlgLogin as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
dlgLogin::dlgLogin( QWidget* parent, Qt::WindowFlags fl )
    : QDialog( parent, fl )
{
    setStyleSheet("QDialog { background-color: rgb(255,255,255) }");
    setSizeGripEnabled( FALSE );
    setModal( TRUE );

    lblLoginUsername = new QLabel( this );
    lblLoginUsername->setGeometry( QRect( 20, 90, 70, 21 ) );
    lblLoginUsername->setAlignment( Qt::AlignVCenter | Qt::AlignLeft );

    lblLoginPassword = new QLabel( this );
    lblLoginPassword->setGeometry( QRect( 20, 130, 70, 21 ) );
    lblLoginPassword->setLineWidth( 1 );
    lblLoginPassword->setAlignment( Qt::AlignVCenter | Qt::AlignLeft );

    txtLoginUsername = new QLineEdit( this );
    txtLoginUsername->setGeometry( QRect( 100, 90, 170, 21 ) );

    txtLoginPassword = new QLineEdit( this );
    txtLoginPassword->setGeometry( QRect( 100, 130, 170, 21 ) );
    txtLoginPassword->setTextMargins( 0, 0, 0, 0 );
    txtLoginPassword->setEchoMode( QLineEdit::Password );

    pixLogin = new QLabel( this );
    pixLogin->setGeometry( QRect( 0, 0, 300, 29 ) );
    pixLogin->setScaledContents( TRUE );

    textLabel1 = new QLabel( this );
    textLabel1->setGeometry( QRect( 18, 40, 113, 43 ) );
    textLabel1->setStyleSheet("QLabel {color: rgb(1,73,88);}");
    QFont textLabel1_font(  textLabel1->font() );
    textLabel1_font.setFamily( "Sans Serif" );
    textLabel1_font.setPointSize( 36 );
    textLabel1_font.setBold( TRUE );
    textLabel1->setFont( textLabel1_font );
    textLabel1->setAlignment( Qt::AlignCenter );

    // Dialog buttons
    QWidget* privateLayoutWidget = new QWidget( this );
    privateLayoutWidget->setGeometry( QRect( 20, 170, 250, 33 ) );

    Horizontal_Spacing2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );

    buttonOk = new QPushButton( privateLayoutWidget );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );

    buttonCancel = new QPushButton( privateLayoutWidget );
    buttonCancel->setAutoDefault( TRUE );

    Layout1 = new QHBoxLayout( privateLayoutWidget );
    Layout1->addItem( Horizontal_Spacing2 );
    Layout1->addWidget( buttonOk );
    Layout1->addWidget( buttonCancel );

    languageChange();
    resize( QSize(300, 212).expandedTo(minimumSizeHint()) );
    ensurePolished();

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
void dlgLogin::languageChange()
{
    setWindowTitle( tr( "RaW // Digiplay // Login" ) );
    lblLoginUsername->setText( tr( "Username:" ) );
    lblLoginPassword->setText( tr( "Password:" ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setShortcut( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setShortcut( QKeySequence( QString::null ) );
    textLabel1->setText( tr( "Login" ) );
}

void dlgLogin::init() {
    QString path = DPSDIR;
    pixLogin->setPixmap(QPixmap(path + "/images/loginlogo.png"));
    txtLoginUsername->setFocus();
    txtLoginUsername->setFocus();
}

QString dlgLogin::getUsername() {
    return txtLoginUsername->text();
}

QString dlgLogin::getPassword() {
    return txtLoginPassword->text();
}
