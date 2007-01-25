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

#include "FileBrowser.h"
#include "config.h"
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
QPixmap *fileCartset = 0;
QPixmap *fileShowplan = 0;

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

void Directory::setUid( string u ) {
    _uid = u;
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
        string SQL;
        try {
            SQL =   "SELECT dir.id, dir.name, dir.notes "
                    "FROM dir, dirusers "
                    "WHERE dir.id = dirusers.directory "
                        "AND (dirusers.permissions='r' "
                            "OR dirusers.permissions='rw' "
                            "OR dirusers.permissions='o') "
                        "AND dir.parent=" + dps_itoa(id) + " "
                        "AND dirusers.userid=" + _uid + " "
                    "UNION "
                    "SELECT dir.id, dir.name, dir.notes "
                    "FROM dir, dirgroups, groups, groupmembers "
                    "WHERE dir.id = dirgroups.directory "
                        "AND (dirgroups.permissions='r' "
                            "OR dirgroups.permissions='rw' "
                            "OR dirgroups.permissions='o') "
                        "AND dir.parent=" + dps_itoa(id) + " "
                        "AND dirgroups.groupid = groups.id "
                        "AND groupmembers.groupid = groups.id "
                        "AND groupmembers.userid = " + _uid;
            Result R_dir = T.exec(SQL);
            SQL =   "SELECT audio.id, audio.title, audio.md5, "
                        "audiotypes.name as type "
                    "FROM audio, audiodir, audiotypes, audiousers "
                    "WHERE audio.type = audiotypes.id "
                        "AND audio.id = audiodir.audio "
                        "AND (audiousers.permissions='r' "
                            "OR audiousers.permissions='rw' "
                            "OR audiousers.permissions='o') "
                        "AND audiodir.directory = " + dps_itoa(id) + " "
                        "AND audiousers.userid=" + _uid + " "
                    "UNION "
                    "SELECT audio.id, audio.title, audio.md5, "
                        "audiotypes.name as type "
                    "FROM audio, audiodir, audiotypes, audiogroups, groups, "
                        "groupmembers "
                    "WHERE audio.type = audiotypes.id "
                        "AND audio.id = audiodir.audio "
                        "AND (audiogroups.permissions='r' "
                            "OR audiogroups.permissions='rw' "
                            "OR audiogroups.permissions='o') "
                        "AND audiodir.directory = " + dps_itoa(id) + " "
                        "AND audiogroups.groupid = groups.id "
                        "AND groupmembers.groupid = groups.id "
                        "AND groupmembers.userid = " + _uid;
            Result R_audio = T.exec(SQL);
            SQL =   "SELECT cartsets.id,cartsets.name "
                    "FROM cartsets,cartsetsdir,cartsetsusers "
                    "WHERE cartsets.id = cartsetsdir.cartsetid "
                        "AND (cartsetsusers.permissions='r' "
                            "OR cartsetsusers.permissions='rw' "
                            "OR cartsetsusers.permissions='o') "
                        "AND cartsetsdir.dir = " + dps_itoa(id) + " "
                        "AND cartsetsusers.userid=" + _uid + " "
                    "UNION "
                    "SELECT cartsets.id, cartsets.name "
                    "FROM cartsets, cartsetsdir, cartsetsgroups, groups, "
                        "groupmembers "
                    "WHERE cartsets.id = cartsetsdir.cartsetid "
                        "AND (cartsetsgroups.permissions='r' "
                            "OR cartsetsgroups.permissions='rw' "
                            "OR cartsetsgroups.permissions='o') "
                        "AND cartsetsdir.dir = " + dps_itoa(id) + " "
                        "AND cartsetsgroups.groupid = groups.id "
                        "AND groupmembers.groupid = groups.id "
                        "AND groupmembers.userid = " + _uid;
            Result R_cartset = T.exec(SQL);
            SQL =   "SELECT scripts.id, scripts.name "
                    "FROM scripts,scriptsdir,scriptusers "
                    "WHERE scripts.id = scriptsdir.scriptid "
                        "AND (scriptusers.permissions='r' "
                            "OR scriptusers.permissions='rw' "
                            "OR scriptusers.permissions='o') "
                        "AND scriptsdir.dir = " + dps_itoa(id) + " "
                        "AND scriptusers.userid = " + _uid + " "
                    "UNION "
                    "SELECT scripts.id, scripts.name "
                    "FROM scripts, scriptsdir, scriptgroups, groups, "
                        "groupmembers "
                    "WHERE scripts.id = scriptsdir.scriptid "
                        "AND (scriptgroups.permissions='r' "
                            "OR scriptgroups.permissions='rw' "
                            "OR scriptgroups.permissions='o') "
                        "AND scriptsdir.dir = " + dps_itoa(id) + " "
                        "AND scriptgroups.groupid = groups.id "
                        "AND groupmembers.groupid = groups.id "
                        "AND groupmembers.userid = " + _uid;
            Result R_script = T.exec(SQL);
            SQL =   "SELECT showplans.id,showplans.name "
                    "FROM showplans,showplandir,showplanusers "
                    "WHERE showplans.id = showplandir.showplanid "
                        "AND (showplanusers.permissions='r' "
                            "OR showplanusers.permissions='rw' "
                            "OR showplanusers.permissions='o') "
                        "AND showplandir.dir = " + dps_itoa(id) + " "
                        "AND showplanusers.userid = " + _uid + " "
                    "UNION "
                    "SELECT showplans.id, showplans.name "
                    "FROM showplans,showplandir,showplangroups,groups, "
                        "groupmembers "
                    "WHERE showplans.id = showplandir.showplanid "
                        "AND (showplangroups.permissions = 'r' "
                            "OR showplangroups.permissions = 'rw' "
                            "OR showplangroups.permissions = 'o') "
                        "AND showplandir.dir = " + dps_itoa(id) + " "
                        "AND showplangroups.groupid = groups.id "
                        "AND groupmembers.groupid = groups.id "
                        "AND groupmembers.userid = " + _uid;
            Result R_showplan = T.exec(SQL);
            T.abort();
            Directory *D;
            FileItem *F;
            for (unsigned int i = 0; i < R_dir.size(); i++) {
                D = new Directory(this,atoi(R_dir[i]["id"].c_str()),
                                        R_dir[i]["name"].c_str(),C);
                D->setUid(_uid);
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
                                    "Audio File");
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
    }
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
}


/* =======================================================================
 * DirectoryView
 * =======================================================================
 */
DirectoryView::DirectoryView( QWidget *parent, const char *name, bool sdo )
    : QListView( parent, name ), dirsOnly( sdo ), oldCurrent( 0 ),
      dropItem( 0 ), mousePressed( FALSE )
{
    config *conf = new config("digiplay");
    C = new Connection(conf->getDBConnectString());
    delete conf;
    _uid = "-1";

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

    connect( this, SIGNAL( doubleClicked( QListViewItem * ) ),
             this, SLOT( slotFolderSelected( QListViewItem * ) ) );
    connect( this, SIGNAL( returnPressed( QListViewItem * ) ),
             this, SLOT( slotFolderSelected( QListViewItem * ) ) );
}

DirectoryView::~DirectoryView() {
    if (C && C->is_open()) {
        C->Disconnect();
    }
    delete C;
}

void DirectoryView::populate() {
    clear();
    Directory *D;
    Transaction T(*C,"");
    try {
        Result R = T.exec("SELECT id,name,notes FROM dir WHERE parent=-1");
        T.abort();
        for (unsigned int i = 0; i < R.size(); i++) {
            D = new Directory(this,atoi(R[i]["id"].c_str()),
                            R[i]["name"].c_str(),C);
            D->setUid(_uid);
            D->setPixmap(folderTopClosed);
            D->setOpen(true);
        }
    }
    catch (...) {
        T.abort();
    }
}

void DirectoryView::setUser(string username) {
    if (username == "") {
        _uid = "-1";
        populate();
        return;
    }
    Transaction T(*C,"");
    Result R = T.exec("SELECT id FROM users WHERE username='" + username + "'");
    T.abort();
    if (R.size() == 1) {
        _uid = R[0]["id"].c_str();
    }
    else {
        _uid = "-1";
    }
    populate();
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
    if ( dropItem && !dropItem->isOpen() ) {
        dropItem->setOpen( TRUE );
        dropItem->repaint();
    }
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

/* =======================================================================
 * FileItem
 * =======================================================================
 */
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


