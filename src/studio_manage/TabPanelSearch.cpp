/*
 * Library Search GUI Module
 * TabPanelSearch.cpp
 * Allows searching of the music database.
 *
 * Copyright (c) 2006 Chris Cantwell
 * Copyright (c) 2006 Ian Liverton
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#include <cstdlib>

#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QTreeWidget>
#include <QtCore/QString>
#include <QtGui/QPixmap>
#include <QtGui/QIconSet>
#include <QtGui/QHeaderView>
#include <QtGui/QApplication>
#include <QtCore/QObject>
#include <QtGui/QPushButton>
#include <QtGui/QCheckBox>
//#include <QtGui/QTable>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QToolTip>

#include "Auth.h"
#include "Logger.h"
#include "dps/DpsObject.h"

#include "TabPanelSearch.h"

/**
 * Constructor.
 */
TabPanelSearch::TabPanelSearch(QTabWidget *parent, QString text)
		: TabPanel(parent,text)  {
    // Set panel tag
	panelTag = "TabSearch";

    // Draw GUI components
    draw();

    // Access configuration
	conf = new Config("digiplay", this);

    // Create library search engine.
    library_engine = new DpsMusicSearch();
    searching = false;
}


/**
 * Delete dynamically created objects.
 */
TabPanelSearch::~TabPanelSearch() {
    // Delete GUI components
    clear();

    // Delete configuration object
	delete conf;
}


/**
 * MessagingInterface
 */
void TabPanelSearch::onMessage() {

}


/**
 * Performs a music search.
 */
void TabPanelSearch::Library_Search() {
	if (searching) return;

	searching = true;
	btnLibrarySearch->setEnabled(false);
	txtLibrarySearchText->setEnabled(false);
	TitleCheckBox->setEnabled(false);
	ArtistCheckBox->setEnabled(false);
	AlbumCheckBox->setEnabled(false);

	// Check if user has entered required information
    if (txtLibrarySearchText->text() == "") {
        dlgWarn *warning = new dlgWarn(getPanel(), 0);
        warning->setTitle("Oops!");
        warning->setWarning(
                "You seem to have forgotten to enter something to search for.");
        warning->setQuestion(false);
        warning->exec();
        delete warning;
		btnLibrarySearch->setEnabled(true);
		txtLibrarySearchText->setEnabled(true);
		TitleCheckBox->setEnabled(true);
		ArtistCheckBox->setEnabled(true);
		AlbumCheckBox->setEnabled(true);
		searching = false;
        return;
    }
    if ( ! (TitleCheckBox->isChecked()
                ||ArtistCheckBox->isChecked()
                ||AlbumCheckBox->isChecked() )) {
        dlgWarn *warning = new dlgWarn(getPanel(), 0);
        warning->setTitle("Oops!");
        warning->setWarning(
                "Please select at least one of Title, Artist, Album.");
        warning->setQuestion(false);
        warning->exec();
        delete warning;
		btnLibrarySearch->setEnabled(true);
		txtLibrarySearchText->setEnabled(true);
		TitleCheckBox->setEnabled(true);
		ArtistCheckBox->setEnabled(true);
		AlbumCheckBox->setEnabled(true);
		searching = false;
        return;
    }

    // Clear the results list
    lstSearchResults->selectAll();
    lstSearchResults->clearSelection();

    // Display a "searching..." notice
	new QTreeWidgetItem( lstSearchResults, QStringList("Searching......."));
	lstSearchResults->setEnabled(false);

    // Set search parameters
	library_engine->searchLimit(atoi(conf->getParam("search_limit").c_str()));
	library_engine->searchTitle(TitleCheckBox->isChecked());
	library_engine->searchArtist(ArtistCheckBox->isChecked());
	library_engine->searchAlbum(AlbumCheckBox->isChecked());

	// Pass control over to separate searching thread
	threadStart();
}

void TabPanelSearch::threadExecute() {
	// Perform search
    try {
	    SearchResults = library_engine->query(txtLibrarySearchText->text().toStdString());
    }
    catch ( DpsMusicSearch::Error &e ) {
        dlgWarn *warning = new dlgWarn(getPanel(), 0);
        warning->setTitle("Oops!");
        warning->setWarning(QString::fromStdString(e.getMessage()));
        warning->setQuestion(false);
        warning->exec();
        delete warning;
		btnLibrarySearch->setEnabled(true);
		txtLibrarySearchText->setEnabled(true);
		TitleCheckBox->setEnabled(true);
		ArtistCheckBox->setEnabled(true);
		AlbumCheckBox->setEnabled(true);
		searching = false;
    }
	processResults();
}

void TabPanelSearch::processResults() {
	// Clear the list and enter search results (disable updates until done)
	lstSearchResults->setUpdatesEnabled(false);
	lstSearchResults->clear();

    // Display information message if nothing found
	if (SearchResults.size() == 0) {
		new QTreeWidgetItem( lstSearchResults, QStringList("(Sorry, no matches found.)"));

		btnLibrarySearch->setEnabled(true);
		txtLibrarySearchText->setEnabled(true);
		TitleCheckBox->setEnabled(true);
		ArtistCheckBox->setEnabled(true);
		AlbumCheckBox->setEnabled(true);
		lstSearchResults->setUpdatesEnabled(true);
//		lstSearchResults->triggerUpdate();

		searching = false;
		return;
	}

    lstSearchResults->setEnabled(true);
	QTreeWidgetItem *x;

	for (unsigned int i = 0; i < SearchResults.size(); i++) {
	    QStringList s;
	    s.append(QString::fromStdString(SearchResults[i]["title"]));
	    s.append(QString::fromStdString(SearchResults[i]["artist"]));
	    s.append(QString::fromStdString(SearchResults[i]["album"]));
	    s.append(QString::fromStdString(SearchResults[i]["id"]));
		x = new QTreeWidgetItem(  lstSearchResults, s );

// TODO: Views currently missing censor column
/*		if (SearchResults[i]["censor"] == "t") {
			x->setPixmap(0,*pixCensored);
		} else {
			x->setPixmap(0,*pixAudio);
		}
*/	}

	btnLibrarySearch->setEnabled(true);
	txtLibrarySearchText->setEnabled(true);
	TitleCheckBox->setEnabled(true);
	ArtistCheckBox->setEnabled(true);
	AlbumCheckBox->setEnabled(true);
	lstSearchResults->setUpdatesEnabled(true);
//	lstSearchResults->triggerUpdate();
	txtLibrarySearchText->setFocus();

	searching = false;
}


/**
 * Emits a signal indicating which item is selected.
 */
void TabPanelSearch::playlistAdd(QTreeWidgetItem* x) {
	if (x) {
		DpsAudioItem vAudio(x->text(3).toLong());
        emit audioSelected( vAudio );
	}
}


/**
 * Draw GUI components
 */
void TabPanelSearch::draw() {
    // Load icons for display
    path = DPSDIR;
    pixAudio = new QPixmap(path + "/images/music16.png");
    pixCensored = new QPixmap(path + "/images/censoredmusic16.png");

    lblSearch = new QLabel( getPanel() );
    lblSearch->setGeometry( QRect( 28, 10, 60, 20 ) );
    QFont lblSearch_font(  lblSearch->font() );
    lblSearch_font.setPointSize( 10 );
    lblSearch_font.setBold( FALSE );
    lblSearch->setFont( lblSearch_font );

    Searchlable = new QLabel( getPanel() );
    Searchlable->setGeometry( QRect( 10, 33, 67, 20 ) );
    QFont Searchlable_font(  Searchlable->font() );
    Searchlable_font.setPointSize( 10 );
    Searchlable_font.setBold( FALSE );
    Searchlable->setFont( Searchlable_font );

    txtLibrarySearchText = new QLineEdit( getPanel() );
    txtLibrarySearchText->setGeometry( QRect( 83, 10, 330, 20 ) );

    ArtistCheckBox = new QCheckBox( getPanel() );
    ArtistCheckBox->setGeometry( QRect( 83, 35, 70, 20 ) );
    QFont ArtistCheckBox_font(  ArtistCheckBox->font() );
    ArtistCheckBox_font.setBold( FALSE );
    ArtistCheckBox->setFont( ArtistCheckBox_font );
    ArtistCheckBox->setChecked( TRUE );

    TitleCheckBox = new QCheckBox( getPanel() );
    TitleCheckBox->setGeometry( QRect( 190, 35, 60, 20 ) );
    QFont TitleCheckBox_font(  TitleCheckBox->font() );
    TitleCheckBox_font.setBold( FALSE );
    TitleCheckBox->setFont( TitleCheckBox_font );
    TitleCheckBox->setChecked( TRUE );

    AlbumCheckBox = new QCheckBox( getPanel() );
    AlbumCheckBox->setGeometry( QRect( 290, 35, 91, 20 ) );
    QFont AlbumCheckBox_font(  AlbumCheckBox->font() );
    AlbumCheckBox_font.setBold( FALSE );
    AlbumCheckBox->setFont( AlbumCheckBox_font );
    AlbumCheckBox->setChecked( TRUE );

    btnLibrarySearch = new QPushButton( getPanel() );
    btnLibrarySearch->setGeometry( QRect( 421, 10, 80, 20 ) );
//    btnLibrarySearch->setStyleSheet("color: rgb(0,0,0);");

    QFont btnLibrarySearch_font(  btnLibrarySearch->font() );
    btnLibrarySearch_font.setPointSize( 10 );
    btnLibrarySearch_font.setBold( FALSE );
    btnLibrarySearch->setFont( btnLibrarySearch_font );
    btnLibrarySearch->setAutoDefault( FALSE );
    QStringList vHeaderLabels;
    vHeaderLabels.append("Title");
    vHeaderLabels.append("Artist");
    vHeaderLabels.append("Album");
    vHeaderLabels.append("ID");

    lstSearchResults = new QTreeWidget(getPanel() );
    lstSearchResults->setGeometry( QRect( 10, 60, 510, 570 ) );
    lstSearchResults->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    lstSearchResults->setAllColumnsShowFocus( TRUE );
    //lstSearchResults->setColumnWidthMode(3, QListView::Manual);
    lstSearchResults->setColumnWidth(3, 0);
    lstSearchResults->setColumnCount(4);
    lstSearchResults->setHeaderLabels(vHeaderLabels);
    lstSearchResults->header()->setMovable( FALSE );
    lstSearchResults->header()->setResizeMode(
            lstSearchResults->header()->count() - 1,
            QHeaderView::Fixed);
    lstSearchResults->header()->setResizeMode(
            lstSearchResults->header()->count() - 1,
            QHeaderView::Fixed);
    lstSearchResults->header()->setResizeMode(
            lstSearchResults->header()->count() - 1,
            QHeaderView::Fixed);
    lstSearchResults->header()->setResizeMode(
            lstSearchResults->header()->count() - 1,
            QHeaderView::Fixed);
    //lstSearchResults->setColumnWidthMode(0, QTreeWidget::Manual);
    //lstSearchResults->setColumnWidthMode(1, QListView::Manual);
    //lstSearchResults->setColumnWidthMode(2, QListView::Manual);
    //lstSearchResults->setColumnWidthMode(3, QListView::Manual);
    lstSearchResults->setColumnWidth(0, 200);
    lstSearchResults->setColumnWidth(1, 200);
    lstSearchResults->setColumnWidth(2, 90);
    lstSearchResults->setColumnWidth(3, 0);
    lstSearchResults->header()->setMovable( FALSE );
    lstSearchResults->sortByColumn(0);

    lblSearch->setText( tr( "Search:" ) );
    TitleCheckBox->setText( tr( "Title" ) );
    AlbumCheckBox->setText( tr( "Album" ) );
    Searchlable->setText( tr( "Search by:" ) );
    ArtistCheckBox->setText( tr( "Artist" ) );
    btnLibrarySearch->setText( tr( "Search" ) );

    connect( btnLibrarySearch, SIGNAL( clicked() ),
                this, SLOT( Library_Search() ) );
    connect( lstSearchResults, SIGNAL( doubleClicked(QListViewItem*) ),
                this, SLOT( playlistAdd(QListViewItem*) ) );
    connect( txtLibrarySearchText, SIGNAL( returnPressed() ),
                this, SLOT( Library_Search() ) );

}


/**
 * Delete GUI components.
 */
void TabPanelSearch::clear() {
	delete btnLibrarySearch;
	delete lstSearchResults;
	delete txtLibrarySearchText;
	delete Searchlable;
	delete ArtistCheckBox;
	delete AlbumCheckBox;
	delete TitleCheckBox;
	delete lblSearch;
	delete library_engine;
}
