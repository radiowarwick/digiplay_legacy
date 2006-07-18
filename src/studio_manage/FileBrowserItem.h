#ifndef CLASS_FILE_BROWSER_ITEM
#define CLASS_FILE_BROWSER_ITEM

#include <qlistview.h>

class FileBrowserItem : public QListViewItem {
	public:
		FileBrowserItem( QListView *parent, QListViewItem *after );
		FileBrowserItem( );
		FileBrowserItem( QListViewItem *parent, QListViewItem *after );
		FileBrowserItem( QListView *parent, 
				QString txtFolderName, int idInput, int type );
		FileBrowserItem( FileBrowserItem *parent, 
				QString txtFolderName, int idInput, int type );

	protected:

	private:
		void init();
		int id;
};

#endif
