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

#include "dps.h"

#include "audio/Audio.h"
#include "audio/ProcessMixer.h"

#include "AudioWallItem.h"

#define AUDIOWALL_BUTTON_OUT_OF_RANGE 12000

class QGroupBox;
class QPushButton;
class QLabel;

class ProcessMixer;

struct AudioWallPage {
	QString title;
	QString description;
	vector<AudioWallItem*> items;
	unsigned short index;
};

struct AudioWallItemSpec {
    QString file;
    unsigned long start;
    unsigned long end;
    QString text;
    QColor fgColour;
    QColor bgColour;
};

class AudioWall :   public QWidget,
                    public Audio::ProcessMixer {
	Q_OBJECT

	public:
		AudioWall(QWidget *parent, const char* name, unsigned short rows, 
						unsigned short cols);
		~AudioWall();
		void resizeEvent (QResizeEvent *e);
		void setButton(unsigned short page, unsigned short index, 
						AudioWallItemSpec item);
		void setCaption(unsigned short page, QString text);
		void setMultipage(bool mp);
		bool isMultipage();
		unsigned short getSize() {return _rows*_cols;}
		bool isPlaying(unsigned short index);
        
        void addPage();
        void deletePage(unsigned int index);
        void displayPage(unsigned int index);

	private slots:
		void nextPage();
		void prevPage();
	
	private:
        void resizePage(unsigned int index);
		void configurePageList();
		void configurePageNav();

		void drawCreate();
		void drawResize();

		void clean();

        OutputDsp *_audioPlayer;
        ProcessMixer *_audioMixer;

		unsigned short _rows;
		unsigned short _cols;
		unsigned short _pageSize;
		unsigned short _currentPage;
		unsigned short _activePage;
		unsigned short _activeIndex;
		vector<AudioWallPage*> _pages;
		
        // Geometry parameters
        int border;
        int wFrame;
        int hFrame;
        int wCell;
        int hCell;

		QGroupBox *grpFrame;
		QPushButton *btnPageNext;
		QPushButton *btnPagePrev;
		QLabel *lblPageNum;
		QLabel *lblCounter;

		bool _running;
//		QMutex _mutRunning;
//		QMutex _mutEvent;
		vector<eventData*> events;
};

#endif
