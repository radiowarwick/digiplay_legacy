#ifndef CLASS_TAB_PANEL_EMAIL
#define CLASS_TAB_PANEL_EMAIL

#include "TabPanel.h"
#include "triggerThread.h"
#include "config.h"

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

class QTabWidget;
class QTextBrowser;
class QListView;
class QListViewItem;
class QIconSet;
class Auth;

class TabPanelEmail : public TabPanel {
	Q_OBJECT
	public:
		TabPanelEmail(QTabWidget *parent, string text) 
			: TabPanel(parent,text) {txtEmailBody = NULL;}
		~TabPanelEmail();
		void configure(Auth *authModule);
		void customEvent(QCustomEvent *event);

	public slots:
		virtual void getEmailBody(QListViewItem *current);		
	
	private:
		void markRead(string id);
		void draw();
		void clear();
		void getEmail();
		
		config *conf;
		Connection *C;
		triggerThread *emailTrigger;
		QListView *lstEmail;
		QTextBrowser *txtEmailBody;
		QPixmap *email_new, *email_old;
		QIconSet *email_Icons;
};

#endif
