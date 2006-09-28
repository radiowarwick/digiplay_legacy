#include <iostream>
using namespace std;

#include <qapplication.h>
#include <qwidget.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qlabel.h>

#include "Logger.h"

#include "AudioWall.h"

AudioWall::AudioWall(QWidget *parent, const char* name, unsigned short rows, unsigned short cols, unsigned short playerId)
		: QWidget(parent,name) {
	grpFrame = 0;
	btnPageNext = 0;
	btnPagePrev = 0;
	lblPageNum = 0;
	drawCreate();

	// default to a single empty page
	_rows = rows;
	_cols = cols;
	_pageSize = _rows * _cols;
	_currentPage = 0;
	_activePage = 0;
	_activeIndex = 0;

	_audioPlayer = new audioplayer("channel_" + dps_itoa(playerId));
	_audioMixer = new audiomixer();
	_audioPlayer->attachMixer(_audioMixer);
}

AudioWall::AudioWall(QWidget *parent, const char* name, unsigned short rows,
		unsigned short cols, AudioWall *A) : QWidget(parent, name) {
	grpFrame = 0;
	btnPageNext = 0;
	btnPagePrev = 0;
	lblPageNum = 0;
	drawCreate();

	_rows = rows;
	_cols = cols;
	_pageSize = _rows * _cols;
	_currentPage = 0;
	_activePage = 0;
	_activeIndex = 0;

	_audioMixer = A->_audioMixer;
}

AudioWall::~AudioWall() {
	clean();
}

void AudioWall::play(unsigned short page, unsigned short index) {
	cout << "AudioWall::play(short,short)" << endl;
	AudioWallItem *item = _pages[page]->items[index];
	if (item->state == AUDIO_STATE_PLAYING) {
		cout << "Doing channel stop..." << endl;
		item->ch->stop();
		cout << "Changing channel state..." << endl;
		item->state = AUDIO_STATE_STOPPED;
		if (page == _currentPage) {
			cout << "Reconfiguring button" << endl;
			configureButton(index);
		}
		cout << "NOW STOPPED" << endl;
	}
	else {
		cout << _activePage << ", " << _activeIndex << endl;
		AudioWallItem *activeItem = _pages[_activePage]->items[_activeIndex];
		if (activeItem->state == AUDIO_STATE_PLAYING) {
			cout << "FIRST WE STOP EXISTING CHANNEL";
			cout << _activePage << ", " << _activeIndex << endl;
			play(_activePage,_activeIndex);
		}
		item->state = AUDIO_STATE_PLAYING;
		_activePage = page;
		_activeIndex = index;
		item->ch->play();
		cout << "NOW PLAYING" << endl;
	}
}

void AudioWall::play(unsigned short index) {
	play(_currentPage,index);
}

void AudioWall::play() {
	cout << "AudioWall::play" << endl;
	QPushButton *sender = (QPushButton*)QObject::sender();
	string name = sender->name();
	short x = atoi(name.substr(8,name.size() - 8).c_str());
	play(_currentPage,x);
}

void AudioWall::nextPage() {
	if (_currentPage <= _pages.size()) {
		_currentPage++;
		for (unsigned short i = 0; i < _pageSize; i++) {
			configureButton(i);
		}
	}
	configurePageNav();	
}

void AudioWall::prevPage() {
	if (_currentPage > 0) {
		_currentPage--;
		for (unsigned short i = 0; i < _pageSize; i++) {
			configureButton(i);
		}
	}
	configurePageNav();
}

void AudioWall::resizeEvent (QResizeEvent *e) {
	if (e) drawResize();
}

void AudioWall::setButton(unsigned short page, unsigned short index,
							AudioWallItem newItem) {
	cout << "AudioWall::setButton" << endl;
	char *routine = "AudioWall::setButton";
	if (index > _pageSize) {
		Logger::log(ERROR,routine,"Button index out of range",1);
		throw AUDIOWALL_BUTTON_OUT_OF_RANGE;
	}
	for (unsigned short i = 0; i <= page; i++) {
		if (_pages.size() <= i) {
			cout << "Creating page " << i << endl;
			AudioWallPage *p = new AudioWallPage;
			_pages.push_back(p);
			p->index = i;
			AudioWallItem *item;
			for (unsigned short j = 0; j < _pageSize; j++) {
				item = new AudioWallItem;
				item->ch = NULL;
				item->index = j;
				item->text = "";
				item->state = AUDIO_STATE_STOPPED;
				item->pos = 0;
				item->page = p;
                if (!(item->ch)) {
                    cout << "Creating channel " << j<<endl;
                    item->ch = _audioMixer->createChannel();
                    item->ch->setVolume(100);
                    item->ch->addCounter(AudioWall::callbackCounter,
                                     (void*)(item));
                    item->ch->autoReload(true);
                }
				item->parent = this;
				p->items.push_back(item);
			}
			cout << "Finished creating page " << i << endl;
		}
	}
	cout << "Pages: " << _pages.size() << "  page: " << page;
	cout << "index: " << index << endl;
	AudioWallItem *item = _pages[page]->items[index];
	cout << "A" << endl;
	AudioWallItem olditem = *(_pages[page]->items[index]);
	cout << "B" << endl;
	*item = newItem;
	item->state = AUDIO_STATE_STOPPED;
	item->pos = item->start;
	item->ch = olditem.ch;
	item->parent = this;
	cout << "C" << endl;
	item->page = olditem.page;
	item->index = olditem.index;
	cout << "D" << endl;
	item->ch->load(item->file.ascii(), item->start, item->end);
	cout << "New item configured" << endl;
	if (page == _currentPage) {
		configureButton(index);
	}
	configurePageNav();
}

void AudioWall::setCaption(unsigned short page, QString text) {
	cout << "AudioWall::setCaption" << endl;
	if (page >= _pages.size()) return;
	_pages[page]->title = text;
}

void AudioWall::drawCreate() {
	cout << "AudioWall::drawCreate" << endl;
	clean();
	string path = qApp->applicationDirPath();

	// Create frame, and page next, previous buttons and page num label
	grpFrame = new QGroupBox( this, "grpFrame" );
	grpFrame->setTitle("No title");
	QFont f;
	f.setFamily( "Sans Serif" );
	f.setPointSize( 16 );
	f.setBold( true );
	grpFrame->setFont( f );

	btnPageNext = new QPushButton( grpFrame, "btnPageNext" );
	btnPageNext->setEnabled( false );
	btnPageNext->setPixmap(QPixmap(path + "/images/fastforward.png"));
	connect( btnPageNext, SIGNAL(pressed()), this, SLOT(nextPage()) );

	btnPagePrev = new QPushButton( grpFrame, "btnPagePrev" );
	btnPagePrev->setEnabled( false );
	btnPagePrev->setPixmap(QPixmap(path + "/images/fastbackward.png"));
	connect( btnPagePrev, SIGNAL(pressed()), this, SLOT(prevPage()) );

	lblPageNum = new QLabel( grpFrame, "lblPageNum" );
	lblPageNum->setEnabled( false );

	lblCounter = new QLabel( grpFrame, "lblCounter" );
	lblCounter->setEnabled( false );
	
	// Create the audio buttons and keep a handle to them in a vector
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			btnAudio.push_back(new QPushButton( grpFrame,
							"btnAudio" + QString::number(3*i+j) ));
			btnAudio[3*i+j]->setEnabled(false);
			connect( btnAudio[3*i+j], SIGNAL(pressed()),
						this, SLOT(play()) );
		}
	}
}

void AudioWall::drawResize() {
	cout << "AudioWall::drawResize" << endl;
	// What's our size?
	int border = 10;
	int wFrame = this->width();
	int hFrame = this->height();
	int wCell = int((wFrame - 2*border) / _cols);
	int hCell = int((hFrame - 3*border) / (_rows+1));
	if (wCell <= 0 || hCell <= 0) return;
	
	grpFrame->setGeometry( QRect( 0, 0, wFrame, hFrame ));
	btnPagePrev->setGeometry( QRect( border, 2*border + _rows*hCell, wCell, hCell ));
	lblPageNum->setGeometry( QRect( border + wCell, 2*border + _rows*hCell + hCell/2, wCell, hCell / 2 ) );
	lblPageNum->setAlignment( int( QLabel::AlignCenter ) );
	lblCounter->setGeometry( QRect( border + wCell, 2*border + _rows*hCell,wCell, hCell / 2 ) );
	lblCounter->setAlignment( int( QLabel::AlignCenter ) );
	btnPageNext->setGeometry( QRect( border + 2*wCell, 2*border + _rows*hCell, wCell, hCell ) );
	
	// Set properties for the buttons and connect them up
	QFont f = btnAudio[0]->font();
	f.setPointSize(14);
	for (unsigned int i = 0; i < _rows; i++) {
		for (unsigned int j = 0; j < _cols; j++) {
			btnAudio[i*_cols+j]->setGeometry(j*wCell+border, i*hCell+2*border, wCell, hCell);
			btnAudio[i*_cols+j]->setFont(f);
		}
	}
}

void AudioWall::configureButton(unsigned short index) {
	cout << "AudioWall::configureButton " << index << endl;
	AudioWallItem *item = _pages[_currentPage]->items[index];
	if (item->text != "") {
		switch (item->state) {
			case AUDIO_STATE_STOPPED:
				cout << "We're stopped" << endl;
				btnAudio[index]->setText(item->text);
				btnAudio[index]->setPaletteForegroundColor(item->fgColor);
				btnAudio[index]->setPaletteBackgroundColor(item->bgColor);
				btnAudio[index]->setEnabled(true);
				break;
			case AUDIO_STATE_PLAYING:
				btnAudio[index]->setText("PLAYING\n" 
											+ dps_prettyTime(item->pos));
                btnAudio[index]
					->setPaletteForegroundColor(QColor(QRgb(16776960)));
				btnAudio[index]
					->setPaletteBackgroundColor(QColor(QRgb(16711680)));
				break;
			case AUDIO_STATE_PAUSED:
				break;
		}
	}
	else {
		btnAudio[index]->setText("");
		btnAudio[index]->setPaletteForegroundColor(QColor(QRgb(0)));
		btnAudio[index]->setPaletteBackgroundColor(QColor(QRgb(12632256)));
		btnAudio[index]->setEnabled(false);
	}
}

void AudioWall::configurePageNav() {
	cout << "AudioWall::ConfigurePageNav" << endl;
	if (_currentPage == _pages.size() - 1) {
		btnPageNext->setEnabled(false);
	}
	else {
		btnPageNext->setEnabled(true);
	}
	if (_currentPage == 0) {
		btnPagePrev->setEnabled(false);
	}
	else {
		btnPagePrev->setEnabled(true);
	}
	lblPageNum->setText("Page " + QString::number(_currentPage+1) + "/"
							+ QString::number(_pages.size()));

}

void AudioWall::clean() {
	cout << "AudioWall::clean" << endl;
	delete btnPageNext;
	delete btnPagePrev;
	delete lblPageNum;
	while (btnAudio.size() > 0) {	
		delete btnAudio[0];
		btnAudio.erase(btnAudio.begin());
	}
	delete grpFrame;
}

void AudioWall::callbackCounter(long smpl, void *obj) {
//	cout << "AudioWall::callbackCounter" << endl;
	if (!obj) return;
	AudioWallItem *item = (AudioWallItem*)obj;
//	cout << "callback index: " << item->index << endl;
//	cout << "callback page index: " << item->page->index << endl;

	if (item->text == "") return;
	if (item->state == AUDIO_STATE_STOPPED) return;
	item->pos = smpl;
	
	QCustomEvent *e = new QCustomEvent(QEvent::Type(20000),obj);
	QApplication::postEvent(item->parent,e);
//	cout << " -> CALLBACK POSTED!" << endl;
}

void AudioWall::customEvent(QCustomEvent *event) {
	_mutEvent.lock();
	cout << "AudioWall::customEvent" << endl;
	if (!event) {
		cout << "NULL EVENT!" << endl;
		_mutEvent.unlock();
		return;
	}
	switch (event->type()) {
		case 20000: {
			//_mutData.lock();
			AudioWallItem *item = (AudioWallItem*)(event->data());
			if (!item) {
				cout << "NULL EVENT DATA!" << endl;
				_mutEvent.unlock();
				return;
			}

			unsigned short index = item->index;
			unsigned short page_id = item->page->index;
			
			// we update the appropriate button depending on the state
            switch (item->state) {
				case AUDIO_STATE_PLAYING:
					cout << "CUSTOM EVENT PLAYING" << endl;
					if (page_id == _currentPage) {
						configureButton(index);
					}
					lblCounter->setText(dps_prettyTime(item->pos));
					break;
				default:
					break;
			}
    	    break;
		}
		default:
			break;
	}
	cout << "END AudioWall::customEvent" << endl;
	_mutEvent.unlock();
}

void AudioWall::run() {
	_mutRunning.lock();
	_running = true;
	_mutRunning.unlock();

	while (_running) {
		sleep(1);
	}
}

void AudioWall::stop() {
	_mutRunning.lock();
	_running = false;
	_mutRunning.unlock();
}
