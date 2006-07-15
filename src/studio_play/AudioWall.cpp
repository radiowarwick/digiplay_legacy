#include <qwidget.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qlabel.h>

#include "AudioWall.h"

void AudioWall::init() {
	grpFrame = 0;
	btnPageNext = 0;
	btnPagePrev = 0;
	lblPageNum = 0;
}

void AudioWall::play(int index) {

}

void AudioWall::play() {

}

void AudioWall::draw() {
	clean();

	// What's our size?
	int w = this->width() - 20;
	int h = this->height() - 20;

	// Create frame, and page next, previous buttons and page num label
	grpFrame = new QGroupBox( this, "grpFrame" );
	grpFrame->setGeometry( QRect( 10, 10, w, h ));

	btnPageNext = new QPushButton( grpFrame, "btnPageNext" );
	btnPageNext->setEnabled( false );
	btnPageNext->setGeometry( QRect( 40, 40, 140, 60 ) );

	btnPagePrev = new QPushButton( grpFrame, "btnPagePrev" );
	btnPagePrev->setEnabled( false );
	btnPagePrev->setGeometry( QRect( 100, 40, 140, 60 ) );

	lblPageNum = new QLabel( grpFrame, "lblPageNum" );
	lblPageNum->setEnabled( false );
	lblPageNum->setGeometry( QRect( 160, 40, 140, 60 ) );
	lblPageNum->setAlignment( int( QLabel::AlignCenter ) );

	// Create the audio buttons and keep a handle to them in a vector
	for (unsigned int i = 0; i < 12; i++) {
		btnAudio->push_back(new QPushButton( grpFrame,
							"btnAudio" + QString::number(i) ));
	}

	// Set properties for the buttons and connect them up
	w = int(w / 3);
	h = int(h / 3);
	QFont f = btnAudio[0]->font();
	f.setPointSize(14);
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			btnAudio[i*3+j]->setGeometry(j*w+10, i*h+20, 140, 60);
			btnAudio[i*3+j]->setFont(f);
			btnAudio[i*3+j]->setEnabled(false);
			connect( btnAudio[i*3+j], SIGNAL(pressed()),
						this, SLOT(play()) );
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
