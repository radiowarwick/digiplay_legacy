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
#include <qtabwidget.h>
#include <qtextbrowser.h>
#include <qlistview.h>
#include <qstring.h>
#include <qpixmap.h>
#include <qiconset.h>
#include <qheader.h>
#include <qapplication.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qtable.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtooltip.h>

#include "Auth.h"
#include "Logger.h"

#include "TabPanelSearch.h"

/**
 * Constructor.
 */
TabPanelSearch::TabPanelSearch(QTabWidget *parent, string text)
		: TabPanel(parent,text)  {
    // Set panel tag
	panelTag = "TabSearch";
    
    // Draw GUI components
    draw();
    
    // Access configuration
	conf = new Config("digiplay", this);

    // Create library search engine.
    library_engine = new DpsMusicSearch();
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
    
	// Check if user has entered required information
    if (txtLibrarySearchText->text() == "") {
        dlgWarn *warning = new dlgWarn(getPanel(), "");
        warning->setTitle("Oops!");
        warning->setWarning(
                "You seem to have forgotten to enter something to search for.");
        warning->setQuestion(false);
        warning->exec();
        delete warning;
		btnLibrarySearch->setEnabled(true);
		txtLibrarySearchText->setEnabled(true);
		searching = false;
        return;
    }
    if ( ! (TitleCheckBox->isChecked()
                ||ArtistCheckBox->isChecked()
                ||AlbumCheckBox->isChecked() )) {
        dlgWarn *warning = new dlgWarn(getPanel(), "");
        warning->setTitle("Oops!");
        warning->setWarning(
                "Please select at least one of Title, Artist, Album.");
        warning->setQuestion(false);
        warning->exec();
        delete warning;
		btnLibrarySearch->setEnabled(true);
		txtLibrarySearchText->setEnabled(true);
		searching = false;
        return;
    }
    
    // Clear the results list
    lstSearchResults->clear();
    
    // Display a "searching..." notice
	new QListViewItem( lstSearchResults,
							lstSearchResults->lastItem(), "Searching.......");
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
	SearchResults = library_engine->query(txtLibrarySearchText->text());
	// Display results
	processResults();
}    

void TabPanelSearch::processResults() {
	// Lock GUI while updating
	qApp->lock();

	// Clear the list and enter search results (disable updates until done)
	lstSearchResults->setUpdatesEnabled(false);
	lstSearchResults->clear();

    // Display information message if nothing found
	if (SearchResults.size() == 0) {
		new QListViewItem( lstSearchResults, lstSearchResults->lastItem(),
							"(Sorry, no matches found.)");

		btnLibrarySearch->setEnabled(true);
		txtLibrarySearchText->setEnabled(true);
		lstSearchResults->setUpdatesEnabled(true);
		lstSearchResults->triggerUpdate();
		qApp->unlock();
		
		searching = false;
		return;
	}
	
    lstSearchResults->setEnabled(true);
	QListViewItem *x;
	for (unsigned int i = 0; i < SearchResults.size(); i++) {
		x = new QListViewItem(  lstSearchResults, lstSearchResults->lastItem(),
			SearchResults.at(i).title,
			SearchResults.at(i).artists.at(0),
			SearchResults.at(i).album,
			SearchResults.at(i).id 
                         );
		if (SearchResults.at(i).censor) {
			x->setPixmap(0,*pixCensored);
		} else {
			x->setPixmap(0,*pixAudio);
		}
	}

	btnLibrarySearch->setEnabled(true);
	txtLibrarySearchText->setEnabled(true);
	lstSearchResults->setUpdatesEnabled(true);
	lstSearchResults->triggerUpdate();
	txtLibrarySearchText->setFocus();
	qApp->unlock();
	
	searching = false;
}


/**
 * Emits a signal indicating which item is selected.
 */
void TabPanelSearch::playlistAdd(QListViewItem* x) {
	if (x) {
        emit itemSelected( x->text(3) );
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


    lblSearch = new QLabel( getPanel(), "lblSearch" );
    lblSearch->setGeometry( QRect( 28, 10, 60, 20 ) );
    QFont lblSearch_font(  lblSearch->font() );
    lblSearch_font.setPointSize( 12 );
    lblSearch_font.setBold( FALSE );
    lblSearch->setFont( lblSearch_font );

    Searchlable = new QLabel( getPanel(), "Searchlable" );
    Searchlable->setGeometry( QRect( 10, 33, 67, 20 ) );
    QFont Searchlable_font(  Searchlable->font() );
    Searchlable_font.setPointSize( 12 );
    Searchlable_font.setBold( FALSE );
    Searchlable->setFont( Searchlable_font );

    txtLibrarySearchText = new QLineEdit( getPanel(), "txtLibrarySearchText" );
    txtLibrarySearchText->setGeometry( QRect( 83, 10, 330, 20 ) );

    ArtistCheckBox = new QCheckBox( getPanel(), "ArtistCheckBox" );
    ArtistCheckBox->setGeometry( QRect( 83, 35, 70, 20 ) );
    QFont ArtistCheckBox_font(  ArtistCheckBox->font() );
    ArtistCheckBox_font.setBold( FALSE );
    ArtistCheckBox->setFont( ArtistCheckBox_font );
    ArtistCheckBox->setChecked( TRUE );

    TitleCheckBox = new QCheckBox( getPanel(), "TitleCheckBox" );
    TitleCheckBox->setGeometry( QRect( 190, 35, 60, 20 ) );
    QFont TitleCheckBox_font(  TitleCheckBox->font() );
    TitleCheckBox_font.setBold( FALSE );
    TitleCheckBox->setFont( TitleCheckBox_font );
    TitleCheckBox->setChecked( TRUE );

    AlbumCheckBox = new QCheckBox( getPanel(), "AlbumCheckBox" );
    AlbumCheckBox->setGeometry( QRect( 290, 35, 91, 20 ) );
    QFont AlbumCheckBox_font(  AlbumCheckBox->font() );
    AlbumCheckBox_font.setBold( FALSE );
    AlbumCheckBox->setFont( AlbumCheckBox_font );
    AlbumCheckBox->setChecked( TRUE );

    btnLibrarySearch = new QPushButton( getPanel(), "btnLibrarySearch" );
    btnLibrarySearch->setGeometry( QRect( 421, 10, 80, 20 ) );
    btnLibrarySearch->setPaletteForegroundColor( QColor( 0, 0, 0 ) );

    QFont btnLibrarySearch_font(  btnLibrarySearch->font() );
    btnLibrarySearch_font.setPointSize( 12 );
    btnLibrarySearch_font.setBold( FALSE );
    btnLibrarySearch->setFont( btnLibrarySearch_font );
    btnLibrarySearch->setAutoDefault( FALSE );

    lstSearchResults = new QListView(getPanel(), "lstSearchResults" );
    lstSearchResults->setGeometry( QRect( 10, 60, 510, 570 ) );
    lstSearchResults->setVScrollBarMode( QListView::AlwaysOn );
    lstSearchResults->setAllColumnsShowFocus( TRUE );
    lstSearchResults->setColumnWidthMode(3, QListView::Manual);
    lstSearchResults->setColumnWidth(3, 0);
    lstSearchResults->header()->setMovingEnabled( FALSE );
    lstSearchResults->addColumn( tr( "Title" ) );
    lstSearchResults->header()->setResizeEnabled( FALSE,
            lstSearchResults->header()->count() -1);
    lstSearchResults->addColumn( tr( "Artist" ) );
    lstSearchResults->header()->setResizeEnabled( FALSE,
            lstSearchResults->header()->count() -1);
    lstSearchResults->addColumn( tr( "Album" ) );
    lstSearchResults->header()->setResizeEnabled( FALSE,
            lstSearchResults->header()->count() -1);
    lstSearchResults->addColumn( tr( "ID" ) );
    lstSearchResults->header()->setResizeEnabled( FALSE,
            lstSearchResults->header()->count() -1);
    lstSearchResults->setColumnWidthMode(0, QListView::Manual);
    lstSearchResults->setColumnWidthMode(1, QListView::Manual);
    lstSearchResults->setColumnWidthMode(2, QListView::Manual);
    lstSearchResults->setColumnWidthMode(3, QListView::Manual);
    lstSearchResults->setColumnWidth(0, 200);
    lstSearchResults->setColumnWidth(1, 200);
    lstSearchResults->setColumnWidth(2, 90);
    lstSearchResults->setColumnWidth(3, 0);
    lstSearchResults->header()->setMovingEnabled( FALSE );
    lstSearchResults->setSorting(0,TRUE);

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
