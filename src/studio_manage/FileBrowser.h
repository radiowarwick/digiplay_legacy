/*
 * Filebrowser Widget
 * FileBrowser.h
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

#ifndef DIRVIEW_H
#define DIRVIEW_H

#include <string>

#include <QtGui/QTreeWidget>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QString>
#include <QtCore/QTimer>

#include "DataAccess.h"

class QWidget;
class QDragEnterEvent;
class QDragMoveEvent;
class QDragLeaveEvent;
class QDropEvent;

class FileItem : public QTreeWidgetItem {
    public:
        FileItem( QTreeWidgetItem *parent, const QString &s1, const QString &s2 )
            : QTreeWidgetItem( parent ), pix( 0 ) {}

        const QPixmap *pixmap( int i ) const;
        void setPixmap( QPixmap *p );

    private:
        QPixmap *pix;

};

class Directory : public QTreeWidgetItem {
    public:
        Directory( QTreeWidget * parent, const int my_id,
                    const QString& filename, DataAccess *topDB);
        Directory( Directory * parent, const int my_id,
                    const QString& filename, DataAccess *topDB);

        QString text( int column ) const;

        QString fullName();

        void setUid( std::string );
        void setOpen( bool );
        void setup();

        const QPixmap *pixmap( int i ) const;
        void setPixmap( QPixmap *p );

    private:
        DataAccess* DB;
        QFile f;
        Directory * p;
        int id;
        bool readable;
        bool showDirsOnly;
        QPixmap *pix;
        std::string _uid;
};

class DirectoryView : public QTreeWidget {
    Q_OBJECT

    public:
        DirectoryView( QWidget *parent = 0, const char *name = 0, bool sdo =
                        FALSE );
        ~DirectoryView();
        bool showDirsOnly() { return dirsOnly; }
        void setUser(std::string username);

    public slots:
        void setDir( const QString & );

    signals:
        void folderSelected( const QString & );

    protected slots:
        void slotFolderSelected( QTreeWidgetItem * );
        void openFolder();

    private:
        void populate();

        DataAccess* DB;
        QString fullPath(QTreeWidgetItem* item);
        bool dirsOnly;
        QAbstractItemDelegate *oldCurrent;
        QAbstractItemDelegate *dropItem;
        QPoint presspos;
        bool mousePressed;
        std::string _uid;
};

#endif


