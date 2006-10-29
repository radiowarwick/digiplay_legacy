/*
 * Show Plan Script Item
 * ShowPlanScript.cpp
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
#include <iostream>
using namespace std;

#include <qstring.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qapplication.h>

#include "ShowPlanScript.h"

ShowPlanScript::ShowPlanScript( QListView *parent, QListViewItem *after )
		: ShowPlanItem(parent,after) {
	rootElement = true;
	init();
}

ShowPlanScript::ShowPlanScript( QListViewItem *parent, QListViewItem *after ) 
		: ShowPlanItem(parent,after) {
	rootElement = false;
	init();
}

ShowPlanScript::ShowPlanScript( QListView *parent, QListViewItem *after, script s )
		: ShowPlanItem(parent, after) {
	rootElement = false;
	setText(0,s.title);
	setText(1,s.owner);
	setText(2,dps_prettyTime(s.length_smpl));
	setText(3,"");
	_s = s;
	init();
}

void ShowPlanScript::init() {
	string path = qApp->applicationDirPath();
	backBrushUnloaded = new QBrush(QColor(0,173,189));
	backBrushLoaded = new QBrush(QColor(0,173,189));
	backBrushFinished = new QBrush(QColor(148,148,148));
	pixUnloaded = new QPixmap(path + "/images/script32.png");
	pixLoaded = new QPixmap(path + "/images/scriptLoaded32.png");
	pixFinished = new QPixmap(path + "/images/scriptGrey32.png");
	ShowPlanItem::init();
}

