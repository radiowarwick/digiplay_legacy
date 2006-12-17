/*
 * Studio Playout application
 * frmPlayout.ui.h
 * A studio playout application
 *
 * Copyright (c) 2004-2006 Chris Cantwell
 * Copyright (c) 2004-2006 Ian Liverton
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
#include "remoteStartThread.h"

void frmPlayout::init() {
	path = qApp->applicationDirPath();
	pixPlay = new QPixmap(path + "/images/play.png");
	pixPause = new QPixmap(path + "/images/pause.png");
	pixStop = new QPixmap(path + "/images/stop.png");
	pixSeekback = new QPixmap(path + "/images/fastbackward.png");
	pixSeekforward = new QPixmap(path + "/images/fastforward.png");
	pixReset = new QPixmap(path + "/images/reset.png");
	
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

    cout << "Connecting to database..." << endl;
    conf = new config("digiplay");
	C = new Connection(conf->getDBConnectString());
	cout << " -> Connected." << endl;

	cout << "Initialising Digital Playout Hardware..." << endl;
	player1 = new playerThread(this, 1);
	player2 = new playerThread(this, 2);	
	player3 = new playerThread(this, 3);
//	remoteStartThread *remotes = new remoteStartThread(this);
	player1->start();
	usleep(100000);
	player2->start();
	usleep(100000);
	player3->start();
	usleep(100000);
//	remotes->start();
//	usleep(500000);
	cout << " -> Hardware initialisation complete." << endl;

	QCustomEvent *config_refresh = new QCustomEvent(30001);
	QApplication::postEvent(this, config_refresh);

	cout << "Creating trigger on configuration settings..." << endl;
	dbTrigger = new triggerThread(this, QString(conf->getDBConnectString()), 1);
	cout << " -> Created trigger thread" << endl;
	dbTrigger->start();
	cout << " -> Trigger active." << endl;

	AudioWall *stnAudioWall = new AudioWall(this,"stnAudioWall",4,3,4);
	stnAudioWall->setGeometry(560,0,460,373);
	stnAudioWallMan = new AudioWallManager(stnAudioWall,C);
	stnAudioWallMan->load(atoi(conf->getParam("station_cartset").c_str()));
	
	AudioWall *usrAudioWall = new AudioWall(this,"usrAudioWall",4,3,stnAudioWall);
	usrAudioWall->setGeometry(560,373,460,373);
	usrAudioWallMan = new AudioWallManager(usrAudioWall,C);
	usrAudioWallMan->load(atoi(conf->getParam("user_cartset").c_str()));

	cout << "Finished init" << endl;
}

void frmPlayout::destroy() {
	delete conf;
}

// START Events ======================================================
void frmPlayout::customEvent(QCustomEvent *event) {
	switch (event->type()) {
		case 20001:	{
			eventData *e_data = (eventData*)event->data();
			switch (e_data->t) {
				case EVENT_TYPE_STOP: {
					btnPlay1->setPixmap(*pixPlay);
					if (conf->getParam("next_on_showplan") != "") {
			        	btnLoadPlaylist1->setEnabled(true);
					}
					lblCounter1->setPaletteForegroundColor(QColor(QRgb(0)));
					if (lblPlayerTime1->text() == "REMAIN")
					    lblCounter1->setText(getTime(player1->getLength()));
					else
					    lblCounter1->setText(getTime(0));
					sldSeek1->setValue(0);
					sldSeek1->setMaxValue(player1->getLength());
		        	break;
				}
				case EVENT_TYPE_PLAY: {
					break;
				}
				case EVENT_TYPE_SMPL: {
					sldSeek1->setValue(e_data->smpl);
                    if (e_data->smpl != 0 
							&& (player1->getLength()-e_data->smpl)/44100 < 20) {
						lblCounter1->setPaletteForegroundColor(
											QColor(QRgb(16711680)));
					}
					else {
						lblCounter1->setPaletteForegroundColor(
											QColor(QRgb(0)));
					}
					if (lblPlayerTime1->text() == "REMAIN") {
						e_data->smpl = player1->getLength() - e_data->smpl;
					}
					lblCounter1->setText(getTime(e_data->smpl));
					break;
				}
				case EVENT_TYPE_MAX_SMPL: {
					sldSeek1->setMaxValue(e_data->smpl);
					break;
				}
				case EVENT_TYPE_END: {
					break;
				}
			}
			break;
		}
		case 20002: {
            eventData *e_data = (eventData*)event->data();
            switch (e_data->t) {
                case EVENT_TYPE_STOP: {
                    btnPlay2->setPixmap(*pixPlay);
					if (conf->getParam("next_on_showplan") != "") {
	                    btnLoadPlaylist2->setEnabled(true);
					}
                    lblCounter2->setPaletteForegroundColor(QColor(QRgb(0)));
					if (lblPlayerTime2->text() == "REMAIN")
					    lblCounter2->setText(getTime(player2->getLength()));
					else
					    lblCounter2->setText(getTime(0));
					sldSeek2->setValue(0);
					sldSeek2->setMaxValue(player2->getLength());
                    break;
                }
                case EVENT_TYPE_PLAY: {
                    break;
                }
                case EVENT_TYPE_SMPL: {
					sldSeek2->setValue(e_data->smpl);
                    if (e_data->smpl != 0 
							&& (player2->getLength()-e_data->smpl)/44100 < 20) {
                        lblCounter2->setPaletteForegroundColor(
                                            QColor(QRgb(16711680)));
                    }
                    else {
                        lblCounter2->setPaletteForegroundColor(
                                            QColor(QRgb(0)));
                    }
					if (lblPlayerTime2->text() == "REMAIN") {
						e_data->smpl = player2->getLength() - e_data->smpl;
					}
					lblCounter2->setText(getTime(e_data->smpl));
                    break;
                }
                case EVENT_TYPE_MAX_SMPL: {
					sldSeek2->setMaxValue(e_data->smpl);
                    break;
                }
                case EVENT_TYPE_END: {
                    break;
                }
            }
			break;
		}
		case 20003: {
            eventData *e_data = (eventData*)event->data();
            switch (e_data->t) {
                case EVENT_TYPE_STOP: {
                    btnPlay3->setPixmap(*pixPlay);
					if (conf->getParam("next_on_showplan") != "") {
	                    btnLoadPlaylist3->setEnabled(true);
					}
                    lblCounter3->setPaletteForegroundColor(QColor(QRgb(0)));
					if (lblPlayerTime3->text() == "REMAIN")
					    lblCounter3->setText(getTime(player3->getLength()));
					else
					    lblCounter3->setText(getTime(0));
					sldSeek3->setValue(0);
					sldSeek3->setMaxValue(player3->getLength());
                    break;
                }
                case EVENT_TYPE_PLAY: {
                    break;
                }
                case EVENT_TYPE_SMPL: {
					sldSeek3->setValue(e_data->smpl);
                    if (e_data->smpl != 0 
							&& (player3->getLength()-e_data->smpl)/44100 < 20) {
                        lblCounter3->setPaletteForegroundColor(
                                            QColor(QRgb(16711680)));
                    }
                    else {
                        lblCounter3->setPaletteForegroundColor(
                                            QColor(QRgb(0)));
                    }
					if (lblPlayerTime3->text() == "REMAIN") {
						e_data->smpl = player3->getLength() - e_data->smpl;
					}
					lblCounter3->setText(getTime(e_data->smpl));
                    break;
                }
                case EVENT_TYPE_MAX_SMPL: {
					sldSeek3->setMaxValue(e_data->smpl);
                    break;
                }
                case EVENT_TYPE_END: {
                    break;
                }
            }
			break;
		}							  
	case 30001: {
			conf->requery();
			// Configure load buttons
			if (conf->getParam("next_on_showplan") == "") {
				btnLoadPlaylist1->setEnabled(false);
				btnLoadPlaylist2->setEnabled(false);
				btnLoadPlaylist3->setEnabled(false);
			}
			else {
				if (player1->getState() != STATE_PLAY)
					btnLoadPlaylist1->setEnabled(true);
				if (player2->getState() != STATE_PLAY)
					btnLoadPlaylist2->setEnabled(true);
				if (player3->getState() != STATE_PLAY)
					btnLoadPlaylist3->setEnabled(true);
			}
			// Configure cartsets if they've changed
			if (atoi(conf->getParam("station_cartset").c_str()) 
					!= stnAudioWallMan->getCartset()) {
				cout << "Load on cartset" << endl;
				stnAudioWallMan->load(atoi(conf->getParam("station_cartset").c_str()));

			}
			if (atoi(conf->getParam("user_cartset").c_str())
 				!= usrAudioWallMan->getCartset()) {
				usrAudioWallMan->load(atoi(conf->getParam("user_cartset").c_str()));
			}
			break;
		}
	case 40000: {
		switch (player1->getState()) {
			case STATE_STOP: {
				player1->do_play();
				btnPlay1->setPixmap(*pixPause);
				btnLoadPlaylist1->setEnabled(false);
				break;
			}
			case STATE_PAUSE: {
				player1->do_resume();
				btnPlay1->setPixmap(*pixPause);
				btnLoadPlaylist1->setEnabled(false);
				break;
			}
		}
		break;
	}
	case 40001: {
		if (player1->getState() == STATE_PLAY) {
			player1->do_pause();
			btnPlay1->setPixmap(*pixPlay);
			if (conf->getParam("next_on_showplan") != "") {
				btnLoadPlaylist1->setEnabled(true);
			}
		}
		break;
	}
	case 40002: {
		switch (player2->getState()) {
			case STATE_STOP: {
				player2->do_play();
				btnPlay2->setPixmap(*pixPause);
				btnLoadPlaylist2->setEnabled(false);
				break;
			}
			case STATE_PAUSE: {
				player2->do_resume();
				btnPlay2->setPixmap(*pixPause);
				btnLoadPlaylist2->setEnabled(false);
				break;
			}
		}
		break;
	}
	case 40003: {
		if (player2->getState() == STATE_PLAY) {
			player2->do_pause();
			btnPlay2->setPixmap(*pixPlay);
			if (conf->getParam("next_on_showplan") != "") {
				btnLoadPlaylist2->setEnabled(true);
			}
		}
		break;
	}
	case 40004: {
		switch (player3->getState()) {
			case STATE_STOP: {
				player3->do_play();
				btnPlay3->setPixmap(*pixPause);
				btnLoadPlaylist3->setEnabled(false);
				break;
			}
			case STATE_PAUSE: {
				player3->do_resume();
				btnPlay3->setPixmap(*pixPause);
				btnLoadPlaylist3->setEnabled(false);
				break;
			}
		}
		break;
	}
	case 40005: {
		if (player3->getState() == STATE_PLAY) {
			player3->do_pause();
			btnPlay3->setPixmap(*pixPlay);
			if (conf->getParam("next_on_showplan") != "") {
				btnLoadPlaylist3->setEnabled(true);
			}
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
	btnLoadPlaylist1->setEnabled(false);
	if (conf->getParam("next_on_showplan") == "") {
		return;
	}
	Transaction T(*C,"");
	string SQL = "SELECT audio.md5 AS md5, audio.title AS title, artists.name as artist, "
				 "audio.intro_smpl as start, audio.extro_smpl as end, "
				 "archives.localpath AS path "
				 "FROM audio,artists,audioartists,archives "
				 "WHERE audio.archive=archives.id AND audioartists.audio=audio.id "
				 "AND audioartists.artist = artists.id AND audio.md5='" 
				 + conf->getParam("next_on_showplan") + "'";
	Result R = T.exec(SQL);
	T.abort();

	string f = R[0]["path"].c_str() + string("/") + (string(R[0]["md5"].c_str())).substr(0,1)
			   + string("/") + R[0]["md5"].c_str();
	player1->do_load(new QString(f), atoi(R[0]["start"].c_str()),atoi(R[0]["end"].c_str()));
	conf->setParam("next_on_showplan","");
	lblTitle1->setText(R[0]["title"].c_str());
	lblArtist1->setText(R[0]["artist"].c_str());
	btnPlay1->setEnabled(true);
	btnStop1->setEnabled(true);
	//btnSeekBack1->setEnabled(true);
	//btnSeekForward1->setEnabled(true);
	sldSeek1->setEnabled(true);
}   

void frmPlayout::Player1_Play() {
	switch (player1->getState()) {
	case STATE_STOP:
		player1->do_play();
		btnPlay1->setPixmap(*pixPause);
		btnLoadPlaylist1->setEnabled(false);
		break;
	case STATE_PLAY:
		player1->do_pause();
		btnPlay1->setPixmap(*pixPlay);
		if (conf->getParam("next_on_showplan") != "") {
			btnLoadPlaylist1->setEnabled(true);
		}
		break;
	case STATE_PAUSE:
		player1->do_resume();
		btnPlay1->setPixmap(*pixPause);
		btnLoadPlaylist1->setEnabled(false);
		break;
	}
}

void frmPlayout::Player1_Stop() {
	player1->do_stop();
	btnPlay1->setEnabled(true);
	if (conf->getParam("next_on_showplan") != "") {
		btnLoadPlaylist1->setEnabled(true);
	}
}


void frmPlayout::Player1_Seek() {
	player1->do_seek(sldSeek1->value());
}

void frmPlayout::Player2_Load() {
	btnLoadPlaylist2->setEnabled(false);
	if (conf->getParam("next_on_showplan") == "") {
		return;
	}
	Transaction T(*C,"");
	string SQL = "SELECT audio.md5 AS md5, audio.title AS title, artists.name as artist, "
				 "audio.intro_smpl as start, audio.extro_smpl as end, "
				 "archives.localpath AS path "
				 "FROM audio,artists,audioartists,archives "
				 "WHERE audio.archive=archives.id AND audioartists.audio=audio.id "
				 "AND audioartists.artist = artists.id AND audio.md5='" 
				 + conf->getParam("next_on_showplan") + "'";
	Result R = T.exec(SQL);
	T.abort();
	
	string f = R[0]["path"].c_str() + string("/") + (string(R[0]["md5"].c_str())).substr(0,1)
			   + string("/") + R[0]["md5"].c_str();
	player2->do_load(new QString(f), atoi(R[0]["start"].c_str()),atoi(R[0]["end"].c_str()));
	conf->setParam("next_on_showplan","");
	lblTitle2->setText(R[0]["title"].c_str());
	lblArtist2->setText(R[0]["artist"].c_str());
	btnPlay2->setEnabled(true);
	btnStop2->setEnabled(true);
	//btnSeekBack2->setEnabled(true);
	//btnSeekForward2->setEnabled(true);
	sldSeek2->setEnabled(true);
}   

void frmPlayout::Player2_Play() {

	switch (player2->getState()) {
	case STATE_STOP:
		player2->do_play();
		btnPlay2->setPixmap(*pixPause);
		btnLoadPlaylist2->setEnabled(false);
		break;
	case STATE_PLAY:
		player2->do_pause();
		btnPlay2->setPixmap(*pixPlay);
		if (conf->getParam("next_on_showplan") != "") {
			btnLoadPlaylist2->setEnabled(true);
		}
		break;
	case STATE_PAUSE:
		player2->do_resume();
		btnPlay2->setPixmap(*pixPause);
		btnLoadPlaylist2->setEnabled(false);
		break;
	}
}

void frmPlayout::Player2_Stop() {
	player2->do_stop();
	btnPlay2->setEnabled(true);
	if (conf->getParam("next_on_showplan") != "") {
		btnLoadPlaylist2->setEnabled(true);
	}
}


void frmPlayout::Player2_Seek() {
	player2->do_seek(sldSeek2->value());
}

void frmPlayout::Player3_Load() {
	btnLoadPlaylist3->setEnabled(false);
	if (conf->getParam("next_on_showplan") == "") {
		return;
	}
	Transaction T(*C,"");
	string SQL = "SELECT audio.md5 AS md5, audio.title AS title, artists.name as artist, "
				 "audio.intro_smpl as start, audio.extro_smpl as end, "
				 "archives.localpath AS path "
				 "FROM audio,artists,audioartists,archives "
				 "WHERE audio.archive=archives.id AND audioartists.audio=audio.id "
				 "AND audioartists.artist = artists.id AND audio.md5='" 
				 + conf->getParam("next_on_showplan") + "'";
	Result R = T.exec(SQL);
	T.abort();

	string f = R[0]["path"].c_str() + string("/") + (string(R[0]["md5"].c_str())).substr(0,1)
			   + string("/") + R[0]["md5"].c_str();
	player3->do_load(new QString(f), atoi(R[0]["start"].c_str()),atoi(R[0]["end"].c_str()));
	conf->setParam("next_on_showplan","");
	lblTitle3->setText(R[0]["title"].c_str());
	lblArtist3->setText(R[0]["artist"].c_str());
	btnPlay3->setEnabled(true);
	btnStop3->setEnabled(true);
	//btnSeekBack3->setEnabled(true);
	//btnSeekForward3->setEnabled(true);
	sldSeek3->setEnabled(true);
}   

void frmPlayout::Player3_Play() {
	switch (player3->getState()) {
	case STATE_STOP:
		player3->do_play();
		btnPlay3->setPixmap(*pixPause);
		btnLoadPlaylist3->setEnabled(false);
		break;
	case STATE_PLAY:
		player3->do_pause();
		btnPlay3->setPixmap(*pixPlay);
		if (conf->getParam("next_on_showplan") != "") {
			btnLoadPlaylist3->setEnabled(true);
		}
		break;
	case STATE_PAUSE:
		player3->do_resume();
		btnPlay3->setPixmap(*pixPause);
		btnLoadPlaylist3->setEnabled(false);
		break;
	}
}

void frmPlayout::Player3_Stop() {
	player3->do_stop();
	btnPlay3->setEnabled(true);
	if (conf->getParam("next_on_showplan") != "") {
		btnLoadPlaylist3->setEnabled(true);
	}
}

void frmPlayout::Player3_Seek() {
    player3->do_seek(sldSeek3->value());
}

void frmPlayout::Player1_Time() {
    if (lblPlayerTime1->text() == "REMAIN") {
        lblPlayerTime1->setText("ELAPSED");
    }
    else {
        lblPlayerTime1->setText("REMAIN");
    }	
	player1->do_updateCounter();
}


void frmPlayout::Player2_Time(){
    if (lblPlayerTime2->text() == "REMAIN") {
        lblPlayerTime2->setText("ELAPSED");
    }
    else {
        lblPlayerTime2->setText("REMAIN");
    }	
	player2->do_updateCounter();
}


void frmPlayout::Player3_Time() {
    if (lblPlayerTime3->text() == "REMAIN") {
        lblPlayerTime3->setText("ELAPSED");
    }
    else {
        lblPlayerTime3->setText("REMAIN");
    }
	player3->do_updateCounter();
}

QString frmPlayout::getTime( long smpl ) {
	QString S;
	int mil, sec, min;
	
	mil = smpl/441;
    sec = (int)(mil / 100);
    mil = mil%100;
    min = (int)(sec / 60);
    sec = sec%60;
	if (min < 10) S += "0";
	S += QString::number(min) + ":";
	if (sec < 10) S += "0";
	S += QString::number(sec) + ".";
    if (mil < 10) S += "0";
	S += QString::number(mil);
	return S;
}
