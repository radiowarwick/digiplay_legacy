#include <qtabwidget.h>
#include <qheader.h>
#include <qapplication.h>
#include <qobject.h>

#include "Auth.h"
#include "Logger.h"
#include "dps.h"

#include "TabPanelCart.h"

TabPanelCart::TabPanelCart(QTabWidget *parent, string text)
		: TabPanel(parent,text) {
	config *conf = new config("digiplay");
	C = new Connection(conf->getDBConnectString());
	delete conf;
}

// clean up stuff
TabPanelCart::~TabPanelCart() {
	if (C && C->is_open()) {
		C->Deactivate();
	}
	delete C;
}

// this is called whenever the application reconfigures itself,
// usually due to a change in authentication status (login, logoff)
void TabPanelCart::configure(Auth *authModule) {
	hide();
	if (authModule->isPermitted("TabInfo")) {
		draw();
		show();
	}
}

// This handles drawing the contents of the form, and connecting slots,
// but has little actual implementation
void TabPanelCart::draw() {
	char* routine = "TabCartl::draw()";

/*	// this deletes the objects if they already exist so to avoid a leak
	if (lstEmail || txtEmailBody) {
		Logger::log(WARNING,routine,"Implicit clear() called",3);
		clear();
	}
*/
	// do all form drawing here, create widgets, set properties

    lstCarts = new QListView( getPanel(), "lstCarts" );
    lstCarts->addColumn( tr( "Audiowall" ) );
    lstCarts->addColumn( tr( "id" ) );
    lstCarts->setGeometry( QRect( 10, 10, 491, 620 ) );
    lstCarts->header()->setLabel( 0, tr( "Cartwall" ) );
    lstCarts->header()->setLabel( 1, tr( "id" ) );
    lstCarts->clear();
    QListViewItem * item_2 = new QListViewItem( lstCarts, 0 );
    item_2->setOpen( TRUE );
    QListViewItem * item_3 = new QListViewItem( item_2, 0 );
    item_3->setOpen( TRUE );
    QListViewItem * item = new QListViewItem( item_3, 0 );
    item->setText( 0, tr( "GOAL!!" ) );
    item->setText( 1, tr( "25" ) );
    item_3->setOpen( TRUE );
    item = new QListViewItem( item_3, item );
    item->setText( 0, tr( "News bed 2" ) );
    item->setText( 1, tr( "25" ) );
    item_3->setOpen( TRUE );
    item = new QListViewItem( item_3, item );
    item->setText( 0, tr( "News bed 1" ) );
    item->setText( 1, tr( "25" ) );
    item_3->setText( 0, tr( "Sport" ) );
    item_3->setText( 1, tr( "25" ) );
    item_2->setOpen( TRUE );
    QListViewItem * item_4 = new QListViewItem( item_2, item_3 );
    item_4->setOpen( TRUE );
    item = new QListViewItem( item_4, item_3 );
    item->setText( 0, tr( "News Bed 1" ) );
    item->setText( 1, tr( "36" ) );
    item_4->setText( 0, tr( "News" ) );
    item_4->setText( 1, tr( "36" ) );
    item_2->setText( 0, tr( "User Audiowalls" ) );

    item = new QListViewItem( lstCarts, item_2 );
    item->setText( 0, tr( "Station Audiowalls" ) );


}

void TabPanelCart::clear() {
	delete lstCarts;
	delete item;
	delete item_2;
	delete item_3;
	delete item_4;

}
