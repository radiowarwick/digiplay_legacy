#include <qtabwidget.h>
#include <qtextbrowser.h>
#include <qlistview.h>
#include <qstring.h>
#include <qpixmap.h>
#include <qiconset.h>
#include <qheader.h>
#include <qapplication.h>
#include <qobject.h>

#include "Auth.h"
#include "Logger.h"
#include "dps.h"
#include "config.h"

#include "TabPanelEmail.h"

TabPanelEmail::~TabPanelEmail() {

}

void TabPanelEmail::configure(Auth *authModule) {
	hide();
	if (authModule->isPermitted("TabInfo")) {
		draw();
		show();
	}
}

void TabPanelEmail::draw() {
	char* routine = "TabEmail::draw()";


/*	######################################
	for some reason this code is fscked up
	 and since i don't know what it does
		anyway..............
	######################################


	if (txtEmailBody||lstEmail) {
		Logger::log(WARNING,routine,"Implicit clear() called",3);
		clear();
	}


*/
	QString path = qApp->applicationDirPath();
        email_new = new QPixmap(path + "/images/email_new.bmp");
        email_old = new QPixmap(path + "/images/email_old.bmp");
        email_Icons = new QIconSet(*email_new, QIconSet::Automatic);
	lstEmail = new QListView(getPanel(), "lstEmail" );
	lstEmail->addColumn( QString::null );
	lstEmail->header()->setResizeEnabled( FALSE, lstEmail->header()->count() - 1 );
	lstEmail->addColumn( QObject::tr( "From" ) );
	lstEmail->header()->setResizeEnabled( FALSE, lstEmail->header()->count() - 1 );
	lstEmail->addColumn( QObject::tr( "Subject" ) );
	lstEmail->header()->setResizeEnabled( FALSE, lstEmail->header()->count() - 1 );
	lstEmail->addColumn( QObject::tr( "Received" ) );
	lstEmail->header()->setResizeEnabled( FALSE, lstEmail->header()->count() - 1 );
	lstEmail->addColumn( QObject::tr( "ID" ) );
	lstEmail->header()->setResizeEnabled( FALSE, lstEmail->header()->count() - 1 );
	lstEmail->setGeometry( QRect( 10, 10, 495, 265 ) );
	lstEmail->setVScrollBarMode( QListView::AlwaysOn );
	lstEmail->setAllColumnsShowFocus( TRUE );
        lstEmail->setColumnText(0, *email_Icons, "");
        lstEmail->setColumnWidth(0,22); //New
        lstEmail->setColumnWidth(1,183); //From
        lstEmail->setColumnWidth(2,183); //Subject
        lstEmail->setColumnWidth(3,90); //Received
        lstEmail->setColumnWidth(4,0); //ID
        lstEmail->setSorting(4, FALSE);
	txtEmailBody = new QTextBrowser(getPanel(), "txtEmailBody" );
	txtEmailBody->setGeometry( QRect( 10, 280, 495, 350 ) );
	QObject::connect( lstEmail, SIGNAL( selectionChanged(QListViewItem*) ), this, SLOT( getEmailBody(QListViewItem*) ) );

}

void TabPanelEmail::getEmail(Connection *C){


        Transaction *T = new Transaction(*C,"");
	email e;
        tm *dte;
        char date[30];
        stringstream SQL;
	QListViewItem *new_email;

                SQL << "SELECT * FROM email ORDER BY datetime DESC LIMIT 50;";
//              cout << SQL.str() << endl;
        try {
                Result R = T->exec(SQL.str());
                string flag;

//              cout << (int)R.size()-1 << endl;
                for (int i = (int)R.size()-1; i > -1; i--) {
                        time_t thetime(atoi(R[i]["datetime"].c_str()));
                        dte = localtime(&thetime);
                        strftime(date, 30, "%Ex %H:%M", dte);
			new_email = new QListViewItem(lstEmail, "",
                        	R[i]["sender"].c_str(),
                        	R[i]["subject"].c_str(),
                        	date,
                        	R[i]["id"].c_str());

//                      cout << "   *" << (R[i]["new_flag"].c_str()) << "*  " << endl;
                        string flag = R[i]["new_flag"].c_str();
                        if (  !flag.compare("t")   )
                                new_email->setPixmap(0, *email_new);
                        else
                                 new_email->setPixmap(0, *email_old);

                }
        }
        catch (...) {
                cout << " -> ERROR: Failed to get new e-mails." << endl;
        }
        delete T;
}

void TabPanelEmail::getEmailBody(QListViewItem *current) {
	config *conf = new config("digiplay");
	Connection *C = new Connection(conf->getDBConnectString());
        Transaction *T = new Transaction(*C,"");
	string id = current->text(4);
        stringstream SQL;
                SQL << "SELECT * FROM email WHERE id='"
                    << id
                    << "' ORDER BY datetime DESC LIMIT 50;";
//      cout << SQL.str() << endl;
        try {
                Result R = T->exec(SQL.str());
                txtEmailBody->setText(R[0]["body"].c_str());
        }
        catch (...) {
                cout << " -> ERROR: Failed to get e-mail body." << endl;
        }
        delete T;
	delete C;
	delete conf;

}

void TabPanelEmail::markRead(Connection *C, string id) {
        Transaction *T = new Transaction(*C,"");
        stringstream SQL;
                SQL << "UPDATE email SET new_flag='f' WHERE id='"
                    << id << "';";
  //      cout << SQL.str() << endl;
        try {
                T->exec(SQL.str());
                T->commit();
        }
        catch (...) {
                                T->abort();
                cout << " -> ERROR: Failed to set e-mail read." << endl;
        }
        delete T;
}




void TabPanelEmail::clear() {
	delete txtEmailBody;
	delete lstEmail;
}
