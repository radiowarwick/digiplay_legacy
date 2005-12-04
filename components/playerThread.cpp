#include "playerThread.h"

// START General Thread Stop-Start ============================================
void playerThread::run() {
	stringstream S;
	S << "channel_" << player_id;
	mixer = new audiomixer();
	mixer->createChannel();
	ch = mixer->channel(0);
	ch->setVolume(100);
	ch->addCounter(playerThread::callback_counter, (void*)this);
	ch->autoReload(true);
	player = new audioplayer(S.str());
	player->attachMixer(mixer);
	state_mutex.lock();
	state = STATE_EJECT;
	state_mutex.unlock();
	while (!stopped)
		sleep(1000);
}

void playerThread::stop() {
	stopped_mutex.lock();
	stopped = TRUE;
	stopped_mutex.unlock();
}

// START Playback control functions ===========================================
void playerThread::do_load(QString *md5_hash,long int start,long int end) {
	md5 = md5_hash->ascii();
	ch->load(md5,start,end);
	state_mutex.lock();
	state = STATE_STOP;
	state_mutex.unlock();
	length = end - start;
	do_updateCounter(0);
	QCustomEvent *sliderEvent = new QCustomEvent(20002 + 10*player_id);
	sliderEvent->setData(&length);
	QApplication::postEvent(receiver, sliderEvent);
}

void playerThread::do_play() {
	state_mutex.lock();
	if (state == STATE_STOP) {
		state = STATE_PLAY;
		ch->play();
	}
	else cout << "playerThread: Can't 'play' when not 'stopped'!" << endl;
	state_mutex.unlock();
}

void playerThread::do_stop() {
	state_mutex.lock();
	if (state == STATE_PLAY || state == STATE_PAUSE) {
		state = STATE_STOP;
		state_mutex.unlock();
		ch->stop();
		QCustomEvent *stopEvent = new QCustomEvent(20003 + 10*player_id);
		QApplication::postEvent(receiver, stopEvent);
	}
	else {
		state_mutex.unlock();
		cout << "playerThread: Can't 'stop' when not 'playing'!" << endl;
	}	
}

void playerThread::do_pause() {
	state_mutex.lock();
	if (state == STATE_PLAY) {
		state = STATE_PAUSE;
		state_mutex.unlock();
		ch->pause();
	}
	else {
		cout << "playerThread: Can't pause when not playing!" << endl;
		state_mutex.unlock();
	}
}

void playerThread::do_resume() {
	state_mutex.lock();
	if (state == STATE_PAUSE) {
		state = STATE_PLAY;
		state_mutex.unlock();
		ch->resume();
	}
	else {
		cout << "playerThread: Can't resume when not paused!" << endl;
		state_mutex.unlock();
	}
}

void playerThread::do_seek(long position) {
	if (state == STATE_PAUSE || state == STATE_STOP) {
		ch->seek(position);
	}
	else cout << "playerThread: Can't seek when not stopped or paused!" << endl;
}

void playerThread::do_updateCounter(int smpl) {
	position_mutex.lock();
	position = smpl;
	position_mutex.unlock();
	if (smpl == 0) {
		QCustomEvent *stopEvent = new QCustomEvent(20003 + 10*player_id);
		QApplication::postEvent(receiver, stopEvent);
		state_mutex.lock();
		state = STATE_STOP;
		state_mutex.unlock();
	}
	
	stringstream S; 
	int min, sec, mil; 
	
	if (time_mode == TIME_MODE_REMAIN) {
		mil = (int)((length - smpl)/441);
	}
	else {
		mil = (int)(smpl/441);
	}
	sec = (int)(mil / 100);
	mil = mil%100;
	min = (int)(sec / 60);
	sec = sec%60;
	if (min < 10) S << "0";
	S << min << ":";
	if (sec < 10) S << "0";
	S << sec << ".";
	if (mil < 10) S << "0";
	S << mil << "";
	QCustomEvent *counterEvent = new QCustomEvent(20000 + 10*player_id);
	QCustomEvent *sliderEvent = new QCustomEvent(20001 + 10*player_id);
	counterEvent->setData(new QString(S.str()));
	int *s = new int;
	sliderEvent->setData(&(*s = smpl));
	QApplication::postEvent(receiver, counterEvent);
	QApplication::postEvent(receiver, sliderEvent);
}

int playerThread::getState() {
	return state;
}

void playerThread::callback_counter(long ms, void *obj) {
	playerThread *me = (playerThread *)obj;
	me->do_updateCounter(ms);
}
