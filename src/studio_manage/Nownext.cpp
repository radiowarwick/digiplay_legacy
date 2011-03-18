/*
 * Now/Next Widget
 * Nownext.cpp
 * Manages and displays the active showplan. Facilities provided for loading
 * and saving showplans to the database.
 *
 * Copyright (c) 2004-2006 Chris Cantwell
 * Copyright (c) 2004-2006 Ian Liverton
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
#include <cstdlib>

#include <QtGui/QApplication>
#include <QtCore/QString>
#include <QtGui/QPixmap>
#include <QtCore/QVariant>

#include "dps/DpsObject.h"
#include "dps.h"
#include "Logger.h"
#include "Auth.h"

#include "Nownext.h"

using namespace std;

/* =======================================================================
 * Nownext
 * =======================================================================
 */
Nownext::Nownext(QWidget *parent)
        : QWidget(parent) {
    conf = new Config("digiplay",this);
	DB = new DataAccess();
	trigger = new QtTrigger( "trigger", "CHANGEME" );
	connect(trigger, SIGNAL(trigger()),
	                 this, SLOT(updateDisplay()));
    draw();
	//threadStart();
}

Nownext::~Nownext() {
    clean();
}

void Nownext::configure(Auth *authModule) {
    const char* routine = "Nownext::configure";
    if (!authModule) {
        L_WARNING(LOG_TAB,"authModule isn't defined. Can't configure Tab.");
        return;
    }
    // TODO: add any user dependant stuff here
}

string Nownext::formatTime(long start, long end) {
	
	string strShowTime;
	tm tme;
	char buff[30];
	time_t timeStart(start);
	time_t timeEnd(end);

	tme = *localtime(&timeStart);
	strftime(buff, 30, "%H:%M", &tme);
	strShowTime = string(" ( ") + buff + " - ";
	tme = *localtime(&timeEnd);
	strftime(buff, 30, "%H:%M", &tme);
	strShowTime += string(buff) + " )";
	return strShowTime;
}

void Nownext::updateDisplay() {
	mutex.lock();
	string strShowTime;
	time_t current_time;
	time(&current_time);
	string SQL = "SELECT txshows.name, txschedule.starttime, ";
	SQL += "txschedule.endtime AS name, starttime, endtime FROM txshows, ";
	SQL += "txschedule WHERE txshows.id=txschedule.txshowid AND txschedule.endtime>";
	SQL += dps_itoa(current_time);
	SQL += " ORDER BY txschedule.starttime LIMIT 2";
	try {
		PqxxResult R = DB->exec("Fetch nownext", SQL);
		DB->abort("Fetch nownext");

		if (R.size() == 2) {
			if (atoi(R[0]["starttime"].c_str()) <= current_time ) {
				strShowTime=formatTime( atoi(R[0]["starttime"].c_str()),
										atoi(R[0]["endtime"].c_str()) );
				lblNow->setText( QString::fromStdString(string("On now: ") + R[0]["name"].c_str() + strShowTime));

				strShowTime=formatTime( atoi(R[1]["starttime"].c_str()),
										atoi(R[1]["endtime"].c_str()) );
				lblNext->setText( QString::fromStdString(string("On next: ") + R[1]["name"].c_str() + strShowTime));
			}
			else {
				strShowTime=formatTime( atoi(R[0]["starttime"].c_str()),
										atoi(R[0]["endtime"].c_str()) );
				lblNext->setText( QString::fromStdString(string("On next: ") + R[0]["name"].c_str() + strShowTime));
				lblNow->setText( "On now: " );
			}
		}
		else if (R.size() == 1) {
			strShowTime=formatTime( atoi(R[0]["starttime"].c_str()),
									atoi(R[0]["endtime"].c_str()) );
			if (atoi(R[0]["starttime"].c_str()) <= current_time ) {
				lblNow->setText( QString::fromStdString(string("On now: ") + R[0]["name"].c_str() + strShowTime));
				lblNext->setText( "On next: " );
			}
			else {
				lblNow->setText( "On now: " );
				lblNext->setText( QString::fromStdString(string("On next: ") + R[0]["name"].c_str() +strShowTime));
			}
		}
		else {
			lblNow->setText( "On now: " );
			lblNext->setText( "On next: " );
		}
	}
	catch(...) {
		cout<<"Dammit!"<<endl;
		DB->abort("Fetch nownext");
	}
	mutex.unlock();
}

void Nownext::onMessage() {
/*    const char* routine = "Nownext::onMessage";
	L_INFO(LOG_DB,"Showplan received message");
	activePointLock.lock();
    if (conf->getParam("next_on_showplan") == ""
                        && lstShowPlan->childCount() > 0
                        && activePoint != lstShowPlan->lastItem()) {
        L_INFO(LOG_DB,"Processing track load event");
        if (activePoint == 0) {
            activePoint = (ShowPlanItem*)lstShowPlan->firstChild();
        }
        else {
            activePoint->setState(SHOWPLAN_STATE_FINISHED);
            activePoint = (ShowPlanItem*)activePoint->nextSibling();
			// while we have a script selected...
//            while (activePoint->getType() == 1
//                    && activePoint != lstShowPlan->lastItem()) {
//                activePoint = (ShowPlanItem*)activePoint->nextSibling();
//            }
        }
        activePoint->setState(SHOWPLAN_STATE_LOADED);
        lstShowPlan->ensureItemVisible(activePoint);
        if (lstShowPlan->selectedItem()) {
            selectionChanged(lstShowPlan->selectedItem());
        }

        activePointLock.unlock();
    	L_INFO(LOG_DB,"Configuration refresh complete.");
        
		L_INFO(LOG_DB,"Triggering update of next_on_showplan entry");
        updateNextTrack();
    }
	else {
		activePointLock.unlock();
	}	*/
}

void Nownext::setGeometry(const QRect& r) {
    QWidget::setGeometry(r);
}

void Nownext::resizeEvent(QResizeEvent *e) {
    if (!e) return;
    setUpdatesEnabled(false);
    clean();
    draw();
    setUpdatesEnabled(true);
    repaint();
    // TODO: Replace this with proper resize code
}

void Nownext::draw() {
    QString path = DPSDIR;

    frameOutline = new QFrame( this );
    frameOutline->setGeometry( QRect( 0, 0, 1030, 30 ) );
    frameOutline->setProperty("id","TopBarFrame");
    frameOutline->setFrameShape( QFrame::StyledPanel );
    frameOutline->setFrameShadow( QFrame::Plain );
    frameOutline->setLineWidth( 0 );

    frameInternal = new QFrame( frameOutline );
    frameInternal->setGeometry( QRect( 514, 0, 2, 37 ) );
    frameInternal->setFrameShape( QFrame::StyledPanel );
    frameInternal->setFrameShadow( QFrame::Raised );

    pixFade = new QLabel( frameOutline );
    pixFade->setGeometry( QRect( 960, 0, 43, 30 ) );
    pixFade->setPixmap( QPixmap(path + "/images/fade.png") );
    pixFade->setScaledContents( TRUE );

    lblNext = new QLabel( frameOutline );
    lblNext->setGeometry( QRect( 520, 0, 440, 31 ) );
    lblNext->setProperty("id","TopBarNext");
    lblNext->setText ( "On next: " );

    lblNow = new QLabel( frameOutline );
    lblNow->setGeometry( QRect( 0, 0, 512, 31 ) );
    lblNow->setProperty("id","TopBarNow");
    lblNow->setText( "On now: RaW 1251AM" );

    Area_of_Black = new QLabel( frameOutline );
    Area_of_Black->setGeometry( QRect( 1003, 0, 21, 30 ) );
    Area_of_Black->setProperty("id","TopBarBorder");

	updateDisplay();
}

void Nownext::threadExecute() {
	bool sync=0;
	while(1) {
		if (sync) {
			sleep(60);
			sync = (time(NULL) % 60) < 5; 
		}
		else {
			sleep (4);
			sync = (time(NULL) % 60) < 5; 
		}
		updateDisplay();
	}
}

void Nownext::clean() {
}
