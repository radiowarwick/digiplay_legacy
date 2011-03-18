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

#ifndef CLASS_SHOWPLANMODEL
#define CLASS_SHOWPLANMODEL

using namespace std;

#include <QtCore/QAbstractListModel>

#include "dps/Dps.h"

class ShowplanModel : 	public QAbstractListModel,
                        public DpsShowPlan {
	Q_OBJECT

	public:
	    ShowplanModel();
		virtual ~ShowplanModel();

		virtual void loadShowplan(const DpsShowPlan& pSrc);
		virtual void append(const DpsShowItem& pSrc);
        virtual void erase(unsigned int pPos);
        virtual void erase(const DpsShowItem& pSrc);
        virtual void clear();
        virtual void moveUp(const DpsShowItem& pSrc);
        virtual void moveDown(const DpsShowItem& pSrc);
        virtual void moveTop(const DpsShowItem& pSrc);
        virtual void moveBottom(const DpsShowItem& pSrc);

        int rowCount(const QModelIndex & parent = QModelIndex()) const;
        QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
        QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
        Qt::ItemFlags flags ( const QModelIndex & index ) const;

};

#endif
