#ifndef CLASS_TAB_PANEL_SEARCH
#define CLASS_TAB_PANEL_SEARCH

#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qtable.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtooltip.h>

#include "frmStudioManage.h"

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
		TabPanelSearch(QTabWidget *parent, frmStudioManage *parent2, string text) : TabPanel(parent,text)  {
			parentForm = parent2;
			cout << "Running TabPanelSearch constructor" << endl;
			init();
		}
		~TabPanelSearch();
		void configure(Auth *authModule);

	public slots:
		virtual void Library_Search();
		virtual void playlistAdd(int, int, int, const QPoint&);
	
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
		frmStudioManage *parentForm;
		QCheckBox *ArtistCheckBox;
		QCheckBox *AlbumCheckBox;
		QCheckBox *TitleCheckBox;
};

#endif
