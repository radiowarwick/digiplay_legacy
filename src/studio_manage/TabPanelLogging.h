#ifndef CLASS_TAB_PANEL_LOGGING
#define CLASS_TAB_PANEL_LOGGING

#include <qlistview.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qpushbutton.h>

#include "TabPanel.h"
#include "config.h"

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

class QTabWidget;
class Auth;

class TabPanelLogging : public TabPanel {
	Q_OBJECT
	public:
		TabPanelLogging(QTabWidget *parent, string text) : TabPanel(parent,text) {
			cout << "Running TabPanelLogging constructor" << endl;
			init();
		}
		~TabPanelLogging();
		void configure(Auth *authModule);
		int md5(string hash);

	public slots:
		virtual void buttonPressed();		
	
	private:
		void init();
		void draw();
		void clear();
		int reclibID(string id);
		int logRecord(string artist, string title);
		void getRecentlyLogged();
		
		Connection *C;
		int location, userid;
		QListView *lstRecentlyLogged;
		QLineEdit *txtArtist, *txtTitle, *txtReclibID;
		QLabel *lblArtist, *lblTitle, *lblReclibID, *lblRecentlyLogged;
		QPushButton *btnLog;
};

#endif
