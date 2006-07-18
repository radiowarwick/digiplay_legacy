#ifndef CLASS_FILE_BROWSER
#define CLASS_FILE_BROWSER

#include <qlistview.h>
#include <qwidget.h>

#include "FileBrowserItem.h"
#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

class FileBrowser : public QListView {
	public:
		FileBrowser( QWidget *parent, const char *name, int types_in=0 );
		void getFiles(void);
		static const int Audio = 1;
		static const int Folder = 2;
		static const int Script = 4;
		static const int Cartwall = 8;
		static const int Root = 16;

	protected:

	private:
		void init();
		void addChildren(FileBrowserItem *parent, int id);
		Connection *C;
		int types;
};

#endif
