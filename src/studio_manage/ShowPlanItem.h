#ifndef SHOWPLANITEM_H_
#define SHOWPLANITEM_H_

#include <qwidget.h>
#include <qlistview.h>

#include "dps/DpsShowItem.h"

class ShowPlanItem : public QListViewItem,
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
