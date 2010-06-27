/*
 * Audiowall Driver Widget
 * AudioWallDriver.h
 * Provides an output driver for multiple audio wall widget
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
#ifndef CLASS_AUDIO_WALL_DRIVER
#define CLASS_AUDIO_WALL_DRIVER

#include <vector>
using namespace std;

#include <qwidget.h>

#include "audiolib/Audio.h"
#include "audiolib/ProcessMixer.h"
#include "audiolib/OutputDsp.h"

#include "dps.h"

class AudioWall;

class AudioWallDriver : public QObject {
    Q_OBJECT

    public:
       AudioWallDriver(unsigned short playerId);
       ~AudioWallDriver();

       void addAudioWall(AudioWall* A);

    private:
       Audio::ProcessMixer* mixer;
       Audio::OutputDsp* player;
       unsigned short count;
};

#endif
