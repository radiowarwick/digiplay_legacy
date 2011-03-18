/*
 * Showplan Widget
 * Showplan.cpp
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
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "dps/Dps.h"
#include "dps.h"
#include "Logger.h"
#include "Auth.h"
#include "dlgWarn.h"

#include "ShowplanView.h"

ShowplanView::ShowplanView(QWidget* parent)
        : QListView(parent) {

}

ShowplanView::~ShowplanView() {

}

void ShowplanView::selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected )
{
    if (selected.size() > 0) {
        emit itemSelected(selected.indexes().at(0));
    }
    else {
        emit itemSelected(QModelIndex());
    }
}


/*
QRect ShowplanView::visualRect(const QModelIndex &index) const {
cout << "a" << endl;
}

void ShowplanView::scrollTo(const QModelIndex &index, ScrollHint hint) {
    cout << "b" << endl;
}

//QModelIndex ShowplanView::indexAt(const QPoint &point) const {

//}

bool ShowplanView::edit(const QModelIndex &index, EditTrigger trigger, QEvent *event) {
    cout << "d" << endl;
}

QModelIndex ShowplanView::moveCursor(QAbstractItemView::CursorAction cursorAction,
                        Qt::KeyboardModifiers modifiers) {
    QModelIndex current = currentIndex();

    switch (cursorAction) {
        case MoveLeft:
        case MoveUp:
            if (current.row() > 0)
                current = model()->index(current.row() - 1, current.column(),
                                         rootIndex());
            else
                current = model()->index(0, current.column(), rootIndex());
            break;
        case MoveRight:
        case MoveDown:
            if (current.row() < rows(current) - 1)
                current = model()->index(current.row() + 1, current.column(),
                                         rootIndex());
            else
                current = model()->index(rows(current) - 1, current.column(),
                                         rootIndex());
            break;
        default:
            break;
    }

    viewport()->update();
    return current;
}

int ShowplanView::horizontalOffset() const {

}

int ShowplanView::verticalOffset() const {

}

bool ShowplanView::isIndexHidden(const QModelIndex &index) const {

}

void ShowplanView::setSelection(const QRect&, QItemSelectionModel::SelectionFlags command) {

}

QRegion ShowplanView::visualRegionForSelection(const QItemSelection &selection) const {

}

int ShowplanView::rows(const QModelIndex &index) const {
    return model()->rowCount(model()->parent(index));
}
*/
