#ifndef CLASS_SHOW_PLAN_ITEM
#define CLASS_SHOW_PLAN_ITEM

#include <qlistview.h>

#include "dps.h"

class QPainter;
class QColorGroup;
class QString;
class QSimpleRichText;

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

#endif
