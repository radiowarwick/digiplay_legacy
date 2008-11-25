/*
 * Showplan Widget
 * Showplan.cpp
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
#include <cstdlib>

#include <qapplication.h>
#include <qgroupbox.h>
#include <qheader.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qstring.h>
#include <qsimplerichtext.h>
#include <qpainter.h>
#include <qpixmap.h>

#include "DpsObject.h"
#include "dps.h"
#include "Logger.h"
#include "Auth.h"
#include "dlgWarn.h"

#include "Showplan.h"

/* =======================================================================
 * Showplan
 * =======================================================================
 */
Showplan::Showplan(QWidget *parent, const char* name) 
        : QWidget(parent, name) {
    activePoint = 0;
    selectedItem = 0;
    draw();

    conf = new Config("digiplay",this);
}

Showplan::~Showplan() {
    clean();
}

void Showplan::configure(Auth *authModule) {
    const char* routine = "Showplan::configure";
    if (!authModule) {
        L_WARNING(LOG_TAB,"authModule isn't defined. Can't configure Tab.");
        return;
    }
    // TODO: add any user dependant stuff here
}

void Showplan::onMessage() {
    const char* routine = "Showplan::onMessage";
	L_INFO(LOG_DB,"Showplan received message");
	activePointLock.lock();
    if (conf->getParam("next_on_showplan") == ""
                        && lstShowPlan->childCount() > 0
                        && activePoint != lstShowPlan->lastItem()) {
        L_INFO(LOG_DB,"Processing track load event");
        if (activePoint == 0) {
            activePoint = (ShowPlanItem*)lstShowPlan->firstChild();
        }
        else {
            activePoint->setState(SHOWPLAN_STATE_FINISHED);
            activePoint = (ShowPlanItem*)activePoint->nextSibling();
			// while we have a script selected...
//            while (activePoint->getType() == 1
//                    && activePoint != lstShowPlan->lastItem()) {
//                activePoint = (ShowPlanItem*)activePoint->nextSibling();
//            }
        }
        activePoint->setState(SHOWPLAN_STATE_LOADED);
        lstShowPlan->ensureItemVisible(activePoint);
        if (lstShowPlan->selectedItem()) {
            selectionChanged(lstShowPlan->selectedItem());
        }

        activePointLock.unlock();
    	L_INFO(LOG_DB,"Configuration refresh complete.");
        
		L_INFO(LOG_DB,"Triggering update of next_on_showplan entry");
        updateNextTrack();
    }
	else {
		activePointLock.unlock();
	}	
	L_INFO(LOG_DB,"Finished Showplan onMessage");
}


void Showplan::loadShowplan(DpsShowplan& S) {
    clear(false);
    
    lstShowPlan->setUpdatesEnabled(false);
    for (unsigned int i = 0; i < S.size(); i++) {
        switch (S[i].getType()) {
            case DPS_SHOWTRACK:
            case DPS_SHOWJINGLE:
            case DPS_SHOWADVERT:
                new ShowPlanAudio( lstShowPlan, lstShowPlan->lastItem(), S[i]);
                break;
            case DPS_SHOWSCRIPT:
                new ShowPlanScript( lstShowPlan, lstShowPlan->lastItem(), S[i]);
                break;
            case DPS_SHOWNOTE:
                new ShowPlanNote( lstShowPlan, lstShowPlan->lastItem(), S[i]);
                break;
            default:
                break;
        }
    }
    lstShowPlan->setUpdatesEnabled(true);
    lstShowPlan->repaint();
    updateNextTrack();
}

DpsShowplan Showplan::getShowplan() {
    DpsShowplan S;
    if (lstShowPlan->childCount() == 0) return S;
    // TODO: Add code to generate DpsShowplan from our lstShowPlan
    return S;
}

void Showplan::setGeometry(const QRect& r) {
    QWidget::setGeometry(r);
    if (grpFrame) grpFrame->setGeometry(r);
}

void Showplan::resizeEvent(QResizeEvent *e) {
    if (!e) return;
    setUpdatesEnabled(false);
    clean();
    draw();
    setUpdatesEnabled(true);
    repaint();
    // TODO: Replace this with proper resize code
}

void Showplan::addTrack(QString id) {
    const char *routine = "Showplan::addTrack";
    L_INFO(LOG_SHOWPLAN,"Adding to showplan " + id);
    DpsShowTrack x(id);
    new ShowPlanAudio( lstShowPlan, lstShowPlan->lastItem(), x);
    L_INFO(LOG_DB,"Triggering update of next_on_showplan entry");
    updateNextTrack();
    L_INFO(LOG_DB,"Playlist add complete.");
}

void Showplan::addJingle(QString id) {
    const char *routine = "Showplan::addJingle";
    L_INFO(LOG_SHOWPLAN,"Adding to showplan " + id);
    DpsShowJingle x(id);
    new ShowPlanAudio( lstShowPlan, lstShowPlan->lastItem(), x);
    L_INFO(LOG_DB,"Triggering update of next_on_showplan entry");
    updateNextTrack();
    L_INFO(LOG_DB,"Playlist add complete.");
}

void Showplan::addAdvert(QString id) {
    const char *routine = "Showplan::addAdvert";
    L_INFO(LOG_SHOWPLAN,"Adding to showplan " + id);
    DpsShowAdvert x(id);
    new ShowPlanAudio( lstShowPlan, lstShowPlan->lastItem(), x);
    L_INFO(LOG_DB,"Triggering update of next_on_showplan entry");
    updateNextTrack();
    L_INFO(LOG_DB,"Playlist add complete.");
}

void Showplan::addScript(DpsShowScript& S) {
    const char *routine = "Showplan::addScript";
    L_INFO(LOG_SHOWPLAN,"Adding to showplan " + S["name"]);
    new ShowPlanScript( lstShowPlan, lstShowPlan->lastItem(), S);
    L_INFO(LOG_DB,"Playlist add complete.");
}

void Showplan::addNote(DpsShowNote& N) {
    const char* routine = "Showplan::addNote";
    L_INFO(LOG_SHOWPLAN,"Adding note to showplan");
    new ShowPlanNote( lstShowPlan, lstShowPlan->lastItem(), N);
    L_INFO(LOG_DB,"Playlist add complete");
}

void Showplan::clear(bool prompt) {
    if (lstShowPlan->childCount() == 0) return;
    if (prompt) {
        dlgWarn *dlg = new dlgWarn(this, "");
        dlg->setTitle("Clear All");
        dlg->setWarning("Are you sure you wish to clear the show plan?");
        if ( dlg->exec() != QDialog::Accepted ){
            delete dlg;
            return;
        }
        delete dlg;
    }
    selectionChanged(0);
    lstShowPlan->clear();
	activePointLock.lock();
    activePoint = 0;
	activePointLock.unlock();
    updateNextTrack();
}

void Showplan::remove() {
    if (lstShowPlan->childCount() == 0) return;
    QListViewItem *x = lstShowPlan->selectedItem();
    QListViewItem *y;
    // Check something is selected.
    if ( x ) {
        // Get the next item
        y = x->nextSibling();
        // If we're not at the end of the list, select the next item
        if ( y ) {
            lstShowPlan->setSelected(y,true);
        }
        // Otherwise get the item before the selected item
        else {
            y = lstShowPlan->lastItem()->itemAbove();
            // If there is such an item, select it, otherwise y is 0
            if ( y ) {
                lstShowPlan->setSelected(y,true);
            }
        }
        // Change selection to the new item
        selectionChanged(y);
        // Delete the originally selected item
        delete x;
    }
    // Update the next track (in case we deleted the existing one)
    updateNextTrack();
}

void Showplan::moveUp() {
    if (lstShowPlan->childCount() == 0) return;
    QListViewItem *x = lstShowPlan->selectedItem();
    if ( x ) {
        if (x == lstShowPlan->firstChild()->itemBelow() ) {
            lstShowPlan->takeItem(x);
            lstShowPlan->insertItem(x);
            lstShowPlan->setSelected(x,true);
        }
        else if (x != lstShowPlan->firstChild()) {
            x->moveItem(x->itemAbove()->itemAbove());
        }
        selectionChanged(x);
        updateNextTrack();
    }
}

void Showplan::moveDown() {
    if (lstShowPlan->childCount() == 0) return;
    QListViewItem *x = lstShowPlan->selectedItem();
    if ( x ) {
        if (x != lstShowPlan->lastItem() ) {
            x->moveItem(x->itemBelow());
            lstShowPlan->setSelected(x,true);
            selectionChanged(x);
            updateNextTrack();
        }
    }
}

void Showplan::moveTop() {
    if (lstShowPlan->childCount() == 0) return;
    QListViewItem *x = lstShowPlan->selectedItem();
    if ( x && x != lstShowPlan->firstChild()) {
        if (!activePoint) {
            lstShowPlan->takeItem(x);
            lstShowPlan->insertItem(x);
        }
        else {
            x->moveItem(activePoint);
        }
        lstShowPlan->setSelected(x,true);
        selectionChanged(x);
        updateNextTrack();
    }
}

void Showplan::moveBottom() {
    if (lstShowPlan->childCount() == 0) return;
    QListViewItem *x = lstShowPlan->selectedItem();
    if ( x ) {
        x->moveItem(lstShowPlan->lastItem());
        lstShowPlan->setSelected(lstShowPlan->lastItem(),true);
        selectionChanged(x);
        updateNextTrack();
    }
}

void Showplan::clicked(QListViewItem *x) {
    // if no item is clicked, then there should now be nothing selected
    // so disable all the appropriate buttons
    if (x == 0) {
        btnMoveBottom->setEnabled(false);
        btnMoveDown->setEnabled(false);
        btnMoveUp->setEnabled(false);
        btnMoveTop->setEnabled(false);
        btnDelete->setEnabled(false);
        selectionChanged(0);
    }
}

void Showplan::selectionChanged(QListViewItem* x) {
    // Check if the currently selected item is a script
    // Need to clear script tab, and set item to unloaded state.
	if ( selectedItem && selectedItem->getType() == 1 &&
		 	selectedItem->getState() == SHOWPLAN_STATE_LOADED ) {
		emit scriptDeselected();
		selectedItem->setState(SHOWPLAN_STATE_UNLOADED);
	}
    
	// If x is null, we're not having anything selected.
    if ( ! x ) {
        btnMoveUp->setEnabled(false);
        btnMoveDown->setEnabled(false);
        btnMoveTop->setEnabled(false);
        btnMoveBottom->setEnabled(false);
        btnDelete->setEnabled(false);
        selectedItem = 0;
        return;
    }

    // Type cast to a ShowPlanItem.
    ShowPlanItem *y = (ShowPlanItem*)x;

    // If item is unloaded, activate applicable move buttons
    if ( y && y->getState() == SHOWPLAN_STATE_UNLOADED ) {
        ShowPlanItem *z = (ShowPlanItem*)y->itemAbove();
        if ( z && z->getState() == SHOWPLAN_STATE_UNLOADED) {
            btnMoveUp->setEnabled(true);
            btnMoveTop->setEnabled(true);
        }
        else {
            btnMoveUp->setEnabled(false);
            btnMoveTop->setEnabled(false);
        }
        if ( y == (ShowPlanItem*)lstShowPlan->lastItem() ) {
            btnMoveBottom->setEnabled(false);
            btnMoveDown->setEnabled(false);
        }
        else {
            btnMoveBottom->setEnabled(true);
            btnMoveDown->setEnabled(true);
        }
        btnDelete->setEnabled(true);
        // If item is a script, load the script into the script tab
        // Then set item as loaded.
		if (y->getType() == 1) {
			ShowPlanScript *s = (ShowPlanScript*)y;
			emit scriptSelected( s->getScript().getId() );
			y->setState( SHOWPLAN_STATE_LOADED );
		}
        // Change the selected item pointer to the new item.
		selectedItem = y;
    }
    else //item has already been loaded so disable all buttons
    {
        btnMoveUp->setEnabled(false);
        btnMoveDown->setEnabled(false);
        btnMoveTop->setEnabled(false);
        btnMoveBottom->setEnabled(false);
        btnDelete->setEnabled(false);
    }
}

void Showplan::scriptDone() {
	if ( selectedItem && selectedItem->getType() == 1 &&
		 	selectedItem->getState() == SHOWPLAN_STATE_LOADED ) {
		emit scriptDeselected();
		selectedItem->setState(SHOWPLAN_STATE_FINISHED);
	}
}

void Showplan::updateNextTrack() {
    activePointLock.lock();
    ShowPlanItem *x = 0;
    if (lstShowPlan->childCount() == 0) {
		conf->setParam("next_on_showplan","");
		activePointLock.unlock();
		return;
	}


    if ( ! activePoint ) {
        x = (ShowPlanItem*)lstShowPlan->firstChild();
    }
    else {
        x = (ShowPlanItem*)activePoint->nextSibling();
    }

    if ( x ) {
        do
            if (x->getType() == 0) {
                ShowPlanAudio *audio = (ShowPlanAudio*)x;
                DpsShowItem t = audio->getTrack();
                conf->setParam("next_on_showplan",t["md5"]);
				activePointLock.unlock();
                return;
            }
        while ((x = (ShowPlanItem*)x->nextSibling()) != 0);
    }
    activePointLock.unlock();
}

void Showplan::draw() {
    QString path = DPSDIR;
    
    grpFrame = new QGroupBox( this, "grpShowplan" );
    grpFrame->setGeometry( QRect( 0, 0, 470, 670 ) );
    QFont grpFrame_font(  grpFrame->font() );
    grpFrame_font.setFamily( "Sans Serif" );
    grpFrame_font.setPointSize( 16 );
    grpFrame_font.setBold( TRUE );
    grpFrame->setFont( grpFrame_font );
    grpFrame->setFrameShadow( QGroupBox::Sunken );
    grpFrame->setLineWidth( 1 );
    grpFrame->setFlat( FALSE );
    grpFrame->setTitle( "Showplan" );
    
    lstShowPlan = new QListView( grpFrame, "lstShowPlan" );
    lstShowPlan->addColumn( tr( "Item" ) ); 
    lstShowPlan->header()->setClickEnabled( FALSE, 
            lstShowPlan->header()->count() - 1 );
    lstShowPlan->header()->setResizeEnabled( FALSE, 
            lstShowPlan->header()->count() - 1 );
    lstShowPlan->setGeometry( QRect( 10, 20, 450, 580 ) );
    lstShowPlan->setPaletteBackgroundColor( QColor( 255, 255, 255 ) );
    QFont lstShowPlan_font(  lstShowPlan->font() );
    lstShowPlan_font.setPointSize( 10 );
    lstShowPlan_font.setBold( FALSE );
    lstShowPlan->setFont( lstShowPlan_font );  
    lstShowPlan->setFrameShape( QListView::Box ); 
    lstShowPlan->setFrameShadow( QListView::Plain );
    lstShowPlan->setVScrollBarMode( QListView::AlwaysOn );
    lstShowPlan->setHScrollBarMode( QListView::AlwaysOff );
    lstShowPlan->setAllColumnsShowFocus( TRUE );
    lstShowPlan->setResizeMode( QListView::NoColumn );
    lstShowPlan->setColumnWidth(0,lstShowPlan->width() - 5);
    lstShowPlan->setSorting(-1);
    lstShowPlan->header()->hide();
    
    btnMoveTop = new QPushButton( grpFrame, "btnMoveTop" );
    btnMoveTop->setGeometry( QRect( 10, 600, 75, 60 ) );
    btnMoveTop->setEnabled( FALSE );
    btnMoveTop->setPixmap(QPixmap(path + "/images/movetop32.png"));

    btnMoveUp = new QPushButton( grpFrame, "btnMoveUp" );
    btnMoveUp->setGeometry( QRect( 85, 600, 75, 60 ) );
    btnMoveUp->setEnabled( FALSE );
    btnMoveUp->setPixmap(QPixmap(path + "/images/moveup32.png"));

    btnDelete = new QPushButton( grpFrame, "btnDelete" );
    btnDelete->setGeometry( QRect( 160, 600, 75, 60 ) );
    btnDelete->setEnabled( FALSE );
    btnDelete->setPixmap(QPixmap(path + "/images/delete48.png"));
    
    btnClear = new QPushButton( grpFrame, "btnClear" );
    btnClear->setGeometry( QRect( 235, 600, 75, 60 ) );
    btnClear->setPixmap(QPixmap(path + "/images/clear32.png"));

    btnMoveBottom = new QPushButton( grpFrame, "btnMoveBottom" );
    btnMoveBottom->setGeometry( QRect( 385, 600, 75, 60 ) );
    btnMoveBottom->setEnabled( FALSE );
    btnMoveBottom->setPixmap(QPixmap(path + "/images/movebottom32.png"));

    btnMoveDown = new QPushButton( grpFrame, "btnMoveDown" );
    btnMoveDown->setGeometry( QRect( 310, 600, 75, 60 ) );
    btnMoveDown->setEnabled( FALSE );
    btnMoveDown->setPixmap(QPixmap(path + "/images/movedown32.png"));

    connect( btnDelete, SIGNAL( clicked() ),        this, SLOT( remove() ));
    connect( btnMoveBottom, SIGNAL( clicked() ),    this, SLOT( moveBottom() ));
    connect( btnMoveDown, SIGNAL( clicked() ),      this, SLOT( moveDown() ));
    connect( btnMoveTop, SIGNAL( clicked() ),       this, SLOT( moveTop() ));
    connect( btnMoveUp, SIGNAL( clicked() ),        this, SLOT( moveUp() ));
    connect( btnClear, SIGNAL( clicked() ),         this, SLOT( clear() ));
    connect( lstShowPlan, SIGNAL( selectionChanged(QListViewItem*) ),
                this, SLOT( selectionChanged(QListViewItem*) ));
    connect( lstShowPlan, SIGNAL( clicked(QListViewItem*) ),
                this, SLOT( clicked(QListViewItem*) ));
}

void Showplan::clean() {
    delete grpFrame;
}


/* =======================================================================
 * ShowPlanItem
 * =======================================================================
 */
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
    
    QRect recTitle( r + ITEM_INDENT + wPix,
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
    QRect recTime(  lv->columnWidth(0) - 15 - wTime - r,
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


/* =======================================================================
 * ShowPlanAudio
 *  - derived from ShowPlanItem
 * =======================================================================
 */
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

ShowPlanAudio::ShowPlanAudio( QListView *parent, QListViewItem *after, 
        DpsShowItem& t ) : ShowPlanItem(parent, after) {
    const char *routine = "ShowPlanAudio::ShowPlanAudio";
    rootElement = false;
    setText(0,t["title"]);
    setText(2,dps_prettyTime(atoi(t["end_smpl"].c_str()) 
                             - atoi(t["start_smpl"].c_str())));
    switch (t.getType()) {
        case DPS_SHOWTRACK:
            setText(1,t["artist"]);
            break;
        case DPS_SHOWJINGLE:
            setText(1,t["pkg"]);
            break;
        case DPS_SHOWADVERT:
            setText(1,t["company"]);
            break;
        default:
            L_WARNING(LOG_SHOWPLAN, "Unknown type: " + t.getType());
            break;
    }
    setText(3,"");
    _t = t;
    init();
}

void ShowPlanAudio::init() {
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
    ShowPlanItem::init();
}


/* =======================================================================
 * ShowPlanScript
 *  - derived from ShowPlanItem
 * =======================================================================
 */
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

ShowPlanScript::ShowPlanScript( QListView *parent, QListViewItem *after,        DpsShowItem& s )
        : ShowPlanItem(parent, after) {
    if (s.getType() != DPS_SHOWSCRIPT) throw;
    rootElement = false;
    setText(0,s["name"]);
    setText(1,s["creator"]);
    setText(2,dps_prettyTime(atoi(s["length"].c_str())));
    setText(3,"");
    _s = s;
    init();
}

void ShowPlanScript::init() {
    string path = DPSDIR;
    backBrushUnloaded = new QBrush(QColor(0,173,189));
    backBrushLoaded = new QBrush(QColor(0,173,189));
    backBrushFinished = new QBrush(QColor(148,148,148));
    backBrushUnloadedSel = new QBrush(QColor(0,233,249));
    backBrushLoadedSel = new QBrush(QColor(0,233,249));
    backBrushFinishedSel = new QBrush(QColor(208,208,208));
    pixUnloaded = new QPixmap(path + "/images/script32.png");
    pixLoaded = new QPixmap(path + "/images/scriptLoaded32.png");
    pixFinished = new QPixmap(path + "/images/scriptGrey32.png");
    ShowPlanItem::init();
}


/* =======================================================================
 * ShowPlanNote
 *  - derived from ShowPlanItem
 * =======================================================================
 */
ShowPlanNote::ShowPlanNote( QListView *parent, QListViewItem *after )
        : ShowPlanItem(parent,after) {
    rootElement = true;
    init();
}

ShowPlanNote::ShowPlanNote( QListViewItem *parent, QListViewItem *after )
        : ShowPlanItem(parent,after) {
    rootElement = false;
    init();
}

ShowPlanNote::ShowPlanNote( QListView *parent, QListViewItem *after,        DpsShowItem& n )
        : ShowPlanItem(parent, after) {
    if (n.getType() != DPS_SHOWNOTE) throw;
    rootElement = false;
    setText(0,n["comment"]);
    setText(1,"");
    setText(2,"");
    setText(3,"");
    _n = n;
    init();
}

void ShowPlanNote::init() {
    string path = DPSDIR;
    backBrushUnloaded = new QBrush(QColor(0,103,209));
    backBrushLoaded = new QBrush(QColor(0,103,209));
    backBrushFinished = new QBrush(QColor(168,168,168));
    backBrushUnloadedSel = new QBrush(QColor(0,153,255));
    backBrushLoadedSel = new QBrush(QColor(0,153,255));
    backBrushFinishedSel = new QBrush(QColor(228,228,228));
    pixUnloaded = new QPixmap(path + "/images/script32.png");
    pixLoaded = new QPixmap(path + "/images/scriptLoaded32.png");
    pixFinished = new QPixmap(path + "/images/scriptGrey32.png");
    ShowPlanItem::init();
}

