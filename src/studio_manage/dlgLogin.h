/****************************************************************************
** Form interface generated from reading ui file 'dlgLogin.ui'
**
** Created: Fri Jul 14 09:37:52 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.5   edited Aug 31 12:13 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef DLGLOGIN_H
#define DLGLOGIN_H

#include <qvariant.h>
#include <qdialog.h>


class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QPushButton;
class QLineEdit;

class dlgLogin : public QDialog
{
    Q_OBJECT

public:
    dlgLogin( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~dlgLogin();

    QString getUsername();
    QString getPassword();

    QLabel* textLabel1;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QLabel* lblLoginUsername;
    QLabel* lblLoginPassword;
    QLineEdit* txtLoginPassword;
    QLineEdit* txtLoginUsername;

public slots:

protected:
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;

protected slots:
    virtual void languageChange();

private:
    void init();

};

#endif // DLGLOGIN_H
