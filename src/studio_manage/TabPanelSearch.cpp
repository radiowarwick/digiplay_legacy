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

#include "Auth.h"
#include "Logger.h"

#include "TabPanelSearch.h"

TabPanelSearch::TabPanelSearch(QTabWidget *parent, frmStudioManage *parent2, string text)
		: TabPanel(parent,text)  {
	panelTag = "TabSearch";
	parentForm = parent2;
	config *conf = new config("digiplay");
	C = new Connection(conf->getDBConnectString());
	delete conf;
	draw();
}

// clean up stuff
TabPanelSearch::~TabPanelSearch() {
	if (C && C->is_open()) {
		C->Deactivate();
	}
	delete C;
}

// This handles drawing the contents of the form, and connecting slots,
// but has little actual implementation
void TabPanelSearch::draw() {
	char* routine = "TabSearch::draw()";

    SearchResults = 0;

    library_engine = new libsearch();
    lblSearch = new QLabel( getPanel(), "lblSearch" );
    lblSearch->setGeometry( QRect( 28, 10, 60, 20 ) );
    QFont lblSearch_font(  lblSearch->font() );
    lblSearch_font.setPointSize( 12 );
    lblSearch_font.setBold( FALSE );
    lblSearch->setFont( lblSearch_font );

    TitleCheckBox = new QCheckBox( getPanel(), "TitleCheckBox" );
//    TitleCheckBox->setGeometry( QRect( 83, 35, 60, 20 ) );
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

    Searchlable = new QLabel( getPanel(), "Searchlable" );
    Searchlable->setGeometry( QRect( 10, 33, 67, 20 ) );
    QFont Searchlable_font(  Searchlable->font() );
    Searchlable_font.setPointSize( 12 );
    Searchlable_font.setBold( FALSE );
    Searchlable->setFont( Searchlable_font );

    ArtistCheckBox = new QCheckBox( getPanel(), "ArtistCheckBox" );
//    ArtistCheckBox->setGeometry( QRect( 190, 35, 70, 20 ) );
    ArtistCheckBox->setGeometry( QRect( 83, 35, 70, 20 ) );
    QFont ArtistCheckBox_font(  ArtistCheckBox->font() );
    ArtistCheckBox_font.setBold( FALSE );
    ArtistCheckBox->setFont( ArtistCheckBox_font );
    ArtistCheckBox->setChecked( TRUE );

    btnLibrarySearch = new QPushButton( getPanel(), "btnLibrarySearch" );
    btnLibrarySearch->setGeometry( QRect( 421, 10, 80, 20 ) );
    btnLibrarySearch->setPaletteForegroundColor( QColor( 0, 0, 0 ) );

    QFont btnLibrarySearch_font(  btnLibrarySearch->font() );
    btnLibrarySearch_font.setPointSize( 12 );
    btnLibrarySearch_font.setBold( FALSE );
    btnLibrarySearch->setFont( btnLibrarySearch_font );
    btnLibrarySearch->setAutoDefault( FALSE );

    txtLibrarySearchText = new QLineEdit( getPanel(), "txtLibrarySearchText" );
    txtLibrarySearchText->setGeometry( QRect( 83, 10, 330, 20 ) );

    tblLibrarySearchResults = new QTable( getPanel(), "tblLibrarySearchResults" );
    tblLibrarySearchResults->setNumCols( tblLibrarySearchResults->numCols() + 1 );
    tblLibrarySearchResults->horizontalHeader()->setLabel(
	tblLibrarySearchResults->numCols() - 1, tr( "Artist          " ) );
    tblLibrarySearchResults->setNumCols( tblLibrarySearchResults->numCols() + 1 );
    tblLibrarySearchResults->horizontalHeader()->setLabel(
	tblLibrarySearchResults->numCols() - 1, tr( "Title          " ) );
    tblLibrarySearchResults->setNumCols( tblLibrarySearchResults->numCols() + 1 );
    tblLibrarySearchResults->horizontalHeader()->setLabel(
	tblLibrarySearchResults->numCols() - 1, tr( "Album          " ) );
    tblLibrarySearchResults->setNumCols( tblLibrarySearchResults->numCols() + 1 );
    tblLibrarySearchResults->horizontalHeader()->setLabel(
	tblLibrarySearchResults->numCols() - 1, tr( "ID" ) );
    tblLibrarySearchResults->setGeometry( QRect( 10, 57, 490, 573 ) );
    tblLibrarySearchResults->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0,
	(QSizePolicy::SizeType)0, 0, 0,
	tblLibrarySearchResults->sizePolicy().hasHeightForWidth() ) );
    tblLibrarySearchResults->setPaletteForegroundColor( QColor( 0, 0, 0 ) );
    tblLibrarySearchResults->setColumnWidth(3,0);

    lblSearch->setText( tr( "Search:" ) );
    TitleCheckBox->setText( tr( "Title" ) );
    AlbumCheckBox->setText( tr( "Album" ) );
    Searchlable->setText( tr( "Search by:" ) );
    ArtistCheckBox->setText( tr( "Artist" ) );
    btnLibrarySearch->setText( tr( "Search" ) );
    tblLibrarySearchResults->horizontalHeader()->setLabel( 0, tr( "Artist          " ) );
    tblLibrarySearchResults->horizontalHeader()->setLabel( 1, tr( "Title          " ) );
    tblLibrarySearchResults->horizontalHeader()->setLabel( 2, tr( "Album          " ) );
    tblLibrarySearchResults->horizontalHeader()->setLabel( 3, tr( "ID" ) );
    QToolTip::add( tblLibrarySearchResults, tr( "Library Search Engine", "Enter text to search for and click the Search button to display matches." ) );


    connect( btnLibrarySearch, SIGNAL( clicked() ), this, SLOT( Library_Search() ) );
    connect( tblLibrarySearchResults, SIGNAL( doubleClicked(int,int,int,const QPoint&) ), this, SLOT( playlistAdd(int,int,int,const QPoint&) ) );
    connect( txtLibrarySearchText, SIGNAL( returnPressed() ), this, SLOT( Library_Search() ) );


}

void TabPanelSearch::Library_Search() {
	library_engine->searchLimit(200);
	library_engine->searchTitle(TitleCheckBox->isChecked());
	library_engine->searchArtist(ArtistCheckBox->isChecked());
	library_engine->searchAlbum(AlbumCheckBox->isChecked());
	delete SearchResults;
	SearchResults = library_engine->query(txtLibrarySearchText->text());
        
	tblLibrarySearchResults->setNumRows(SearchResults->size());
	for (unsigned int i = 0; i < SearchResults->size(); i++) {
		tblLibrarySearchResults->setItem(i,0,
		        new QTableItem( tblLibrarySearchResults, QTableItem::Never,
								SearchResults->at(i).artist));
        	tblLibrarySearchResults->setItem(i,1,
				new QTableItem( tblLibrarySearchResults, QTableItem::Never,
								SearchResults->at(i).title));
	        tblLibrarySearchResults->setItem(i,2,
			    new QTableItem( tblLibrarySearchResults, QTableItem::Never,
								SearchResults->at(i).album));
        	tblLibrarySearchResults->setItem(i,3,
				new QTableItem( tblLibrarySearchResults, QTableItem::Never,
								SearchResults->at(i).md5));
	}
    tblLibrarySearchResults->adjustColumn(0);
    tblLibrarySearchResults->adjustColumn(1);
    tblLibrarySearchResults->adjustColumn(2);
    tblLibrarySearchResults->setColumnWidth(3,0); 
}

void TabPanelSearch::playlistAdd(int row, int col, int button, const QPoint& mousepos) {
	if (mousepos.isNull()) {button = 0; row = 0; col = 0;}
	if (row != -1) {
		parentForm->playlistAdd(SearchResults->at(row).md5);
	}
}

void TabPanelSearch::clear() {
	delete btnLibrarySearch;
	delete tblLibrarySearchResults;
	delete txtLibrarySearchText;
	delete Searchlable;
	delete ArtistCheckBox;
	delete AlbumCheckBox;
	delete TitleCheckBox;
	delete lblSearch;
	delete library_engine;
}
