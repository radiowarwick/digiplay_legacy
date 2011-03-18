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

#ifndef CLASS_TAB_PANEL_SEARCH
#define CLASS_TAB_PANEL_SEARCH

//#include "frmStudioManage.h"
#include <QtCore/QEvent>

#include "Showplan.h"
#include "TabPanel.h"
#include "DpsMusicSearch.h"
#include "MessagingInterface.h"
#include "dlgWarn.h"

class QTabWidget;
class QPushButton;
class QStandardItemModel;
class QTableView;
class QLineEdit;
class QLabel;
class QCheckBox;
class QIcon;

class Auth;
class Config;


/**
 * TabPanel class for providing a music library search.
 */
class TabPanelSearch : 	public TabPanel,
						public MessagingInterface {
	Q_OBJECT
	public:
        /// Event class issued when search thread completes to trigger update
	    /// of display.
        class SearchCompleteEvent : public QEvent {
        public:
            SearchCompleteEvent(Type type) : QEvent(type) {}
            SearchCompleteEvent(const SearchCompleteEvent& pSrc)
                : QEvent(pSrc) {}
            virtual ~SearchCompleteEvent() {}
        };

        /// Event class issued when search thread produces an error.
        class SearchErrorEvent : public QEvent {
        public:
            SearchErrorEvent(Type type, DpsMusicSearch::Error& e)
                : QEvent(type), mError(e) {}
            SearchErrorEvent(const SearchErrorEvent& pSrc)
                : QEvent(pSrc), mError(pSrc.mError) {}
            virtual ~SearchErrorEvent() {}

            DpsMusicSearch::Error getError() {
                return mError;
            }

        private:
            DpsMusicSearch::Error mError;
        };

        /// Constructor
		TabPanelSearch(QTabWidget *parent, QString text);
        /// Destructor
		~TabPanelSearch();
        /// ???
		void onMessage();
		void customEvent(QEvent *e);
	signals:
        /// Emitted when an item is selected from the search results.
        void audioSelected( const DpsAudioItem& );

	private slots:
        /// Searches the library.
		virtual void Library_Search();
		/// Processes search results when they are ready.
		void processResults();
        /// Emits the signal indicating an item is selected.
		virtual void playlistAdd(const QModelIndex&);

	private:
        /// Draws the panel.
		void draw();
        /// Clears the panel.
		void clear();
		void threadExecute();

		bool searching;
		Config *conf;
		vector<DpsAudioItem> SearchResults;
		DpsMusicSearch* library_engine;
		QPushButton *btnLibrarySearch;
		QStandardItemModel *modSearch;
		QTableView *lstSearchResults;
		QLineEdit *txtLibrarySearchText;
		QLabel *Searchlable;
		QLabel *lblSearch;
		QCheckBox *ArtistCheckBox;
		QCheckBox *AlbumCheckBox;
		QCheckBox *TitleCheckBox;
		QString path;
		QIcon *icnAudio;
		QIcon *icnCensored;
};

#endif
