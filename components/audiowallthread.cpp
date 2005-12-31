#include "audiowallthread.h"

// START General Thread Stop-Start ============================================
void audiowallthread::run() {
	stringstream S;
	S << "channel_" << player_id;
	mixer = new audiomixer();
	player = new audioplayer(S.str());
	player->attachMixer(mixer);
	
	state_mutex.lock();
	state = STATE_STOP;
	active_ch = -1;
	state_mutex.unlock();

	e_data = new eventData;
	e_data->id = player_id;
	
	while (!stopped)
		sleep(1000);
}

void audiowallthread::stop() {
	stopped_mutex.lock();
	stopped = TRUE;
	stopped_mutex.unlock();
}

// START Playback control functions ===========================================
void audiowallthread::do_load(QString *md5_hash,long int start,long int end) {
	string md5 = md5_hash->ascii();
	long int length = end - start;
	mixer->createChannel();
	audiochannel *ch = mixer->channel(mixer->size() - 1);
	ch->setVolume(100);
	ch->addCounter(audiowallthread::callback_counter, (void*)this);
	ch->autoReload(true);
	ch->load(md5,start,end);
	
	do_updateCounter(0);
	e_data->t = EVENT_TYPE_MAX_SMPL;
	e_data->smpl = length;
	e_data->index = mixer->size() - 1;
	QCustomEvent *e = new QCustomEvent(QEvent::Type(20001),e_data);
	QApplication::postEvent(receiver, e);
}

void audiowallthread::do_play(short index) {
	state_mutex.lock();
	if (state == STATE_STOP) {
		state = STATE_PLAY;
		active_ch = index;
		mixer->channel(index)->play();
		cout << "Channel now playing" << endl;
	}
	else cout << "audiowallthread: A channel is still playing!" << endl;
	state_mutex.unlock();
}

void audiowallthread::do_stop(short index) {
	cout << "do_stop on index " << index << endl;
	state_mutex.lock();
	if (state == STATE_PLAY || state == STATE_PAUSE) {
		state = STATE_STOP;
		active_ch = -1;
		state_mutex.unlock();
		mixer->channel(index)->stop();
		e_data->t = EVENT_TYPE_STOP;
		QCustomEvent *e = new QCustomEvent(QEvent::Type(20001),e_data);
		QApplication::postEvent(receiver, e);
	}
	else {
		state_mutex.unlock();
	}	
}

void audiowallthread::do_updateCounter(int smpl) {
	if (active_ch < 0) return;
	
	stringstream S; 
	int min, sec, mil; 
	
	state_mutex.lock();
	// time_mode is always the time remaining
	mil = (int)((mixer->channel(active_ch)->getLength() - smpl)/441);
	if (smpl == 0) {
		cout << "End of audio" << endl;
//		mixer->channel(active_ch)->notify_cache();
		eventData *e_stop = new eventData;
		e_stop->t = EVENT_TYPE_STOP;
		e_stop->index = active_ch;
		QCustomEvent *e = new QCustomEvent(QEvent::Type(20001),e_stop);
		state = STATE_STOP;
		active_ch = -1;
		QApplication::postEvent(receiver, e);
		state_mutex.unlock();
		return;
	}
	state_mutex.unlock();

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
	e_data->t = EVENT_TYPE_SMPL;
	e_data->smpl = mixer->channel(active_ch)->getLength() - smpl;
	e_data->index = active_ch;
	QCustomEvent *e = new QCustomEvent(QEvent::Type(20001),e_data);
	QApplication::postEvent(receiver, e);
}

int audiowallthread::get_state() {
	return state;
}

void audiowallthread::callback_counter(long ms, void *obj) {
	audiowallthread *me = (audiowallthread *)obj;
	me->do_updateCounter(ms);
}
