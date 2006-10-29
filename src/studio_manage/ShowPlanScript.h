/*
 * Show Plan Script Item
 * ShowPlanScript.h
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
#ifndef CLASS_SHOW_PLAN_SCRIPT
#define CLASS_SHOW_PLAN_SCRIPT

#include <qlistview.h>

#include "dps.h"
#include "ShowPlanItem.h"

class QPainter;
class QColorGroup;
class QString;
class QSimpleRichText;

class ShowPlanScript : public ShowPlanItem {
	public:
		ShowPlanScript( QListView *parent, QListViewItem *after );
		ShowPlanScript( QListViewItem *parent, QListViewItem *after );
		ShowPlanScript( QListView *parent, QListViewItem *after, script s);
		int getType() {return 1;}
		script getScript() {return _s;}

	private:
		void init();
		script _s;
};

#endif
