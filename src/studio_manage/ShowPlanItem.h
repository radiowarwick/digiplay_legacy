/*
 * Show Plan Item
 * ShowPlanItem.h
 * Renders an individual item in the showplan.
 *
 * Copyright (c) 2004-2009 Chris Cantwell
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
#ifndef SHOWPLANITEM_H_
#define SHOWPLANITEM_H_

#include <QtGui/QWidget>
#include <QtGui/QAbstractItemDelegate>

#include "dps/DpsShowItem.h"

class ShowPlanItem : public QItemDelegate,
					 public DpsShowItem {
	public:
		ShowPlanItem( QListView * parent, QListViewItem * after,
						const DpsShowItem& pSrc);
		ShowPlanItem( QListView * parent, const DpsShowItem& pSrc );
		virtual ~ShowPlanItem();

        virtual void setup();
        int widthUsed() {return mWidthUsed;}
		void expand();

    protected:
        virtual void init();
        virtual void paintCell(QPainter *p, const QColorGroup &cg, int column,
                int width, int align);
        bool selected;
        bool active;
        int mWidthUsed;
        bool mIsRootElement;
		bool mIsExpanded;

        QSimpleRichText *lblTitle;
        QSimpleRichText *lblComment;
        QSimpleRichText *lblLength;
        QSimpleRichText *lblTime;
		QSimpleRichText *lblAudioTitle;
		QSimpleRichText *lblAudioArtist;
		QSimpleRichText *lblAudioLength;
		QSimpleRichText *lblScriptTitle;
		QSimpleRichText *lblScriptLength;

        QFont titleFont, commentFont, lengthFont, timeFont;
        QFont detailFont;
        QBrush *backBrushUnloaded, *backBrushLoaded, *backBrushFinished;
        QBrush *backBrushUnloadedSel, *backBrushLoadedSel,
                        *backBrushFinishedSel;
        QPixmap *pixUnloaded, *pixLoaded, *pixFinished;
        QPixmap *pixAudio, *pixScript;

        QPen *selectPen;
        QPen *unselectPen;

};

#endif /*SHOWPLANITEM_H_*/
