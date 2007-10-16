/*
 * Showplan Widget
 * Showplan.h
 * Manages and displays the active showplan. Facilities provided for loading
 * and saving showplans to the database.
 *
 * Copyright (c) 2004-2006 Chris Cantwell
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

#ifndef CLASS_SHOWPLAN
#define CLASS_SHOWPLAN

#include <vector>
using namespace std;

#include <qwidget.h>
#include <qlistview.h>
#include <qmutex.h>

#include "DpsObject.h"
#include "DbTrigger.h"
#include "Config.h"
//#include "triggerThread.h"

class QGroupBox;
class QListView;
class QListViewItem;
class QPushButton;
class QPainter;
class QColorGroup;
class QString;
class QSimpleRichText;

class DpsShowItem;
class Auth;
class ShowPlanItem;

class Showplan : public QWidget {
	Q_OBJECT

	public:
		Showplan(QWidget *parent, const char* name);
		~Showplan();

        void configure(Auth *authModule);

        DpsShowplan getShowplan();

        void setGeometry (const QRect& r);
		void resizeEvent (QResizeEvent *e);
//        void customEvent (QCustomEvent *e);

    public slots:
        void loadShowplan(DpsShowplan& S);
        void addTrack(QString md5);
        void addJingle(QString md5);
        void addAdvert(QString md5);
        void addScript(DpsShowScript& S);
        void addNote(DpsShowNote& N);
        void scriptDone();
        void clear(bool prompt = true);
        void remove();
        void moveUp();
        void moveDown();
        void moveTop();
        void moveBottom();

	signals:
		void scriptSelected( int );
		void scriptDeselected();

    private slots:
        void processConfigUpdate();
        void clicked(QListViewItem* x);
        void selectionChanged(QListViewItem* x);
        void updateNextTrack();

	private:
        void draw();
		void clean();

        Config* conf;
        DbTrigger* triggerConfig;
        //triggerThread* confTrigger;

        QWidget* _parent;
		QGroupBox* grpFrame;
        QListView* lstShowPlan;
        QPushButton* btnDelete;
		QPushButton* btnMoveBottom;
		QPushButton* btnMoveDown;
        QPushButton* btnMoveTop;
        QPushButton* btnMoveUp;
        QPushButton* btnClear;

        QMutex activePointLock;
        ShowPlanItem* activePoint;
        ShowPlanItem* selectedItem;
};


class ShowPlanItem : public QListViewItem {
    public:
        ShowPlanItem( QListView *parent, QListViewItem *after );
        ShowPlanItem( QListViewItem *parent, QListViewItem *after );
        virtual int getType() = 0;
        virtual void setup();
        int widthUsed() {return _widthUsed;}
        void setState(enum showPlanState state) {_state = state; setup();}
        enum showPlanState getState() {return _state;}

    protected:
        virtual void init();
        virtual void paintCell(QPainter *p, const QColorGroup &cg, int column,
                int width, int align);
        bool selected;
        bool active;
        int _widthUsed;
        bool rootElement;
        enum showPlanState _state;

        QSimpleRichText *lblTitle;
        QSimpleRichText *lblSubtitle;
        QSimpleRichText *lblLength;
        QSimpleRichText *lblTime;

        QFont titleFont, subtitleFont, lengthFont, timeFont;
        QBrush *backBrushUnloaded, *backBrushLoaded, *backBrushFinished;
        QBrush *backBrushUnloadedSel, *backBrushLoadedSel,
                        *backBrushFinishedSel;
        QPixmap *pixUnloaded, *pixLoaded, *pixFinished;

        QPen *selectPen;
        QPen *unselectPen;
};


class ShowPlanAudio : public ShowPlanItem {
    public:
        ShowPlanAudio( QListView *parent, QListViewItem *after );
        ShowPlanAudio( QListViewItem *parent, QListViewItem *after );
        ShowPlanAudio( QListView *parent, QListViewItem *after,
                            DpsShowItem& t);
        int getType() {return 0;}
        DpsShowItem& getTrack() {return _t;}

    private:
        void init();
        DpsShowItem _t;
};


class ShowPlanScript : public ShowPlanItem {
    public:
        ShowPlanScript( QListView *parent, QListViewItem *after );
        ShowPlanScript( QListViewItem *parent, QListViewItem *after );
        ShowPlanScript( QListView *parent, QListViewItem *after, 
                            DpsShowItem&   s);
        
        int getType() {return 1;}
        DpsShowItem& getScript() {return _s;}

    private:
        void init();
        DpsShowItem _s;
};

class ShowPlanNote : public ShowPlanItem {
    public:
        ShowPlanNote( QListView *parent, QListViewItem *after );
        ShowPlanNote( QListViewItem *parent, QListViewItem *after );
        ShowPlanNote( QListView *parent, QListViewItem *after, 
                            DpsShowItem&   s);
        
        int getType() {return 2;}
        DpsShowItem& getNote() {return _n;}

    private:
        void init();
        DpsShowItem _n;
};

#endif
