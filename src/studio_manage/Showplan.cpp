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
#include <vector>
#include <algorithm>

#include <qapplication.h>
#include <qgroupbox.h>
#include <qheader.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qstring.h>
#include <qsimplerichtext.h>
#include <qpainter.h>
#include <qpixmap.h>

#include "dps/Dps.h"
#include "dps.h"
#include "Logger.h"
#include "Auth.h"
#include "dlgWarn.h"

#include "ShowPlanItem.h"

#include "Showplan.h"

Showplan::Showplan(QWidget *parent, const char* name) 
        : QWidget(parent, name),
          mActive		(0),
          mSelected		(0),
          mIsItemActive (false),
          mIsItemSelected (false) {
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
	mLock.lock();
    if (conf->getParam("next_on_showplan") == ""
                        && getSize() > 0
                        && getLastItem().getHash() != mActive) {
        L_INFO(LOG_DB,"Processing track load event");
        if (!mIsItemActive) {
            mActive = getFirstItem().getHash();
        }
        else {
        	getItemByHash(mActive).setState(DpsShowItem::Finished);
            try {
        	   mActive = getNextItem(getItemByHash(mActive)).getHash();
            }
            catch (int e) {
                cout << "Caught exception - no next item." << endl;
            }
			// while we have a script selected...
//            while (activePoint->getType() == 1
//                    && activePoint != lstShowPlan->lastItem()) {
//                activePoint = (ShowPlanItem*)activePoint->nextSibling();
//            }
        }
        getItemByHash(mActive).setState(DpsShowItem::Loaded);
        mIsItemActive = true;
        //??
        lstShowPlan->ensureItemVisible(lstShowPlan->selectedItem());
        //if (lstShowPlan->selectedItem()) {
        //    selectionChanged(lstShowPlan->selectedItem());
        //}
		mLock.unlock();
        showplanUpdated();
    }
	else {
		mLock.unlock();
	}	
	L_INFO(LOG_DB,"Finished Showplan onMessage");
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

void Showplan::load(const DpsShowPlan& pSrc) {
	DpsShowPlan::operator=(pSrc);
}

void Showplan::append(const DpsShowItem& pSrc) {
	DpsShowPlan::append(pSrc);
}

void Showplan::append(const DpsAudioItem& pSrc) {
	DpsShowPlan::append(DpsShowItem(pSrc));
}

void Showplan::append(const DpsScriptItem& pSrc) {
	DpsShowPlan::append(DpsShowItem(pSrc));
}

void Showplan::showplanUpdated() {
	ShowPlanItem * vNew = 0;
	DpsHash vSelectedHash;
	
	if (lstShowPlan->selectedItem()) {
		vSelectedHash = (dynamic_cast<DpsShowItem*>(lstShowPlan->selectedItem()))->getHash();
	}
	
	lstShowPlan->clear();
	for (unsigned int i = 0; i < getSize(); ++i) {
		vNew = new ShowPlanItem(lstShowPlan, vNew, getItem(i));
		if (mIsItemSelected && getItem(i).getHash() == vSelectedHash) {
			lstShowPlan->setSelected(dynamic_cast<QListViewItem*>(vNew), true);
		}
		if (std::find(mExpandedItems.begin(), mExpandedItems.end(), getItem(i).getHash())
				!= mExpandedItems.end()) {
			vNew->expand();
		}
	}
	lstShowPlan->ensureItemVisible(lstShowPlan->selectedItem());
	selectionChanged(lstShowPlan->selectedItem());
	updateNextTrack();
}

void Showplan::removeItem() {
	if (getSize() == 0) return;
	if (!mIsItemSelected) return;
	DpsShowPlan::erase(getItemByHash(mSelected));
}

void Showplan::moveItemUp() {
	if (getSize() == 0) return;
	if (!mIsItemSelected) return;
	moveUp(getItemByHash(mSelected));
}

void Showplan::moveItemDown() {
	if (getSize() == 0) return;
	if (!mIsItemSelected) return;
	moveDown(getItemByHash(mSelected));
}

void Showplan::moveItemTop() {
	if (getSize() == 0) return;
	if (!mIsItemSelected) return;
	moveTop(getItemByHash(mSelected));
}

void Showplan::moveItemBottom() {
	if (getSize() == 0) return;
	if (!mIsItemSelected) return;
	moveBottom(getItemByHash(mSelected));
}

void Showplan::clearItems() {
    mIsItemActive = false;
    mIsItemSelected = false;
	clear();
}

void Showplan::clicked(QListViewItem *x) {
    // if no item is clicked, then there should now be nothing selected
    // so disable all the appropriate buttons
    if (!x) {
        btnMoveBottom->setEnabled(false);
        btnMoveDown->setEnabled(false);
        btnMoveUp->setEnabled(false);
        btnMoveTop->setEnabled(false);
        btnDelete->setEnabled(false);
        selectionChanged(0);
    }
}

void Showplan::doubleClicked(QListViewItem *x, const QPoint& p, int i) {
	if (!x) return;
	DpsHash vH = reinterpret_cast<ShowPlanItem*>(x)->getHash();
	vector<DpsHash>::iterator vHIt;
	if ((vHIt = std::find(mExpandedItems.begin(), mExpandedItems.end(), vH)) 
						== mExpandedItems.end()) {
		mExpandedItems.push_back(vH);
	}
	else {
		mExpandedItems.erase(vHIt);
	}
	showplanUpdated();
}

void Showplan::selectionChanged(QListViewItem* x) {
	// If x is null, we're not having anything selected.
    if ( ! x ) {
        btnMoveUp->setEnabled(false);
        btnMoveDown->setEnabled(false);
        btnMoveTop->setEnabled(false);
        btnMoveBottom->setEnabled(false);
        btnDelete->setEnabled(false);
        mIsItemSelected = false;
        return;
    }

    // Type cast to a ShowPlanItem.
    ShowPlanItem * y = dynamic_cast<ShowPlanItem*>(x);
	if ( ! y ) {
        btnMoveUp->setEnabled(false);
        btnMoveDown->setEnabled(false);
        btnMoveTop->setEnabled(false);
        btnMoveBottom->setEnabled(false);
        btnDelete->setEnabled(false);
		mIsItemSelected = false;
		return;
	}
		
    // If item is unloaded, activate applicable move buttons
    if ( y->getState() == ShowPlanItem::Unloaded ) {
        ShowPlanItem *z = (ShowPlanItem*)x->itemAbove();
        if ( z && z->getState() == ShowPlanItem::Unloaded) {
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
        // Change the selected item pointer to the new item.
		mSelected = y->getHash();
		mIsItemSelected = true;
    }
    else {
    	//item has already been loaded so disable all buttons
        btnMoveUp->setEnabled(false);
        btnMoveDown->setEnabled(false);
        btnMoveTop->setEnabled(false);
        btnMoveBottom->setEnabled(false);
        btnDelete->setEnabled(false);
    }
}

void Showplan::updateNextTrack() {
    mLock.lock();
    if (getSize() == 0) {
		conf->setParam("next_on_showplan","");
		mLock.unlock();
		return;
	}

	DpsShowItem x;
    if ( ! mIsItemActive ) {
        x = getFirstItem();
    }
    else {
        try {
            x = getNextItem(getItemByHash(mActive));
        }
        catch (DpsShowPlan::Error&) {
            mLock.unlock();
            return;
        }
    }

	try {
        while (1) {
        	if ( x.hasAudio() ) {
            	conf->setParam("next_on_showplan", x.getAudioItem()["md5"]);
                break;
        	}
            if (x == getLastItem()) {
                break;
            }
            x = getNextItem(x);
        }
	}
	catch (DpsShowPlan::Error&) {
		
	}

    mLock.unlock();
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
    btnMoveTop->setAutoDefault( FALSE );
    btnMoveTop->setGeometry( QRect( 10, 600, 75, 60 ) );
    btnMoveTop->setEnabled( FALSE );
    btnMoveTop->setPixmap(QPixmap(path + "/images/movetop32.png"));

    btnMoveUp = new QPushButton( grpFrame, "btnMoveUp" );
    btnMoveUp->setAutoDefault( FALSE );
    btnMoveUp->setGeometry( QRect( 85, 600, 75, 60 ) );
    btnMoveUp->setEnabled( FALSE );
    btnMoveUp->setPixmap(QPixmap(path + "/images/moveup32.png"));

    btnDelete = new QPushButton( grpFrame, "btnDelete" );
    btnDelete->setAutoDefault( FALSE );
    btnDelete->setGeometry( QRect( 160, 600, 75, 60 ) );
    btnDelete->setEnabled( FALSE );
    btnDelete->setPixmap(QPixmap(path + "/images/delete48.png"));
    
    btnClear = new QPushButton( grpFrame, "btnClear" );
    btnClear->setAutoDefault( FALSE );
    btnClear->setGeometry( QRect( 235, 600, 75, 60 ) );
    btnClear->setPixmap(QPixmap(path + "/images/clear32.png"));

    btnMoveBottom = new QPushButton( grpFrame, "btnMoveBottom" );
    btnMoveBottom->setAutoDefault( FALSE );
    btnMoveBottom->setGeometry( QRect( 385, 600, 75, 60 ) );
    btnMoveBottom->setEnabled( FALSE );
    btnMoveBottom->setPixmap(QPixmap(path + "/images/movebottom32.png"));

    btnMoveDown = new QPushButton( grpFrame, "btnMoveDown" );
    btnMoveDown->setAutoDefault( FALSE );
    btnMoveDown->setGeometry( QRect( 310, 600, 75, 60 ) );
    btnMoveDown->setEnabled( FALSE );
    btnMoveDown->setPixmap(QPixmap(path + "/images/movedown32.png"));

    connect( btnDelete, SIGNAL( clicked() ),        this, SLOT( removeItem() ));
    connect( btnMoveBottom, SIGNAL( clicked() ),    this, SLOT( moveItemBottom() ));
    connect( btnMoveDown, SIGNAL( clicked() ),      this, SLOT( moveItemDown() ));
    connect( btnMoveTop, SIGNAL( clicked() ),       this, SLOT( moveItemTop() ));
    connect( btnMoveUp, SIGNAL( clicked() ),        this, SLOT( moveItemUp() ));
    connect( btnClear, SIGNAL( clicked() ),         this, SLOT( clearItems() ));
    connect( lstShowPlan, SIGNAL( selectionChanged(QListViewItem*) ),
                this, SLOT( selectionChanged(QListViewItem*) ));
    connect( lstShowPlan, SIGNAL( clicked(QListViewItem*) ),
                this, SLOT( clicked(QListViewItem*) ));
    connect( lstShowPlan, SIGNAL( doubleClicked(QListViewItem*, const QPoint&, int)),
    			this, SLOT( doubleClicked(QListViewItem*, const QPoint&, int))); 
}

void Showplan::clean() {
    delete grpFrame;
}
