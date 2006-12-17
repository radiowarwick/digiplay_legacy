/*
 * Audiowall Management Class
 * AudioWallManager.h
 * Interfaces the AudioWall widget to the database
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
#ifndef CLASS_AUDIO_WALL_MANAGER
#define CLASS_AUDIO_WALL_MANAGER

#include <vector>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include <qobject.h>
#include <qstring.h>
#include <qfont.h>
#include <qcolor.h>

#include "AudioWall.h"

class AudioWallManager : public QObject {
	Q_OBJECT
	public:
		AudioWallManager( AudioWall *A, Connection *C );
		~AudioWallManager();
		void load(unsigned int cartset);
		int getCartset() {return _cartset;}

	private:
		AudioWall *_A;
		Connection *_C;
		QString _username;
		vector<AudioWallPage*> _pages;
		int _cartset;
};

#endif
