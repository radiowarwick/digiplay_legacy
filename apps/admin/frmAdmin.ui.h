/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
#include "dirent.h"
#include "sys/types.h"

#include "config_reader.h"
#include "trackinfo.h"

string DB_CONNECT;
string AUDIO_PATH;	

Connection *C;
vector<trackinfo*> *newTracks;
vector<trackinfo*> *currentTracks;
	
void frmAdmin::init() {
    config_reader *Conf = new config_reader("digiplay");

    if (Conf->isDefined("DB_HOST"))
        DB_CONNECT += "hostaddr=" + Conf->getParam("DB_HOST") + " ";
    if (Conf->isDefined("DB_NAME"))
        DB_CONNECT += "dbname=" + Conf->getParam("DB_NAME") + " ";
    if (Conf->isDefined("DB_USER"))
        DB_CONNECT += "user=" + Conf->getParam("DB_USER") + " ";
    if (Conf->isDefined("AUDIO_PATH"))
        AUDIO_PATH = Conf->getParam("AUDIO_PATH");

    if (AUDIO_PATH == "") {
        cout << "FATAL: Missing or invalid AUDIO_PATH setting" << endl;
        cout << "  -> Check /etc/digiplay is correct" << endl;
        exit(-1);
    }
	if (AUDIO_PATH.substr(AUDIO_PATH.size() - 2, 1) != "/") {
		AUDIO_PATH += "/";
	}
    if (DB_CONNECT == "") {
        cout << "FATAL: No database connection defined" << endl;
        cout << "  -> Check /etc/digiplay defined database connection" << endl;
        exit(-1);
    }
	cout << "Database: " << DB_CONNECT << endl;
	C  = new Connection(DB_CONNECT);
	newTracks = new vector<trackinfo*>;
	currentTracks = new vector<trackinfo*>;
}

void frmAdmin::helpIndex()
{

}


void frmAdmin::helpContents()
{

}


void frmAdmin::helpAbout()
{

}


void frmAdmin::ScanTracks()
{
	DIR *dirp;
	struct dirent *dp;
	string filename, path;
	trackinfo *newTrack;
	unsigned int subdir;
	
	cout << "Scanning info files..." << endl;
	txtStatusBar->setText("Scanning audio archives...this may take several minutes...please wait...");
	txtStatusBar->repaint(true);
	for (unsigned short i = 48; i < 64; i++) {
		if (i < 58) subdir = i;
		else subdir = i + 39;
	
		path = AUDIO_PATH + (char)subdir;
		cout << "Scanning: " << path << endl;
		dirp = opendir(path.c_str());
		while (dirp) {
			errno = 0;
			if ((dp = readdir(dirp)) != NULL) {
				filename = dp->d_name;
				if (filename.length() > 5) {
					if (filename.substr(filename.length() - 5, 5) == ".info") {
						newTrack = new trackinfo(C, 
										filename.substr(filename.length() - 37,
										filename.length() - 5
										));
						if (!newTrack->hasAudio()) {
							delete newTrack;
							continue;
						}
						newTrack->readFromFile();
						newTrack->clean();
						if (newTrack->inDB()) {
							currentTracks->push_back(newTrack);
						}
						else {
							newTracks->push_back(newTrack);
						}
					}
				}
			}
			else {
				if (errno == 0) {
					closedir(dirp);
					break;
				}
				closedir(dirp);
				break;
			}
		}
	}
	cout << "done." << endl;
	UpdateLists();
	stringstream status;
	status << "Ready. " << newTracks->size() << " tracks to be imported.";
	txtStatusBar->setText(status.str());
}


void frmAdmin::AddTracks() {
	stringstream status;
	txtStatusBar->setText("Adding new tracks to database...");
	txtStatusBar->repaint(true);
	unsigned int number_of_tracks = newTracks->size();
	for (unsigned int i = 0; i < number_of_tracks; i++) {
		status.str("");
		status << "Importing track " << i << ".         " << number_of_tracks << "." << endl;
		txtStatusBar->setText(status.str());
		txtStatusBar->repaint(true);
		newTracks->at(0)->audio_trim();
		newTracks->at(0)->saveToDB();
		currentTracks->push_back(newTracks->at(0));
		newTracks->erase(newTracks->begin());
	}
	UpdateLists();
	txtStatusBar->setText("Ready.");
}



void frmAdmin::UpdateLists() {
	cout << "Updating display..." << flush;
	txtStatusBar->setText("Updating Display...");
	txtStatusBar->repaint(true);
	QString title;
	QString artist;
	lstManageNew->clear();
	lstManageCurrent->clear();
	for (unsigned int i = 0; i < newTracks->size(); i++) {
		title = newTracks->at(i)->title();
		artist = newTracks->at(i)->artist();
		lstManageNew->insertItem(title + " (" + artist + ")", -1);
	}
	for (unsigned int i = 0; i < currentTracks->size(); i++) {
		title = currentTracks->at(i)->title();
		artist = currentTracks->at(i)->artist();
		lstManageCurrent->insertItem(title + " (" + artist + ")", -1);
	}
	cout << "done." << endl;
}


void frmAdmin::test()
{
	lstSustDirectory->addColumn( "Item" );
	lstSustDirectory->addColumn( "Description" );
	QPixmap folder = QPixmap("./dir_folder.bmp");
	QPixmap audio = QPixmap("./dir_audio.bmp");
	QListViewItem *element = new QListViewItem( lstSustDirectory, "root", "this is a root element" );
	element->setPixmap( 0, folder );
	QListViewItem *element2 = new QListViewItem( element, "audio1", "this is an audio file" );
	element2->setPixmap( 0, audio );
	QListViewItem *element3 = new QListViewItem( element, "folder", "this is a subfolder");
	element3->setPixmap( 0, folder);
	QListViewItem *element4 = new QListViewItem( element3, "audio2", "this is another audio file" );
	element4->setPixmap( 0, audio);
}
