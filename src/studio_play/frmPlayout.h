/****************************************************************************
** Form interface generated from reading ui file 'frmPlayout.ui'
**
** Created: Sun Oct 24 21:50:32 2010
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FRMPLAYOUT_H
#define FRMPLAYOUT_H

//#include <qvariant.h>
//#include <qdialog.h>
#include <QtGui/QDialog>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;

class frmPlayout : public QDialog
{
    Q_OBJECT

public:
    frmPlayout( QWidget* parent = 0, Qt::WindowFlags fl = 0 );
    ~frmPlayout();


    void destroy();

public slots:
    virtual void keyPressEvent( QKeyEvent * event );
    virtual void keyReleaseEvent( QKeyEvent * event );

protected:

protected slots:
    virtual void languageChange();

private:
    bool isShiftDown;

    void init();

};

#endif // FRMPLAYOUT_H
