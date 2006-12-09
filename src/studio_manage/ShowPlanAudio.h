/*
 * Show Plan Audio Item
 * ShowPlanAudio.h
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
#ifndef CLASS_SHOW_PLAN_AUDIO
#define CLASS_SHOW_PLAN_AUDIO

#include <qlistview.h>

#include "dps.h"
#include "DpsObject.h"
#include "ShowPlanItem.h"

class QPainter;
class QColorGroup;
class QString;
class QSimpleRichText;
class DpsShowTrack;

class ShowPlanAudio : public ShowPlanItem {
	public:
		ShowPlanAudio( QListView *parent, QListViewItem *after );
		ShowPlanAudio( QListViewItem *parent, QListViewItem *after );
		ShowPlanAudio( QListView *parent, QListViewItem *after, 
                            DpsShowItem& t);
		int getType() {return 0;}
		DpsShowItem& getTrack() {return *_t;}

	private:
		void init();
		DpsShowItem* _t;
};

#endif
