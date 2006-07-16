#ifndef CLASS_TAB_PANEL_INFO
#define CLASS_TAB_PANEL_INFO

#include "TabPanel.h"

class QTabWidget;
class QTextBrowser;
class Auth;

class TabPanelInfo : public TabPanel {
	public:
		TabPanelInfo(QTabWidget *parent, string text); 
		~TabPanelInfo();
		void configure(Auth *authModule);

	private:
		void draw();
		void clear();

		QTextBrowser *txtInfoPanel;
};

#endif
