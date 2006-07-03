#include "playerThread.h"

// START General Thread Stop-Start ============================================
void playerThread::run() {
    EVENT_ID = 20000 + player_id;
    e_smpl = new eventData;
    e_stop = new eventData;
    e_max_smpl = new eventData;
    e_end = new eventData;
    e_smpl->id = player_id;
    e_smpl->t = EVENT_TYPE_SMPL;
    e_stop->id = player_id;
    e_stop->t = EVENT_TYPE_STOP;
	e_stop->smpl = 0;
    e_max_smpl->id = player_id;
    e_max_smpl->t = EVENT_TYPE_MAX_SMPL;
    e_end->id = player_id;
    e_end->t = EVENT_TYPE_END;

	stringstream S;
	S << "channel_" << player_id;
	mixer = new audiomixer();
	ch = mixer->createChannel();
	ch->setVolume(100);
	ch->addCounter(playerThread::callback_counter, (void*)this);
	ch->autoReload(true);
	length = 0;	
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
	delete e_smpl;
	delete e_stop;
	delete e_max_smpl;
	delete e_end;
	delete player;
	delete mixer;
}

// START Playback control functions ===========================================
void playerThread::do_load(QString *md5_hash,long int start,long int end) {
	md5 = md5_hash->ascii();
	ch->load(md5,start,end);
	state_mutex.lock();
	state = STATE_STOP;
	state_mutex.unlock();
	length = end - start;
	e_max_smpl->smpl = length;
	QCustomEvent *e = new QCustomEvent(QEvent::Type(EVENT_ID),e_max_smpl);
	QApplication::postEvent(receiver, e);
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
		QCustomEvent *e = new QCustomEvent(QEvent::Type(EVENT_ID),e_stop);
		QApplication::postEvent(receiver, e);
	}
	else {
		state_mutex.unlock();
		cout << "playerThread: Can't 'stop' when not 'playing'!" << endl;
		cout << " -> current state: " << state << endl;
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
		do_updateCounter(position);
	}
	else cout << "playerThread: Can't seek when not stopped or paused!" << endl;
}

void playerThread::do_updateCounter() {
	do_updateCounter(position);
}

void playerThread::do_updateCounter(int smpl) {
	position_mutex.lock();
	position = smpl;
	position_mutex.unlock();
	
	if (smpl == 0) {
		QCustomEvent *e = new QCustomEvent(QEvent::Type(EVENT_ID),e_stop);
		QApplication::postEvent(receiver, e);
		state_mutex.lock();
		state = STATE_STOP;
		state_mutex.unlock();
	}
	
	stringstream S; 
	if (smpl != 0 && (length - smpl)/44100 < 20) {
		QCustomEvent *e = new QCustomEvent(QEvent::Type(EVENT_ID),e_end);
		QApplication::postEvent(receiver, e);
	}
	e_smpl->smpl = position;
	QCustomEvent *e = new QCustomEvent(QEvent::Type(EVENT_ID),e_smpl);
	QApplication::postEvent(receiver, e);
}

int playerThread::getState() {
	return state;
}

void playerThread::callback_counter(long ms, void *obj) {
	playerThread *me = (playerThread *)obj;
	me->do_updateCounter(ms);
}
