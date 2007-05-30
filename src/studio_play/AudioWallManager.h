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

#include <qobject.h>
#include <qstring.h>
#include <qfont.h>
#include <qcolor.h>

class DataAccess;
class AudioWall;
struct AudioWallItemSpec;

struct Page {
    QString title;  
    QString description;
    vector<AudioWallItemSpec*> items;
    unsigned short index;
};

class AudioWallManager : public QObject {
	Q_OBJECT
	public:
		AudioWallManager( AudioWall *A );
		~AudioWallManager();
		void load(unsigned int cartset);
		int getCartset() {return _cartset;}

	private:
		AudioWall *_A;
        DataAccess *DB;
		QString _username;
		vector<Page*> _pages;
		int _cartset;
};

#endif
