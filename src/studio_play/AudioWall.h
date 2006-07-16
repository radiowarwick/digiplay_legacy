#ifndef CLASS_AUDIO_WALL
#define CLASS_AUDIO_WALL

#include <vector>
using namespace std;

#include <qwidget.h>

class QGroupBox;
class QPushButton;
class QLabel;

class AudioWallManager;

class AudioWall : public QWidget {
	Q_OBJECT
	public:
		AudioWall(QWidget *parent, const char* name);
		void resizeEvent (QResizeEvent *e);
		void setManager(AudioWallManager *manager);

	public slots:
		void play(int index);

	private slots:
		void play();
	
	private:
		void drawCreate();
		void drawResize();
		void clean();

		QGroupBox *grpFrame;
		QPushButton *btnPageNext;
		QPushButton *btnPagePrev;
		QLabel *lblPageNum;
		vector<QPushButton*> btnAudio;
};

#endif
