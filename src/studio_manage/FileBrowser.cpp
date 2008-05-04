/*
 * Filebrowser Widget
 * FileBrowser.cpp
 * Provides a graphical interface to the virtual file system
 *
 * Copyright (c) 2006 Chris Cantwell
 * Copyright (c) 2006 Ian Liverton
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <iostream>
using std::endl;

#include "FileBrowser.h"
#include "Logger.h"
#include "dps.h"

#include <qdir.h>
#include <qpixmap.h>
#include <qevent.h>
#include <qpoint.h>
#include <qmessagebox.h>
#include <qdragobject.h>
#include <qapplication.h>
#include <qheader.h>

/* =======================================================================
 * Directory
 * =======================================================================
 */
QPixmap *folderLocked = 0;
QPixmap *folderClosed = 0;
QPixmap *folderOpen = 0;
QPixmap *folderTopOpen = 0;
QPixmap *folderTopClosed = 0;
QPixmap *folderHome = 0;
QPixmap *fileNormal = 0;
QPixmap *fileAudio = 0;
QPixmap *fileJingle = 0;
QPixmap *fileAdvert = 0;
QPixmap *fileScript = 0;
QPixmap *fileAwSet = 0;
QPixmap *fileShowplan = 0;

Directory::Directory( Directory * parent, const int my_id, 
                        const QString& filename, DataAccess *topDB )
    : QListViewItem( parent ), f(filename),
      showDirsOnly( parent->showDirsOnly ),
      pix( 0 ) {

    p = parent;
    DB = topDB;
    id = my_id;
    readable = QDir( fullName() ).isReadable();

    if ( !readable )
        setPixmap( folderLocked );
    else
        setPixmap( folderClosed );
}


Directory::Directory( QListView * parent, const int my_id,
                        const QString& filename, DataAccess* topDB )
        : QListViewItem( parent ), f(filename),
          showDirsOnly( ( (DirectoryView*)parent )->showDirsOnly() ),
        pix( 0 ) {

    p = 0;
    DB = topDB;
    id = my_id;
    readable = QDir( fullName() ).isReadable();
}


void Directory::setPixmap( QPixmap *px ) {
    pix = px;
    setup();
    widthChanged( 0 );
    invalidateHeight();
    repaint();
}


const QPixmap *Directory::pixmap( int i ) const {
    if ( i )
        return 0;
    return pix;
}

void Directory::setUid( std::string u ) {
    _uid = u;
}

void Directory::setOpen( bool o ) {
    const char *routine = "Directory::setOpen";
    if ( o ) {
        if (parent())
            setPixmap( folderOpen );
        else
            setPixmap( folderTopOpen );
    }
    else {
        if (parent())
            setPixmap( folderClosed );
        else
            setPixmap( folderTopClosed );
    }
	int children = childCount();
	for (int i = 0; i < children; i++)
		delete firstChild();
    if ( o && !childCount() ) {
        std::string SQL;
        try {
            SQL =   "SELECT * FROM v_tree WHERE parent=" + dps_itoa(id)
                        + " AND userid=" + _uid + ";";
            PqxxResult R = DB->exec("FilebrowserGetContents", SQL);
            DB->abort("FilebrowserGetContents");
            Directory *D;
            FileItem *F;
            for (unsigned int i = 0; i < R.size(); i++) {
                std::string type = R[i]["itemtype"].c_str();
                std::string id = R[i]["id"].c_str();
                std::string name = R[i]["name"].c_str();
                if (type == "dir") {
                    D = new Directory(this,atoi(id.c_str()),name,DB);
                    D->setUid(_uid);
                    D->setPixmap( folderClosed );
                }
                else if (type == "music") {
                    F = new FileItem(this,name,"Audio File");
                    F->setPixmap( fileAudio );
                }
                else if (type == "jingle") {
                    F = new FileItem(this,name,"Audio Ident");
                    F->setPixmap( fileJingle );
                }
                else if (type == "advert") {
                    F = new FileItem(this,name,"Audio Advert");
                    F->setPixmap( fileAdvert );
                }
                else if (type == "aw_set") {
                    F = new FileItem(this,name,"AudioWall Set");
                    F->setPixmap( fileAwSet );
                }
                else if (type == "script") {
                    F = new FileItem(this,name,"Script");
                    F->setPixmap( fileScript );
                }
                else if (type == "showplan") {
                    F = new FileItem(this,name,"Showplan");
                    F->setPixmap( fileShowplan );
                }
                if (F) F->setText(2,id);
                F = 0;
            }
        }
        catch (...) {
            L_ERROR(LOG_TABFILES, "Caught exception on Directory::setOpen");
            DB->abort("FilebrowserGetContents");
        }
    }
    QListViewItem::setOpen( o );
}


void Directory::setup() {
    setExpandable( TRUE );
    QListViewItem::setup();
}


QString Directory::fullName() {
    QString s;
    if ( p ) {
        s = p->fullName();
        s.append( f.name() );
        s.append( "/" );
    } else {
        s = f.name();
    }
    return s;
}


QString Directory::text( int column ) const {
    if ( column == 0 )
        return f.name();
    else
        return "";
}


/* =======================================================================
 * DirectoryView
 * =======================================================================
 */
DirectoryView::DirectoryView( QWidget *parent, const char *name, bool sdo )
    : QListView( parent, name ), dirsOnly( sdo ), oldCurrent( 0 ),
      dropItem( 0 ), mousePressed( FALSE ) {

    DB = new DataAccess();
    _uid = "2";

    if ( !folderLocked ) {
        QString path = DPSDIR;
        folderLocked = new QPixmap(path + "/images/folderLocked.png");
        folderClosed = new QPixmap(path + "/images/folder.png");
        folderOpen = new QPixmap(path + "/images/folderOpen.png");
        folderTopClosed = new QPixmap(path + "/images/folderTop.png");
        folderTopOpen = new QPixmap(path + "/images/folderTopOpen.png");
        folderHome = new QPixmap(path + "/images/folderHome.png");
        fileNormal = new QPixmap(path + "/images/script16.png" );
        fileAudio = new QPixmap(path + "/images/music16.png");
        fileJingle = new QPixmap(path + "/images/jingle16.png");
        fileAdvert = new QPixmap(path + "/images/jingle16.png");
        fileScript = new QPixmap(path + "/images/script16.png");
        fileAwSet = new QPixmap(path + "/images/awset16.png");
        fileShowplan = new QPixmap(path + "/images/info16.png");
    }

    connect( this, SIGNAL( doubleClicked( QListViewItem * ) ),
             this, SLOT( slotFolderSelected( QListViewItem * ) ) );
    connect( this, SIGNAL( returnPressed( QListViewItem * ) ),
             this, SLOT( slotFolderSelected( QListViewItem * ) ) );
}

DirectoryView::~DirectoryView() {
    delete DB;
}

void DirectoryView::populate() {
    clear();
    Directory *D;
    try {
        PqxxResult R = DB->exec("FilebrowserGetTopLevel",
                "SELECT * FROM v_tree WHERE parent<0 AND userid = " + _uid);
        DB->abort("FilebrowserGetTopLevel");
        for (unsigned int i = 0; i < R.size(); i++) {
            D = new Directory(this,atoi(R[i]["id"].c_str()),
                            R[i]["name"].c_str(),DB);
            D->setUid(_uid);
            D->setPixmap(folderTopClosed);
        }
    }
    catch (...) {
        DB->abort("FilebrowserGetTopLevel");
    }
}

void DirectoryView::setUser(std::string username) {
    if (username == "") {
        _uid = "2";
        populate();
        return;
    }
    PqxxResult R = DB->exec("FilebrowserGetUser",
            "SELECT id FROM users WHERE username='" + username + "'");
    DB->abort("FilebrowserGetUser");
    if (R.size() == 1) {
        _uid = R[0]["id"].c_str();
    }
    else {
        _uid = "2";
    }
    populate();
}

void DirectoryView::slotFolderSelected( QListViewItem *i ) {
    if ( !i || !showDirsOnly() )
        return;

    Directory *dir = (Directory*)i;
    emit folderSelected( dir->fullName() );
}

void DirectoryView::openFolder() {
    if ( dropItem && !dropItem->isOpen() ) {
        dropItem->setOpen( TRUE );
        dropItem->repaint();
    }
}

QString DirectoryView::fullPath(QListViewItem* item) {
    QString fullpath = item->text(0);
    while ( (item=item->parent()) ) {
        if ( item->parent() )
            fullpath = item->text(0) + "/" + fullpath;
        else
            fullpath = item->text(0) + fullpath;
    }
    return fullpath;
}

void DirectoryView::setDir( const QString &s ) {
    QListViewItemIterator it( this );
    ++it;
    for ( ; it.current(); ++it ) {
        it.current()->setOpen( FALSE );
    }

    QStringList lst( QStringList::split( "/", s ) );
    QListViewItem *item = firstChild();
    QStringList::Iterator it2 = lst.begin();
    for ( ; it2 != lst.end(); ++it2 ) {
        while ( item ) {
            if ( item->text( 0 ) == *it2 ) {
                item->setOpen( TRUE );
                break;
            }
            item = item->itemBelow();
        }
    }

    if ( item )
        setCurrentItem( item );
}

/* =======================================================================
 * FileItem
 * =======================================================================
 */
void FileItem::setPixmap( QPixmap *p ) {
    pix = p;
    setup();
    widthChanged( 0 );
    invalidateHeight();
    repaint();
}


const QPixmap *FileItem::pixmap( int i ) const {
    if ( i )
        return 0;
    return pix;
}


