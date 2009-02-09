/*
 * Show Plan Item
 * ShowPlanItem.cpp
 * Renders an individual item in the showplan.
 *
 * Copyright (c) 2004-2009 Chris Cantwell
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
#include <string>
using namespace std;

#include <qlistview.h>
#include <qstring.h>
#include <qsimplerichtext.h>
#include <qpainter.h>
#include <qpixmap.h>

#include "ShowPlanItem.h"

ShowPlanItem::ShowPlanItem( QListView * parent, QListViewItem * after,
							const DpsShowItem& pSrc) 
		: QListViewItem		(parent, after),
		  DpsShowItem		(pSrc),
		  mIsRootElement	(true),
		  mIsExpanded		(false) {
	init();
}

ShowPlanItem::ShowPlanItem ( QListView * parent, const DpsShowItem& pSrc) 
		: QListViewItem		(parent),
		  DpsShowItem		(pSrc),
		  mIsRootElement	(true),
		  mIsExpanded		(false) {
	init();
}

ShowPlanItem::~ShowPlanItem() {
	delete lblTitle;
	delete lblComment;
	delete lblLength;
	delete lblTime;
	delete lblAudioTitle;
	delete lblAudioArtist;
	delete lblAudioLength;
	delete lblScriptTitle;
	delete lblScriptLength;
	delete backBrushUnloaded;
	delete backBrushLoaded;
	delete backBrushFinished;
	delete backBrushUnloadedSel;
	delete backBrushLoadedSel;
	delete backBrushFinishedSel;
	delete pixUnloaded;
	delete pixLoaded;
	delete pixFinished;
	delete pixAudio;
	delete pixScript;
	delete selectPen;
	delete unselectPen;
}

void ShowPlanItem::expand() {
	mIsExpanded = !mIsExpanded;
}

#define ITEM_INDENT 5
#define TIME_WIDTH 100
#define PIX_SIZE 50

void ShowPlanItem::init() {
    string path = DPSDIR;
    backBrushUnloaded = new QBrush(QColor(0,153,169));
    backBrushLoaded = new QBrush(QColor(0,153,169));
    backBrushFinished = new QBrush(QColor(128,128,128));
    backBrushUnloadedSel = new QBrush(QColor(0,213,229));
    backBrushLoadedSel = new QBrush(QColor(0,213,229));
    backBrushFinishedSel = new QBrush(QColor(188,188,188));
    pixUnloaded = new QPixmap(path + "/images/music32.png");
    pixLoaded = new QPixmap(path + "/images/musicLoaded32.png");
    pixFinished = new QPixmap(path + "/images/musicGrey32.png");
	pixAudio = new QPixmap(path + "/images/musicLoaded32.png");
	pixScript = new QPixmap(path + "/images/scriptLoaded32.png");

    active = false;
    selected = false;

    lblTitle = 0; 
    lblComment = 0;
    lblLength = 0;
    lblTime = 0;
    lblAudioTitle = 0;
    lblAudioArtist = 0;
    lblAudioLength = 0;
    lblScriptTitle = 0;
    lblScriptLength = 0;

    selectPen = new QPen( black );
    selectPen->setWidth(0); 
    unselectPen = new QPen( black );
    selectPen->setWidth(1);

    titleFont.setBold(true);
    titleFont.setPointSize(16);
    commentFont.setItalic(true);
    commentFont.setPointSize(14);
    lengthFont.setBold(true);
    lengthFont.setPointSize(16);
    timeFont.setPointSize(14);
    detailFont.setBold(true);
    detailFont.setPointSize(10);
}

void ShowPlanItem::setup() {
    QListViewItem::setup();

    const QListView *lv = listView();
    active = lv->isActiveWindow();
    selected = isSelected();
    int w = lv->columnWidth(0);
    int r = lv->itemMargin();
    int stepSize = lv->treeStepSize();

    QPixmap *px = 0;
    switch (getState()) {
        case DpsShowItem::Unloaded:
            px = pixUnloaded;
            break;
        case DpsShowItem::Loaded:
            px = pixLoaded;
            break;
        case DpsShowItem::Finished:
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

    if (lblTitle) delete lblTitle;
    if (lblComment) delete lblComment;
    if (lblLength) delete lblLength;
    if (lblTime) delete lblTime;
    QString txtTitle = getName();
    QString txtComment = getComment();
    QString txtLength = getLength().getHms();
    QString txtTime = "";
    lblTitle = new QSimpleRichText( txtTitle, titleFont );
    lblTitle->setWidth(w - r - depth()*stepSize - TIME_WIDTH - wPix);
    lblComment = new QSimpleRichText( txtComment, commentFont );
    lblComment->setWidth(w - r - depth()*stepSize - ITEM_INDENT - TIME_WIDTH
                            - wPix);
    lblLength = new QSimpleRichText( txtLength, lengthFont );
    lblLength->setWidth( TIME_WIDTH );
    lblLength->setWidth( QMIN(TIME_WIDTH, lblLength->widthUsed()));
    lblTime = new QSimpleRichText( txtTime, timeFont );
    lblTime->setWidth( TIME_WIDTH );
    lblTime->setWidth( QMIN(TIME_WIDTH, lblTime->widthUsed()));
	if (hasAudio()) {
		if (lblAudioTitle) delete lblAudioTitle;
		if (lblAudioArtist) delete lblAudioArtist;
		if (lblAudioLength) delete lblAudioLength;
		QString txtAudioTitle = getAudioItem()["title"];
		QString txtAudioArtist = getAudioItem()["artist"];
		QString txtAudioLength = getAudioItem().getLength().getHms();
		lblAudioTitle = new QSimpleRichText( txtAudioTitle, detailFont);
		lblAudioTitle->setWidth(w-r-depth()*stepSize - ITEM_INDENT - TIME_WIDTH
							- wPix);
		lblAudioArtist = new QSimpleRichText( txtAudioArtist, detailFont);
		lblAudioArtist->setWidth(w-r-depth()*stepSize - ITEM_INDENT - TIME_WIDTH
							- wPix);
		lblAudioLength = new QSimpleRichText( txtAudioLength, detailFont);
		lblAudioLength->setWidth( TIME_WIDTH );
		lblAudioLength->setWidth( QMIN(TIME_WIDTH, lblAudioLength->widthUsed()));
	}
	if (hasScript()) {
		if (lblScriptTitle) delete lblScriptTitle;
		if (lblScriptLength) delete lblScriptLength;
		QString txtScriptTitle = getScriptItem().getTitle();
		QString txtScriptLength = getScriptItem().getLength().getHms();
		lblScriptTitle = new QSimpleRichText( txtScriptTitle, detailFont);
		lblScriptTitle->setWidth(w-r-depth()*stepSize - ITEM_INDENT - TIME_WIDTH
							- wPix);
		lblScriptLength = new QSimpleRichText( txtScriptLength, detailFont);
		lblScriptLength->setWidth( TIME_WIDTH );
		lblScriptLength->setWidth( QMIN(TIME_WIDTH, 
												lblScriptLength->widthUsed()));
	}
	
    mWidthUsed = lv->width();
    int h = 0;
    int totalHeightText = 0;
    int totalHeightLength = 0;
    totalHeightText = lblTitle->height() + lblComment->height();
    totalHeightLength = lblLength->height() + lblTime->height();
    if (hasAudio()) {
    	totalHeightText += QMAX(hPix, 
    					lblAudioTitle->height() + lblAudioArtist->height());
    	totalHeightLength += lblAudioLength->height();
    }
    if (hasScript()) {
    	totalHeightText += QMAX(hPix, lblScriptTitle->height());
    	totalHeightLength += lblScriptLength->height();
    }
    if ( mIsExpanded ) {
    	h = QMAX( QMAX( totalHeightText, totalHeightLength ), hPix ) + 2*r;    	
    }
    else {
    	h = QMAX( QMAX( lblTitle->height() + lblComment->height(),
                lblLength->height() + lblTime->height() ),
            hPix ) + 2*r;
    }
    if (h % 2 > 0) h++;
    setHeight( h );
}

void ShowPlanItem::paintCell(QPainter *p, const QColorGroup &cg, int column,
                                int width, int align) {
    if (!lblTitle) {
        QListViewItem::paintCell(p,cg,column,width,align);
        return;
    }
    if (!p) {
    	cout << "No painter!" << endl;
    	return;
    }
    p->save();

    QListView *lv = listView();
    if (isSelected() != selected || lv->isActiveWindow() != active) {
        setup();
    }

    QPixmap *px = 0;
    QPixmap *pxAudio = 0;
    QPixmap *pxScript = 0;
    QBrush *backBrush, *backBrushSel;
    QRect recPix;
    int wPix = 0;
    int hPix = 0;
    int wLength = lblLength->width();
    int wTime = lblTime->width();
    int r = lv->itemMargin();

    switch (getState()) {
        case DpsShowItem::Unloaded:
            px = pixUnloaded;
            backBrush = backBrushUnloaded;
            backBrushSel = backBrushUnloadedSel;
            break;
        case DpsShowItem::Loaded:
            px = pixLoaded;
            backBrush = backBrushLoaded;
            backBrushSel = backBrushLoadedSel;
            break;
        case DpsShowItem::Finished:
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
    if (hasAudio()) {
    	pxAudio = pixAudio;
    }
    if (hasScript()) {
    	pxScript = pixScript;
    }
    if (selected) backBrush = backBrushSel;

    if (px) {
        wPix = px->width();
        hPix = px->height();
        recPix = QRect(r, r, wPix, hPix);
    }
	
	// Set up clipping and draw labels    
    int top = r;
    QRegion clip(0,0,width, height());
    QRect recTitle( r + ITEM_INDENT + wPix, top,
                    lv->columnWidth(0) - 2*r - wLength - ITEM_INDENT - wPix,
                    lblTitle->height());
    QRect recLength(lv->columnWidth(0) - 15 - wLength - r, top,
                    wLength,
                    lblLength->height());
	top += lblTitle->height();
    QRect recComment(r + 2*ITEM_INDENT + wPix, top,
                    lv->columnWidth(0) - 2*r - 2*ITEM_INDENT - wTime - wPix,
                    lblComment->height());
    QRect recTime(  lv->columnWidth(0) - 15 - wTime - r, top,
                    wTime,
                    lblTime->height());
	top += lblComment->height();
		
	lblTitle->draw(p, recTitle.left(), recTitle.top(), recTitle,
                        cg, backBrush);
    lblComment->draw(p, recComment.left(), recComment.top(), recComment,
                        cg, backBrush);
    lblLength->draw(p, recLength.left(), recLength.top(), recLength,
                        cg, backBrush);
    lblTime->draw(p, recTime.left(), recTime.top(), recTime,
                        cg, backBrush);
    clip = clip - recTitle - recComment - recLength - recTime;
    
    if (mIsExpanded && hasAudio()) {
    	QRect recAudioTitle( r + ITEM_INDENT + 2*wPix, top,
    				lv->columnWidth(0) - 2*r - wLength - ITEM_INDENT - wPix,
    				lblAudioTitle->height());
		QRect recAudioLength( lv->columnWidth(0) - 15 - wLength - r, top,
					wLength,
					lblAudioLength->height());
		QRect recAudioArtist( r + ITEM_INDENT + 2*wPix, 
					top + lblAudioTitle->height(),
					lv->columnWidth(0) - 2*r - wLength - ITEM_INDENT - wPix,
					lblAudioArtist->height());
		
		top += QMAX(pxAudio->height(), 
					lblAudioTitle->height() + lblAudioArtist->height());
		
		lblAudioTitle->draw(p, recAudioTitle.left(), recAudioTitle.top(),
							recAudioTitle, cg, backBrush);
		lblAudioArtist->draw(p, recAudioArtist.left(), recAudioArtist.top(),
							recAudioArtist, cg, backBrush);
		lblAudioLength->draw(p, recAudioLength.left(), recAudioLength.top(),
							recAudioLength, cg, backBrush);
		clip = clip - recAudioTitle - recAudioLength - recAudioArtist;
    }
    if (mIsExpanded && hasScript()) {
    	QRect recScriptTitle( r + ITEM_INDENT + 2*wPix, top,
    				lv->columnWidth(0) - 2*r - wLength - ITEM_INDENT - wPix,
    				lblScriptTitle->height());
    	QRect recScriptLength( lv->columnWidth(0) - 15 - wLength - r, top,
    				wLength,
    				lblScriptLength->height());
    				
    	top += QMAX(pxScript->height(), lblScriptTitle->height());
    	
    	lblScriptTitle->draw(p, recScriptTitle.left(), recScriptTitle.top(),
    						recScriptTitle, cg, backBrush);
    	lblScriptLength->draw(p, recScriptLength.left(), recScriptLength.top(),
    						recScriptLength, cg, backBrush);
    	clip = clip - recScriptTitle - recScriptLength;
    }
    p->setClipRegion(clip, QPainter::CoordPainter);
    p->fillRect(0,0,width, height(), *backBrush);

    if (selected) {
        p->setPen(Qt::red);
        p->drawRect(0,0,width-1,height());
    }

    if (px) {
        p->drawPixmap(recPix,*px);
    }
   	
   	top = lblTitle->height() + lblComment->height();
    if (mIsExpanded && pxAudio) {
    	p->drawPixmap(QRect(wPix + r, top, wPix, hPix), *pxAudio);
    	top += lblAudioTitle->height() + lblAudioArtist->height();
    }
    if (mIsExpanded && pxScript) {
    	p->drawPixmap(QRect(wPix + r, top, wPix, hPix), *pxScript);
    }
    p->restore();
}
