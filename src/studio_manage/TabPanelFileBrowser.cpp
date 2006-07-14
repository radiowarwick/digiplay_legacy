#include <qtabwidget.h>
#include <qheader.h>
#include <qapplication.h>
#include <qobject.h>

#include "Auth.h"
#include "Logger.h"
#include "dps.h"

#include "TabPanelFileBrowser.h"

// Use init to make the constructor a bit less cumbersome in the header file
void TabPanelFileBrowser::init() {
	config *conf = new config("digiplay");
	C = new Connection(conf->getDBConnectString());
	delete conf;
}

// clean up stuff
TabPanelFileBrowser::~TabPanelFileBrowser() {
	if (C && C->is_open()) {
		C->Deactivate();
	}
	delete C;
}

// this is called whenever the application reconfigures itself,
// usually due to a change in authentication status (login, logoff)
void TabPanelFileBrowser::configure(Auth *authModule) {
	hide();
	if (authModule->isPermitted("TabInfo")) {
		draw();
		show();
	}
}

// This handles drawing the contents of the form, and connecting slots,
// but has little actual implementation
void TabPanelFileBrowser::draw() {
	char* routine = "TabFileBrowser::draw()";

/*	// this deletes the objects if they already exist so to avoid a leak
	if (lstEmail || txtEmailBody) {
		Logger::log(WARNING,routine,"Implicit clear() called",3);
		clear();
	}
*/
	// do all form drawing here, create widgets, set properties

    lstFileBrowser = new QListView( getPanel(), "lstFileBrowser" );
    lstFileBrowser->addColumn( tr( "Folder" ) );
    lstFileBrowser->addColumn( tr( "id" ) );
    lstFileBrowser->setGeometry( QRect( 10, 10, 491, 620 ) );
    lstFileBrowser->header()->setLabel( 0, tr( "Item" ) );
    lstFileBrowser->header()->setLabel( 1, tr( "id" ) );
    lstFileBrowser->clear();
    QListViewItem * item_2 = new QListViewItem( lstFileBrowser, 0 );
    item_2->setOpen( TRUE );
    QListViewItem * item_3 = new QListViewItem( item_2, 0 );
    item_3->setOpen( TRUE );
    QListViewItem * item = new QListViewItem( item_3, 0 );
    item->setText( 0, tr( "File3" ) );
    item->setText( 1, tr( "25" ) );
    item_3->setOpen( TRUE );
    item = new QListViewItem( item_3, item );
    item->setText( 0, tr( "File2" ) );
    item->setText( 1, tr( "76" ) );
    item_3->setOpen( TRUE );
    item = new QListViewItem( item_3, item );
    item->setText( 0, tr( "File32" ) );
    item->setText( 1, tr( "234" ) );
    item_3->setText( 0, tr( "Folder 1" ) );
    item_2->setOpen( TRUE );
    QListViewItem * item_4 = new QListViewItem( item_2, item_3 );
    item_4->setOpen( TRUE );
    item = new QListViewItem( item_4, item_3 );
    item->setText( 0, tr( "File5" ) );
    item->setText( 1, tr( "3" ) );
    item_4->setText( 0, tr( "Folder2" ) );
    item_2->setText( 0, tr( "Users" ) );

    item = new QListViewItem( lstFileBrowser, item_2 );
    item->setText( 0, tr( "Departments" ) );


}

void TabPanelFileBrowser::clear() {
	delete lstFileBrowser;
	delete item;
	delete item_2;
	delete item_3;
	delete item_4;

}
