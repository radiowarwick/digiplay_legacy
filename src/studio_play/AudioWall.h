#ifndef CLASS_AUDIO_WALL
#define CLASS_AUDIO_WALL

#include <vector>
using namespace std;

#include <qwidget.h>

#include "audiowallthread.h"

#define AUDIOWALL_BUTTON_OUT_OF_RANGE 12000

class QGroupBox;
class QPushButton;
class QLabel;

enum AUDIO_STATE {
	AUDIO_STATE_STOPPED,
	AUDIO_STATE_PLAYING,
	AUDIO_STATE_PAUSED
};

struct AudioWallItem {
	QString text;
	QColor bgColor;
	QColor fgColor;
	QFont font;
	QString file;
	unsigned long start;
	unsigned long end;
	enum AUDIO_STATE state;
	long pos;
};

struct AudioWallPage {
	QString title;
	QString description;
	vector<AudioWallItem> items;
};

class AudioWall : public QWidget {
	Q_OBJECT
	public:
		AudioWall(QWidget *parent, const char* name, int rows, int cols);
		~AudioWall();
		void resizeEvent (QResizeEvent *e);
		void setButton(unsigned int page, unsigned int index, 
						AudioWallItem item);
		void setCaption(unsigned int page, QString text);
		void setMultipage(bool mp);
		bool isMultipage();
		unsigned short getSize() {return _rows*_cols;}
		bool isPlaying(unsigned int index);
		void customEvent(QCustomEvent *event);

	public slots:
		void play(unsigned int index);

	private slots:
		void play();
		void nextPage();
		void prevPage();
	
	private:
		void drawCreate();
		void drawResize();
		void configureButton(unsigned int index);
		void configurePageNav();
		void clean();

		unsigned int _rows;
		unsigned int _cols;
		unsigned int _currentPage;
		unsigned int _activePage;
		vector<AudioWallPage> _pages;
		audiowallthread *_audioWall;
		
		QGroupBox *grpFrame;
		QPushButton *btnPageNext;
		QPushButton *btnPagePrev;
		QLabel *lblPageNum;
		QLabel *lblCounter;
		vector<QPushButton*> btnAudio;
};

#endif
