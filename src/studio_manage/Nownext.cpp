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

#include <qapplication.h>
#include <qstring.h>
#include <qpixmap.h>

#include "DpsObject.h"
#include "dps.h"
#include "Logger.h"
#include "Auth.h"

#include "Nownext.h"

/* =======================================================================
 * Nownext
 * =======================================================================
 */
Nownext::Nownext(QWidget *parent, const char* name) 
        : QWidget(parent, name) {
    conf = new Config("digiplay",this);
    draw();
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

    frameOutline = new QFrame( this, "frameOutline" );
    frameOutline->setGeometry( QRect( 0, 0, 1030, 30 ) );
    frameOutline->setPaletteBackgroundColor( QColor( 3, 157, 189 ) );
    frameOutline->setFrameShape( QFrame::StyledPanel );
    frameOutline->setFrameShadow( QFrame::Plain );
    frameOutline->setLineWidth( 0 );

    frameInternal = new QFrame( frameOutline, "frameInternal" );
    frameInternal->setGeometry( QRect( 514, 0, 2, 37 ) );
    frameInternal->setFrameShape( QFrame::StyledPanel );
    frameInternal->setFrameShadow( QFrame::Raised );

    pixFade = new QLabel( frameOutline, "pixFade" );
    pixFade->setGeometry( QRect( 960, 0, 43, 30 ) );
    pixFade->setPixmap( QPixmap(path + "/images/fade.png") );
    pixFade->setScaledContents( TRUE );

    lblNext = new QLabel( frameOutline, "lblNext" );
    lblNext->setGeometry( QRect( 520, 0, 440, 31 ) );
    lblNext->setPaletteForegroundColor( QColor( 255, 255, 255 ) );
    lblNext->setPaletteBackgroundColor( QColor( 3, 157, 189 ) );
    QFont lblNext_font(  lblNext->font() );
    lblNext_font.setFamily( "Sans Serif" );
    lblNext_font.setPointSize( 18 );
    lblNext->setFont( lblNext_font );
    lblNext->setText ( "On next: " );

    lblNow = new QLabel( frameOutline, "lblNow" );
    lblNow->setGeometry( QRect( 0, 0, 512, 31 ) );
    lblNow->setPaletteForegroundColor( QColor( 255, 255, 255 ) );
    lblNow->setPaletteBackgroundColor( QColor( 3, 157, 189 ) );
    QFont lblNow_font(  lblNow->font() );
    lblNow_font.setFamily( "Sans Serif" );
    lblNow_font.setPointSize( 18 );
    lblNow_font.setBold( TRUE );
    lblNow->setFont( lblNow_font );
    lblNow->setText( "On now: RaW 1251AM" );

    Area_of_Black = new QLabel( frameOutline, "Area_of_Black" );
    Area_of_Black->setGeometry( QRect( 1003, 0, 21, 30 ) );
    Area_of_Black->setPaletteBackgroundColor( QColor( 0, 0, 0 ) );
}

void Nownext::clean() {
}
