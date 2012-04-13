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
#include <QtGui/QStandardItemModel>
#include <QtGui/QTableView>
#include <QtCore/QString>
#include <QtGui/QIcon>
#include <QtGui/QIconSet>
#include <QtGui/QHeaderView>
#include <QtGui/QApplication>
#include <QtCore/QObject>
#include <QtGui/QPushButton>
#include <QtGui/QCheckBox>
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

	TabPanel::setIcon(QIcon(":/icons/search16.png"));

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

	lstSearchResults->setEnabled(false);

    // Display a "searching..." notice
    modSearch->removeRows(0,modSearch->rowCount());
    modSearch->setRowCount(1);
    modSearch->setItem(0,0,new QStandardItem(QString("Searching... Please wait.")));

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
	    SearchCompleteEvent *e = new SearchCompleteEvent((enum QEvent::Type)20000);
	    QApplication::postEvent(this, dynamic_cast<QEvent*>(e));
    }
    catch ( DpsMusicSearch::Error &s ) {
        SearchErrorEvent *e = new SearchErrorEvent((enum QEvent::Type)20001, s);
        QApplication::postEvent(this, dynamic_cast<QEvent*>(e));
    }
}

void TabPanelSearch::customEvent(QEvent *e)
{
    switch (e->type()) {
        case 20000: { // Search successful
            processResults();
            break;
        }
        case 20001: { // Search failed
            DpsMusicSearch::Error s = dynamic_cast<SearchErrorEvent*>(e)->getError();
            dlgWarn *warning = new dlgWarn(getPanel(), 0);
            warning->setTitle("Oops!");
            warning->setWarning(QString::fromStdString(s.getMessage()));
            warning->setQuestion(false);
            warning->exec();
            delete warning;
            btnLibrarySearch->setEnabled(true);
            txtLibrarySearchText->setEnabled(true);
            TitleCheckBox->setEnabled(true);
            ArtistCheckBox->setEnabled(true);
            AlbumCheckBox->setEnabled(true);
            searching = false;
            break;
        }
        default: {
            cout << "Unknown event type" << endl;
        }
    }
}

void TabPanelSearch::processResults() {
    QStandardItem *new_item;

    // Display information message if nothing found
	if (SearchResults.size() == 0) {
	    modSearch->removeRows(0,modSearch->rowCount());
	    modSearch->setRowCount(1);
	    new_item = new QStandardItem(QString("(Sorry, no matches found.)"));
	    modSearch->setItem(0,0,new_item);
	    modSearch->setItem(0,1,new QStandardItem(QString("")));
	    modSearch->setItem(0,2,new QStandardItem(QString("")));

		btnLibrarySearch->setEnabled(true);
		txtLibrarySearchText->setEnabled(true);
		TitleCheckBox->setEnabled(true);
		ArtistCheckBox->setEnabled(true);
		AlbumCheckBox->setEnabled(true);

		searching = false;
		return;
	}

    lstSearchResults->setEnabled(true);
    modSearch->removeRows(0,modSearch->rowCount());
    modSearch->setRowCount(SearchResults.size());
	for (unsigned int i = 0; i < SearchResults.size(); i++) {
	    modSearch->setItem(i,0,new QStandardItem(QString::fromAscii(SearchResults[i]["title"].c_str())));
	    modSearch->setItem(i,1,new QStandardItem(QString::fromAscii(SearchResults[i]["artist"].c_str())));
	    modSearch->setItem(i,2,new QStandardItem(QString::fromAscii(SearchResults[i]["album"].c_str())));
	    modSearch->setItem(i,3,new QStandardItem(QString::fromAscii(SearchResults[i]["id"].c_str())));
	    modSearch->item(i,0)->setIcon(*icnAudio);
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
	txtLibrarySearchText->setFocus();

	searching = false;
}


/**
 * Emits a signal indicating which item is selected.
 */
void TabPanelSearch::playlistAdd(const QModelIndex& x) {
    QString vIdx = modSearch->item(x.row(),3)->text();
	DpsAudioItem vAudio(vIdx.toLong());
    emit audioSelected( vAudio );
}


/**
 * Draw GUI components
 */
void TabPanelSearch::draw() {
    // Load icons for display
    path = DPSDIR;
    icnAudio = new QIcon(":/icons/music16.png");
    icnCensored = new QIcon(":/icons/censoredmusic16.png");

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
    txtLibrarySearchText->setGeometry( QRect( 83, 8, 330, 25 ) );

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

    QFont btnLibrarySearch_font(  btnLibrarySearch->font() );
    btnLibrarySearch_font.setPointSize( 10 );
    btnLibrarySearch_font.setBold( FALSE );
    btnLibrarySearch->setFont( btnLibrarySearch_font );
    btnLibrarySearch->setAutoDefault( FALSE );

    modSearch = new QStandardItemModel(0,4);
    modSearch->setHeaderData(0, Qt::Horizontal, tr("Title"));
    modSearch->setHeaderData(1, Qt::Horizontal, tr("Artist"));
    modSearch->setHeaderData(2, Qt::Horizontal, tr("Album"));
    modSearch->setHeaderData(3, Qt::Horizontal, tr("ID"));

    lstSearchResults = new QTableView( getPanel() );
    lstSearchResults->setModel(modSearch);
    lstSearchResults->setGeometry( QRect( 10, 60, 510, 570 ) );
    lstSearchResults->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    lstSearchResults->setSelectionBehavior(QTableView::SelectRows);
    lstSearchResults->setSelectionMode(QTableView::SingleSelection);
    lstSearchResults->setAlternatingRowColors(true);
    lstSearchResults->setShowGrid(false);
    lstSearchResults->setColumnHidden(3, true);
    lstSearchResults->setColumnWidth(0, 200);
    lstSearchResults->setColumnWidth(1, 200);
    lstSearchResults->setColumnWidth(2, 200);
    lstSearchResults->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    lstSearchResults->verticalHeader()->hide();
    lstSearchResults->verticalHeader()->setDefaultSectionSize(20);
    lstSearchResults->setEditTriggers(QTableView::NoEditTriggers);
    lstSearchResults->sortByColumn(0);

    lblSearch->setText( tr( "Search:" ) );
    TitleCheckBox->setText( tr( "Title" ) );
    AlbumCheckBox->setText( tr( "Album" ) );
    Searchlable->setText( tr( "Search by:" ) );
    ArtistCheckBox->setText( tr( "Artist" ) );
    btnLibrarySearch->setText( tr( "Search" ) );

    connect( btnLibrarySearch, SIGNAL( clicked() ),
                this, SLOT( Library_Search() ) );
    connect( lstSearchResults, SIGNAL( doubleClicked(const QModelIndex&) ),
                this, SLOT( playlistAdd(const QModelIndex&) ) );
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
