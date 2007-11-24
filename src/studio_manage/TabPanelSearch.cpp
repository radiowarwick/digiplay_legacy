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

TabPanelSearch::TabPanelSearch(QTabWidget *parent, string text)
		: TabPanel(parent,text)  {
	panelTag = "TabSearch";
    path = DPSDIR;
    pixAudio = new QPixmap(path + "/images/music16.png");
    pixCensored = new QPixmap(path + "/images/censoredmusic16.png");
	conf = new Config("digiplay", this);
	
	draw();
}

// clean up stuff
TabPanelSearch::~TabPanelSearch() {
	delete conf;
}

void TabPanelSearch::onMessage() {
	
}

// This handles drawing the contents of the form, and connecting slots,
// but has little actual implementation
void TabPanelSearch::draw() {
    SearchResults = 0;

    library_engine = new DpsMusicSearch();
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
    lstSearchResults = new QListView(getPanel(), "lstSearchResults" );

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

void TabPanelSearch::Library_Search() {
    if (txtLibrarySearchText->text() == "") {
        dlgWarn *warning = new dlgWarn(getPanel(), "");
        warning->setTitle("Oops!");
        warning->setWarning(
                "You seem to have forgotten to enter something to search for.");
        warning->setQuestion(false);
        warning->exec();
        delete warning;
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
        return;
    }

    lstSearchResults->clear();
	lstSearchResults->setEnabled(false);
	library_engine->searchLimit(atoi(conf->getParam("search_limit").c_str()));
	library_engine->searchTitle(TitleCheckBox->isChecked());
	library_engine->searchArtist(ArtistCheckBox->isChecked());
	library_engine->searchAlbum(AlbumCheckBox->isChecked());
	delete SearchResults;
	SearchResults = library_engine->query(txtLibrarySearchText->text());
    
	if (SearchResults->size() == 0) {
		new QListViewItem( lstSearchResults, lstSearchResults->lastItem(),
							"(Sorry, no matches found.)");
		return;
	}
	lstSearchResults->setUpdatesEnabled(false);
	lstSearchResults->setEnabled(true);
	QListViewItem *x;
	for (unsigned int i = 0; i < SearchResults->size(); i++) {
		x = new QListViewItem(  lstSearchResults, lstSearchResults->lastItem(),
			SearchResults->at(i).title,
			SearchResults->at(i).artists.at(0),
			SearchResults->at(i).album,
			SearchResults->at(i).id 
                         );
		if (SearchResults->at(i).censor) {
			x->setPixmap(0,*pixCensored);
		} else {
			x->setPixmap(0,*pixAudio);
		}
	}
	lstSearchResults->setUpdatesEnabled(true);
	lstSearchResults->repaint();
}

void TabPanelSearch::playlistAdd(QListViewItem* x) {
	if (x) {
        emit itemSelected( x->text(3) );
	}
}

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
