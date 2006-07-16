#ifndef CLASS_TAB_PANEL_PLAYLIST
#define CLASS_TAB_PANEL_PLAYLIST

#include <qpixmap.h>
#include <qstring.h>
#include <qlistview.h>

#include "TabPanel.h"
#include "triggerThread.h"
#include "config.h"

#include "frmStudioManage.h"

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

class QTabWidget;
class Auth;

class TabPanelPlaylist : public TabPanel {
	Q_OBJECT
	public:
		TabPanelPlaylist(QTabWidget *parent, frmStudioManage *parent2, string text);
		~TabPanelPlaylist();
		void configure(Auth *authModule);
		void customEvent(QCustomEvent *event);

	public slots:
		virtual void playlistAdd(QListViewItem *current);

	private:
		void draw();
		void clear();
		void getPlaylist();		
		QString getTime( long smpl );
		frmStudioManage *parentForm;
		Connection *C;
		triggerThread *playlistTrigger;
		QListView *lstPlaylist;
		QPixmap *pixAList, *pixBList;
};

#endif
