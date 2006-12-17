/*
 * Audiowall Widget
 * AudioWall.h
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
#ifndef CLASS_AUDIO_WALL
#define CLASS_AUDIO_WALL

#include <vector>
using namespace std;

#include <qwidget.h>

#include "audiochannel.h"
#include "audiomixer.h"
#include "audioplayer.h"
#include "dps.h"

#define AUDIOWALL_BUTTON_OUT_OF_RANGE 12000

class QGroupBox;
class QPushButton;
class QLabel;

class AudioWall;

enum AUDIO_STATE {
	AUDIO_STATE_STOPPED,
	AUDIO_STATE_PLAYING,
	AUDIO_STATE_PAUSED
};

struct AudioWallPage;

struct AudioWallItem {
	QString text;
	QColor bgColor;
	QColor fgColor;
	QFont font;
	QString file;
	unsigned long start;
	unsigned long end;
	enum AUDIO_STATE state;
	unsigned long pos;
	audiochannel *ch;
	AudioWall *parent;
	AudioWallPage *page;
	unsigned short index;
};

struct AudioWallPage {
	QString title;
	QString description;
	vector<AudioWallItem*> items;
	unsigned short index;
};

class AudioWall : public QWidget {
	Q_OBJECT

	public:
		AudioWall(QWidget *parent, const char* name, unsigned short rows, 
						unsigned short cols, unsigned short playerId);
		AudioWall(QWidget *parent, const char* name, unsigned short rows,
						unsigned short cols, AudioWall* A);
		~AudioWall();
		void resizeEvent (QResizeEvent *e);
		void setButton(unsigned short page, unsigned short index, 
						AudioWallItem item);
		void setCaption(unsigned short page, QString text);
		void setMultipage(bool mp);
		bool isMultipage();
		unsigned short getSize() {return _rows*_cols;}
		bool isPlaying(unsigned short index);
		AudioWallItem* getActiveItem();
		static void callbackCounter(long smpl, void *obj);
		void customEvent(QCustomEvent *event);

//		void run();
//		void stop();

	public slots:
		void play(unsigned short page, unsigned short index);
		void play(unsigned short index);
		void stop();

	private slots:
		void play();
		void nextPage();
		void prevPage();
	
	private:
		void drawCreate();
		void drawResize();
		void configureButton(unsigned short index);
		void configurePageList();
		void configurePageNav();
		void clean();

		audioplayer *_audioPlayer;
		audiomixer *_audioMixer;
//		AudioWall *_AMaster;
		vector<AudioWall*> _siblingWalls;

		unsigned short _rows;
		unsigned short _cols;
		unsigned short _pageSize;
		unsigned short _currentPage;
		unsigned short _activePage;
		unsigned short _activeIndex;
		vector<AudioWallPage*> _pages;
		
		QGroupBox *grpFrame;
		QPushButton *btnPageNext;
		QPushButton *btnPagePrev;
		QLabel *lblPageNum;
		QLabel *lblCounter;
		vector<QPushButton*> btnAudio;

		bool _running;
//		QMutex _mutRunning;
//		QMutex _mutEvent;
		vector<eventData*> events;
};

#endif
