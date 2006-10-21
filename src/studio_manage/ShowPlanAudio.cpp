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
	backBrushUnloadedSel = new QBrush(QColor(0,163,179));
	backBrushLoadedSel = new QBrush(QColor(0,163,179));
	backBrushFinishedSel = new QBrush(QColor(188,188,188));
	pixUnloaded = new QPixmap(path + "/images/libTrack32.png");
	pixLoaded = new QPixmap(path + "/images/libTrackLoaded32.png");
	pixFinished = new QPixmap(path + "/images/libTrackGrey32.png");
	ShowPlanItem::init();
}

