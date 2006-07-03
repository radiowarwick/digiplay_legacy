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

#include "systemmanager.h"

void frmAdminAddMusic::init() {
	
}


void frmAdminAddMusic::AddAll() {
	if (!Sys) cout << "Sys is NULL!" << endl;
	for (int i = 0; i < Sys->sizeArchive(); i++) {
		archivemanager *A = Sys->atArchive(i);
		pgrAdd->reset();
		lblStatus->setText("Adding audio from archive '" + A->spec().name + "'");
		lblStatus->repaint();
		pgrAdd->setTotalSteps(lstInbox->childCount());
		for (int j = 0; j < lstInbox->childCount(); j++) {
			A->add(0);
			pgrAdd->setProgress(j);
		}
	}
	this->accept();
}

void frmAdminAddMusic::setSystemManager( systemmanager *S ) {
	Sys = S;
	btnAddAll->setEnabled(true);
}


void frmAdminAddMusic::Cancel() {
	this->reject();
}
