#ifndef CLASS_AUDIO_WALL
#define CLASS_AUDIO_WALL

#include <vector>
using namespace std;

#include <qwidget.h>

#define AUDIOWALL_BUTTON_OUT_OF_RANGE 12000

class QGroupBox;
class QPushButton;
class QLabel;

struct AudioWallItem {
	QString text;
	QColor bgColor;
	QColor fgColor;
	QFont font;
	QString file;
	unsigned long start;
	unsigned long end;
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

	public slots:
		void play(int index);

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
		vector<AudioWallPage> _pages;
		
		QGroupBox *grpFrame;
		QPushButton *btnPageNext;
		QPushButton *btnPagePrev;
		QLabel *lblPageNum;
		vector<QPushButton*> btnAudio;
};

#endif
