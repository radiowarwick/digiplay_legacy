#include <iostream>
#include <sstream>
using namespace std;
#include <qmutex.h>
#include <qstring.h>
#include <qthread.h>
#include <qapplication.h>

#include "audioplayer.h"
#include "audiomixer.h"
#include "track.h"

#define STATE_EJECT -1
#define STATE_STOP 0
#define STATE_PLAY 1
#define STATE_PAUSE 2
#define TIME_MODE_ELAPSED 0
#define TIME_MODE_REMAIN 1

class playerThread : public QThread {
public:
	playerThread(QWidget *o, int id) : receiver(o), stopped(FALSE), player_id(id), state(0), time_mode(0) {;}
	void run();
	void stop();
	int getState();
	void setTimeMode(int mode) { time_mode = mode; do_updateCounter(position);}
	void do_load(QString *md5_hash, long int start, long int end);
	void do_play();
	void do_stop();
	void do_pause();
	void do_resume();
	void do_seek(long position);
	void do_updateCounter(int smpl);
	static void callback_counter(long smpl, void *obj);
	
private:
	QWidget *receiver;
	QMutex stopped_mutex;
	QMutex state_mutex;
	QMutex position_mutex;
	bool stopped;
	int player_id;
	string md5;
	audioplayer *player;
	audiomixer *mixer;
	audiochannel *ch;
	
	int state;
	int time_mode;
	long length;
	long position;
};
