#include <qtabwidget.h>
#include <qheader.h>
#include <qapplication.h>
#include <qobject.h>
#include <string.h>

#include "Auth.h"
#include "Logger.h"
#include "dps.h"

#include "TabPanelFileBrowser.h"

TabPanelFileBrowser::TabPanelFileBrowser(QTabWidget *parent, string text)
		: TabPanel(parent, text) {
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

    lstFileBrowser = new FileBrowser( getPanel(), "lstFileBrowser", 255 );
    lstFileBrowser->addColumn( tr( "Folder" ) );
    lstFileBrowser->setGeometry( QRect( 10, 10, 491, 620 ) );
    lstFileBrowser->header()->setLabel( 0, tr( "Item" ) );
	lstFileBrowser->header()->setMovingEnabled( FALSE );
    lstFileBrowser->getFiles();
}

void TabPanelFileBrowser::clear() {
	delete lstFileBrowser;
}
