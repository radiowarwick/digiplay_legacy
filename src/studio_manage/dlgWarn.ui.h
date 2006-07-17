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

void dlgWarn::init() {
    QString path = qApp->applicationDirPath();
    pixWarning->setPixmap(QPixmap(path + "/images/warning48.png"));
    pixLogout->setPixmap(QPixmap(path + "/images/loginlogo.png"));
}

void dlgWarn::setWarning(QString msg) {
    lblWarn->setText(msg);
}

void dlgWarn::setTitle(QString msg) {
    lblTitle->setText(msg);
}

void dlgWarn::setQuestion(bool ques) {
    if( !ques ) {
	buttonCancel->hide();
	buttonOk->setText("OK");
    }
}
