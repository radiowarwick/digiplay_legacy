#include <iostream>
using namespace std;

#include <qstring.h>
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

ShowPlanItem::ShowPlanItem( QListView *parent, QListViewItem *after,
		QString txtTitle, QString txtArtist, QString txtLength, 
		QString txtTime ) 
		: QListViewItem(parent, after, txtTitle, txtArtist, txtLength, txtTime) {
	rootElement = false;
	setText(0,txtTitle);
	setText(1,txtArtist);
	setText(2,txtLength);
	setText(3,txtTime);
	init();
}

void ShowPlanItem::init() {
	active = false;
	selected = false;
	selectPen = new QPen( black );
	selectPen->setWidth(5);
	unselectPen = new QPen( black );
	selectPen->setWidth(1);
	backColor = new QBrush( red );
	titleFont.setBold(true);
	titleFont.setPointSize(16);
	artistFont.setItalic(true);
	artistFont.setPointSize(14);
	lengthFont.setBold(true);
	lengthFont.setPointSize(16);
	timeFont.setPointSize(14);
}

void ShowPlanItem::setup() {
	QListViewItem::setup();

	QString txtTitle = text(0);
	QString txtArtist = text(1);
	QString txtLength = text(2);
	QString txtTime = text(3);
	if (txtTitle.isEmpty() ){
		if (lblTitle) delete lblTitle;
		if (lblArtist) delete lblArtist;
		if (lblLength) delete lblLength;
		if (lblTime) delete lblTime;
		return;
	}
	
	const QListView *lv = listView();
	active = lv->isActiveWindow();
	selected = isSelected();
	int w = lv->columnWidth(0);
	int r = lv->itemMargin();
	int stepSize = lv->treeStepSize();
	
	const QPixmap *px = pixmap(0);
	int wPix = 0;
	int hPix = 0;
	if (px) {
		wPix = px->width();
		hPix = px->height();
	}	
		
	lblTitle = new QSimpleRichText( txtTitle, titleFont );
	lblTitle->setWidth(w - r - depth()*stepSize - TIME_WIDTH - wPix);
	lblArtist = new QSimpleRichText( txtArtist, artistFont );
	lblArtist->setWidth(w - r - depth()*stepSize - ITEM_INDENT - TIME_WIDTH 
							- wPix);
	lblLength = new QSimpleRichText( txtLength, lengthFont );
	lblLength->setWidth( TIME_WIDTH );
	lblLength->setWidth( QMIN(TIME_WIDTH, lblLength->widthUsed()));
	lblTime = new QSimpleRichText( txtTime, timeFont );
	lblTime->setWidth( TIME_WIDTH );
	lblTime->setWidth( QMIN(TIME_WIDTH, lblTime->widthUsed()));
	
	_widthUsed = lv->width();
	int h = QMAX( QMAX( lblTitle->height() + lblArtist->height(),
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
	
	int r = lv->itemMargin();
	p->setBrush(*backColor);
	p->drawRect(0,0,lv->columnWidth(0),height());
	if (isSelected()) {

	}
	else {

	}

	const QPixmap *px = pixmap( 0 );
	QRect recPix;
	int wPix = 0;
	int hPix = 0;
	if (px) {
		wPix = px->width();
		hPix = px->height();
		recPix = QRect(r, (height() - hPix)/2, wPix, hPix);
	}

	int wLength = lblLength->width();
	int wTime = lblTime->width();
	QRect recTitle(	r + ITEM_INDENT + wPix, 
					r, 
					lv->columnWidth(0) - 2*r - wLength - ITEM_INDENT - wPix, 
					lblTitle->height());
	QRect recArtist(r + 2*ITEM_INDENT + wPix, 
					lblTitle->height() + r, 
					lv->columnWidth(0) - 2*r - 2*ITEM_INDENT - wTime - wPix, 
					lblArtist->height());
	QRect recLength(lv->columnWidth(0) - wLength - r, 
					r, 
					wLength,
					lblLength->height());
	QRect recTime(	lv->columnWidth(0) - wTime - r,
					lblLength->height() + r,
					wTime, 
					lblTime->height());

	lblTitle->draw(p, recTitle.left(), recTitle.top(), recTitle, 
						cg, backColor);
	lblArtist->draw(p, recArtist.left(), recArtist.top(), recArtist, 
						cg, backColor);
	lblLength->draw(p, recLength.left(), recLength.top(), recLength, 
						cg, backColor);
	lblTime->draw(p, recTime.left(), recTime.top(), recTime, 
						cg, backColor);

	QRegion clip(0,0,width, height());
	clip = clip - recTitle - recArtist - recLength - recTime;
	p->setClipRegion(clip, QPainter::CoordPainter);
	p->fillRect(0,0,width, height(), *backColor);

	if (px) {
		p->drawRect(recPix);
		p->drawPixmap(recPix,*px);
	}

	p->restore();
}

