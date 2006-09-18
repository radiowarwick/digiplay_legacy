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

