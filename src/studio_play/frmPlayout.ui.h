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
#include <qapplication.h>
#include <cstdlib>

#include "AudioPlayer.h"
#include "AudioWall.h"
#include "AudioWallDriver.h"
#include "AudioWallManager.h"
#include "dps.h"
#include "RemoteStartThread.h"
#include "Security.h"
#include "Logger.h"
#include "Config.h"

RemoteStartThread* remotes;
AudioPlayer* audioPlayer1;
AudioPlayer* audioPlayer2;
AudioPlayer* audioPlayer3;
AudioWall* stnAudioWall;
AudioWall* usrAudioWall;
AudioWallDriver* audioWallOutput;
AudioWallManager* stnAudioWallMan;
AudioWallManager* usrAudioWallMan;
unsigned int stnAudioWallId;
unsigned int usrAudioWallId;

Config *conf;

void frmPlayout::init() {
    const char* routine = "frmPlayout::init";

    isShiftDown = false;
    conf = new Config("digiplay");

    // Create audio players
    audioPlayer1 = new AudioPlayer(this,"audioPlayer1",1);
    audioPlayer1->setGeometry(10,10,540,245);
    audioPlayer2 = new AudioPlayer(this,"audioPlayer2",2);
    audioPlayer2->setGeometry(10,262,540,245);
    audioPlayer3 = new AudioPlayer(this,"audioPlayer3",3);
    audioPlayer3->setGeometry(10,514,540,245);

	// Create the station audio wall
    stnAudioWall = new AudioWall(this,"stnAudioWall",4,3);
	stnAudioWall->setGeometry(555,10,460,373);
	stnAudioWallMan = new AudioWallManager(stnAudioWall, "station_aw_set");
	
    // Create the user audio wall
	usrAudioWall = new AudioWall(this,"usrAudioWall",4,3);
	usrAudioWall->setGeometry(555,386,460,373);
	usrAudioWallMan = new AudioWallManager(usrAudioWall, "user_aw_set");

    // Link the audio walls to the fourth channel
    audioWallOutput = new AudioWallDriver(4);
    audioWallOutput->addAudioWall(stnAudioWall);
    audioWallOutput->addAudioWall(usrAudioWall);

	try {
    	remotes = new RemoteStartThread();
		connect(remotes, SIGNAL(player1_play()),
									audioPlayer1, SLOT(play()));
		connect(remotes, SIGNAL(player1_pause()),
									audioPlayer1, SLOT(pause()));
		connect(remotes, SIGNAL(player2_play()),
									audioPlayer2, SLOT(play()));
		connect(remotes, SIGNAL(player2_pause()),
									audioPlayer2, SLOT(pause()));
		connect(remotes, SIGNAL(player3_play()),
									audioPlayer3, SLOT(play()));
		connect(remotes, SIGNAL(player3_pause()),
									audioPlayer3, SLOT(pause()));

	    // Initialise remote starts
		remotes->start();

	    L_INFO(LOG_DB,"Started remotes");
	}
	catch (int e) {
		L_ERROR(LOG_AUDIOHW, "Initialisation of remote starts failed.");
	}
	
	losePrivilage();
}

void frmPlayout::destroy() {
    delete conf;
}


void frmPlayout::keyPressEvent(QKeyEvent* e) {
    switch (e->key()) {
        case Key_Escape: {
            if (conf->isParamDefined("enable_shift_esc")) {
                string confValue = conf->getParam("enable_shift_esc");
                char c = toupper(confValue[0]);
                if (isShiftDown && (c == 'Y' || c == '1')) {
                    exit(0);
                }
            }
            break;
        }
        case Key_Shift:
            isShiftDown = true;
            break;
        default:
            break;
    }
    e->ignore();
}

void frmPlayout::keyReleaseEvent(QKeyEvent* e) {
    switch (e->key()) {
        case Key_Escape:
            break;
        case Key_Shift:
            isShiftDown = false;
            break;
        default:
            break;
    }
    e->ignore();
}
