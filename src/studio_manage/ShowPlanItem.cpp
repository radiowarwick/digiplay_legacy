/*
 * Show Plan Item Base class
 * ShowPlanItem.cpp
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
#include <iostream>
using namespace std;

#include <qstring.h>
#include <qsimplerichtext.h>
#include <qpainter.h>
#include <qpixmap.h>

#include "ShowPlanItem.h"

#define ITEM_INDENT 5
#define TIME_WIDTH 100
#define PIX_SIZE 50

ShowPlanItem::ShowPlanItem( QListView *parent, QListViewItem *after )
		: QListViewItem(parent,after) {
	rootElement = true;
	init();
}

ShowPlanItem::ShowPlanItem( QListViewItem *parent, QListViewItem *after ) 
		: QListViewItem(parent,after) {
	rootElement = false;
	init();
}

void ShowPlanItem::init() {
	active = false;
	selected = false;
	_state = SHOWPLAN_STATE_UNLOADED;

    lblTitle = 0;
    lblSubtitle = 0;
    lblLength = 0;
    lblTime = 0;

	selectPen = new QPen( black );
	selectPen->setWidth(0);
	unselectPen = new QPen( black );
	selectPen->setWidth(1);
	
	titleFont.setBold(true);
	titleFont.setPointSize(16);
	subtitleFont.setItalic(true);
	subtitleFont.setPointSize(14);
	lengthFont.setBold(true);
	lengthFont.setPointSize(16);
	timeFont.setPointSize(14);
}

void ShowPlanItem::setup() {
	QListViewItem::setup();

	QString txtTitle = text(0);
	QString txtSubtitle = text(1);
	QString txtLength = text(2);
	QString txtTime = text(3);
	if (lblTitle) delete lblTitle;
	if (lblSubtitle) delete lblSubtitle;
	if (lblLength) delete lblLength;
	if (lblTime) delete lblTime;
	
	const QListView *lv = listView();
	active = lv->isActiveWindow();
	selected = isSelected();
	int w = lv->columnWidth(0);
	int r = lv->itemMargin();
	int stepSize = lv->treeStepSize();

	QPixmap *px = 0;
	switch (_state) {
		case SHOWPLAN_STATE_UNLOADED:
			px = pixUnloaded;
			break;
		case SHOWPLAN_STATE_LOADED:
			px = pixLoaded;
			break;
		case SHOWPLAN_STATE_FINISHED:
			px = pixFinished;
			break;
        default:
            px = pixUnloaded;
            break;
	}

	int wPix = 0;
	int hPix = 0;
	if (px) {
		wPix = px->width();
		hPix = px->height();
	}	
		
	lblTitle = new QSimpleRichText( txtTitle, titleFont );
	lblTitle->setWidth(w - r - depth()*stepSize - TIME_WIDTH - wPix);
	lblSubtitle = new QSimpleRichText( txtSubtitle, subtitleFont );
	lblSubtitle->setWidth(w - r - depth()*stepSize - ITEM_INDENT - TIME_WIDTH 
							- wPix);
	lblLength = new QSimpleRichText( txtLength, lengthFont );
	lblLength->setWidth( TIME_WIDTH );
	lblLength->setWidth( QMIN(TIME_WIDTH, lblLength->widthUsed()));
	lblTime = new QSimpleRichText( txtTime, timeFont );
	lblTime->setWidth( TIME_WIDTH );
	lblTime->setWidth( QMIN(TIME_WIDTH, lblTime->widthUsed()));
	
	_widthUsed = lv->width();
	int h = QMAX( QMAX( lblTitle->height() + lblSubtitle->height(),
				lblLength->height() + lblTime->height() ),
			hPix ) + 2*r;
	if (h % 2 > 0) h++;
	setHeight( h );
}

void ShowPlanItem::paintCell(QPainter *p, const QColorGroup &cg, int column,
								int width, int align) {
	if (!lblTitle) {
		QListViewItem::paintCell(p,cg,column,width,align);
		return;
	}

	p->save();

	QListView *lv = listView();
	if (isSelected() != selected || lv->isActiveWindow() != active) {
		setup();
	}

	QPixmap *px = 0;
	QBrush *backBrush, *backBrushSel;
	QRect recPix;
	int wPix = 0;
	int hPix = 0;
	int wLength = lblLength->width();
	int wTime = lblTime->width();
	int r = lv->itemMargin();
	
	switch (_state) {
		case SHOWPLAN_STATE_UNLOADED:
			px = pixUnloaded;
			backBrush = backBrushUnloaded;
			backBrushSel = backBrushUnloadedSel;
			break;
		case SHOWPLAN_STATE_LOADED:
			px = pixLoaded;
			backBrush = backBrushLoaded;
			backBrushSel = backBrushLoadedSel;
			break;
		case SHOWPLAN_STATE_FINISHED:
			px = pixFinished;
			backBrush = backBrushFinished;
			backBrushSel = backBrushFinishedSel;
			break;
		default:
            px = pixUnloaded;
			backBrush = backBrushUnloaded;
			backBrushSel = backBrushUnloadedSel;
			break;
	}
	if (selected) backBrush = backBrushSel;
	
	if (px) {
		wPix = px->width();
		hPix = px->height();
		recPix = QRect(r, (height() - hPix)/2, wPix, hPix);
	}
	
	QRect recTitle(	r + ITEM_INDENT + wPix, 
					r, 
					lv->columnWidth(0) - 2*r - wLength - ITEM_INDENT - wPix, 
					lblTitle->height());
	QRect recSubtitle(r + 2*ITEM_INDENT + wPix, 
					lblTitle->height() + r, 
					lv->columnWidth(0) - 2*r - 2*ITEM_INDENT - wTime - wPix, 
					lblSubtitle->height());
	QRect recLength(lv->columnWidth(0) - 15 - wLength - r, 
					r, 
					wLength,
					lblLength->height());
	QRect recTime(	lv->columnWidth(0) - 15 - wTime - r,
					lblLength->height() + r,
					wTime, 
					lblTime->height());

	lblTitle->draw(p, recTitle.left(), recTitle.top(), recTitle, 
						cg, backBrush);
	lblSubtitle->draw(p, recSubtitle.left(), recSubtitle.top(), recSubtitle, 
						cg, backBrush);
	lblLength->draw(p, recLength.left(), recLength.top(), recLength, 
						cg, backBrush);
	lblTime->draw(p, recTime.left(), recTime.top(), recTime, 
						cg, backBrush);

	QRegion clip(0,0,width, height());
	clip = clip - recTitle - recSubtitle - recLength - recTime;
	p->setClipRegion(clip, QPainter::CoordPainter);
	p->fillRect(0,0,width, height(), *backBrush);

	if (selected) {
		p->setPen(Qt::red);
		p->drawRect(0,0,width-1,height());	
	}

	if (px) {
		p->drawPixmap(recPix,*px);
	}

	p->restore();
}

