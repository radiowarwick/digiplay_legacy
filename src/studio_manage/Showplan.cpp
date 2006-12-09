#include <qapplication.h>
#include <qgroupbox.h>
#include <qheader.h>
#include <qlistview.h>
#include <qpushbutton.h>

#include "dps.h"
#include "Logger.h"
#include "Auth.h"
#include "dlgWarn.h"

#include "Showplan.h"

Showplan::Showplan(QWidget *parent, const char* name) {
    conf = new config("digiplay");
    activePoint = 0;
    _parent = parent;
    draw();
    confTrigger = new triggerThread(this,QString(conf->getDBConnectString()),1);
    confTrigger->start();
}

Showplan::~Showplan() {
    clean();
}

void Showplan::configure(Auth *authModule) {

}

void Showplan::load(unsigned int index) {

}

void Showplan::setGeometry(const QRect& r) {
    if (grpFrame) grpFrame->setGeometry(r);
}

void Showplan::resizeEvent(QResizeEvent *e) {

}

void Showplan::customEvent(QCustomEvent *e) {
    char* routine = "Showplan::customEvent";

    if (e->type() == 30001) {
        L_INFO(LOG_DB,"Triggering configuration refresh");

        conf->requery();
        if (conf->getParam("next_on_showplan") == "" 
                            && lstShowPlan->childCount() > 0
                            && activePoint != lstShowPlan->lastItem()) {
            activePointLock.lock();
            L_INFO(LOG_DB,"Processing track load event");
            if (activePoint == 0) {
                activePoint = (ShowPlanItem*)lstShowPlan->firstChild();
            }
            else {
                activePoint->setState(SHOWPLAN_STATE_FINISHED);
                activePoint = (ShowPlanItem*)activePoint->nextSibling();
            }
            activePoint->setState(SHOWPLAN_STATE_LOADED);
            lstShowPlan->ensureItemVisible(activePoint);
            if (lstShowPlan->selectedItem()) {
                selectionChanged(lstShowPlan->selectedItem());
            }
            L_INFO(LOG_DB,"Triggering update of next_on_showplan entry");
            activePointLock.unlock();
            updateNextTrack();
        }
        L_INFO(LOG_DB,"Configuration refresh complete.");
    }
}

void Showplan::addTrack(QString md5) {
    char *routine = "Showplan::addTrack";
    L_INFO(LOG_SHOWPLAN,"Adding to showplan " + md5);
    new DpsShowTrack(*this,md5.ascii());
    new ShowPlanAudio( lstShowPlan, lstShowPlan->lastItem(), this->lastItem());
    L_INFO(LOG_DB,"Triggering update of next_on_showplan entry");
    updateNextTrack();
    L_INFO(LOG_DB,"Playlist add complete.");
}

void Showplan::addJingle(QString md5) {
    char *routine = "Showplan::addJingle";
    L_INFO(LOG_SHOWPLAN,"Adding to showplan " + md5);
    new DpsShowJingle(*this,md5.ascii());
    new ShowPlanAudio( lstShowPlan, lstShowPlan->lastItem(), this->lastItem());
    L_INFO(LOG_DB,"Triggering update of next_on_showplan entry");
    updateNextTrack();
    L_INFO(LOG_DB,"Playlist add complete.");
}

void Showplan::addAdvert(QString md5) {
    char *routine = "Showplan::addAdvert";
    L_INFO(LOG_SHOWPLAN,"Adding to showplan " + md5);
    new DpsShowAdvert(*this,md5.ascii());
    new ShowPlanAudio( lstShowPlan, lstShowPlan->lastItem(), this->lastItem());
    L_INFO(LOG_DB,"Triggering update of next_on_showplan entry");
    updateNextTrack();
    L_INFO(LOG_DB,"Playlist add complete.");
}

void Showplan::clear() {
    if (lstShowPlan->childCount() == 0) return;
    dlgWarn *dlg = new dlgWarn(this, "");
    dlg->setTitle("Clear All");
    dlg->setWarning("Are you sure you wish to clear the show plan?");
    if ( dlg->exec() == QDialog::Accepted ){
        lstShowPlan->clear();
        selectionChanged(0);
        activePoint = 0;
        updateNextTrack();
    }
    delete dlg;
}

void Showplan::remove() {
    if (lstShowPlan->childCount() == 0) return;
    QListViewItem *x = lstShowPlan->selectedItem();
    QListViewItem *y;
    if ( x ) {
        y = x->nextSibling();
        delete x;
        if ( y ) {
            lstShowPlan->setSelected(y,true);
        }
        else {
            y = lstShowPlan->lastItem();
            lstShowPlan->setSelected(y,true);
        }
        selectionChanged(y);

    }
    updateNextTrack();
}

void Showplan::moveUp() {
    if (lstShowPlan->childCount() == 0) return;
    QListViewItem *x = lstShowPlan->selectedItem();
    if ( x ) {
        if (x == lstShowPlan->firstChild()->itemBelow() ) {
            lstShowPlan->takeItem(x);
            lstShowPlan->insertItem(x);
            lstShowPlan->setSelected(x,true);
        }
        else if (x != lstShowPlan->firstChild()) {
            x->moveItem(x->itemAbove()->itemAbove());
        }
        selectionChanged(x);
        updateNextTrack();
    }
}

void Showplan::moveDown() {
    if (lstShowPlan->childCount() == 0) return;
    QListViewItem *x = lstShowPlan->selectedItem();
    if ( x ) {
        if (x != lstShowPlan->lastItem() ) {
            x->moveItem(x->itemBelow());
            lstShowPlan->setSelected(x,true);
            selectionChanged(x);
            updateNextTrack();
        }
    }
}

void Showplan::moveTop() {
    if (lstShowPlan->childCount() == 0) return;
    QListViewItem *x = lstShowPlan->selectedItem();
    if ( x && x != lstShowPlan->firstChild()) {
        if (!activePoint) {
            lstShowPlan->takeItem(x);
            lstShowPlan->insertItem(x);
        }
        else {
            x->moveItem(activePoint);
        }
        lstShowPlan->setSelected(x,true);
        selectionChanged(x);
        updateNextTrack();
    }
}

void Showplan::moveBottom() {
    if (lstShowPlan->childCount() == 0) return;
    QListViewItem *x = lstShowPlan->selectedItem();
    if ( x ) {
        x->moveItem(lstShowPlan->lastItem());
        lstShowPlan->setSelected(lstShowPlan->lastItem(),true);
        selectionChanged(x);
        updateNextTrack();
    }
}

void Showplan::selectionChanged(QListViewItem* x) {
    ShowPlanItem *y = (ShowPlanItem*)x;
    if ( y && y->getState() == SHOWPLAN_STATE_UNLOADED ) {
        ShowPlanItem *z = (ShowPlanItem*)y->itemAbove();
        if ( z && z->getState() == SHOWPLAN_STATE_UNLOADED) {
            btnMoveUp->setEnabled(true);
            btnMoveTop->setEnabled(true);
        }
        else {
            btnMoveUp->setEnabled(false);
            btnMoveTop->setEnabled(false);
        }
        if ( y == (ShowPlanItem*)lstShowPlan->lastItem() ) {
            btnMoveBottom->setEnabled(false);
            btnMoveDown->setEnabled(false);
        }
        else {
            btnMoveBottom->setEnabled(true);
            btnMoveDown->setEnabled(true);
        }
        btnDelete->setEnabled(true);
        return;
    }
    btnMoveBottom->setEnabled(false);
    btnMoveDown->setEnabled(false);
    btnMoveUp->setEnabled(false);
    btnMoveTop->setEnabled(false);
    btnDelete->setEnabled(false);
}

void Showplan::updateNextTrack() {
    ShowPlanItem *x = 0;
    if (lstShowPlan->childCount() == 0) return;
    activePointLock.lock();
    if ( ! activePoint ) {
        x = (ShowPlanItem*)lstShowPlan->firstChild();
    }
    else {
        x = (ShowPlanItem*)activePoint->nextSibling();
    }
    activePointLock.unlock();
    if ( x ) {
        do
            if (x->getType() == 0) {
                ShowPlanAudio *audio = (ShowPlanAudio*)x;
                DpsShowItem t = audio->getTrack();
                conf->setParam("next_on_showplan",t["md5"]);
                return;
            }
        while ((x = (ShowPlanItem*)x->nextSibling()) != 0);
    }
}

void Showplan::draw() {
    QString path = qApp->applicationDirPath();
    
    grpFrame = new QGroupBox( _parent, "grpShowplan" );
    grpFrame->setGeometry( QRect( 0, 0, 470, 670 ) );
    QFont grpFrame_font(  grpFrame->font() );
    grpFrame_font.setFamily( "Sans Serif" );
    grpFrame_font.setPointSize( 16 );
    grpFrame_font.setBold( TRUE );
    grpFrame->setFont( grpFrame_font );
    grpFrame->setFrameShadow( QGroupBox::Sunken );
    grpFrame->setLineWidth( 1 );
    grpFrame->setFlat( FALSE );
    
    lstShowPlan = new QListView( grpFrame, "lstShowPlan" );
    lstShowPlan->addColumn( tr( "Item" ) ); 
    lstShowPlan->header()->setClickEnabled( FALSE, 
            lstShowPlan->header()->count() - 1 );
    lstShowPlan->header()->setResizeEnabled( FALSE, 
            lstShowPlan->header()->count() - 1 );
    lstShowPlan->setGeometry( QRect( 10, 20, 450, 580 ) );
    lstShowPlan->setPaletteBackgroundColor( QColor( 255, 255, 255 ) );
    QFont lstShowPlan_font(  lstShowPlan->font() );
    lstShowPlan_font.setPointSize( 10 );
    lstShowPlan_font.setBold( FALSE );
    lstShowPlan->setFont( lstShowPlan_font );  
    lstShowPlan->setFrameShape( QListView::Box ); 
    lstShowPlan->setFrameShadow( QListView::Plain );
    lstShowPlan->setVScrollBarMode( QListView::AlwaysOn );
    lstShowPlan->setHScrollBarMode( QListView::AlwaysOff );
    lstShowPlan->setAllColumnsShowFocus( TRUE );
    lstShowPlan->setResizeMode( QListView::NoColumn );
    lstShowPlan->setColumnWidth(0,lstShowPlan->width() - 5);
    lstShowPlan->setSorting(-1);
    lstShowPlan->header()->hide();
    
    btnDelete = new QPushButton( grpFrame, "btnDelete" );
    btnDelete->setGeometry( QRect( 160, 600, 75, 60 ) );
    btnDelete->setEnabled( FALSE );
    btnDelete->setPixmap(QPixmap(path + "/images/delete48.png"));

    btnMoveBottom = new QPushButton( grpFrame, "btnMoveBottom" );
    btnMoveBottom->setGeometry( QRect( 385, 600, 75, 60 ) );
    btnMoveBottom->setEnabled( FALSE );
    btnMoveBottom->setPixmap(QPixmap(path + "/images/movebottom32.png"));

    btnMoveDown = new QPushButton( grpFrame, "btnMoveDown" );
    btnMoveDown->setGeometry( QRect( 310, 600, 75, 60 ) );
    btnMoveDown->setEnabled( FALSE );
    btnMoveDown->setPixmap(QPixmap(path + "/images/movedown32.png"));

    btnMoveTop = new QPushButton( grpFrame, "btnMoveTop" );
    btnMoveTop->setGeometry( QRect( 10, 600, 75, 60 ) );
    btnMoveTop->setEnabled( FALSE );
    btnMoveTop->setPixmap(QPixmap(path + "/images/movetop32.png"));

    btnMoveUp = new QPushButton( grpFrame, "btnMoveUp" );
    btnMoveUp->setGeometry( QRect( 85, 600, 75, 60 ) );
    btnMoveUp->setEnabled( FALSE );
    btnMoveUp->setPixmap(QPixmap(path + "/images/moveup32.png"));

    btnClear = new QPushButton( grpFrame, "btnClear" );
    btnClear->setGeometry( QRect( 235, 600, 75, 60 ) );
    btnClear->setPixmap(QPixmap(path + "/images/clear32.png"));

    connect( btnDelete, SIGNAL( clicked() ),        this, SLOT( remove() ));
    connect( btnMoveBottom, SIGNAL( clicked() ),    this, SLOT( moveBottom() ));
    connect( btnMoveDown, SIGNAL( clicked() ),      this, SLOT( moveDown() ));
    connect( btnMoveTop, SIGNAL( clicked() ),       this, SLOT( moveTop() ));
    connect( btnMoveUp, SIGNAL( clicked() ),        this, SLOT( moveUp() ));
    connect( btnClear, SIGNAL( clicked() ),         this, SLOT( clear() ));
    connect( lstShowPlan, SIGNAL( selectionChanged(QListViewItem*) ),
                this, SLOT( selectionChanged(QListViewItem*) ));
}

void Showplan::clean() {

}
