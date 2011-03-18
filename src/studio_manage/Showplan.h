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

#include <QtGui/QWidget>
#include <QtGui/QListView>
#include <QtCore/QMutex>

#include "dps/Dps.h"
#include "Config.h"
#include "MessagingInterface.h"
#include "ShowplanModel.h"
#include "ShowplanView.h"

class QGroupBox;
class QPushButton;
class QPainter;
class QColorGroup;
class QString;
class QSimpleRichText;

class Auth;

class Showplan : 	public QWidget,
					public MessagingInterface {
	Q_OBJECT

	public:
		Showplan(QWidget *parent);
		virtual ~Showplan();

        void configure(Auth *authModule);

		void onMessage();

        DpsShowPlan getShowplan();

        void setGeometry (const QRect& r);
		void resizeEvent (QResizeEvent *e);

	signals:
		void scriptSelected( const DpsScriptItem& );
		void scriptDeselected();

	public slots:
		void load(const DpsShowPlan& pSrc);
		void append(const DpsShowItem& pSrc);
		void append(const DpsAudioItem& pSrc);
		void append(const DpsScriptItem& pSrc);
		void clear();
		void scriptDone( const DpsScriptItem& pSrc );

	protected:
		// Showplan has changed, so redisplay
		virtual void showplanUpdated();

    private slots:
    	// Slots for showplan clicking
        void doubleClicked(const QModelIndex& x);
        void selectionChanged(const QModelIndex& x);
        void updateNextTrack();

		// Slots for showplan buttons
		void removeItem();
		void moveItemUp();
		void moveItemDown();
		void moveItemTop();
		void moveItemBottom();
		void clearItems();

	private:
        void draw();
		void clean();

        Config* conf;

        ShowplanModel* modShowplan;
        QWidget* _parent;
		QGroupBox* grpFrame;
        ShowplanView* lstShowPlan;
        QPushButton* btnDelete;
		QPushButton* btnMoveBottom;
		QPushButton* btnMoveDown;
        QPushButton* btnMoveTop;
        QPushButton* btnMoveUp;
        QPushButton* btnClear;

        QMutex mLock;
        DpsHash mActive;
        DpsHash mSelected;
        bool mIsItemActive;
        bool mIsItemSelected;
        std::vector<DpsHash> mExpandedItems;
};

#endif
