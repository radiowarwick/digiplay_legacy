/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

#include <qapplication.h>

void dlgLogin::init() {
    
    QString path = qApp->applicationDirPath();
    pixLogin->setPixmap(QPixmap(path + "/images/loginlogo.png"));
}

QString dlgLogin::getUsername() {
    return txtLoginUsername->text();
}

QString dlgLogin::getPassword() {
    return txtLoginPassword->text();
}

