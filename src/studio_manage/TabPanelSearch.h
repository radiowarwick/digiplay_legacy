#ifndef CLASS_TAB_PANEL_SEARCH
#define CLASS_TAB_PANEL_SEARCH

#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qtable.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtooltip.h>

#include "TabPanel.h"
#include "config.h"
#include "libsearch.h"
#include "track.h"
#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

class QTabWidget;
class Auth;

class TabPanelSearch : public TabPanel {
	Q_OBJECT
	public:
		TabPanelSearch(QTabWidget *parent, string text) : TabPanel(parent,text)  {
			cout << "Running TabPanelSearch constructor" << endl;
			init();
		}
		~TabPanelSearch();
		void configure(Auth *authModule);

	public slots:
		virtual void Library_Search();
	
	private:
//		TabPanelSearch()
//			: TabPanel(0,"") {cout << "GOAT" << endl;}
		void init();
		void draw();
		void clear();
		
		Connection *C;
		vector<_track*> *SearchResults;
		libsearch *library_engine;
		QPushButton *btnLibrarySearch;
		QTable *tblLibrarySearchResults;
		QLineEdit *txtLibrarySearchText;
		QLabel *Searchlable;
		QLabel *lblSearch;
		QCheckBox *ArtistCheckBox;
		QCheckBox *AlbumCheckBox;
		QCheckBox *TitleCheckBox;
};

#endif
