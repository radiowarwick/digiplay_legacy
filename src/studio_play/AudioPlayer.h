/*
 * Audio Player Widget
 * AudioPlayer.h
 * Provides a graphical audio player widget
 *
 * Copyright (c) 2007 Chris Cantwell
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
#ifndef CLASS_AUDIO_PLAYER
#define CLASS_AUDIO_PLAYER

#include <qapplication.h>
#include <qwidget.h>
#include <qmutex.h>

#include "audio/Audio.h"
#include "audio/InputRaw.h"
#include "audio/OutputDsp.h"
#include "audio/Counter.h"
#include "clockThread.h"
#include "Config.h"
#include "DataAccess.h"

class QGroupBox;
class QPushButton;
class QLabel;
class QSlider;

class AudioPlayer:  public QWidget,
                    public Audio::Counter {
    Q_OBJECT

    public:
        AudioPlayer(QWidget *parent, const char* name, unsigned short playerId);
        ~AudioPlayer();

    public slots:
        void load();
        void log();
        void play();
        void stop();
        void seek();
        void seek(unsigned long sample);
        void setTimeDisplay();
        void processConfigUpdate();

    private:
        void onSetSample();
        void onSetState();
        void onSetTotalSamples();
        void customEvent(QCustomEvent *event);
        void updateEndTime();
        QString getTime(long smpl);

        void drawCreate();
        void drawResize();
        void clean();

        string id;
		int location;
		int userid;
        Config* conf;
        DataAccess* DB;
        Audio::InputRaw* audioFilereader;
        Audio::OutputDsp* audioPlayer;
        unsigned long _lastSample;

        clockThread *ck;
        QGroupBox* grpFrame;
        QLabel* lblTime;
        QPushButton* btnTimeMode;
        QLabel* lblCounter;
        QLabel* lblEndlbl;
        QLabel* lblEnd;
        QPushButton* btnLoad;
        QPushButton* btnLog;
        QPushButton* btnStop;
        QPushButton* btnPlay;
        QPushButton* btnReset;
        QPushButton* btnSeekBack;
        QPushButton* btnSeekForward;
        QSlider* sldSeek;
        int length_hours;
        int length_mins;
        int length_secs;
        QString* strTime;
        QLabel* lblTitleLabel;
        QLabel* lblTitle;
        QLabel* lblArtistLabel;
        QLabel* lblArtist;

        QPixmap* pixPlay;
        QPixmap* pixPause;
};

#endif
