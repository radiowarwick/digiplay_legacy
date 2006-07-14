#ifndef CLASS_TAB_PANEL_FILEBROWSER
#define CLASS_TAB_PANEL_FILEBROWSER

#include "TabPanel.h"
#include "triggerThread.h"
#include "config.h"

#include <qlistview.h>


#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

class QTabWidget;
class Auth;

class TabPanelFileBrowser : public TabPanel {
	Q_OBJECT
	public:
		TabPanelFileBrowser(QTabWidget *parent, string text) : TabPanel(parent,text) {
			cout << "Running TabPanelFileBrowser constructor" << endl;
			init();
		}
		~TabPanelFileBrowser();
		void configure(Auth *authModule);

	private:
		void init();
		void draw();
		void clear();
		
		Connection *C;
		QListView *lstFileBrowser;
		QListViewItem *item, *item_2, *item_3, *item_4;
};

#endif
