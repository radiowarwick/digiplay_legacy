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

    lstCarts = new FileBrowser( getPanel(), "lstCarts", FileBrowser::Cartwall );
    lstCarts->addColumn( tr( "Item" ) );
    lstCarts->setGeometry( QRect( 10, 10, 491, 620 ) );
    lstCarts->header()->setLabel( 0, tr( "Item" ) );
    lstCarts->getFiles();

}

void TabPanelCart::clear() {
	delete lstCarts;
}
