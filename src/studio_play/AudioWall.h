#ifndef CLASS_AUDIO_WALL
#define CLASS_AUDIO_WALL

#include <vector>
using namespace std;

#include <qobject.h>

class QWidget;
class QGroupBox;
class QPushButton;
class QLabel;

class AudioWall : public QWidget {
	QOBJECT
	public:
		AudioWall(QWidget *parent, const char* name) : QWidget(parent,name) {
			cout << "AudioWall Constructor" << endl;
			init();
		}
		void play(int index);

	public slots:
		void play();
	
	private:
		void init();
		void draw();
		void clean();

		QGroupBox *grpFrame;
		QPushButton *btnPageNext;
		QPushButton *btnPagePrev;
		QLabel *lblPageNum;
		vector<QPushButton*> btnAudio;
};

#endif
