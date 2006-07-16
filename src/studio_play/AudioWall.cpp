#include <iostream>
using namespace std;

#include <qwidget.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qlabel.h>

#include "AudioWallManager.h"

#include "AudioWall.h"

AudioWall::AudioWall(QWidget *parent, const char* name)
		: QWidget(parent,name) {
	grpFrame = 0;
	btnPageNext = 0;
	btnPagePrev = 0;
	lblPageNum = 0;
	drawCreate();
}

void AudioWall::play(int index) {

}

void AudioWall::play() {

}

void AudioWall::resizeEvent (QResizeEvent *e) {
	drawResize();
}

void AudioWall::setManager (AudioWallManager *manager) {

}

void AudioWall::drawCreate() {
	clean();

	// Create frame, and page next, previous buttons and page num label
	grpFrame = new QGroupBox( this, "grpFrame" );
	
	btnPageNext = new QPushButton( grpFrame, "btnPageNext" );
	btnPageNext->setEnabled( false );
	
	btnPagePrev = new QPushButton( grpFrame, "btnPagePrev" );
	btnPagePrev->setEnabled( false );
	
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
	int wFrame = this->width() - 2*border;
	int hFrame = this->height() - 2*border;
	if (wFrame <= 0 || hFrame <= 0) return;
	int wCell = int((wFrame - 2*border) / 3);
	int hCell = int((hFrame - 3*border) / 5);

	grpFrame->setGeometry( QRect( border, 2*border, wFrame, hFrame ));
	btnPagePrev->setGeometry( QRect( border, 2*border + 4*hCell, wCell, hCell ));
	lblPageNum->setGeometry( QRect( border + wCell, 2*border + 4*hCell, wCell, hCell ) );
	lblPageNum->setAlignment( int( QLabel::AlignCenter ) );
	btnPageNext->setGeometry( QRect( border + 2*wCell, 2*border + 4*hCell, wCell, hCell ) );

	// Set properties for the buttons and connect them up
	QFont f = btnAudio[0]->font();
	f.setPointSize(14);
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			btnAudio[3*i+j]->setGeometry(j*wCell+border, i*hCell+2*border, wCell, hCell);
			btnAudio[i*3+j]->setFont(f);
		}
	}
}

void AudioWall::clean() {
	delete grpFrame;
	delete btnPageNext;
	delete btnPagePrev;
	delete lblPageNum;
	for (unsigned int i = 0; i < btnAudio.size(); i++) {
		delete btnAudio[i];
	}
}
