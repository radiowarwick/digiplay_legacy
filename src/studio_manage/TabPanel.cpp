#include <qwidget.h>
#include <qtabwidget.h>

#include "Auth.h"
#include "Logger.h"

#include "TabPanel.h"

TabPanel::TabPanel(QTabWidget *parent, string text) {
	tabParent = parent;
	tabText = text;
	panel = new QWidget(0,"tabPanel");
}

TabPanel::~TabPanel() {
	delete panel;
}

void TabPanel::configure(Auth *authModule) {
	char* routine = "TabPanel::configure";
	if (!authModule) {
		Logger::log(WARNING,routine,"authModule isn't defined",2);
	}
	else {
		show();
	}
}

void TabPanel::show() {
	int p = tabParent->indexOf(panel);
	if (p == -1) {
		panel->reparent(tabParent,QPoint(0,0),false);
		tabParent->insertTab(panel,tabText);
	}
}

void TabPanel::hide() {
	int p = tabParent->indexOf(panel);
	if (p != -1) {
		tabParent->removePage(panel);
		panel->reparent(0,QPoint(0,0),false);
	}
}
