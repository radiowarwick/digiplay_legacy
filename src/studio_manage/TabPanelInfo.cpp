#include <qtabwidget.h>
#include <qtextbrowser.h>

#include "Auth.h"
#include "Logger.h"

#include "TabPanelInfo.h"

TabPanelInfo::~TabPanelInfo() {

}

void TabPanelInfo::configure(Auth *authModule) {
	hide();
	if (authModule->isPermitted("TabInfo")) {
		draw();
		show();
	}
}

void TabPanelInfo::draw() {
	char* routine = "TabInfo::draw()";
	
	if (txtInfoPanel) {
		Logger::log(WARNING,routine,"Implicit clear() called",3);
		clear();
	}
	
	txtInfoPanel = new QTextBrowser(getPanel(), "txtInfoPanel");
	txtInfoPanel->setGeometry( QRect( 10, 10, 500, 610 ) );
	txtInfoPanel->setVScrollBarMode( QTextBrowser::AlwaysOn );
	txtInfoPanel->setHScrollBarMode( QTextBrowser::AlwaysOff );
	txtInfoPanel->setTextFormat( QTextBrowser::RichText );
}

void TabPanelInfo::clear() {
	delete txtInfoPanel;
}
