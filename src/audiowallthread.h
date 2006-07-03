#ifndef CLASS_AUDIOWALLTHREAD
#define CLASS_AUDIOWALLTHREAD

#include <iostream>
#include <sstream>
using namespace std;
#include <qmutex.h>
#include <qstring.h>
#include <qthread.h>
#include <qpushbutton.h>
#include <qapplication.h>

#include "audioplayer.h"
#include "audiomixer.h"
#include "dps.h"

#define STATE_EJECT -1
#define STATE_STOP 0
#define STATE_PLAY 1
#define STATE_PAUSE 2
#define TIME_MODE_ELAPSED 0
#define TIME_MODE_REMAIN 1

struct audioClip {
	string fn;
	QPushButton *btn;
	string text;
	long start;
	long end;
	int fg;
	int bg;
};

struct audioWall {
	audioClip clip[12];
	string name;
	string description;
};

class audiowallthread : public QThread {
	public:
		audiowallthread(QWidget *o, int id) : receiver(o), stopped(FALSE), player_id(id), state(0) {;}
		void run();
		void stop();
		void do_load(QString *md5_hash, long int start, long int end);
		void do_play(short index);
		void do_stop(short index);
		void do_updateCounter(int smpl);
		int get_state();
		short get_active_channel() {return active_ch;}
		static void callback_counter(long smpl, void *obj);
		
	private:
		QWidget *receiver;
		QMutex stopped_mutex;
		QMutex state_mutex;
		bool stopped;
		int player_id;
		audioplayer *player;
		audiomixer *mixer;

		int EVENT_ID;
		eventData *e_smpl;	
		eventData *e_stop;	
		eventData *e_play;
		int state;
		short active_ch;
};

#endif
