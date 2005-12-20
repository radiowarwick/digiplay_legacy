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
#include "config.h"

QString path;
QPixmap *pixPlay, *pixPause, *pixStop, *pixSeekback, *pixSeekforward, *pixReset;
playerThread *player1;
playerThread *player2;
playerThread *player3;
triggerThread *dbTrigger;
Connection *C;
config *conf;

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
	btnSCartPrev->setPixmap(*pixSeekback);
	btnSCartNext->setPixmap(*pixSeekforward);
	btnUCartPrev->setPixmap(*pixSeekback);
	btnUCartNext->setPixmap(*pixSeekforward);
	
	cout << "Connecting to database..." << endl;
	conf = new config("digiplay");
    QCustomEvent *config_refresh = new QCustomEvent(30000);
    QApplication::postEvent(this, config_refresh);
	C = new Connection(conf->getDBConnectString());
	cout << " -> Connected." << endl;
	
	cout << "Initialising Digital Playout Hardware..." << endl;
	player1 = new playerThread(this, 1);
	player2 = new playerThread(this, 2);	
	player3 = new playerThread(this, 3);
	player1->start();
	usleep(100000);
	player2->start();
	usleep(100000);
	player3->start();
	usleep(500000);
	cout << " -> Hardware initialisation complete." << endl;
	
	cout << "Creating trigger on configuration settings..." << endl;
	dbTrigger = new triggerThread(this, QString(conf->getDBConnectString()), 1, 5);
	cout << " -> Created trigger thread" << endl;
	dbTrigger->start();
	cout << " -> Trigger active." << endl;
}

void frmPlayout::destroy() {
	delete conf;
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
	case 30000: {
			conf->requery();
			if (conf->getParam("next_on_showplan") == "") {
				btnLoadPlaylist1->setEnabled(false);
				btnLoadPlaylist2->setEnabled(false);
				btnLoadPlaylist3->setEnabled(false);
			}
			else {
				btnLoadPlaylist1->setEnabled(true);
				btnLoadPlaylist2->setEnabled(true);
				btnLoadPlaylist3->setEnabled(true);
			}
			break;
		}
	default: {
			qWarning("Unknown event type: %d", event->type());
			break;
		}
	}
}

void frmPlayout::Player1_Load() {
	if (conf->getParam("next_on_showplan") == "") {
		return;
	}
	Transaction *T = new Transaction(*C,"");
	string SQL = "SELECT audio.md5 AS md5, audio.title AS title, artists.name as artist, "
				 "audio.intro_smpl as start, audio.extro_smpl as end, "
				 "archives.localpath AS path "
				 "FROM audio,artists,audioartists,archives "
				 "WHERE audio.archive=archives.id AND audioartists.audio=audio.id "
				 "AND audioartists.artist = artists.id AND audio.md5='" 
				 + conf->getParam("next_on_showplan") + "'";
	Result R = T->exec(SQL);
	T->abort();
	delete T;
	string f = R[0]["path"].c_str() + string("/") + (string(R[0]["md5"].c_str())).substr(0,1)
			   + string("/") + R[0]["md5"].c_str();
	player1->do_load(new QString(f), atoi(R[0]["start"].c_str()),atoi(R[0]["end"].c_str()));
	conf->setParam("next_on_showplan","");
	lblTitle1->setText(R[0]["title"].c_str());
	lblArtist1->setText(R[0]["artist"].c_str());
	btnPlay1->setEnabled(true);
	btnStop1->setEnabled(true);
	btnSeekBack1->setEnabled(true);
	btnSeekForward1->setEnabled(true);
	sldSeek1->setEnabled(true);
}   

void frmPlayout::Player1_Play() {
	cout << "State: " << player1->getState() << endl;
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
	if (conf->getParam("next_on_showplan") == "") {
		return;
	}
	Transaction *T = new Transaction(*C,"");
	string SQL = "SELECT audio.md5 AS md5, audio.title AS title, artists.name as artist, "
				 "audio.intro_smpl as start, audio.extro_smpl as end, "
				 "archives.localpath AS path "
				 "FROM audio,artists,audioartists,archives "
				 "WHERE audio.archive=archives.id AND audioartists.audio=audio.id "
				 "AND audioartists.artist = artists.id AND audio.md5='" 
				 + conf->getParam("next_on_showplan") + "'";
	Result R = T->exec(SQL);
	T->abort();
	delete T;
	string f = R[0]["path"].c_str() + string("/") + (string(R[0]["md5"].c_str())).substr(0,1)
			   + string("/") + R[0]["md5"].c_str();
	player2->do_load(new QString(f), atoi(R[0]["start"].c_str()),atoi(R[0]["end"].c_str()));
	conf->setParam("next_on_showplan","");
	lblTitle2->setText(R[0]["title"].c_str());
	lblArtist2->setText(R[0]["artist"].c_str());
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
	if (conf->getParam("next_on_showplan") == "") {
		return;
	}
	Transaction *T = new Transaction(*C,"");
	string SQL = "SELECT audio.md5 AS md5, audio.title AS title, artists.name as artist, "
				 "audio.intro_smpl as start, audio.extro_smpl as end, "
				 "archives.localpath AS path "
				 "FROM audio,artists,audioartists,archives "
				 "WHERE audio.archive=archives.id AND audioartists.audio=audio.id "
				 "AND audioartists.artist = artists.id AND audio.md5='" 
				 + conf->getParam("next_on_showplan") + "'";
	Result R = T->exec(SQL);
	T->abort();
	delete T;
	string f = R[0]["path"].c_str() + string("/") + (string(R[0]["md5"].c_str())).substr(0,1)
			   + string("/") + R[0]["md5"].c_str();
	player3->do_load(new QString(f), atoi(R[0]["start"].c_str()),atoi(R[0]["end"].c_str()));
	conf->setParam("next_on_showplan","");
	lblTitle3->setText(R[0]["title"].c_str());
	lblArtist3->setText(R[0]["artist"].c_str());
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



void frmPlayout::Player1_Time() {
    if (lblPlayerTime1->text() == "REMAIN") {
        lblPlayerTime1->setText("ELAPSED");
        player1->setTimeMode(TIME_MODE_ELAPSED);
    }
    else {
        lblPlayerTime1->setText("REMAIN");
        player1->setTimeMode(TIME_MODE_REMAIN);
    }	
}


void frmPlayout::Player2_Time(){
    if (lblPlayerTime2->text() == "REMAIN") {
        lblPlayerTime2->setText("ELAPSED");
        player2->setTimeMode(TIME_MODE_ELAPSED);
    }
    else {
        lblPlayerTime2->setText("REMAIN");
        player2->setTimeMode(TIME_MODE_REMAIN);
    }	
}


void frmPlayout::Player3_Time() {
    if (lblPlayerTime3->text() == "REMAIN") {
        lblPlayerTime3->setText("ELAPSED");
        player3->setTimeMode(TIME_MODE_ELAPSED);
    }
    else {
        lblPlayerTime3->setText("REMAIN");
        player3->setTimeMode(TIME_MODE_REMAIN);
    }	
}
