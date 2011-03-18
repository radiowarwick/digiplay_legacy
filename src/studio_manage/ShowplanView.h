/*
 * Showplan Widget
 * Showplan.h
 * Manages and displays the active showplan. Facilities provided for loading
 * and saving showplans to the database.
 *
 * Copyright (c) 2004-2006 Chris Cantwell
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

#ifndef CLASS_SHOWPLANVIEW
#define CLASS_SHOWPLANVIEW

using namespace std;

#include <QtGui/QListView>
#include <QtGui/QItemSelection>
#include <QtGui/QItemSelectionModel>
#include <QtCore/QModelIndex>
#include <QtGui/QWidget>

#include "dps/Dps.h"

class ShowplanView : 	public QListView {
    Q_OBJECT
    public:
	    ShowplanView(QWidget* parent);
		virtual ~ShowplanView();

    signals:
        void itemSelected(const QModelIndex& index);

    protected:
		virtual void selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected );
/*
		QRect visualRect(const QModelIndex &index) const;
		void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible);
//		QModelIndex indexAt(const QPoint &point) const;

    protected:
        bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);
        QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction,
                                Qt::KeyboardModifiers modifiers);

        int horizontalOffset() const;
        int verticalOffset() const;

        bool isIndexHidden(const QModelIndex &index) const;

        void setSelection(const QRect&, QItemSelectionModel::SelectionFlags command);

        QRegion visualRegionForSelection(const QItemSelection &selection) const;

    private:
        int rows(const QModelIndex &index = QModelIndex()) const;
*/
};

#endif
