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

#include <qapplication.h>
#include <qwidget.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qlabel.h>

#include "Logger.h"
#include "Config.h"

#include "AudioWall.h"

/**
 * Initiliase an audio wall
 */
AudioWall::AudioWall(QWidget *parent, const char* name, unsigned short rows, unsigned short cols)
		: QWidget(parent,name) {
	// default to a single empty page
	_rows = rows;
	_cols = cols;
	_pageSize = _rows * _cols;
	_currentPage = 1;
	_activePage = 0;
	_activeIndex = 0;

	grpFrame = 0;
	btnPageNext = 0;
	btnPagePrev = 0;
	lblPageNum = 0;
    drawCreate();
    cout << "Completed AudioWall constructor" << endl;
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
	if (_currentPage <= _pages.size()) {
        displayPage(_currentPage + 1);
	}
}

/**
 * Move to the previous page
 */
void AudioWall::prevPage() {
	if (_currentPage > 0) {
        displayPage(_currentPage - 1);
	}
}

/**
 * Process a widget resize event
 */
void AudioWall::resizeEvent (QResizeEvent *e) {
	if (e) drawResize();
}

/**
 * Sets a cartwall item for a single button on a cartwall.
 */
void AudioWall::setButton(unsigned short page, unsigned short index,
							AudioWallItemSpec newItem) {
	char *routine = "AudioWall::setButton";
    cout << "Set button: page=" << page  << ", index=" << index << endl;

    // Sanity checks
    if (page >= _pages.size()) {
        L_ERROR(LOG_PLAYOUT,"Button page out of range");
        throw AUDIOWALL_BUTTON_OUT_OF_RANGE;
    }
	if (index > _pageSize) {
        L_ERROR(LOG_PLAYOUT,"Button index out of range");
		throw AUDIOWALL_BUTTON_OUT_OF_RANGE;
	}

    // Get the AudioWallItem we're updating
    AudioWallItem* I = _pages[page]->items[index];

    // Configure cosmetic properties
    I->setBackgroundColour(newItem.bgColour);
    I->setForegroundColour(newItem.fgColour);
    I->setText(newItem.text);

    // If the button has audio, load the audio
	if (newItem.file != "") {
        I->load(newItem.file.ascii(), newItem.start, newItem.end);
	}

}

/**
 * Sets the title on a page and updates the display if it's the current page
 */
void AudioWall::setCaption(unsigned short page, QString text) {
	if (page >= _pages.size()) return;
	_pages[page]->title = text;
	if (page == _currentPage) {
		grpFrame->setTitle(text);
	}
}

/**
 * Adds a page of cartwall buttons to the wall list
 */
void AudioWall::addPage() {
    AudioWallPage* P = new AudioWallPage;
    AudioWallItem* I;

    P->items.clear();
    P->items.resize(_rows*_cols);
    for (unsigned int i = 0; i < _rows*_cols; ++i) P->items.at(i) = 0;

    // Create a new page of buttons/AudioWallItems
    qApp->lock();
	for (unsigned int i = 0; i < _rows; i++) {
		for (unsigned int j = 0; j < _cols; j++) {
            I = new AudioWallItem(this,"button" 
                        + QString::number(P->items.size()-1) 
                        + "-" + QString::number(_rows*i+j));
            Audio::ProcessMixer::connect(
                _pages.size()*_pageSize + i*_cols + j + 1, I, OUT0);
            I->hide();
            I->setEnabled(false);
            P->items.at(i*_cols + j) = I;
		}
    }
    _pages.push_back(P);
    qApp->unlock();

    // Resize the buttons on the page to the correct layout
    resizePage(_pages.size() - 1);
    
    // Configure the page navigation buttons
    configurePageNav();
}

/**
 * Deletes the specified cartwall (and buttons) from the wall list
 */
void AudioWall::deletePage(unsigned int index) {
    // Sanity check
    if (index > _pages.size() - 1) {
        cout << "Tried to delete page " << index << " out of range" << endl;
        throw;
    }

    // Delete the page
    qApp->lock();
    for (unsigned int i = 0; i < _pages.at(index)->items.size(); i++) {
        delete _pages.at(index)->items.at(i);
    }
    delete _pages.at(index);
    _pages.erase(_pages.begin() + index);
    qApp->unlock();

    if (_currentPage == index) {
        if (index + 1 < _pages.size()) {
            displayPage(index + 1);
        }
        else if (index > 0) {
            displayPage(index - 1);
        }
        else {
		    grpFrame->setTitle("");
        }
    }

    // Configure page navigation
    configurePageNav();
}

/**
 * Displays the specified cartwall buttons, hiding any other buttons
 */
void AudioWall::displayPage(unsigned int index) {
    cout << "Display page " << index+1 << " of " << _pages.size() << endl;

    // Sanity check
    if (index > _pages.size() - 1) {
        cout << "Tried to set active page " << index << " out of range" << endl;
        throw;
    }
    
    qApp->lock();

    // Hide the currently displayed page
    cout << "Hiding old page " << _currentPage << endl;
    if (_currentPage < _pages.size()) {
        for (unsigned int i = 0; i < _pages[_currentPage]->items.size(); i++) {
            _pages[_currentPage]->items[i]->hide();
        }
    }

    // Change page number
    _currentPage = index;

    // Show the new page
    cout << "Showing new page" << endl;
    for (unsigned int i = 0; i < _pages[_currentPage]->items.size(); i++) {
        _pages[_currentPage]->items[i]->show();
    }

    qApp->unlock();
    
    // Set title
    grpFrame->setTitle(_pages[_currentPage]->title);

    // Configure naviagation buttons
    configurePageNav();
}

/**
 * Resize the specified page buttons based on parent geometry
 */
void AudioWall::resizePage(unsigned int index) {
    qApp->lock();
    AudioWallPage* P = _pages[index];
	for (unsigned int i = 0; i < _rows; i++) {
		for (unsigned int j = 0; j < _cols; j++) {
            P->items[i*_cols+j]->setGeometry(j*wCell+border, i*hCell+2*border,
                                            wCell, hCell);
		}
	}
    qApp->unlock();
}

/**
 * Configures the page navigation display based on current page and page count
 * Also enabled/disables buttons which aren't available
 */
void AudioWall::configurePageNav() {
    qApp->lock();
	if (_currentPage == _pages.size() - 1) {
		btnPageNext->setEnabled(false);
	}
	else {
		btnPageNext->setEnabled(true);
	}
	if (_currentPage == 0) {
		btnPagePrev->setEnabled(false);
	}
	else {
		btnPagePrev->setEnabled(true);
	}
	lblPageNum->setText("Page " + QString::number(_currentPage+1) + "/"
							+ QString::number(_pages.size()));
    qApp->unlock();
}

// ========================================================================
/**
 * Draws an empty audio wall with one page
 */
void AudioWall::drawCreate() {
    // clear out any existing objects
	clean();
	string path = qApp->applicationDirPath();

    qApp->lock();
	// Create frame, and page next, previous buttons and page num label
	grpFrame = new QGroupBox( this, "grpFrame" );
	grpFrame->setTitle("");
	QFont f;
	f.setFamily( "Sans Serif" );
	f.setPointSize( 16 );
	f.setBold( true );
	grpFrame->setFont( f );

	btnPageNext = new QPushButton( grpFrame, "btnPageNext" );
	btnPageNext->setEnabled( false );
	btnPageNext->setPixmap(QPixmap(path + "/images/fastforward.png"));
    QObject::connect( btnPageNext, SIGNAL(pressed()), this, SLOT(nextPage()) );

	btnPagePrev = new QPushButton( grpFrame, "btnPagePrev" );
	btnPagePrev->setEnabled( false );
	btnPagePrev->setPixmap(QPixmap(path + "/images/fastbackward.png"));
    QObject::connect( btnPagePrev, SIGNAL(pressed()), this, SLOT(prevPage()) );

	lblPageNum = new QLabel( grpFrame, "lblPageNum" );
	lblPageNum->setEnabled( false );

	lblCounter = new QLabel( grpFrame, "lblCounter" );
	lblCounter->setEnabled( false );
	qApp->unlock();
}

/**
 * Resize and reposition all the child widgets on resize
 */
void AudioWall::drawResize() {
	// What's our size?
	border = 10;
	wFrame = this->width();
	hFrame = this->height();
	wCell = int((wFrame - 2*border) / _cols);
	hCell = int((hFrame - 3*border) / (_rows+1));
	if (wCell <= 0 || hCell <= 0) return;

    qApp->lock();
	grpFrame->setGeometry( QRect( 0, 0, wFrame, hFrame ));
	btnPagePrev->setGeometry( QRect( border, 2*border + _rows*hCell, wCell, hCell ));
	lblPageNum->setGeometry( QRect( border + wCell, 2*border + _rows*hCell + hCell/2, wCell, hCell / 2 ) );
	lblPageNum->setAlignment( int( QLabel::AlignCenter ) );
	lblCounter->setGeometry( QRect( border + wCell, 2*border + _rows*hCell,wCell, hCell / 2 ) );
	lblCounter->setAlignment( int( QLabel::AlignCenter ) );
	btnPageNext->setGeometry( QRect( border + 2*wCell, 2*border + _rows*hCell, wCell, hCell ) );
    qApp->unlock();

    for (unsigned int i = 0; i < _pages.size(); i++) {
        resizePage(i);
    }
}

/**
 * Deletes all objects associated with this audio wall
 */
void AudioWall::clean() {
	delete btnPageNext;
	delete btnPagePrev;
	delete lblPageNum;
	delete grpFrame;
}

