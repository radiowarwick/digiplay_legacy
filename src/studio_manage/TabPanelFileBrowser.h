#ifndef CLASS_TAB_PANEL_FILEBROWSER
#define CLASS_TAB_PANEL_FILEBROWSER

#include "TabPanel.h"
#include "triggerThread.h"
#include "config.h"
#include "FileBrowserItem.h"
#include "FileBrowser.h"

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
		TabPanelFileBrowser(QTabWidget *parent, string text);
		~TabPanelFileBrowser();
		void configure(Auth *authModule);

	private:
		void draw();
		void clear();
		void getFiles();
		void addChildren(FileBrowserItem *parent, int id);

		Connection *C;
		FileBrowser *lstFileBrowser;
};

#endif
