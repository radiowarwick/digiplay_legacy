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

#ifndef CLASS_NOWNEXT
#define CLASS_NOWNEXT

using namespace std;

#include <qwidget.h>
#include <qlabel.h>
#include <qframe.h>
#include <qmutex.h>

#include "DpsObject.h"
#include "MessagingInterface.h"
#include "Config.h"

class QPainter;
class QColorGroup;
class QString;

class DpsShowItem;
class Auth;
class ShowPlanItem;

class Nownext : 	public QWidget,
					public MessagingInterface {
	Q_OBJECT

	public:
		Nownext(QWidget *parent, const char* name);
		~Nownext();

        void configure(Auth *authModule);

		void onMessage();
		
        void setGeometry (const QRect& r);
		void resizeEvent (QResizeEvent *e);

	private:
        void draw();
		void clean();

        Config* conf;
        //triggerThread* confTrigger;

        QWidget* _parent;
		QLabel* lblNow;
		QLabel* lblNext;
		QLabel* Area_of_Black;
		QLabel* pixFade;
		QFrame* frameInternal;
		QFrame* frameOutline;
};

#endif
