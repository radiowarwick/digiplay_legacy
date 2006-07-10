#ifndef CLASS_TAB_PANEL
#define CLASS_TAB_PANEL

#include <string>
using namespace std;

class QWidget;
class QTabWidget;
class Auth;

class TabPanel {
	public:
		TabPanel(QTabWidget *parent, string text);
		virtual ~TabPanel();
		virtual void configure(Auth *authModule);
		void setText(string text) {tabText = text;}

	protected:
		QWidget *getPanel() {return panel;}
		void hide();
		void show();
		virtual void draw() = 0;
		virtual void clear() = 0;

	private:
		QWidget *panel;
		QTabWidget *tabParent;
		string tabText;
};

#endif
