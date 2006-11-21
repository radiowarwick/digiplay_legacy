/****************************************************************************
** $Id:  qt/dirview.h   3.0.6   edited Oct 12 2001 $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#ifndef DIRVIEW_H
#define DIRVIEW_H

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include <qlistview.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qstring.h>
#include <qtimer.h>

class QWidget;
class QDragEnterEvent;
class QDragMoveEvent;
class QDragLeaveEvent;
class QDropEvent;

class FileItem : public QListViewItem {
    public:
        FileItem( QListViewItem *parent, const QString &s1, const QString &s2 )
            : QListViewItem( parent, s1, s2 ), pix( 0 ) {}

        const QPixmap *pixmap( int i ) const;
        void setPixmap( QPixmap *p );

    private:
        QPixmap *pix;

};

class Directory : public QListViewItem {
    public:
        Directory( QListView * parent, const int my_id, 
                    const QString& filename, Connection *openC);
//        Directory( Directory * parent, const QString& filename, const QString 
//                    &col2 )
//            : QListViewItem( parent, filename, col2 ), pix( 0 ) {}
        Directory( Directory * parent, const int my_id, 
                    const QString& filename, Connection *openC);

        QString text( int column ) const;

        QString fullName();

        void setOpen( bool );
        void setup();

        const QPixmap *pixmap( int i ) const;
        void setPixmap( QPixmap *p );

    private:
        QFile f;
        Directory * p;
        int id;
        Connection *C;
        bool readable;
        bool showDirsOnly;
        QPixmap *pix;

};

class DirectoryView : public QListView {
    Q_OBJECT

    public:
        DirectoryView( QWidget *parent = 0, const char *name = 0, bool sdo = 
                        FALSE );
        bool showDirsOnly() { return dirsOnly; }

    public slots:
        void setDir( const QString & );

    signals:
        void folderSelected( const QString & );

    protected slots:
        void slotFolderSelected( QListViewItem * );
        void openFolder();

    protected:
        void contentsDragEnterEvent( QDragEnterEvent *e );
        void contentsDragMoveEvent( QDragMoveEvent *e );
        void contentsDragLeaveEvent( QDragLeaveEvent *e );
        void contentsDropEvent( QDropEvent *e );
        void contentsMouseMoveEvent( QMouseEvent *e );
        void contentsMousePressEvent( QMouseEvent *e );
        void contentsMouseReleaseEvent( QMouseEvent *e );

    private:
        Connection *C;
        QString fullPath(QListViewItem* item);
        bool dirsOnly;
        QListViewItem *oldCurrent;
        QListViewItem *dropItem;
        QTimer* autoopen_timer;
        QPoint presspos;
        bool mousePressed;

};

#endif


