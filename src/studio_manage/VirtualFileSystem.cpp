#include "VirtualFileSystem.h"
#include "dps.h"
#include <QStringList>
#include <QString>

VirtualDirectory::VirtualDirectory() {
        config *conf = new config("digiplay");
        C = new Connection(conf->getDBConnectString());
        delete conf;
}

VirtualDirectory::VirtualDirectory( const QString & path, const QString &
                        nameFilter = QString::null, int sortSpec = Name |
                        IgnoreCase, int filterSpec = All ) {
        config *conf = new config("digiplay");
        C = new Connection(conf->getDBConnectString());
        delete conf;
        _path = path;
        _id=GetIDFromPath(path);
        _name = GetNameFromID()
}

VirtualDirectory::VirtualDirectory( VirtualDirectory & d ) {
        config *conf = new config("digiplay");
        C = new Connection(conf->getDBConnectString());
        delete conf;
}

VirtualDirectory::~VirtualDirectory() {
        if (C && C->is_open()) {
                C->Deactivate();
        }
        delete C;
}

virtual void VirtualDirectory::setPath ( const QString & path ) {
	_path = path;
	_id=GetIDFromPath(path);
        _name = GetNameFromID(_id)
}

virtual QString VirtualDirectory::path () const {
	return _path();
}

virtual bool isReadable () {
	//Return True - Auth checking needs writing into here!!!
	return TRUE;
}

virtual const VirtualFileInfoList * entryInfoList ( int filterSpec = 
	DefaultFilter, int sortSpec = DefaultSort ) const {

	//Get here soon!
}









////////////////////////////PRIVATE//////////////////////////////




int VirtualDirectory::GetIDFromPath () {
	int id;
        QStringList dirs = QStringList::split("/", _path, FALSE )
        for ( QStringList::Iterator it = dirs.begin(); it != dirs.end(); ++it ) {
                QString SQL = "SELECT id FROM dir WHERE parent='";
                        SQL+= id;
                        SQL+= "' AND name='";
                        SQL+=*it;
                        SQL+="';";
                Transaction *T = new Transaction (*C,"");
                try {
                        Result R = T->exec(SQL.c_str());
                        if ((int)R.size()==1) {
                                id=atoi(R[0]["id"].c_str());
                        }
                        else {
                                cout << " -> ERROR: Too many directories returned." << endl;
                        }
                }
                catch (...) {
                        cout << " -> ERROR: Failed to get directory." << endl;
                }
                delete T;
        }
	return id;
}

QString VirtualDirectory::GetNameFromID( int id ) {
	QString SQL = "SELECT name FROM dir WHERE id=";
		SQL+=dps_itoa(id);
		SQL+=";";
        Transaction *T = new Transaction (*C,"");
        try {
                 Result R = T->exec(SQL.c_str());
		 if ((int)R.size()==1)
                 	return QString(R[0]["name"].c_str());
	 	 else {
                 	cout << " -> ERROR: Too many directories returned." << endl;
        	 }
	}
        catch (...) {
                 cout << " -> ERROR: Failed to get directory." << endl;
        }    
        delete T;
}
