#include <iostream>
using namespace std;

#include <qapplication.h>
#include <qwidget.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qlabel.h>

#include "Logger.h"

#include "AudioWall.h"

AudioWall::AudioWall(QWidget *parent, const char* name, int rows, int cols)
		: QWidget(parent,name) {
	grpFrame = 0;
	btnPageNext = 0;
	btnPagePrev = 0;
	lblPageNum = 0;
	drawCreate();

	// default to a single empty page
	_rows = rows;
	_cols = cols;
	_currentPage = 0;
	_pages.resize(1);
	_pages[0].items.resize(_rows*_cols);
}

AudioWall::~AudioWall() {
	clean();
}

void AudioWall::play(int index) {

}

void AudioWall::play() {

}

void AudioWall::nextPage() {
	if (_currentPage + 1 < _pages.size()) {
		_currentPage++;
		for (unsigned int i = 0; i < _rows*_cols; i++) {
			configureButton(i);
		}
	}
	configurePageNav();	
}

void AudioWall::prevPage() {
	if (_currentPage > 0) {
		_currentPage--;
		for (unsigned int i = 0; i < _rows*_cols; i++) {
			configureButton(i);
		}
	}
	configurePageNav();
}

void AudioWall::resizeEvent (QResizeEvent *e) {
	drawResize();
}

void AudioWall::setButton(unsigned int page, unsigned int index,
							AudioWallItem item) {
	char *routine = "AudioWall::setButton";
	if (index > _rows*_cols) {
		Logger::log(ERROR,routine,"Button index out of range",1);
		throw AUDIOWALL_BUTTON_OUT_OF_RANGE;
	}
	for (unsigned int i = 0; i <= page; i++) {
		if (_pages.size() <= i) {
			AudioWallPage p;
			p.items.resize(_rows*_cols);
			_pages.push_back(p);
		}
	}
	_pages[page].items[index] = item;
	if (page == _currentPage) {
		configureButton(index);
	}
	configurePageNav();
}

void AudioWall::setCaption(unsigned int page, QString text) {
	if (page+1 > _pages.size()) return;
	_pages[page].title = text;
}

void AudioWall::drawCreate() {
	clean();
	string path = qApp->applicationDirPath();

	// Create frame, and page next, previous buttons and page num label
	grpFrame = new QGroupBox( this, "grpFrame" );
	grpFrame->setTitle("No title");
	QFont f;
	f.setFamily( "Sans Serif" );
	f.setPointSize( 16 );
	f.setBold( true );
	grpFrame->setFont( f );

	btnPageNext = new QPushButton( grpFrame, "btnPageNext" );
	btnPageNext->setEnabled( false );
	btnPageNext->setPixmap(QPixmap(path + "/images/fastforward.png"));
	connect( btnPageNext, SIGNAL(pressed()), this, SLOT(nextPage()) );

	btnPagePrev = new QPushButton( grpFrame, "btnPagePrev" );
	btnPagePrev->setEnabled( false );
	btnPagePrev->setPixmap(QPixmap(path + "/images/fastbackward.png"));
	connect( btnPagePrev, SIGNAL(pressed()), this, SLOT(prevPage()) );

	lblPageNum = new QLabel( grpFrame, "lblPageNum" );
	lblPageNum->setEnabled( false );
	
	// Create the audio buttons and keep a handle to them in a vector
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			btnAudio.push_back(new QPushButton( grpFrame,
							"btnAudio" + QString::number(3*i+j) ));
			btnAudio[3*i+j]->setEnabled(false);
			connect( btnAudio[3*i+j], SIGNAL(pressed()),
						this, SLOT(play()) );
		}
	}
}

void AudioWall::drawResize() {
	// What's our size?
	int border = 10;
	int wFrame = this->width();
	int hFrame = this->height();
	int wCell = int((wFrame - 2*border) / _cols);
	int hCell = int((hFrame - 3*border) / (_rows+1));
	if (wCell <= 0 || hCell <= 0) return;

	grpFrame->setGeometry( QRect( 0, 0, wFrame, hFrame ));
	btnPagePrev->setGeometry( QRect( border, 2*border + _rows*hCell, wCell, hCell ));
	lblPageNum->setGeometry( QRect( border + wCell, 2*border + _rows*hCell, wCell, hCell ) );
	lblPageNum->setAlignment( int( QLabel::AlignCenter ) );
	btnPageNext->setGeometry( QRect( border + 2*wCell, 2*border + _rows*hCell, wCell, hCell ) );

	// Set properties for the buttons and connect them up
	QFont f = btnAudio[0]->font();
	f.setPointSize(14);
	for (unsigned int i = 0; i < _rows; i++) {
		for (unsigned int j = 0; j < _cols; j++) {
			btnAudio[i*_cols+j]->setGeometry(j*wCell+border, i*hCell+2*border, wCell, hCell);
			btnAudio[i*_cols+j]->setFont(f);
		}
	}
}

void AudioWall::configureButton(unsigned int index) {
	if (_pages[_currentPage].items[index].text != "") {
		AudioWallItem item = _pages[_currentPage].items[index];
		btnAudio[index]->setText(item.text);
		btnAudio[index]->setPaletteForegroundColor(item.fgColor);
		btnAudio[index]->setPaletteBackgroundColor(item.bgColor);
		btnAudio[index]->setEnabled(true);
	}
	else {
		btnAudio[index]->setText("");
		btnAudio[index]->setPaletteForegroundColor(QColor(QRgb(0)));
		btnAudio[index]->setPaletteBackgroundColor(QColor(QRgb(12632256)));
		btnAudio[index]->setEnabled(false);
	}
}

void AudioWall::configurePageNav() {
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

}

void AudioWall::clean() {
	delete btnPageNext;
	delete btnPagePrev;
	delete lblPageNum;
	while (btnAudio.size() > 0) {	
		delete btnAudio[0];
		btnAudio.erase(btnAudio.begin());
	}
	delete grpFrame;
}
