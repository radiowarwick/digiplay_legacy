/****************************************************************************
** Form interface generated from reading ui file 'dlgLogin.ui'
**
** Created: Sat Nov 6 09:42:23 2010
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef DLGLOGIN_H
#define DLGLOGIN_H

#include <QtGui/QDialog>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;
class QFrame;

class dlgLogin : public QDialog
{
    Q_OBJECT

public:
    dlgLogin( QWidget* parent = 0, Qt::WindowFlags fl = 0 );
    ~dlgLogin();

    QFrame* frmLogin;
    QLabel* lblLoginUsername;
    QLabel* lblLoginPassword;
    QLineEdit* txtLoginPassword;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QLabel* pixLogin;
    QLineEdit* txtLoginUsername;
    QLabel* textLabel1;

    virtual QString getUsername();
    virtual QString getPassword();

protected:
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;

    virtual void paintEvent(QPaintEvent *paintevent);

protected slots:
    virtual void languageChange();

private:
    void init();

};

#endif // DLGLOGIN_H
