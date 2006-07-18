#include <iostream>
using namespace std;

#include <qstring.h>
#include <string.h>
#include "FileBrowser.h"
#include "config.h"

FileBrowser::FileBrowser( QWidget *parent, const char *name, int types_in )
		: QListView(parent,name) {
        config *conf = new config("digiplay");
        C = new Connection(conf->getDBConnectString());
        delete conf;
	types=types_in;
	init();
}

void FileBrowser::init() {
	getFiles();
}

void FileBrowser::getFiles() {
        clear();
        FileBrowserItem *root = new FileBrowserItem(this, "Digiplay", 0, 16);
	root->setOpen(true);
        addChildren(root, 0);
}

void FileBrowser::addChildren(FileBrowserItem *parent, int id) {
        stringstream SQL;
        Result R;

	//Add directories
        SQL << "SELECT * FROM dir WHERE parent=" << id << ";";
        try {
                Transaction *T = new Transaction(*C, "");
                R = T->exec(SQL.str());
                delete T;
        }
        catch (...) {
                cout << "DB failure: " << SQL.str() << endl;
        }
        for (int i=0; i < (int)R.size(); i++) {
                FileBrowserItem *item = new FileBrowserItem(parent, QString(R[i]["name"].c_str()), atoi(R[i]["id"].c_str()), 2);
                addChildren(item, atoi(R[i]["id"].c_str()));
        }

	//Add file types

	if (types & Audio) {
//		cout << "Would be getting audio files" << endl;
	}
	if (types & Script) {
//		cout << "Would be getting scripts" << endl;
	}
	if (types & Cartwall) {
//		cout << "Would be getting cartwalls" << endl;
	}
}

