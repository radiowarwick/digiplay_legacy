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

#include "clockThread.h"
#include "Config.h"
#include "DataAccess.h"
#include "MessagingInterface.h"

#include "audiolib/Counter.h"

// Forward declarations
class QGroupBox;
class QPushButton;
class QLabel;
class QSlider;

class AudioPlayer:  public QWidget,
                    public Audio::Counter,
                    public MessagingInterface {
    Q_OBJECT

    public:
        AudioPlayer(QWidget *parent, const char* name, unsigned short playerId);
        ~AudioPlayer();
		void onMessage();
		
    public slots:
        void load();
        void log();
        void play();
        void pause();
        void stop();
        void seek();
        void seek(unsigned long sample);
        void setVocalStart();
        void setVocalStart(unsigned long sample);
        void setVocalEnd();
        void setVocalEnd(unsigned long sample);
        void setTimeDisplay();

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
        int audioid;
        Config* conf;
        DataAccess* DB;
        Audio::Input* audioFilereader;
        Audio::OutputDsp* audioPlayer;
        unsigned long _lastSample;
        unsigned long vocalStartSample;
        unsigned long vocalEndSample;

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
        QSlider* sldSeek;
        int length_hours;
        int length_mins;
        int length_secs;
        QString* strTime;
        QLabel* lblTitleLabel;
        QLabel* lblTitle;
        QLabel* lblArtistLabel;
        QLabel* lblArtist;
        QLabel* lblVocalStartLabel;
        QLabel* lblVocalStart;
        QLabel* lblVocalEndLabel;
        QLabel* lblVocalEnd;
        QLabel* lblVocalStartNegative;
        QLabel* lblVocalEndNegative;


        QPushButton* btnVocalStart;
        QPushButton* btnVocalEnd;

        QPixmap* pixPlay;
        QPixmap* pixPause;
};

#endif
