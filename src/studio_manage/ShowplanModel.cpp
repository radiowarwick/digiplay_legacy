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

#include "ShowplanModel.h"

Q_DECLARE_METATYPE(DpsShowItem)

ShowplanModel::ShowplanModel()
        : QAbstractListModel() {

}

ShowplanModel::~ShowplanModel() {

}

void ShowplanModel::loadShowplan(const DpsShowPlan& pSrc) {
    DpsShowPlan::operator =(pSrc);
}

void ShowplanModel::append(const DpsShowItem& pSrc) {
    try {
        QModelIndex root = index(0,0,QModelIndex());
        beginInsertRows(QModelIndex(),rowCount(),rowCount()+1);
        DpsShowPlan::append(pSrc);
        endInsertRows();
    }
    catch (...) {
        cout << "Unable to append item." << endl;
    }
}

void ShowplanModel::erase(unsigned int pPos) {
    try {
        beginRemoveRows(QModelIndex(),pPos,pPos);
        DpsShowPlan::erase(pPos);
        endRemoveRows();
    }
    catch (...) {
        cout << "Unable to delete item." << endl;
    }
}

void ShowplanModel::erase(const DpsShowItem& pSrc) {
    try {
        unsigned int vPos = DpsShowPlan::getItemIndex(pSrc);
        ShowplanModel::erase(vPos);
    }
    catch (const DpsShowPlan::OutOfRange& x) {
        cout << "ShowplanModel::erase: No such item in showplan." << endl;
    }
    catch (...) {
        cout << "Unable to delete item." << endl;
    }

}

void ShowplanModel::clear() {
    try {
        beginResetModel();
        DpsShowPlan::clear();
        endResetModel();
    }
    catch (...) {
        cout << "Unable to clear showplan." << endl;
    }
}

void ShowplanModel::moveUp(const DpsShowItem& pSrc) {
    try {
        unsigned int vPos = DpsShowPlan::getItemIndex(pSrc);
        if (vPos == 0) return;

        // Destination index (last parameter) must specify index at which
        // elements will be placed before, rather than new index of first
        // element moved.
        beginMoveRows(QModelIndex(), vPos, vPos, QModelIndex(), vPos - 1);
        DpsShowPlan::moveUp(pSrc);
        endMoveRows();
    }
    catch (const DpsShowPlan::OutOfRange& x) {
        cout << "ShowplanModel::moveUp: No such item in showplan." << endl;
    }
    catch (...) {
        cout << "Unable to move item" << endl;
    }
}

void ShowplanModel::moveDown(const DpsShowItem& pSrc) {
    unsigned int vPos;
    try {
        vPos = DpsShowPlan::getItemIndex(pSrc);
        if (vPos + 1 == DpsShowPlan::getSize()) return;

        // Destination index (last parameter) must specify index at which
        // elements will be placed before, rather than new index of first
        // element moved.
        beginMoveRows(QModelIndex(), vPos, vPos, QModelIndex(), vPos+2);
        DpsShowPlan::moveDown(pSrc);
        endMoveRows();
    }
    catch (const DpsShowPlan::OutOfRange& x) {
        cout << "ShowplanModel::moveDown: No such item in showplan." << endl;
    }
    catch (...) {
        cout << "Unable to move item" << endl;
    }
}

void ShowplanModel::moveTop(const DpsShowItem& pSrc) {
    try {
        unsigned int vPos = DpsShowPlan::getItemIndex(pSrc);
        if (vPos == 0) return;

        // Destination index (last parameter) must specify index at which
        // elements will be placed before, rather than new index of first
        // element moved.
        beginMoveRows(QModelIndex(), vPos, vPos, QModelIndex(), 0);
        DpsShowPlan::moveTop(pSrc);
        endMoveRows();
    }
    catch (const DpsShowPlan::OutOfRange& x) {
        cout << "ShowplanModel::moveTop: No such item in showplan." << endl;
    }
    catch (...) {
        cout << "Unable to move item" << endl;
    }
}

void ShowplanModel::moveBottom(const DpsShowItem& pSrc) {
    try {
        unsigned int vPos = DpsShowPlan::getItemIndex(pSrc);
        if (vPos == DpsShowPlan::getSize() - 1) return;

        // Destination index (last parameter) must specify index at which
        // elements will be placed before, rather than new index of first
        // element moved.
        beginMoveRows(QModelIndex(), vPos, vPos, QModelIndex(), DpsShowPlan::getSize());
        DpsShowPlan::moveBottom(pSrc);
        endMoveRows();
    }
    catch (const DpsShowPlan::OutOfRange& x) {
        cout << "ShowplanModel::moveBottom: No such item in showplan." << endl;
    }
    catch (...) {
        cout << "Unable to move item" << endl;
    }
}

int ShowplanModel::rowCount(const QModelIndex & parent ) const {
    return DpsShowPlan::getSize();
}

QVariant ShowplanModel::data ( const QModelIndex & index, int role ) const {
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() < 0 || index.row() >= DpsShowPlan::getSize()) {
        return QVariant();
    }
    switch (role) {
        case Qt::DisplayRole: {
            return qVariantFromValue(DpsShowPlan::getItem(index.row()));
            break;
        }
        default: {
            return QVariant();
        }
    }
}

QVariant ShowplanModel::headerData ( int section, Qt::Orientation orientation, int role ) const {
    QVariant vTmp;
    return vTmp;
}

Qt::ItemFlags ShowplanModel::flags ( const QModelIndex & index ) const {
    if (!index.isValid()) {
        return 0;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
