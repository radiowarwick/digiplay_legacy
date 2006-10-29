/*
 * Show Plan Audio Item
 * ShowPlanAudio.cpp
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

#include "ShowPlanAudio.h"

ShowPlanAudio::ShowPlanAudio( QListView *parent, QListViewItem *after )
		: ShowPlanItem(parent,after) {
	rootElement = true;
	init();
}

ShowPlanAudio::ShowPlanAudio( QListViewItem *parent, QListViewItem *after ) 
		: ShowPlanItem(parent,after) {
	rootElement = false;
	init();
}

ShowPlanAudio::ShowPlanAudio( QListView *parent, QListViewItem *after, track t )
		: ShowPlanItem(parent, after) {
	rootElement = false;
	setText(0,t.title);
	setText(1,t.artist);
	setText(2,dps_prettyTime(t.length_smpl));
	setText(3,"");
	_t = t;
	init();
}

void ShowPlanAudio::init() {
	string path = qApp->applicationDirPath();
	backBrushUnloaded = new QBrush(QColor(0,153,169));
	backBrushLoaded = new QBrush(QColor(0,153,169));
	backBrushFinished = new QBrush(QColor(128,128,128));
	backBrushUnloadedSel = new QBrush(QColor(0,213,229));
	backBrushLoadedSel = new QBrush(QColor(0,213,229));
	backBrushFinishedSel = new QBrush(QColor(188,188,188));
	pixUnloaded = new QPixmap(path + "/images/libTrack32.png");
	pixLoaded = new QPixmap(path + "/images/libTrackLoaded32.png");
	pixFinished = new QPixmap(path + "/images/libTrackGrey32.png");
	ShowPlanItem::init();
}

