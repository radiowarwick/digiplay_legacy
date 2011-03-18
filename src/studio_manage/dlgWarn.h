/****************************************************************************
** Form interface generated from reading ui file 'dlgWarn.ui'
**
** Created: Sat Nov 6 09:42:49 2010
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef DLGWARN_H
#define DLGWARN_H

#include <QtGui/QDialog>

class QFrame;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLabel;

class dlgWarn : public QDialog
{
    Q_OBJECT

public:
    dlgWarn( QWidget* parent = 0, Qt::WindowFlags fl = 0 );
    ~dlgWarn();

    QFrame* frameContent;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QLabel* pixWarning;
    QLabel* lblTitle;
    QLabel* lblWarn;
    QLabel* pixLogout;

public slots:
    virtual void setWarning( QString msg );
    virtual void setTitle( QString msg );
    virtual void setQuestion( bool ques );

protected:
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;

    virtual void paintEvent(QPaintEvent *paintevent);

protected slots:
    virtual void languageChange();

private:
    void init();

};

#endif // DLGWARN_H
