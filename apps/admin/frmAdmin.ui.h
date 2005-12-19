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
#include <iostream>
using namespace std;

void frmAdmin::init() {
	Sys = new systemmanager();
	DisplayArchives();
}


void frmAdmin::destroy() {
	
}

/*
 * Adds an Archive to the database
 */
void frmAdmin::ArchiveAdd() {
	if (txtArchiveNewName->text() == "" || txtArchiveNewLocalPath->text() == "" || txtArchiveNewRemotePath->text() == "") {
		QMessageBox::warning(this,"DPS Administration",
							 "Please fill in all the fields!");
		return;
	}
	if (Sys->atArchive(txtArchiveNewName->text())) {
		QMessageBox::critical(this, "DPS Administration",
							  "An Archive with this name already exists");
		return;
	}
	Sys->addArchive(txtArchiveNewName->text().ascii(),
					txtArchiveNewLocalPath->text().ascii(),
					txtArchiveNewRemotePath->text().ascii());
	DisplayArchives();
	txtArchiveNewName->setText("");
	txtArchiveNewLocalPath->setText("");
	txtArchiveNewRemotePath->setText("");
}

/*
 * Drops an archive entry from the database
 */
void frmAdmin::ArchiveDrop() {
	Sys->dropArchive(tblArchives->currentRow());
	DisplayArchives();
}

/*
 * Refreshes the list of archives on the screen
 */
void frmAdmin::DisplayArchives() {
	archive A;
	tblArchives->setNumRows(Sys->sizeArchive());
	for (short i = 0; i < Sys->sizeArchive(); i++) {
		A = Sys->atArchive(i)->spec();
		tblArchives->setText(i,0,A.name);
		tblArchives->setText(i,1,A.localPath);
		tblArchives->setText(i,2,A.remotePath);
	}
	for (short i = 0; i < 3; i++) tblArchives->adjustColumn(i);
}

/* ============================
 * MUSIC LIBRARY ROUTINES
 * ============================*/
/*
 * Loads the archive managers for each archive in the system
 */
void frmAdmin::MusicLoad() {
	btnMusicLoad->setEnabled(false);
	lblStatus->setText("Loading audio data...");
	lblStatus->repaint();
	for (unsigned short i = 0; i < Sys->sizeArchive(); i++) {
		Sys->atArchive(i)->load();
	}
	DisplayMusic();
	lstMusicDB->setEnabled(true);
	btnMusicAdd->setEnabled(true);
	lblStatus->setText("Ready.");
}

void frmAdmin::MusicAdd() {
	lblStatus->setText("Examining inbox. Please wait...");
	lblStatus->repaint();
	frmAdminAddMusic *F = new frmAdminAddMusic(this);
	F->setSystemManager(Sys);
	archivemanager *A;
	track t;
	for (unsigned short i = 0; i < Sys->sizeArchive(); i++) {
		A = Sys->atArchive(i);
		for (unsigned long j = 0; j < A->size(DPS_INBOX); j++) {
			t = A->at(DPS_INBOX,j);
			QCheckListItem *new_track = new QCheckListItem(F->lstInbox,
														   t.title + " (" + t.artist + ")",
														   QCheckListItem::CheckBox);
			new_track->setOn(true);
		}
	}
	F->lstInbox->adjustColumn(0);
	lblStatus->setText("");
	F->exec();
	DisplayMusic();
	lblStatus->setText("Ready.");
}


void frmAdmin::DisplayMusic() {
	archivemanager *A;
	track t;
	lstMusicDB->clear();
	for (unsigned short i = 0; i < Sys->sizeArchive(); i++) {
		A = Sys->atArchive(i);
		for (unsigned long j = 0; j < A->size(DPS_DB); j++) {
			t = A->at(DPS_DB,j);
			QListViewItem new_track = new QListViewItem(lstMusicDB,
														t.title,
														t.artist);
		}
	}
}


void frmAdmin::Quit() {
	delete Sys;
	exit(0);
}
