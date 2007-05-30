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
#include <qslider.h>

#include "Logger.h"

#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(QWidget *parent, const char* name, unsigned short playerId) 
        : QWidget(parent,name) {
    drawCreate();
    id = dps_itoa(playerId);
    DB = new DataAccess();
    conf = new Config("digiplay");
    std::string device = conf->getParam("channel_" + id);

    grpFrame = 0;


    processConfigUpdate();

    audioFilereader = new Audio::InputRaw();
    audioPlayer = new Audio::OutputDsp(device);

    audioFilereader->connect(OUT0,audioPlayer,IN0);
    audioFilereader->addCounter(this);
}

AudioPlayer::~AudioPlayer() {
    clean();
}

void AudioPlayer::load() {
    cout << "AudioPlayer::load" << endl;
    btnLoad->setEnabled(false);
    if (conf->getParam("next_on_showplan") == "") {
        return;
    }
    string SQL = "SELECT * FROM v_audio WHERE md5='"
                    + conf->getParam("next_on_showplan") + "'";
    Result R = DB->exec(SQL);
    cout << "Done query!" << endl;
    DB->abort();
    if (R.size() == 0) {
        cout << "No such track!" << endl;
        return;
    }
    string f = R[0]["path"].c_str() + string("/") 
                + (string(R[0]["md5"].c_str())).substr(0,1)
                + string("/") + R[0]["md5"].c_str();
    audioFilereader->load(f, atoi(R[0]["start_smpl"].c_str()),
                                    atoi(R[0]["end_smpl"].c_str()));
    conf->setParam("next_on_showplan","");
    lblTitle->setText(R[0]["title"].c_str());
    lblArtist->setText(R[0]["artist"].c_str());
    btnPlay->setEnabled(true);
    btnStop->setEnabled(true);
    //btnSeekBack1->setEnabled(true);
    //btnSeekForward1->setEnabled(true);
    sldSeek->setEnabled(true);
}

void AudioPlayer::play() {
    if (_state == STATE_PLAY) {
        cout << "Do pause" << endl;
        audioFilereader->pause();
    }
    else {
        cout << "Do play" << endl;
        audioFilereader->play();
        cout << "Done play" << endl;
    }
}

void AudioPlayer::stop() {
    cout << "Do stop" << endl;
    audioFilereader->stop();
    cout << "Done stop" << endl;
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
}

void AudioPlayer::processConfigUpdate() {
    conf->requery();
    if (conf->getParam("next_on_showplan") == "") {
        cout << "Config updated: DISABLED LOAD" << endl;
        btnLoad->setEnabled(false);
    }
    else {
        cout << "Config updated: ENABLED LOAD" << endl;
        btnLoad->setEnabled(true);
    }
}

void AudioPlayer::onSetSample() {
/*    if (_currentSample - _lastSample < 441) return;
    _lastSample = _currentSample;
    sldSeek->setValue(_currentSample);
    if (_currentSample != 0 
            && (_totalSamples - _currentSample)/44100 < 20) {
        lblCounter->setPaletteForegroundColor(QColor(QRgb(16711680)));
    }
    else {
        lblCounter->setPaletteForegroundColor(QColor(QRgb(0)));
    }
    if (lblTime->text() == "REMAIN") {
        lblCounter->setText(getTime(_totalSamples - _currentSample));
    }
    else {
        lblCounter->setText(getTime(_currentSample));
    }*/
}

void AudioPlayer::onSetState() {
    cout << "SEtting state" << endl;
    switch (_state) {
        case STATE_PLAY:
            {
                btnLoad->setEnabled(false);
                btnPlay->setPixmap(*pixPause);
            }
            break;
        case STATE_STOP:
            {
                if (audioFilereader->isLoaded()) btnPlay->setEnabled(true);
                btnPlay->setPixmap(*pixPlay);
                if (conf->getParam("next_on_showplan") != "") {
                    btnLoad->setEnabled(true);
                }
                lblCounter->setPaletteForegroundColor(QColor(QRgb(0)));
                if (lblTime->text() == "REMAIN")
                    lblCounter->setText(getTime(_totalSamples));
                else
                    lblCounter->setText(getTime(0));
                sldSeek->setValue(0);
                sldSeek->setMaxValue(_totalSamples);
            }
            break;
        case STATE_PAUSE:
            {
                btnPlay->setPixmap(*pixPlay);
            }
            break;
    }
}

void AudioPlayer::onSetTotalSamples() {
    sldSeek->setMaxValue(_totalSamples);
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
    string path = qApp->applicationDirPath();
    pixPlay = new QPixmap(path + "/images/play.png");
    pixPause = new QPixmap(path + "/images/pause.png");

    grpFrame = new QGroupBox( this, "grpFrame" );
    grpFrame->setGeometry( QRect( 0, 0, 540, 240 ) );
    QFont grpFrame_font(  grpFrame->font() );
    grpFrame_font.setPointSize( 16 );
    grpFrame_font.setBold( TRUE );
    grpFrame->setFont( grpFrame_font );
    grpFrame->setTitle( "Audio Player " + id);

    lblTime = new QLabel( grpFrame, "lblTime" );
    lblTime->setGeometry( QRect( 270, 100, 110, 17 ) );
    QFont lblTime_font(  lblTime->font() );
    lblTime_font.setPointSize( 14 );
    lblTime->setFont( lblTime_font );
    lblTime->setAlignment( int( QLabel::AlignCenter ) );
    lblTime->setText( tr( "ELAPSED" ) );

    btnTimeMode = new QPushButton( grpFrame, "btnTimeMode" );
    btnTimeMode->setGeometry( QRect( 280, 60, 90, 40 ) );
    QFont btnTimeMode_font(  btnTimeMode->font() );
    btnTimeMode_font.setPointSize( 14 );
    btnTimeMode_font.setBold( FALSE );
    btnTimeMode->setFont( btnTimeMode_font );
    btnTimeMode->setText( tr( "Time Mode") );
    connect(btnTimeMode,SIGNAL(pressed()),this,SLOT(setTimeDisplay()));

    lblCounter = new QLabel( grpFrame, "lblCounter" );
    lblCounter->setGeometry( QRect( 10, 60, 260, 57 ) );
    QFont lblCounter_font(  lblCounter->font() );
    lblCounter_font.setPointSize( 48 );
    lblCounter->setFont( lblCounter_font );
    lblCounter->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignLeft )  );
    lblCounter->setText( tr( "00:00.00" ) );

    btnLoad = new QPushButton( grpFrame, "btnLoad" );
    btnLoad->setGeometry( QRect( 390, 60, 140, 50 ) );
    QFont btnLoad_font(  btnLoad->font() );
    btnLoad_font.setPointSize( 18 );
    btnLoad->setFont( btnLoad_font );
    btnLoad->setText( tr( "Load" ) );
    connect(btnLoad,SIGNAL(pressed()),this,SLOT(load()));

    btnStop = new QPushButton( grpFrame, "btnStop" );
    btnStop->setEnabled( FALSE );
    btnStop->setGeometry( QRect( 10, 159, 110, 80 ) );
    btnStop->setText( QString::null );
    btnStop->setPixmap( QPixmap(path + "/images/stop.png") );
    connect( btnStop, SIGNAL(pressed()), this, SLOT(stop()) );

    btnPlay = new QPushButton( grpFrame, "btnPlay" );
    btnPlay->setEnabled( FALSE );
    btnPlay->setGeometry( QRect( 130, 159, 110, 80 ) );
    btnPlay->setText( QString::null );
    btnPlay->setPixmap( *pixPlay );
    connect( btnPlay, SIGNAL(pressed()), this, SLOT(play()) );

    btnReset = new QPushButton( grpFrame, "btnReset" );
    btnReset->setEnabled( FALSE );
    btnReset->setGeometry( QRect( 290, 159, 80, 80 ) );
    btnReset->setText( QString::null );
    btnReset->setPixmap( QPixmap(path + "/images/reset.png") );

    btnSeekBack = new QPushButton( grpFrame, "btnSeekBack" );
    btnSeekBack->setEnabled( FALSE );
    btnSeekBack->setGeometry( QRect( 370, 159, 80, 80 ) );
    btnSeekBack->setText( QString::null );
    btnSeekBack->setPixmap( QPixmap(path + "/images/fastbackward.png") );

    btnSeekForward = new QPushButton( grpFrame, "btnSeekForward" );
    btnSeekForward->setEnabled( FALSE );
    btnSeekForward->setGeometry( QRect( 450, 159, 80, 80 ) );
    btnSeekForward->setText( QString::null );
    btnSeekForward->setPixmap( QPixmap(path + "/images/fastforward.png") );

    sldSeek = new QSlider( grpFrame, "sldSeek" );
    sldSeek->setGeometry( QRect( 10, 120, 520, 29 ) );
    sldSeek->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7,             (QSizePolicy::SizeType)4, 0, 0, sldSeek->sizePolicy().hasHeightForWidth() ) );
    sldSeek->setOrientation( QSlider::Horizontal );

    lblTitleLabel = new QLabel( grpFrame, "lblTitleLabel" );
    lblTitleLabel->setGeometry( QRect( 10, 40, 60, 20 ) );
    QFont lblTitleLabel_font(  lblTitleLabel->font() );
    lblTitleLabel_font.setPointSize( 14 );
    lblTitleLabel->setFont( lblTitleLabel_font );
    lblTitleLabel->setMouseTracking( FALSE );
    lblTitleLabel->setAcceptDrops( FALSE );
    lblTitleLabel->setText( tr( "Title: ") );

    lblTitle = new QLabel( grpFrame, "lblTitle" );
    lblTitle->setGeometry( QRect( 80, 40, 450, 20 ) );
    QFont lblTitle_font(  lblTitle->font() );
    lblTitle_font.setPointSize( 14 );
    lblTitle->setFont( lblTitle_font );

    lblArtistLabel = new QLabel( grpFrame, "lblArtistLabel" );
    lblArtistLabel->setGeometry( QRect( 10, 20, 60, 20 ) );
    QFont lblArtistLabel_font(  lblArtistLabel->font() );
    lblArtistLabel_font.setPointSize( 14 );
    lblArtistLabel->setFont( lblArtistLabel_font );
    lblArtistLabel->setText( tr( "Artist: " ) );

    lblArtist = new QLabel( grpFrame, "lblArtist" );
    lblArtist->setGeometry( QRect( 80, 20, 450, 20 ) );
    QFont lblArtist_font(  lblArtist->font() );
    lblArtist_font.setPointSize( 14 );
    lblArtist->setFont( lblArtist_font );
}

void AudioPlayer::clean() {

}
