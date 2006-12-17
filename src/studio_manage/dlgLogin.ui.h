/*
 * Login dialog box
 * dlgLogin.ui.h
 * Requests username \ password from user
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

void dlgLogin::init() {
    
    QString path = qApp->applicationDirPath();
    pixLogin->setPixmap(QPixmap(path + "/images/loginlogo.png"));
    txtLoginUsername->setFocus();
}

QString dlgLogin::getUsername() {
    return txtLoginUsername->text();
}

QString dlgLogin::getPassword() {
    return txtLoginPassword->text();
}

