/****************************************************************************
** Form implementation generated from reading ui file 'dlgWarn.ui'
**
** Created: Sat Nov 6 09:42:49 2010
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QLayout>
#include <QtGui/QToolTip>
#include <QtGui/QWhatsThis>
#include <QtGui/QImage>
#include <QtGui/QPixmap>

#include "dlgWarn.h"

/*
 *  Constructs a dlgWarn as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
dlgWarn::dlgWarn( QWidget* parent, Qt::WindowFlags fl )
    : QDialog( parent, fl )
{
    setStyleSheet("QDialog { background-color: rgb(255,255,255) }");
    setSizeGripEnabled( FALSE );
    setModal( TRUE );

    QWidget* privateLayoutWidget = new QWidget( this );
    privateLayoutWidget->setGeometry( QRect( 10, 150, 250, 33 ) );
    Layout1 = new QHBoxLayout( privateLayoutWidget );
    Horizontal_Spacing2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( Horizontal_Spacing2 );

    buttonOk = new QPushButton( privateLayoutWidget );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    buttonCancel = new QPushButton( privateLayoutWidget );
    buttonCancel->setAutoDefault( TRUE );
    Layout1->addWidget( buttonCancel );

    pixWarning = new QLabel( this );
    pixWarning->setGeometry( QRect( 240, 40, 48, 48 ) );
    pixWarning->setScaledContents( TRUE );

    lblTitle = new QLabel( this );
    lblTitle->setGeometry( QRect( 10, 40, 220, 43 ) );
    lblTitle->setStyleSheet("background-color: rgb(1,73,88); color: rgb(255,255,255);");
    QFont lblTitle_font(  lblTitle->font() );
    lblTitle_font.setFamily( "Sans Serif" );
    lblTitle_font.setPointSize( 36 );
    lblTitle_font.setBold( TRUE );
    lblTitle->setFont( lblTitle_font );
    lblTitle->setAlignment( Qt::AlignVCenter | Qt::AlignLeft );

    lblWarn = new QLabel( this );
    lblWarn->setGeometry( QRect( 10, 100, 280, 40 ) );
    lblWarn->setAlignment( Qt::AlignVCenter );

    pixLogout = new QLabel( this );
    pixLogout->setGeometry( QRect( 0, 0, 300, 29 ) );
    pixLogout->setScaledContents( TRUE );

    languageChange();
    resize( QSize(300, 194).expandedTo(minimumSizeHint()) );
    ensurePolished();

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );

    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
dlgWarn::~dlgWarn()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void dlgWarn::languageChange()
{
    setWindowTitle( tr( "Warning" ) );
    buttonOk->setText( tr( "&Yes" ) );
    buttonOk->setShortcut( QKeySequence( tr( "Alt+Y" ) ) );
    buttonCancel->setText( tr( "&No" ) );
    buttonCancel->setShortcut( QKeySequence( tr( "Alt+N" ) ) );
    lblTitle->setText( tr( "Title" ) );
    lblWarn->setText( tr( "Are you sure you would like to......." ) );
}

void dlgWarn::init() {
    QString path = DPSDIR;
    pixWarning->setPixmap(QPixmap(path + "/images/warning48.png"));
    pixLogout->setPixmap(QPixmap(path + "/images/loginlogo.png"));
}

void dlgWarn::setWarning(QString msg) {
    lblWarn->setText(msg);
}

void dlgWarn::setTitle(QString msg) {
    setWindowTitle(msg);
    lblTitle->setText(msg);
}

void dlgWarn::setQuestion(bool ques) {
    if( !ques ) {
    buttonCancel->hide();
    buttonOk->setText("OK");
    }
}

