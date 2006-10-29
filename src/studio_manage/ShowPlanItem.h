/*
 * Show Plan Item Base class
 * ShowPlanItem.h
 * A base class for items in the show plan. Derive classes from this class
 * and reimplement the init() routine and constructors to format the show
 * plan item as required. 
 *
 * Copyright (c) 2006 Chris Cantwell
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
#ifndef CLASS_SHOW_PLAN_ITEM
#define CLASS_SHOW_PLAN_ITEM

#include <qlistview.h>

#include "dps.h"

class QPainter;
class QColorGroup;
class QString;
class QSimpleRichText;

class ShowPlanItem : public QListViewItem {
	public:
		ShowPlanItem( QListView *parent, QListViewItem *after );
		ShowPlanItem( QListViewItem *parent, QListViewItem *after );
		virtual int getType() = 0;
		virtual void setup();
		int widthUsed() {return _widthUsed;}
		void setState(enum showPlanState state) {_state = state; setup();}
		enum showPlanState getState() {return _state;}

	protected:
		virtual void init();
		virtual void paintCell(QPainter *p, const QColorGroup &cg, int column,
				int width, int align);
		bool selected;
		bool active;
		int _widthUsed;
		bool rootElement;
		enum showPlanState _state;

		QSimpleRichText *lblTitle;
		QSimpleRichText *lblSubtitle;
		QSimpleRichText *lblLength;
		QSimpleRichText *lblTime;

		QFont titleFont, subtitleFont, lengthFont, timeFont;
		QBrush *backBrushUnloaded, *backBrushLoaded, *backBrushFinished;
		QBrush *backBrushUnloadedSel, *backBrushLoadedSel, 
						*backBrushFinishedSel;
		QPixmap *pixUnloaded, *pixLoaded, *pixFinished;

		QPen *selectPen;
		QPen *unselectPen;
};

#endif
