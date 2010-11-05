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

#include <QtGui/QWidget>

#include "dps.h"

#include "audiolib/Audio.h"
#include "audiolib/ProcessMixer.h"

#include "AudioWallItem.h"

#define AUDIOWALL_BUTTON_OUT_OF_RANGE 12000

class QGroupBox;
class QPushButton;
class QLabel;

class ProcessMixer;

struct AudioWallPage {
	QString mTitle;
	QString mDescription;
	vector<AudioWallItem*> mItems;
	unsigned short mIndex;
};

class AudioWall :   public QWidget,
                    public Audio::ProcessMixer {
	Q_OBJECT

	public:
		AudioWall(QWidget *parent, const char* name, unsigned short rows,
						unsigned short cols);
		~AudioWall();
		void resizeEvent (QResizeEvent *e);
		void setButton(unsigned short pPage, unsigned short pIndex,
						AudioWallItemSpec pItem);
		void setCaption(unsigned short pPage, QString pText);
		void setMultipage(bool mp);
		bool isMultipage();
		unsigned short getSize() {return mRows*mCols;}
		bool isPlaying(unsigned short pIndex);

        void addPage();
        void deletePage(unsigned int pIndex);
        void displayPage(unsigned int pIndex);

		void updateWall();

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

        bool mLoaded;
        string mName;
		unsigned short mRows;
		unsigned short mCols;
		unsigned short mPageSize;
		unsigned short mCurrentPage;
		unsigned short mActivePage;
		unsigned short mActiveIndex;
		vector<AudioWallPage*> mPages;

        // Geometry parameters
        int mBorder;
        int mFrameWidth;
        int mFrameHeight;
        int mCellWidth;
        int mCellHeight;

		QGroupBox* mGrpFrame;
		QPushButton* mBtnPageNext;
		QPushButton* mBtnPagePrev;
		QLabel* mLblPageNum;
		QLabel* mLblCounter;
};

#endif
