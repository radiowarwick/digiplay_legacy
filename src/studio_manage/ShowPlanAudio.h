#ifndef CLASS_SHOW_PLAN_AUDIO
#define CLASS_SHOW_PLAN_AUDIO

#include <qlistview.h>

#include "dps.h"
#include "ShowPlanItem.h"

class QPainter;
class QColorGroup;
class QString;
class QSimpleRichText;

class ShowPlanAudio : public ShowPlanItem {
	public:
		ShowPlanAudio( QListView *parent, QListViewItem *after );
		ShowPlanAudio( QListViewItem *parent, QListViewItem *after );
		ShowPlanAudio( QListView *parent, QListViewItem *after, track t);
		int getType() {return 0;}
		track getTrack() {return _t;}

	private:
		void init();
		track _t;
};

#endif
