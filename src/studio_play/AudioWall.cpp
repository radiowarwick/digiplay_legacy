/*
 * Audiowall Widget
 * AudioWall.cpp
 * Provides a graphical audio wall widget
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

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>

#include "Logger.h"
#include "Config.h"

#include "AudioWall.h"

/**
 * Initiliase an audio wall
 */
AudioWall::AudioWall(QWidget* pParent, const char* pName, unsigned short pRows, unsigned short pCols)
		: QWidget(pParent),
		  mLoaded(false), mName(pName), mRows(pRows), mCols(pCols),
		  mPageSize(pRows*pCols), mCurrentPage(0), mActivePage(0),
		  mActiveIndex(0), mGrpFrame(0), mBtnPageNext(0), mBtnPagePrev(0),
		  mLblPageNum(0), mLblCounter(0) {
    const char *routine = "AudioWall::AudioWall";
    drawCreate();
    L_INFO(LOG_PLAYOUT, "Completed AudioWall constructor");
}

/**
 * Clear up the audio wall
 */
AudioWall::~AudioWall() {
	clean();
}

/**
 * Move to the next page
 */
void AudioWall::nextPage() {
	if (mCurrentPage <= mPages.size()) {
        displayPage(mCurrentPage + 1);
	}
}

/**
 * Move to the previous page
 */
void AudioWall::prevPage() {
	if (mCurrentPage > 0) {
        displayPage(mCurrentPage - 1);
	}
}

/**
 * Process a widget resize event
 */
void AudioWall::resizeEvent (QResizeEvent* pE) {
	if (pE) drawResize();
}

/**
 * Sets an audiowall item for a single button on a audiowall.
 */
void AudioWall::setButton(unsigned short pPage, unsigned short pIndex,
							AudioWallItemSpec pNewItem) {
	const char *routine = "AudioWall::setButton";
    L_INFO(LOG_PLAYOUT, "Set button: page=" + dps_itoa(pPage)  +
            ", index=" + dps_itoa(pIndex));

    // Sanity checks
    if (pPage >= mPages.size()) {
        L_ERROR(LOG_PLAYOUT,"Button page out of range");
        throw AUDIOWALL_BUTTON_OUT_OF_RANGE;
    }
	if (pIndex > mPageSize) {
        L_ERROR(LOG_PLAYOUT,"Button index out of range");
		throw AUDIOWALL_BUTTON_OUT_OF_RANGE;
	}

    // Get the AudioWallItem we're updating
    AudioWallItem* vI = mPages[pPage]->mItems[pIndex];

    // Configure button
    vI->set(pNewItem);
}

/**
 * Sets the title on a page and updates the display if it's the current page
 */
void AudioWall::setCaption(unsigned short pPage, QString pText) {
	if (pPage >= mPages.size()) return;
	mPages[pPage]->mTitle = pText;
	if (pPage == mCurrentPage) {
		mGrpFrame->setTitle(pText);
	}
}

/**
 * Adds a page of audiowall buttons to the wall list
 */
void AudioWall::addPage() {
    AudioWallPage* P = new AudioWallPage;
    AudioWallItem* I;

    P->mItems.clear();
    P->mItems.resize(mRows*mCols);
    for (unsigned short i = 0; i < mRows*mCols; ++i) {
        P->mItems.at(i) = 0;
    }

    // Create a new page of buttons/AudioWallItems
	for (unsigned int i = 0; i < mRows; i++) {
		for (unsigned int j = 0; j < mCols; j++) {
            I = new AudioWallItem(this);
            patch(mPages.size()*mPageSize + i*mCols + j + 1, I, OUT0);
            I->hide();
            I->setEnabled(false);
            P->mItems.at(i*mCols + j) = I;
		}
    }
    mPages.push_back(P);

    // Resize the buttons on the page to the correct layout
    resizePage(mPages.size() - 1);

    // If we're loading from an empty audiowall, display first page
    if ( ! mLoaded ) {
        mLoaded = true;
        displayPage(0);
    }

    // Configure the page navigation buttons
    configurePageNav();
}


/**
 * Deletes the specified audiowall (and buttons) from the wall list
 */
void AudioWall::deletePage(unsigned int pIndex) {
    const char *routine = "AudioWall::deletePage";
    // Sanity check
    if (pIndex > mPages.size() - 1) {
        L_ERROR(LOG_PLAYOUT, "Tried to delete page " + dps_itoa(pIndex) +
                " out of range");
        throw;
    }

    // Delete the page
    for (unsigned int i = 0; i < mPages.at(pIndex)->mItems.size(); i++) {
        delete mPages.at(pIndex)->mItems.at(i);
    }
    delete mPages.at(pIndex);
    mPages.erase(mPages.begin() + pIndex);

    if (mCurrentPage == pIndex) {
        if (pIndex + 1 < mPages.size()) {
            displayPage(pIndex + 1);
        }
        else if (pIndex > 0) {
            displayPage(pIndex - 1);
        }
        else {
		    mGrpFrame->setTitle("");
        }
    }

    // if there are no pages left, we've not got an audiowall loaded.
    if (mPages.size() == 0) {
        mLoaded = false;
    }

    // Configure page navigation
    configurePageNav();
}


/**
 * Displays the specified audiowall buttons, hiding any other buttons
 */
void AudioWall::displayPage(unsigned int pIndex) {
    const char *routine = "AudioWall::displayPage";
    L_INFO(LOG_PLAYOUT, "Display page " + dps_itoa(pIndex+1) + " of " +
            dps_itoa(mPages.size()));

    // Sanity check
    if (pIndex > mPages.size() - 1) {
        L_ERROR(LOG_PLAYOUT, "Tried to set active page " + dps_itoa(pIndex) +
                " out of range");
        throw;
    }

    // Hide the currently displayed page
    L_INFO(LOG_PLAYOUT, "Hiding old page " + dps_itoa(mCurrentPage));
    if (mCurrentPage < mPages.size()) {
        for (unsigned int i = 0; i < mPages[mCurrentPage]->mItems.size(); i++) {
            mPages[mCurrentPage]->mItems[i]->hide();
        }
    }

    // Change page number
    mCurrentPage = pIndex;

    // Show the new page
    L_INFO(LOG_PLAYOUT, "Showing new page");
    for (unsigned int i = 0; i < mPages[mCurrentPage]->mItems.size(); i++) {
        mPages[mCurrentPage]->mItems[i]->show();
    }

    // Set title
    mGrpFrame->setTitle(mPages[mCurrentPage]->mTitle);

    // Configure naviagation buttons
    configurePageNav();
}


/**
 * Resize the specified page buttons based on parent geometry
 */
void AudioWall::resizePage(unsigned int pIndex) {
    AudioWallPage* vP = mPages[pIndex];
	for (unsigned int i = 0; i < mRows; i++) {
		for (unsigned int j = 0; j < mCols; j++) {
            vP->mItems[i*mCols+j]->setGeometry( j*mCellWidth+mBorder,
                                                i*mCellHeight+2*mBorder,
                                                mCellWidth, mCellHeight);
		}
	}
}


/**
 * Updates the audiowall
 */
void AudioWall::updateWall() {
	configurePageNav();
}

/**
 * Configures the page navigation display based on current page and page count
 * Also enabled/disables buttons which aren't available
 */
void AudioWall::configurePageNav() {
    if (!mLoaded || (mPages.size() == 0)) {
		mBtnPageNext->setEnabled(false);
		mBtnPagePrev->setEnabled(false);
        mLblPageNum->setText("No AudioWall\nLoaded");
        mGrpFrame->setTitle("");
        return;
    }
    else {
    	mLblPageNum->setText("Page " + QString::number(mCurrentPage+1) + "/"
							+ QString::number(mPages.size()));
    }

	if (mCurrentPage == mPages.size() - 1) {
		mBtnPageNext->setEnabled(false);
	}
	else {
		mBtnPageNext->setEnabled(true);
	}
	if (mCurrentPage == 0) {
		mBtnPagePrev->setEnabled(false);
	}
	else {
		mBtnPagePrev->setEnabled(true);
	}
}

// ========================================================================
/**
 * Draws an empty audio wall with one page
 */
void AudioWall::drawCreate() {
    // clear out any existing objects
	clean();

	// Create frame, and page next, previous buttons and page num label
	mGrpFrame = new QGroupBox( this );
	mGrpFrame->setTitle("");
	QFont f;
	f.setFamily( "Sans Serif" );
	f.setPointSize( 12 );
	f.setBold( true );
	mGrpFrame->setFont( f );

	mBtnPageNext = new QPushButton( mGrpFrame );
	mBtnPageNext->setEnabled( false );
    mBtnPageNext->setIcon(QIcon(":/icons/fastforward.png"));
    mBtnPageNext->setIconSize(QSize(64,64));
    QObject::connect( mBtnPageNext, SIGNAL(pressed()), this, SLOT(nextPage()) );

	mBtnPagePrev = new QPushButton( mGrpFrame );
	mBtnPagePrev->setEnabled( false );
	mBtnPagePrev->setIcon(QIcon(":/icons/fastbackward.png"));
	mBtnPagePrev->setIconSize(QSize(64,64));
    QObject::connect( mBtnPagePrev, SIGNAL(pressed()), this, SLOT(prevPage()) );

	mLblPageNum = new QLabel( mGrpFrame );
	mLblPageNum->setEnabled( false );

	mLblCounter = new QLabel( mGrpFrame );
	mLblCounter->setEnabled( false );
}


/**
 * Resize and reposition all the child widgets on resize
 */
void AudioWall::drawResize() {
	// What's our size?
	mBorder = 10;
	mFrameWidth = this->width();
	mFrameHeight = this->height();
	mCellWidth = int((mFrameWidth - 2*mBorder) / mCols);
	mCellHeight = int((mFrameHeight - 3*mBorder) / (mRows+1));
	if (mCellWidth <= 0 || mCellHeight <= 0) return;

	mGrpFrame->setGeometry( QRect( 0, 0, mFrameWidth, mFrameHeight ));
	mBtnPagePrev->setGeometry( QRect( mBorder, 2*mBorder + mRows*mCellHeight, mCellWidth, mCellHeight ));
	mLblPageNum->setGeometry( QRect( mBorder + mCellWidth, 2*mBorder + mRows*mCellHeight + mCellHeight/2, mCellWidth, mCellHeight / 2 ) );
	mLblPageNum->setAlignment( Qt::AlignCenter );
	mLblCounter->setGeometry( QRect( mBorder + mCellWidth, 2*mBorder + mRows*mCellHeight,mCellWidth, mCellHeight / 2 ) );
	mLblCounter->setAlignment( Qt::AlignCenter );
	mBtnPageNext->setGeometry( QRect( mBorder + 2*mCellWidth, 2*mBorder + mRows*mCellHeight, mCellWidth, mCellHeight ) );

    for (unsigned int i = 0; i < mPages.size(); i++) {
        resizePage(i);
    }
}

/**
 * Deletes all objects associated with this audio wall
 */
void AudioWall::clean() {
	delete mBtnPageNext;
	delete mBtnPagePrev;
	delete mLblPageNum;
	delete mLblCounter;
	delete mGrpFrame;
}

