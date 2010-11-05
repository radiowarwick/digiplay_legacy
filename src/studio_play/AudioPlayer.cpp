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
#include <cstdlib>
using namespace std;

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtCore/QEvent>

#include "Logger.h"
#include "dps.h"

#include "audiolib/Audio.h"
#include "audiolib/Input.h"
#include "audiolib/InputFile.h"
#include "audiolib/OutputDsp.h"
#include "audiolib/Counter.h"
using namespace Audio;

#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(QWidget *parent, unsigned short playerId)
        : QWidget(parent) {

    drawCreate();
    id = QString::number(playerId);
    DB = new DataAccess();
    conf = new Config("digiplay",this);
    std::string device = conf->getParam("channel_" + id.toStdString());
	location = atoi( conf->getParam("LOCATION").c_str() );
    conf->setParam("player" + id.toStdString() + "_md5","");
    grpFrame = 0;

    // Setup track end counter
    ck = new clockThread(this);
    ck->start();

    // Setup audio
    _lastSample = 0;
	// Set up new InputRaw with 10 minute cache for network resiliance
    audioFilereader = 0;
    audioPlayer = new OutputDsp(device);

    length_hours = 0;
    length_mins = 0;
    length_secs = 0;
    mRedCounter = false;
}

AudioPlayer::~AudioPlayer() {
    clean();
}

void AudioPlayer::customEvent(QEvent *event) {
    const char *routine = "AudioPlayer::customEvent";
    switch (event->type()) {
    case 20000: {       // Clock update
            updateEndTime(dynamic_cast<ClockUpdateEvent*>(event)->data());
            break;
        }
    case 20001: {       // Date update - unused
            break;
        }
    case 20002: {
        lblCounter->setStyleSheet("color: rgb(255,0,0);");
        break;
    }
    case 20003: {
        lblCounter->setStyleSheet("color: rgb(0,0,0);");
        break;
    }
    default: {
            qWarning("Unknown event type: %d", event->type());
            L_WARNING(LOG_DB,"Unknown event type: " + dps_itoa(event->type()));
            break;
        }
    }
}


void AudioPlayer::load() {
    const char *routine = "AudioPlayer::load";
    btnLoad->setEnabled(false);

    if (conf->getParam("next_on_showplan") == "") {
        return;
    }

    string SQL = "SELECT * FROM v_audio WHERE md5='"
                    + conf->getParam("next_on_showplan") + "'";
    PqxxResult R = DB->exec("AudioPlayerLoad",SQL);
    DB->abort("AudioPlayerLoad");

    if (R.size() == 0) {
        L_ERROR(LOG_PLAYOUT, "No such track!");
        return;
    }

    string ext = "";
    string filetype(R[0]["filetype"].c_str());

    if (filetype == "raw") {
    }
    else if (filetype == "flac") {
        ext = ".flac";
    }
    else if (filetype == "mp3") {
        ext = ".mp3";
    }
    else {
        cout << "Unknown file type: " << filetype << endl;
    }
    if (!audioFilereader) {
        audioFilereader = new InputFile(105840000);
        audioFilereader->patch(OUT0,audioPlayer,IN0);
        audioFilereader->addCounter(this);
    }
    string f = R[0]["path"].c_str() + string("/")
                + (string(R[0]["md5"].c_str())).substr(0,1)
                + string("/") + R[0]["md5"].c_str() + ext;

    audioFilereader->load(f, atoi(R[0]["start_smpl"].c_str()),
                                    atoi(R[0]["end_smpl"].c_str()));

    conf->setParam("next_on_showplan","");
    conf->setParam("player" + id.toStdString() + "_md5", string(R[0]["md5"].c_str()));

    lblTitle->setText(R[0]["title"].c_str());
    lblArtist->setText(R[0]["artist"].c_str());
    btnPlay->setEnabled(true);
    btnStop->setEnabled(true);
    btnLog->setEnabled(true);
    sldSeek->setEnabled(true);

    // Set last sample to be the end sample and update counter
    _lastSample = _totalSamples;
    onSetSample();
}

void AudioPlayer::updateEndTime(QString pTime){
    int current_position = (_totalSamples-_currentSample) / 44100;
    if ((_totalSamples-_currentSample) % 44100 > 22050) {
        current_position++;
    }
    int time_hours = pTime.section(':', 0, 0).toInt();
    int time_mins = pTime.section(':', 1, 1).toInt();
    int time_secs = pTime.section(':', 2, 2).toInt();
    length_hours = current_position / 3600;
    length_mins = (current_position % 3600) / 60;
    length_secs = ((current_position % 3600) % 60);
    int carry=0;
    time_secs += length_secs;
    if (time_secs >= 60) {
        time_secs -= 60;
        carry++;;
    }
    time_mins += length_mins + carry;
    if (time_mins >= 60) {
        time_mins -= 60;
        carry = 1;
    }
    else {
        carry = 0;
    }
    time_hours += length_hours + carry;
    if (time_hours >= 24) {
        time_hours -= 24;
    }
    QString hours = QString::number(time_hours);
    QString mins = QString::number(time_mins);
    QString secs = QString::number(time_secs);
    if (secs.length() == 1) secs = "0" + secs;
    if (mins.length() == 1) mins = "0" + mins;
    if (hours.length() == 1) hours = "0" + hours;

    lblEnd->setText(hours + ":" + mins + ":" + secs);
}

void AudioPlayer::log() {
	btnLog->setEnabled(false);

	// Get current time
    int now = (int)time(NULL);

    // Escape the artist and title
    string artist = DB->esc(lblArtist->text().toStdString());
    string title = DB->esc(lblTitle->text().toStdString());

    // Try and insert into database
    string SQL = "INSERT INTO log "
                "(userid, datetime, track_title, track_artist, location) "
                "VALUES (" + dps_itoa(userid) + ", " + dps_itoa(now) + ", '"
                + title + "', '" + artist + "', " + dps_itoa(location) + ");";
    DB->exec("AudioPlayerLog",SQL);
    DB->commit("AudioPlayerLog");
}

void AudioPlayer::play() {
    if (audioFilereader) {
        if (_state == STATE_PLAY) {
            audioFilereader->pause();
        }
        else {
            audioFilereader->play();
        }
    }
}

void AudioPlayer::pause() {
    if (_state == STATE_PLAY) {
        audioFilereader->pause();
    }
}

void AudioPlayer::stop() {
    audioFilereader->stop();
}

void AudioPlayer::seek() {
    seek(sldSeek->value());
}

void AudioPlayer::seek(unsigned long sample) {
    audioFilereader->seek(sample);
}

void AudioPlayer::setTimeDisplay() {
    if (lblTime->text() == "ELAPSED") {
        lblTime->setText( tr( "REMAIN" ) );
    }
    else {
        lblTime->setText( tr( "ELAPSED" ) );
    }
    onSetSample();
}

void AudioPlayer::onMessage() {
    const char *routine = "AudioPlayer::onMessage";

    if (conf->getParam("next_on_showplan") == "") {
        L_INFO(LOG_PLAYOUT, "Config updated: DISABLED LOAD");
        btnLoad->setEnabled(false);
    }
    else if (_state == STATE_STOP) {
        L_INFO(LOG_PLAYOUT, "Config updated: ENABLED LOAD");
        btnLoad->setEnabled(true);
    }
	userid = atoi(conf->getParam("userid").c_str());
}

void AudioPlayer::onSetSample() {
    if (_state == STATE_PLAY && _currentSample - _lastSample < 1764) return;

    if ((_totalSamples - _currentSample)/44100 < 20 && !mRedCounter) {
        mRedCounter = true;
        QApplication::postEvent(this, new QEvent((QEvent::Type)20002));
    }
    else if ((_totalSamples - _currentSample)/44100 > 20 && mRedCounter) {
        mRedCounter = false;
        QApplication::postEvent(this, new QEvent((QEvent::Type)20003));
    }

    _lastSample = _currentSample;
    sldSeek->setValue(_currentSample);

    if (lblTime->text() == "REMAIN") {
	    lblCounter->setText(getTime(_totalSamples - _currentSample));
	}
	else {
      	lblCounter->setText(getTime(_currentSample));
	}
}

void AudioPlayer::onSetState() {
    switch (_state) {
        case STATE_PLAY:
            {
                btnLoad->setEnabled(false);
                sldSeek->setEnabled(false);
                btnPlay->setIcon(icnPause);
            }
            break;
        case STATE_STOP:
            {
            	bool loaded = audioFilereader->isLoaded();
                if (loaded) {
                    btnPlay->setEnabled(true);
                }

                if (conf->getParam("next_on_showplan") != "") {
                    btnLoad->setEnabled(true);
                }
                btnPlay->setIcon(icnPlay);
                sldSeek->setMaximum(_totalSamples);
                sldSeek->setEnabled(true);
                onSetSample();
            }
            break;
        case STATE_PAUSE:
            {
                btnPlay->setIcon(icnPlay);
                sldSeek->setEnabled(true);
            }
            break;
    }
}

void AudioPlayer::onSetTotalSamples() {
    sldSeek->setMaximum(_totalSamples);
}

QString AudioPlayer::getTime( long smpl ) {
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

void AudioPlayer::drawCreate() {
    QString path = DPSDIR;

    icnPlay = QIcon(":/icons/play.png");
    icnPause = QIcon(":/icons/pause.png");

    grpFrame = new QGroupBox( this );
    grpFrame->setGeometry( QRect( 0, 0, 540, 240 ) );
    QFont grpFrame_font(  grpFrame->font() );
    grpFrame_font.setPointSize( 12 );
    grpFrame_font.setBold( TRUE );
    grpFrame->setFont( grpFrame_font );
    grpFrame->setTitle( "Audio Player " + id);

    lblTime = new QLabel( grpFrame );
    lblTime->setGeometry( QRect( 270, 100, 110, 17 ) );
    QFont lblTime_font(  lblTime->font() );
    lblTime_font.setPointSize( 10 );
    lblTime->setFont( lblTime_font );
    lblTime->setAlignment( Qt::AlignCenter );
    lblTime->setText( tr( "REMAIN" ) );

    btnTimeMode = new QPushButton( grpFrame );
    btnTimeMode->setGeometry( QRect( 280, 60, 90, 40 ) );
    QFont btnTimeMode_font(  btnTimeMode->font() );
    btnTimeMode_font.setPointSize( 10 );
    btnTimeMode_font.setBold( FALSE );
    btnTimeMode->setFont( btnTimeMode_font );
    btnTimeMode->setText( tr( "Time Mode") );
    connect(btnTimeMode,SIGNAL(pressed()),this,SLOT(setTimeDisplay()));

    lblCounter = new QLabel( grpFrame );
    lblCounter->setGeometry( QRect( 10, 54, 260, 45 ) );
    QFont lblCounter_font(  lblCounter->font() );
    lblCounter_font.setPointSize( 24 );
    lblCounter->setFont( lblCounter_font );
    lblCounter->setAlignment( Qt::AlignVCenter | Qt::AlignLeft );
    lblCounter->setText( tr( "00:00.00" ) );

    lblEndlbl = new QLabel( grpFrame );
    lblEndlbl->setGeometry( QRect( 10, 96, 80, 15 ) );
    QFont lblEndlbl_font(  lblEndlbl->font() );
    lblEndlbl_font.setPointSize( 10 );
    lblEndlbl->setFont( lblEndlbl_font );
    lblEndlbl->setAlignment( Qt::AlignVCenter | Qt::AlignLeft );
    lblEndlbl->setText( tr( "End Time:" ) );

    lblEnd = new QLabel( grpFrame );
    lblEnd->setGeometry( QRect( 90, 96, 180, 15 ) );
    QFont lblEnd_font(  lblEnd->font() );
    lblEnd_font.setPointSize( 10 );
    lblEnd->setFont( lblEnd_font );
    lblEnd->setAlignment( Qt::AlignVCenter | Qt::AlignLeft );
    lblEnd->setText( tr( "--:--:--" ) );

    btnLog = new QPushButton( grpFrame );
    btnLog->setGeometry( QRect( 390, 20, 140, 40 ) );
    QFont btnLog_font(  btnLog->font() );
    btnLog_font.setPointSize( 14 );
    btnLog->setFont( btnLog_font );
    btnLog->setText( tr( "Log this!" ) );
    btnLog->setEnabled(false);
    connect(btnLog,SIGNAL(pressed()),this,SLOT(log()));

    btnLoad = new QPushButton( grpFrame );
    btnLoad->setGeometry( QRect( 390, 60, 140, 40 ) );
    QFont btnLoad_font(  btnLoad->font() );
    btnLoad_font.setPointSize( 14 );
    btnLoad->setFont( btnLoad_font );
    btnLoad->setText( tr( "Load" ) );
    connect(btnLoad,SIGNAL(pressed()),this,SLOT(load()));

    btnStop = new QPushButton( grpFrame );
    btnStop->setEnabled( FALSE );
    btnStop->setGeometry( QRect( 10, 159, 110, 70 ) );
    btnStop->setText( QString::null );
    btnStop->setIcon( QIcon(":/icons/stop.png") );
    btnStop->setIconSize( QSize(64,64) );
    connect( btnStop, SIGNAL(pressed()), this, SLOT(stop()) );

    btnPlay = new QPushButton( grpFrame );
    btnPlay->setEnabled( FALSE );
    btnPlay->setGeometry( QRect( 130, 159, 110, 70 ) );
    btnPlay->setText( QString::null );
    btnPlay->setIcon( icnPlay );
    btnPlay->setIconSize( QSize(64,64) );
    connect( btnPlay, SIGNAL(pressed()), this, SLOT(play()) );

    btnReset = new QPushButton( grpFrame );
    btnReset->setEnabled( FALSE );
    btnReset->setGeometry( QRect( 290, 159, 80, 70 ) );
    btnReset->setText( QString::null );
    btnReset->setIcon( QIcon(":/icons/reset.png") );
    btnReset->setIconSize( QSize(64,64) );

    btnSeekBack = new QPushButton( grpFrame );
    btnSeekBack->setEnabled( FALSE );
    btnSeekBack->setGeometry( QRect( 370, 159, 80, 70 ) );
    btnSeekBack->setText( QString::null );
    btnSeekBack->setIcon( QIcon(":/icons/fastbackward.png") );
    btnSeekBack->setIconSize( QSize(64,64) );

    btnSeekForward = new QPushButton( grpFrame );
    btnSeekForward->setEnabled( FALSE );
    btnSeekForward->setGeometry( QRect( 450, 159, 80, 70 ) );
    btnSeekForward->setText( QString::null );
    btnSeekForward->setIcon( QIcon(":/icons/fastforward.png" ) );
    btnSeekForward->setIconSize( QSize(64,64) );

    sldSeek = new QSlider( grpFrame );
    sldSeek->setGeometry( QRect( 10, 120, 520, 29 ) );
    sldSeek->setSizePolicy( QSizePolicy( QSizePolicy::Expanding,
    			QSizePolicy::Preferred ) );
    sldSeek->setOrientation( Qt::Horizontal );
    connect( sldSeek, SIGNAL(sliderReleased()), this, SLOT(seek()));

    lblTitleLabel = new QLabel( grpFrame );
    lblTitleLabel->setGeometry( QRect( 10, 40, 60, 20 ) );
    QFont lblTitleLabel_font(  lblTitleLabel->font() );
    lblTitleLabel_font.setPointSize( 10 );
    lblTitleLabel->setFont( lblTitleLabel_font );
    lblTitleLabel->setMouseTracking( FALSE );
    lblTitleLabel->setAcceptDrops( FALSE );
    lblTitleLabel->setText( tr( "Title: ") );

    lblTitle = new QLabel( grpFrame );
    lblTitle->setGeometry( QRect( 80, 40, 300, 20 ) );
    QFont lblTitle_font(  lblTitle->font() );
    lblTitle_font.setPointSize( 10 );
    lblTitle->setFont( lblTitle_font );

    lblArtistLabel = new QLabel( grpFrame );
    lblArtistLabel->setGeometry( QRect( 10, 20, 60, 20 ) );
    QFont lblArtistLabel_font(  lblArtistLabel->font() );
    lblArtistLabel_font.setPointSize( 10 );
    lblArtistLabel->setFont( lblArtistLabel_font );
    lblArtistLabel->setText( tr( "Artist: " ) );

    lblArtist = new QLabel( grpFrame );
    lblArtist->setGeometry( QRect( 80, 20, 300, 20 ) );
    QFont lblArtist_font(  lblArtist->font() );
    lblArtist_font.setPointSize( 10 );
    lblArtist->setFont( lblArtist_font );
}

void AudioPlayer::clean() {

}
