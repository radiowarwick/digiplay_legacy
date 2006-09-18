#ifndef CLASS_SHOW_PLAN_SCRIPT
#define CLASS_SHOW_PLAN_SCRIPT

#include <qlistview.h>

#include "dps.h"
#include "ShowPlanItem.h"

class QPainter;
class QColorGroup;
class QString;
class QSimpleRichText;

class ShowPlanScript : public ShowPlanItem {
	public:
		ShowPlanScript( QListView *parent, QListViewItem *after );
		ShowPlanScript( QListViewItem *parent, QListViewItem *after );
		ShowPlanScript( QListView *parent, QListViewItem *after, script s);
		int getType() {return 1;}
		script getScript() {return _s;}

	private:
		void init();
		script _s;
};

#endif
