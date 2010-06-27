/*
 * Message box
 * dlgWarn.ui.h
 * Displays warning \ error messages
 *
 * Copyright (c) 2006 Ian Liverton
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

void dlgWarn::init() {
    QString path = DPSDIR;
    pixWarning->setPixmap(QPixmap(path + "/images/warning48.png"));
    pixLogout->setPixmap(QPixmap(path + "/images/loginlogo.png"));
}

void dlgWarn::setWarning(QString msg) {
    lblWarn->setText(msg);
}

void dlgWarn::setTitle(QString msg) {
    setCaption(msg);
    lblTitle->setText(msg);
}

void dlgWarn::setQuestion(bool ques) {
    if( !ques ) {
	buttonCancel->hide();
	buttonOk->setText("OK");
    }
}
