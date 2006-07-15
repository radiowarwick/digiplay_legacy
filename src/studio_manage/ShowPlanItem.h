#ifndef CLASS_SHOW_PLAN_ITEM
#define CLASS_SHOW_PLAN_ITEM

#include <qlistview.h>

class QPainter;
class QColorGroup;
class QString;
class QSimpleRichText;

class ShowPlanItem : public QListViewItem {
	public:
		ShowPlanItem( QListView *parent, QListViewItem *after );
		ShowPlanItem( QListViewItem *parent, QListViewItem *after );
		ShowPlanItem( QListView *parent, QListViewItem *after, 
				QString txtTitle, QString txtArtist, QString txtLength, 
				QString txtTime );
		virtual void setup();
		int widthUsed() {return _widthUsed;}
		void setBackColor( QColor &c ) {*backColor = c;}

	protected:
		virtual void paintCell(QPainter *p, const QColorGroup &cg, int column,
				int width, int align);
//		virtual QString expandTemplate(int column = 0) {return QString::null;}

	private:
		void init();

		bool selected;
		bool active;
		int _widthUsed;
		bool rootElement;
		QSimpleRichText *lblTitle;
		QSimpleRichText *lblArtist;
		QSimpleRichText *lblLength;
		QSimpleRichText *lblTime;

		QFont titleFont;
		QFont artistFont;
		QFont lengthFont;
		QFont timeFont;
		QBrush *backColor;
		QPen *selectPen;
		QPen *unselectPen;
};

#endif
