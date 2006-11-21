/****************************************************************************
** $Id:  qt/dirview.cpp   3.0.6   edited Oct 12 2001 $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
** Modified for the Digiplay DB by Ian Liverton, 2006			
*****************************************************************************/

#include "FileBrowser.h"
#include "config.h"
#include "dps.h"

#include <qdir.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qpixmap.h>
#include <qevent.h>
#include <qpoint.h>
#include <qmessagebox.h>
#include <qdragobject.h>
#include <qmime.h>
#include <qstrlist.h>
#include <qstringlist.h>
#include <qapplication.h>
#include <qheader.h>

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
QPixmap *fileCartset = 0;
QPixmap *fileShowplan = 0;

/*****************************************************************************
 *
 * Class Directory
 *
 
*****************************************************************************/

Directory::Directory( Directory * parent, const int my_id, 
                        const QString& filename, Connection *openC )
    : QListViewItem( parent ), f(filename),
      showDirsOnly( parent->showDirsOnly ),
      pix( 0 )
{
    p = parent;
    C = openC;
    id = my_id;
    readable = QDir( fullName() ).isReadable();

    if ( !readable )
        setPixmap( folderLocked );
    else
        setPixmap( folderClosed );
}


Directory::Directory( QListView * parent, const int my_id,
                        const QString& filename, Connection *openC )
    : QListViewItem( parent ), f(filename),
      showDirsOnly( ( (DirectoryView*)parent )->showDirsOnly() ),
      pix( 0 )
{
    p = 0;
    C = openC;
    id = my_id;
    readable = QDir( fullName() ).isReadable();
}


void Directory::setPixmap( QPixmap *px )
{
    pix = px;
    setup();
    widthChanged( 0 );
    invalidateHeight();
    repaint();
}


const QPixmap *Directory::pixmap( int i ) const
{
    if ( i )
        return 0;
    return pix;
}

void Directory::setOpen( bool o )
{
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

    if ( o && !childCount() ) {
        Transaction T(*C,"");
        try {
            Result R_dir = T.exec("SELECT id,name,notes FROM dir WHERE parent="
                                + dps_itoa(id));
            Result R_audio = T.exec("SELECT audio.id,audio.title,audio.md5,audiotypes.name as type FROM audio,audiodir,audiotypes WHERE audio.type = audiotypes.id AND audio.id = audiodir.audio AND audiodir.directory = " + dps_itoa(id));
            Result R_cartset = T.exec("SELECT cartsets.id,cartsets.name FROM cartsets,cartsetsdir WHERE cartsets.id = cartsetsdir.cartsetid AND cartsetsdir.dir = " + dps_itoa(id));
            Result R_script = T.exec("SELECT scripts.id,scripts.name FROM scripts,scriptsdir WHERE scripts.id = scriptsdir.scriptid AND scriptsdir.dir = " + dps_itoa(id));
            Result R_showplan = T.exec("SELECT showplans.id,showplans.name FROM showplans,showplandir WHERE showplans.id = showplandir.showplanid AND showplandir.dir = " + dps_itoa(id));
            T.abort();
            Directory *D;
            FileItem *F;
            for (unsigned int i = 0; i < R_dir.size(); i++) {
                D = new Directory(this,atoi(R_dir[i]["id"].c_str()),
                                        R_dir[i]["name"].c_str(),C);
                D->setPixmap( folderClosed );
            }
            for (unsigned int i = 0; i < R_audio.size(); i++) {
                if (string(R_audio[i]["type"].c_str()) == "jingle") {
                    F = new FileItem(this,R_audio[i]["title"].c_str(),
                                    "Audio Ident");
                    F->setPixmap( fileJingle );
                }
                else if (string(R_audio[i]["type"].c_str()) == "advert") {
                    F = new FileItem(this,R_audio[i]["title"].c_str(),
                                    "Audio Advert");
                    F->setPixmap( fileAdvert );
                }
                else {
                    F = new FileItem(this,R_audio[i]["title"].c_str(),
                                    "Audio file");
                    F->setPixmap( fileAudio );
                }
                F->setText(2, R_audio[i]["md5"].c_str());
            }
            for (unsigned int i = 0; i < R_cartset.size(); i++) {
                F = new FileItem(this,R_cartset[i]["name"].c_str(),
                                    "Cartset");
                F->setPixmap( fileCartset );
                F->setText(2, R_cartset[i]["id"].c_str());
            }
            for (unsigned int i = 0; i < R_script.size(); i++) {
                F = new FileItem(this,R_script[i]["name"].c_str(),
                                    "Script");
                F->setPixmap( fileScript );
                F->setText(2, R_script[i]["id"].c_str());
            }
            for (unsigned int i = 0; i < R_showplan.size(); i++) {
                F = new FileItem(this,R_showplan[i]["name"].c_str(),
                                    "Showplan");
                F->setPixmap( fileShowplan );
                F->setText(2, R_showplan[i]["id"].c_str());
            }
        }
        catch (...) {
            cout << "Caught exception on Directory::setOpen" << endl;
            T.abort();
        }
/*        QString s( fullName() );
        QDir thisDir( s );
        if ( !thisDir.isReadable() ) {
            readable = FALSE;
            setExpandable( FALSE );
            return;
        }

        listView()->setUpdatesEnabled( FALSE );
        const QFileInfoList * files = thisDir.entryInfoList();
        if ( files ) {
            QFileInfoListIterator it( *files );
            QFileInfo * fi;
            while( (fi=it.current()) != 0 ) {
                ++it;
                if ( fi->fileName() == "." || fi->fileName() == ".." )
                    ; // nothing
                else if ( fi->isSymLink() && !showDirsOnly ) {
                    FileItem *item = new FileItem( this, fi->fileName(),
                                                     "Symbolic Link" );
                    item->setPixmap( fileNormal );
                }
                else if ( fi->isDir() )
                    (void)new Directory( this, fi->fileName() );
                else if ( !showDirsOnly ) {
                    FileItem *item
                        = new FileItem( this, fi->fileName(),
                                             fi->isFile()?"File":"Special" 
);
                    item->setPixmap( fileNormal );
                }
            }
        }
        listView()->setUpdatesEnabled( TRUE );
*/    }
    QListViewItem::setOpen( o );
}


void Directory::setup()
{
    setExpandable( TRUE );
    QListViewItem::setup();
}


QString Directory::fullName()
{
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


QString Directory::text( int column ) const
{
    if ( column == 0 )
        return f.name();
    else
        return "";
//    else if ( readable )
//        return "Directory";
//    else
//        return "Unreadable Directory";
}

/*****************************************************************************
 *
 * Class DirectoryView
 *
 
*****************************************************************************/

DirectoryView::DirectoryView( QWidget *parent, const char *name, bool sdo )
    : QListView( parent, name ), dirsOnly( sdo ), oldCurrent( 0 ),
      dropItem( 0 ), mousePressed( FALSE )
{
    config *conf = new config("digiplay");
    C = new Connection(conf->getDBConnectString());
    delete conf;

    autoopen_timer = new QTimer( this );
    if ( !folderLocked ) {
        QString path = qApp->applicationDirPath();
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
        fileCartset = new QPixmap(path + "/images/cartset16.png");
        fileShowplan = new QPixmap(path + "/images/info16.png");
    }

    Directory *D;
    Transaction T(*C,"");
    try {
        Result R = T.exec("SELECT id,name,notes FROM dir WHERE parent<0");
        T.abort();
        for (unsigned int i = 0; i < R.size(); i++) {
            D = new Directory(this,atoi(R[i]["id"].c_str()),
                            R[i]["name"].c_str(),C);
            D->setPixmap(folderTopClosed);
        }
    }
    catch (...) {
        T.abort();    
    }
    connect( this, SIGNAL( doubleClicked( QListViewItem * ) ),
             this, SLOT( slotFolderSelected( QListViewItem * ) ) );
    connect( this, SIGNAL( returnPressed( QListViewItem * ) ),
             this, SLOT( slotFolderSelected( QListViewItem * ) ) );

//    setAcceptDrops( TRUE );
//    viewport()->setAcceptDrops( TRUE );

    connect( autoopen_timer, SIGNAL( timeout() ),
             this, SLOT( openFolder() ) );
}

void DirectoryView::slotFolderSelected( QListViewItem *i )
{
    if ( !i || !showDirsOnly() )
        return;

    Directory *dir = (Directory*)i;
    emit folderSelected( dir->fullName() );
}

void DirectoryView::openFolder()
{
    autoopen_timer->stop();
    if ( dropItem && !dropItem->isOpen() ) {
        dropItem->setOpen( TRUE );
        dropItem->repaint();
    }
}

static const int autoopenTime = 750;


void DirectoryView::contentsDragEnterEvent( QDragEnterEvent *e )
{
    if ( !QUriDrag::canDecode(e) ) {
        e->ignore();
        return;
    }

    oldCurrent = currentItem();

    QListViewItem *i = itemAt( contentsToViewport(e->pos()) );
    if ( i ) {
        dropItem = i;
        autoopen_timer->start( autoopenTime );
    }
}


void DirectoryView::contentsDragMoveEvent( QDragMoveEvent *e )
{
    if ( !QUriDrag::canDecode(e) ) {
        e->ignore();
        return;
    }

    QPoint vp = contentsToViewport( ( (QDragMoveEvent*)e )->pos() );
    QListViewItem *i = itemAt( vp );
    if ( i ) {
        setSelected( i, TRUE );
        e->accept();
        if ( i != dropItem ) {
            autoopen_timer->stop();
            dropItem = i;
            autoopen_timer->start( autoopenTime );
        }
        switch ( e->action() ) {
        case QDropEvent::Copy:
            break;
        case QDropEvent::Move:
            e->acceptAction();
            break;
        case QDropEvent::Link:
            e->acceptAction();
            break;
        default:
            ;
        }
    } else {
        e->ignore();
        autoopen_timer->stop();
        dropItem = 0;
    }
}

void DirectoryView::contentsDragLeaveEvent( QDragLeaveEvent * )
{
    autoopen_timer->stop();
    dropItem = 0;

    setCurrentItem( oldCurrent );
    setSelected( oldCurrent, TRUE );
}

void DirectoryView::contentsDropEvent( QDropEvent *e )
{
    autoopen_timer->stop();

    if ( !QUriDrag::canDecode(e) ) {
        e->ignore();
        return;
    }

    QListViewItem *item = itemAt( contentsToViewport(e->pos()) );
    if ( item ) {

        QStrList lst;

        QUriDrag::decode( e, lst );

        QString str;

        switch ( e->action() ) {
            case QDropEvent::Copy:
            str = "Copy";
            break;
            case QDropEvent::Move:
            str = "Move";
            e->acceptAction();
            break;
            case QDropEvent::Link:
            str = "Link";
            e->acceptAction();
            break;
            default:
            str = "Unknown";
        }

        str += "\n\n";

        e->accept();

        for ( uint i = 0; i < lst.count(); ++i ) {
            QString filename = lst.at( i );
            str += filename + "\n";
        }
        str += QString( "\nTo\n\n   %1" )
               .arg( fullPath(item) );

        QMessageBox::information( this, "Drop target", str, "Not implemented" );
    } else
        e->ignore();

}


QString DirectoryView::fullPath(QListViewItem* item)
{
    QString fullpath = item->text(0);
    while ( (item=item->parent()) ) {
        if ( item->parent() )
            fullpath = item->text(0) + "/" + fullpath;
        else
            fullpath = item->text(0) + fullpath;
    }
    return fullpath;
}

void DirectoryView::contentsMousePressEvent( QMouseEvent* e )
{
    QListView::contentsMousePressEvent(e);
    QPoint p( contentsToViewport( e->pos() ) );
    QListViewItem *i = itemAt( p );
    if ( i ) {
        // if the user clicked into the root decoration of the item, don't try to start a drag!
        if ( p.x() > header()->cellPos( header()->mapToActual( 0 ) ) +
             treeStepSize() * ( i->depth() + ( rootIsDecorated() ? 1 : 0) ) + itemMargin() ||
             p.x() < header()->cellPos( header()->mapToActual( 0 ) ) ) {
            presspos = e->pos();
            mousePressed = TRUE;
        }
    }
}

void DirectoryView::contentsMouseMoveEvent( QMouseEvent* e )
{
    if ( mousePressed && ( presspos - e->pos() ).manhattanLength() > 
QApplication::startDragDistance() ) {
        mousePressed = FALSE;
        QListViewItem *item = itemAt( contentsToViewport(presspos) );
        if ( item ) {
            QString source = fullPath(item);
            if ( QFile::exists(source) ) {
                QUriDrag* ud = new QUriDrag(viewport());
                ud->setUnicodeUris( source );
                if ( ud->drag() )
                    QMessageBox::information( this, "Drag source",
                                              QString("Delete ")+source, "Not implemented" );
            }
        }
    }
}

void DirectoryView::contentsMouseReleaseEvent( QMouseEvent * )
{
    mousePressed = FALSE;
}

void DirectoryView::setDir( const QString &s )
{
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

void FileItem::setPixmap( QPixmap *p )
{
    pix = p;
    setup();
    widthChanged( 0 );
    invalidateHeight();
    repaint();
}


const QPixmap *FileItem::pixmap( int i ) const
{
    if ( i )
        return 0;
    return pix;
}


