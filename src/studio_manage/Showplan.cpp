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

#include <QtGui/QApplication>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtCore/QString>
#include <QtGui/QTextDocument>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>

#include "dps/Dps.h"
#include "dps.h"
#include "Logger.h"
#include "Auth.h"
#include "dlgWarn.h"

#include "ShowplanModel.h"
#include "ShowplanView.h"
#include "ShowplanDelegate.h"
#include "Showplan.h"

Showplan::Showplan(QWidget *parent)
        : QWidget(parent),
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
                        && modShowplan->getSize() > 0
                        && modShowplan->getLastItem().getHash() != mActive) {
        L_INFO(LOG_DB,"Processing track load event");
        if (!mIsItemActive) {
            mActive = modShowplan->getFirstItem().getHash();
        }
        else {
            modShowplan->getItemByHash(mActive).setState(DpsShowItem::Finished);
            try {
        	   mActive = modShowplan->getNextItem(modShowplan->getItemByHash(mActive)).getHash();
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
        modShowplan->getItemByHash(mActive).setState(DpsShowItem::Loaded);
        mIsItemActive = true;
        //??
        lstShowPlan->scrollTo(lstShowPlan->currentIndex(), QListView::EnsureVisible);
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
	modShowplan->loadShowplan(pSrc);
	selectionChanged(lstShowPlan->currentIndex());
}

void Showplan::append(const DpsShowItem& pSrc) {
	modShowplan->append(pSrc);
	selectionChanged(lstShowPlan->currentIndex());
}

void Showplan::append(const DpsAudioItem& pSrc) {
	modShowplan->append(DpsShowItem(pSrc));
	selectionChanged(lstShowPlan->currentIndex());
}

void Showplan::append(const DpsScriptItem& pSrc) {
	modShowplan->append(DpsShowItem(pSrc));
	selectionChanged(lstShowPlan->currentIndex());
}

void Showplan::clear() {
    modShowplan->clear();
    selectionChanged(QModelIndex());
}

void Showplan::scriptDone(const DpsScriptItem& pSrc) {
    cout << "TODO: IMPLEMENT" << endl;
}

void Showplan::showplanUpdated() {
//	DpsHash vSelectedHash;
//
//	if (lstShowPlan->currentIndex().isValid()) {
//	    vSelectedHash = modShowplan->getItem(lstShowPlan->currentIndex().row()).getHash();
//	}

//    if (mShowplan->getSize() == 0) {
//        mIsItemActive = false;
//        mIsItemSelected = false;
//    }

//	lstShowPlan->clear();
//	for (unsigned int i = 0; i < getSize(); ++i) {
//		vNew = new ShowPlanItem(lstShowPlan, vNew, getItem(i));
//		if (mIsItemSelected && getItem(i).getHash() == vSelectedHash) {
//			lstShowPlan->setSelected(dynamic_cast<QListViewItem*>(vNew), true);
//		}
//		if (std::find(mExpandedItems.begin(), mExpandedItems.end(), getItem(i).getHash())
//				!= mExpandedItems.end()) {
//			vNew->expand();
//		}
//	}
//	lstShowPlan->scrollTo(lstShowPlan->currentIndex(), QListView::EnsureVisible);
//	//selectionChanged(lstShowPlan->selectedItem());
//	updateNextTrack();
}

void Showplan::removeItem() {
	if (modShowplan->getSize() == 0) return;
    const QModelIndex& vIdx = lstShowPlan->currentIndex();
    if (!vIdx.isValid()) return;
	modShowplan->erase(lstShowPlan->currentIndex().row());
	selectionChanged(lstShowPlan->currentIndex());
}

void Showplan::moveItemUp() {
	if (modShowplan->getSize() == 0) return;
	const QModelIndex& vIdx = lstShowPlan->currentIndex();
	if (!vIdx.isValid()) return;
	const DpsShowItem& vCurrent = modShowplan->getItem(vIdx.row());
	modShowplan->moveUp(vCurrent);
	selectionChanged(lstShowPlan->currentIndex());
}

void Showplan::moveItemDown() {
    if (modShowplan->getSize() == 0) return;
    const QModelIndex& vIdx = lstShowPlan->currentIndex();
    if (!vIdx.isValid()) return;
    const DpsShowItem& vCurrent = modShowplan->getItem(vIdx.row());
    modShowplan->moveDown(vCurrent);
    selectionChanged(lstShowPlan->currentIndex());
}

void Showplan::moveItemTop() {
    if (modShowplan->getSize() == 0) return;
    const QModelIndex& vIdx = lstShowPlan->currentIndex();
    if (!vIdx.isValid()) return;
    const DpsShowItem& vCurrent = modShowplan->getItem(vIdx.row());
    modShowplan->moveTop(vCurrent);
    selectionChanged(lstShowPlan->currentIndex());
}

void Showplan::moveItemBottom() {
    if (modShowplan->getSize() == 0) return;
    const QModelIndex& vIdx = lstShowPlan->currentIndex();
    if (!vIdx.isValid()) return;
    const DpsShowItem& vCurrent = modShowplan->getItem(vIdx.row());
    modShowplan->moveBottom(vCurrent);
    selectionChanged(lstShowPlan->currentIndex());
}

void Showplan::clearItems() {
    dlgWarn *dlg = new dlgWarn(this->parentWidget());
    dlg->setTitle("Clear all");
    dlg->setWarning("Are you sure you wish to clear the show plan?");
    if ( dlg->exec() != QDialog::Accepted ){
        delete dlg;
        return;
    }
    delete dlg;
	clear();
}


void Showplan::doubleClicked(const QModelIndex& x) {
	if (!x.isValid()) return;
	DpsHash vH = modShowplan->getItem(x.row()).getHash();
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

void Showplan::selectionChanged(const QModelIndex& x) {
	// If x is null, we're not having anything selected.
    if ( ! x.isValid() ) {
        btnMoveUp->setEnabled(false);
        btnMoveDown->setEnabled(false);
        btnMoveTop->setEnabled(false);
        btnMoveBottom->setEnabled(false);
        btnDelete->setEnabled(false);
        mIsItemSelected = false;
        return;
    }

    DpsShowItem& y = modShowplan->getItem(x.row());

    // If item is unloaded, activate applicable move buttons
    if ( y.getState() == DpsShowItem::Unloaded ) {
        if (x.row() == 0) {
            btnMoveUp->setEnabled(false);
            btnMoveTop->setEnabled(false);
        }
        else {
            DpsShowItem& z = modShowplan->getItem(x.row() - 1);
            // Up buttons
            if (z.getState() == DpsShowItem::Loaded) {
                btnMoveUp->setEnabled(false);
                btnMoveTop->setEnabled(false);
            }
            else {
                btnMoveUp->setEnabled(true);
                btnMoveTop->setEnabled(true);
            }
        }

        // Down buttons
        if (x.row() + 1 == modShowplan->getSize()) {
            btnMoveBottom->setEnabled(false);
            btnMoveDown->setEnabled(false);
        }
        else {
            btnMoveBottom->setEnabled(true);
            btnMoveDown->setEnabled(true);
        }
        btnDelete->setEnabled(true);

        // Change the selected item pointer to the new item.
		mSelected = y.getHash();
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
    if (modShowplan->getSize() == 0) {
		conf->setParam("next_on_showplan","");
		mLock.unlock();
		return;
	}

	DpsShowItem x;
    if ( ! mIsItemActive ) {
        x = modShowplan->getFirstItem();
    }
    else {
        try {
            x = modShowplan->getNextItem(modShowplan->getItemByHash(mActive));
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
            if (x == modShowplan->getLastItem()) {
                break;
            }
            x = modShowplan->getNextItem(x);
        }
	}
	catch (DpsShowPlan::Error&) {

	}

    mLock.unlock();
}

void Showplan::draw() {
    QString path = DPSDIR;

    grpFrame = new QGroupBox( this );
    grpFrame->setGeometry( QRect( 0, 0, 470, 670 ) );
//    QFont grpFrame_font(  grpFrame->font() );
//    grpFrame_font.setFamily( "Sans Serif" );
//    grpFrame_font.setPointSize( 12 );
//    //grpFrame_font.setBold( TRUE );
//    grpFrame->setFont( grpFrame_font );
//    //grpFrame->setFrameShadow( QGroupBox::Sunken );
//    //grpFrame->setLineWidth( 1 );
    grpFrame->setFlat( FALSE );
//    grpFrame->setTitle( "Showplan" );

    modShowplan = new ShowplanModel;
    modShowplan->setHeaderData(0, Qt::Horizontal, tr("Item"));

    lstShowPlan = new ShowplanView( grpFrame );
//    lstShowPlan = new QListView(grpFrame);
    lstShowPlan->setModel(modShowplan);
    lstShowPlan->setGeometry( QRect( 10, 20, 450, 580 ) );
    lstShowPlan->setItemDelegate(new ShowplanDelegate);
    lstShowPlan->setResizeMode(QListView::Adjust);
//    lstShowPlan->header()->setClickEnabled( FALSE,
//            lstShowPlan->header()->count() - 1 );
//    lstShowPlan->header()->setResizeEnabled( FALSE,
//            lstShowPlan->header()->count() - 1 );
//    lstShowPlan->setPaletteBackgroundColor( QColor( 255, 255, 255 ) );
//    QFont lstShowPlan_font(  lstShowPlan->font() );
//    lstShowPlan_font.setPointSize( 10 );
//    lstShowPlan_font.setBold( FALSE );
//    lstShowPlan->setFont( lstShowPlan_font );
//    lstShowPlan->setFrameShape( QListView::Box );
//    lstShowPlan->setFrameShadow( QListView::Plain );
    lstShowPlan->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    lstShowPlan->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    lstShowPlan->setSelectionMode(QListView::SingleSelection);
    lstShowPlan->setSelectionBehavior(QListView::SelectRows);
//    lstShowPlan->setResizeMode( QListView::Fixed );
    //lstShowPlan->set(0,lstShowPlan->width() - 5);
    //lstShowPlan->setSorting(-1);

    btnMoveTop = new QPushButton( grpFrame );
    btnMoveTop->setAutoDefault( FALSE );
    btnMoveTop->setGeometry( QRect( 10, 600, 75, 60 ) );
    btnMoveTop->setEnabled( FALSE );
    btnMoveTop->setIcon(QIcon(":/icons/movetop32.png"));

    btnMoveUp = new QPushButton( grpFrame );
    btnMoveUp->setAutoDefault( FALSE );
    btnMoveUp->setGeometry( QRect( 85, 600, 75, 60 ) );
    btnMoveUp->setEnabled( FALSE );
    btnMoveUp->setIcon(QIcon(":/icons/moveup32.png"));

    btnDelete = new QPushButton( grpFrame );
    btnDelete->setAutoDefault( FALSE );
    btnDelete->setGeometry( QRect( 160, 600, 75, 60 ) );
    btnDelete->setEnabled( FALSE );
    btnDelete->setIcon(QIcon(":/icons/delete48.png"));

    btnClear = new QPushButton( grpFrame );
    btnClear->setAutoDefault( FALSE );
    btnClear->setGeometry( QRect( 235, 600, 75, 60 ) );
    btnClear->setIcon(QIcon(":/icons/clear32.png"));

    btnMoveBottom = new QPushButton( grpFrame );
    btnMoveBottom->setAutoDefault( FALSE );
    btnMoveBottom->setGeometry( QRect( 385, 600, 75, 60 ) );
    btnMoveBottom->setEnabled( FALSE );
    btnMoveBottom->setIcon(QIcon(":/icons/movebottom32.png"));

    btnMoveDown = new QPushButton( grpFrame );
    btnMoveDown->setAutoDefault( FALSE );
    btnMoveDown->setGeometry( QRect( 310, 600, 75, 60 ) );
    btnMoveDown->setEnabled( FALSE );
    btnMoveDown->setIcon(QIcon(":/icons/movedown32.png"));

    connect( btnDelete, SIGNAL( clicked() ),        this, SLOT( removeItem() ));
    connect( btnMoveBottom, SIGNAL( clicked() ),    this, SLOT( moveItemBottom() ));
    connect( btnMoveDown, SIGNAL( clicked() ),      this, SLOT( moveItemDown() ));
    connect( btnMoveTop, SIGNAL( clicked() ),       this, SLOT( moveItemTop() ));
    connect( btnMoveUp, SIGNAL( clicked() ),        this, SLOT( moveItemUp() ));
    connect( btnClear, SIGNAL( clicked() ),         this, SLOT( clearItems() ));
    connect( lstShowPlan, SIGNAL( itemSelected(const QModelIndex&) ),
                this, SLOT( selectionChanged(const QModelIndex&) ));
//    connect( lstShowPlan, SIGNAL( clicked(const QModelIndex&) ),
//                this, SLOT( clicked(const QModelIndex&) ));
    connect( lstShowPlan, SIGNAL( doubleClicked(const QModelIndex&)),
    			this, SLOT( doubleClicked(const QModelIndex&)));
}

void Showplan::clean() {
    delete grpFrame;
}
