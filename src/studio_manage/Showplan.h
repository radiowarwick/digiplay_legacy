#ifndef CLASS_SHOWPLAN
#define CLASS_SHOWPLAN

#include <vector>
using namespace std;

#include <qwidget.h>
#include <qmutex.h>

#include "config.h"
#include "triggerThread.h"
#include "ShowPlanItem.h"
#include "ShowPlanAudio.h"
#include "ShowPlanScript.h"
#include "DpsObject.h"

class QGroupBox;
class QListView;
class QListViewItem;
class QPushButton;

class Auth;

class Showplan : public QWidget, private DpsShowplan {
	Q_OBJECT

	public:
		Showplan(QWidget *parent, const char* name);
		~Showplan();
        using DpsShowplan::operator=;

        void configure(Auth *authModule);
        void load(unsigned int index);

        void setGeometry (const QRect& r);
		void resizeEvent (QResizeEvent *e);
        void customEvent (QCustomEvent *e);

    public slots:
        void addTrack(QString md5);
        void addJingle(QString md5);
        void addAdvert(QString md5);
        void clear();
        void remove();
        void moveUp();
        void moveDown();
        void moveTop();
        void moveBottom();

    private slots:
        void selectionChanged(QListViewItem* x);
        void updateNextTrack();

	private:
        void draw();
		void clean();

        config* conf;
        triggerThread* confTrigger;

        QWidget* _parent;
		QGroupBox* grpFrame;
        QListView* lstShowPlan;
        QPushButton* btnDelete;
		QPushButton* btnMoveBottom;
		QPushButton* btnMoveDown;
        QPushButton* btnMoveTop;
        QPushButton* btnMoveUp;
        QPushButton* btnClear;

        QMutex activePointLock;
        ShowPlanItem* activePoint;
};

#endif
