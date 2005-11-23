/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
#include <qapplication.h>

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "playerThread.h"
#include "triggerThread.h"
#include "track.h"

//Connection *C = new Connection("hostaddr=192.168.1.1 dbname=digiplay user=digiplay_user");
//Transaction *T = new Transaction(*C,"");
QString path;
QPixmap *pixPlay, *pixPause, *pixStop, *pixSeekback, *pixSeekforward, *pixReset;
playerThread *player1;
playerThread *player2;
playerThread *player3;
triggerThread *dbTrigger;

void frmPlayout::init() {
	path = qApp->applicationDirPath();
	pixPlay = new QPixmap(path + "/images/play.png");
	pixPause = new QPixmap(path + "/images/pause.png");
	pixStop = new QPixmap(path + "/images/stop.png");
	pixSeekback = new QPixmap(path + "/images/fastbackward.png");
	pixSeekforward = new QPixmap(path + "/images/fastforward.png");
	pixReset = new QPixmap(path + "/images/reset.png");
	cout << path << endl;
	// Set up button images
	btnPlay1->setPixmap(*pixPlay);
	btnPlay2->setPixmap(*pixPlay);
	btnPlay3->setPixmap(*pixPlay);
	btnStop1->setPixmap(*pixStop);
	btnStop2->setPixmap(*pixStop);
	btnStop3->setPixmap(*pixStop);
	btnSeekBack1->setPixmap(*pixSeekback);
	btnSeekBack2->setPixmap(*pixSeekback);
	btnSeekBack3->setPixmap(*pixSeekback);
	btnSeekForward1->setPixmap(*pixSeekforward);
	btnSeekForward2->setPixmap(*pixSeekforward);
	btnSeekForward3->setPixmap(*pixSeekforward);
	btnReset1->setPixmap(*pixReset);
	btnReset2->setPixmap(*pixReset);
	btnReset3->setPixmap(*pixReset);
	btnStnCWallPrev->setPixmap(*pixSeekback);
	btnStnCWallNext->setPixmap(*pixSeekforward);
	btnUsrCWallPrev->setPixmap(*pixSeekback);
	btnUsrCWallNext->setPixmap(*pixSeekforward);
	
	
	cout << "Initialising Digital Playout Interface..." << endl;
	player1 = new playerThread(this, 1);
	player1->start();
	usleep(100000);
	player2 = new playerThread(this, 2);
	player2->start();
	usleep(100000);
	player3 = new playerThread(this, 3);
	player3->start();
	usleep(100000);
	cout << "Interface initialisation complete." << endl;
	
	cout << "Creating trigger on configuration settings..." << endl;
	QString dbconnect = "hostaddr=192.168.1.1 dbname=digiplay user=digiplay_user";
	dbTrigger = new triggerThread(this, dbconnect, 1, 5);
	dbTrigger->start();
	cout << "Trigger active." << endl;
}

void frmPlayout::destroy() {
	
}

// START Events ======================================================
void frmPlayout::customEvent(QCustomEvent *event) {
	//cout << "Event received: " << event->type() << endl;
	switch (event->type()) {
	case 20010: {       // Player1 Counter Update
			QString *s = (QString *) event->data();
			lblCounter1->setText(*s);
			break;
		}
	case 20011: {       // Player1 Slider Update
			int *s  = (int *) event->data();
			sldSeek1->setValue(*s);
			break;
		}
	case 20012: {       // Player1 Slider MaxValue Update
			int *s = (int *) event->data();
			sldSeek1->setMaxValue(*s);
			break;
		}
	case 20013: {       // Player1 Stop Event
			btnPlay1->setPixmap(*pixPlay);
			break;
		}
	case 20020: {       // Player2 Counter Update
			QString *s = (QString *) event->data();
			lblCounter2->setText(*s);
			break;
		}
	case 20021: {       // Player2 Slider Update
			int *s  = (int *) event->data();
			sldSeek2->setValue(*s);
			break;
		}
	case 20022: {       // Player2 Slider MaxValue Update
			int *s = (int *) event->data();
			sldSeek2->setMaxValue(*s);
			break;
		}
	case 20023: {       // Player2 Stop Event
			btnPlay2->setPixmap(*pixPlay);
			break;
		}
	case 20030: {       // Player3 Counter Update
			QString *s = (QString *) event->data();
			lblCounter3->setText(*s);
			break;
		}
	case 20031: {       // Player3 Slider Update
			int *s  = (int *) event->data();
			sldSeek3->setValue(*s);
			break;
		}
	case 20032: {       // Player3 Slider MaxValue Update
			int *s = (int *) event->data();
			sldSeek3->setMaxValue(*s);
			break;
		}
	case 20033: {       // Player2 Stop Event
			btnPlay3->setPixmap(*pixPlay);
			break;
		}   
	default: {
			qWarning("Unknown event type: %d", event->type());
			break;
		}
	}
}

void frmPlayout::Player1_Load() {
	player1->do_load(new QString("/mnt/dps0-0/audio/0/0330d8d87712848bc2f4e40e72abb06d"), 6927,10230667);
	lblTitle1->setText("My first title");
	lblArtist1->setText("My first artist");
	btnPlay1->setEnabled(true);
	btnStop1->setEnabled(true);
	btnSeekBack1->setEnabled(true);
	btnSeekForward1->setEnabled(true);
	sldSeek1->setEnabled(true);
}   

void frmPlayout::Player1_Play() {
	switch (player1->getState()) {
	case STATE_STOP:
		player1->do_play();
		btnPlay1->setPixmap(*pixPause);
		break;
	case STATE_PLAY:
		player1->do_pause();
		btnPlay1->setPixmap(*pixPlay);
		break;
	case STATE_PAUSE:
		player1->do_resume();
		btnPlay1->setPixmap(*pixPause);
		break;
	}
}

void frmPlayout::Player1_Stop() {
	player1->do_stop();
	btnPlay1->setEnabled(true);
}

void frmPlayout::Player2_Load() {
	player2->do_load(new QString("/mnt/dps0-0/audio/0/0330d8d87712848bc2f4e40e72abb06d"), 6927,10230667);
	lblTitle2->setText("My first title");
	lblArtist2->setText("My first artist");
	btnPlay2->setEnabled(true);
	btnStop2->setEnabled(true);
	btnSeekBack2->setEnabled(true);
	btnSeekForward2->setEnabled(true);
	sldSeek2->setEnabled(true);
}   

void frmPlayout::Player2_Play() {

	switch (player2->getState()) {
	case STATE_STOP:
		player2->do_play();
		btnPlay2->setPixmap(*pixPause);
		break;
	case STATE_PLAY:
		player2->do_pause();
		btnPlay2->setPixmap(*pixPlay);
		break;
	case STATE_PAUSE:
		player2->do_resume();
		btnPlay2->setPixmap(*pixPause);
		break;
	}
}

void frmPlayout::Player2_Stop() {
	player2->do_stop();
	btnPlay2->setEnabled(true);
}

void frmPlayout::Player3_Load() {
	player3->do_load(new QString("/mnt/dps0-0/audio/0/0330d8d87712848bc2f4e40e72abb06d"), 6927,10230667);
	lblTitle3->setText("My first title");
	lblArtist3->setText("My first artist");
	btnPlay3->setEnabled(true);
	btnStop3->setEnabled(true);
	btnSeekBack3->setEnabled(true);
	btnSeekForward3->setEnabled(true);
	sldSeek3->setEnabled(true);
}   

void frmPlayout::Player3_Play() {

	switch (player3->getState()) {
	case STATE_STOP:
		player3->do_play();
		btnPlay3->setPixmap(*pixPause);
		break;
	case STATE_PLAY:
		player3->do_pause();
		btnPlay3->setPixmap(*pixPlay);
		break;
	case STATE_PAUSE:
		player3->do_resume();
		btnPlay3->setPixmap(*pixPause);
		break;
	}
}

void frmPlayout::Player3_Stop() {
	player3->do_stop();
	btnPlay3->setEnabled(true);
}

