#include <iostream>
using namespace std;

#include <qstring.h>
#include <qpixmap.h>
#include <qapplication.h>

#include "FileBrowserItem.h"
#include "FileBrowser.h"

FileBrowserItem::FileBrowserItem( QListView *parent, QListViewItem *after )
		: QListViewItem(parent,after) {
	init();
}

FileBrowserItem::FileBrowserItem( ) : QListViewItem(this) {
	init();
}

FileBrowserItem::FileBrowserItem( QListViewItem *parent, QListViewItem *after ) 
		: QListViewItem(parent,after) {
	init();
}

FileBrowserItem::FileBrowserItem( QListView *parent,
		QString txtFolderName, int idInput, int type) 
		: QListViewItem(parent, NULL, txtFolderName) {
	setText(0,txtFolderName);
	QString path = qApp->applicationDirPath();
	if ( type == FileBrowser::Audio ) {
		setPixmap(0, QPixmap(path + "/images/track16.png"));
	} else if ( type == FileBrowser::Folder ) {
		setPixmap(0, QPixmap(path + "/images/folder16.png"));
	} else if ( type == FileBrowser::Script ) {
		setPixmap(0, QPixmap(path + "/images/script16.png"));
	} else if ( type == FileBrowser::Cartwall ) {
		setPixmap(0, QPixmap(path + "/images/jingle16.png"));
	} else if ( type == FileBrowser::Root ) {
		setPixmap(0, QPixmap(path + "/images/rootfolder16.png"));
	}
	id = idInput;
	init();
}

FileBrowserItem::FileBrowserItem( FileBrowserItem *parent,
		QString txtFolderName, int idInput, int type) 
		: QListViewItem(parent, NULL, txtFolderName) {
	setText(0,txtFolderName);
	QString path = qApp->applicationDirPath();
	if ( type == FileBrowser::Audio ) {
		setPixmap(0, QPixmap(path + "/images/track16.png"));
	} else if ( type == FileBrowser::Folder ) {
		setPixmap(0, QPixmap(path + "/images/folder16.png"));
	} else if ( type == FileBrowser::Script ) {
		setPixmap(0, QPixmap(path + "/images/script16.png"));
	} else if ( type == FileBrowser::Cartwall ) {
		setPixmap(0, QPixmap(path + "/images/jingle16.png"));
	} else if ( type == FileBrowser::Root ) {
		setPixmap(0, QPixmap(path + "/images/rootfolder16.png"));
	}
	id = idInput;
	init();
}

void FileBrowserItem::init() {
}

