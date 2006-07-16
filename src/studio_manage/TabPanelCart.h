#ifndef CLASS_TAB_PANEL_CART
#define CLASS_TAB_PANEL_CART

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

class TabPanelCart : public TabPanel {
	Q_OBJECT
	public:
		TabPanelCart(QTabWidget *parent, string text);
		~TabPanelCart();
		void configure(Auth *authModule);

	private:
		void draw();
		void clear();
		
		Connection *C;
		QListView *lstCarts;
		QListViewItem *item, *item_2, *item_3, *item_4;
};

#endif
