/****************************************************************************
** Form interface generated from reading ui file 'frmStudioManage.ui'
**
** Created: Sat Nov 6 09:42:07 2010
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMSTUDIOMANAGE_H
#define FRMSTUDIOMANAGE_H

#include <QtGui/QDialog>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTabWidget;
class QWidget;
class QFrame;
class QLabel;
class QPushButton;

class frmStudioManage : public QDialog
{
    Q_OBJECT

public:
    frmStudioManage( QWidget* parent = 0, Qt::WindowFlags fl = 0 );
    ~frmStudioManage();

    QTabWidget* tabManage;
    QWidget* tabPageInfo;
    QFrame* mBottomFrame;
    QLabel* lblClock;
    QLabel* pixLogo;
    QPushButton* btnLogin;
    QLabel* lblDate;
    QLabel* lblContactPhone;
    QLabel* lblContactEmail;
    QLabel* mLblTopBar;
    QLabel* mLblBottomBar;
    QLabel* lblContactSms;

public slots:
    virtual void customEvent( QEvent * event );
    virtual void updateAwSet( QString index );
    virtual void btnLoginClicked();
    virtual void keyPressEvent( QKeyEvent * event );
    virtual void keyReleaseEvent( QKeyEvent * event );

protected:

protected slots:
    virtual void languageChange();

private:
    bool isShiftDown;

    void init();
    void destroy();
    QString getTime( long smpl );

};

#endif // FRMSTUDIOMANAGE_H
