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

#include "Config.h"
#include "QtTrigger.h"
#include "AudioPlayer.h"
#include "AudioWall.h"
#include "AudioWallDriver.h"
#include "AudioWallManager.h"
#include "dps.h"
#include "RemoteStartThread.h"
#include "Security.h"
#include "Logger.h"

QtTrigger* triggerConfig;
RemoteStartThread* remotes;
AudioPlayer* audioPlayer1;
AudioPlayer* audioPlayer2;
AudioPlayer* audioPlayer3;
AudioWall* stnAudioWall;
AudioWall* usrAudioWall;
AudioWallDriver* audioWallOutput;
AudioWallManager* stnAudioWallMan;
AudioWallManager* usrAudioWallMan;
Config *conf;
unsigned int stnAudioWallId;
unsigned int usrAudioWallId;

void frmPlayout::init() {
    const char* routine = "frmPlayout::init";
    
    // Create audio players
    audioPlayer1 = new AudioPlayer(this,"audioPlayer1",1);
    audioPlayer1->setGeometry(10,10,540,240);
    audioPlayer2 = new AudioPlayer(this,"audioPlayer2",2);
    audioPlayer2->setGeometry(10,260,540,240);
    audioPlayer3 = new AudioPlayer(this,"audioPlayer3",3);
    audioPlayer3->setGeometry(10,510,540,240);

    conf = new Config("digiplay");
    triggerConfig = new QtTrigger("triggerConfig","t_configuration");
    connect(triggerConfig, SIGNAL(trigger()),
                                this, SLOT(configChanged()));

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

    // Get the active station and user awset id from config
    stnAudioWallId = atoi(conf->getParam("station_aw_set").c_str());
    usrAudioWallId = atoi(conf->getParam("user_aw_set").c_str());

	// Create the station audio wall
    stnAudioWall = new AudioWall(this,"stnAudioWall",4,3);
	stnAudioWall->setGeometry(560,0,460,373);
	stnAudioWallMan = new AudioWallManager(stnAudioWall);
	stnAudioWallMan->load(stnAudioWallId);
	
    // Create the user audio wall
	usrAudioWall = new AudioWall(this,"usrAudioWall",4,3);
	usrAudioWall->setGeometry(560,373,460,373);
	usrAudioWallMan = new AudioWallManager(usrAudioWall);
	usrAudioWallMan->load(usrAudioWallId);

    // Link the audio walls to the fourth channel
    audioWallOutput = new AudioWallDriver(4);
    audioWallOutput->addAudioWall(stnAudioWall);
    audioWallOutput->addAudioWall(usrAudioWall);

    // Initialise remote starts
	remotes->start();
    usleep(100000);
    L_INFO(LOG_DB,"Started remotes");
	
	losePrivilage();
}

void frmPlayout::destroy() {
    delete conf;
}

void frmPlayout::configChanged() {
    unsigned int s = atoi(conf->getParam("station_aw_set").c_str());
    unsigned int u = atoi(conf->getParam("user_aw_set").c_str());
    if (s != stnAudioWallId && stnAudioWallMan) {
        stnAudioWallId = s;
        if (stnAudioWallId != 0) {
            stnAudioWallMan->load(stnAudioWallId);
        }
    }
    if (u != usrAudioWallId && usrAudioWallMan) {
        usrAudioWallId = u;
    //    if (usrAudioWallId != 0) {
            cout<< "Doing load" << endl;
            usrAudioWallMan->load(usrAudioWallId);
    //    }
    }
}
