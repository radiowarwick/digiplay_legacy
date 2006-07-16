#ifndef CLASS_TAB_PANEL_SCRIPT
#define CLASS_TAB_PANEL_SCRIPT

#include <qlabel.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qpushbutton.h>

#include "TabPanel.h"
#include "triggerThread.h"
#include "config.h"

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

class QTabWidget;
class Auth;

class TabPanelScript : public TabPanel {
	Q_OBJECT
	public:
		TabPanelScript(QTabWidget *parent, string text);
		~TabPanelScript();
		void configure(Auth *authModule);

	private:
		void draw();
		void clear();
		
		Connection *C;
	        QLabel *lblScriptName, *lblScriptDuration;
	        QLineEdit *txtScriptName, *txtScriptDuration;
		QTextEdit *txtScriptBody;
        	QPushButton *btnScriptSave;
};

#endif
