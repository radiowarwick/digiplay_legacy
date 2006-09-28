#include "audiowallthread.h"

// START General Thread Stop-Start ============================================
void audiowallthread::run() {
    EVENT_ID = 20000 + player_id;
    e_smpl = new eventData;
    e_stop = new eventData;
	e_play = new eventData;
    e_smpl->id = player_id;
    e_smpl->t = EVENT_TYPE_SMPL;
    e_stop->t = EVENT_TYPE_STOP;
	e_play->t = EVENT_TYPE_PLAY;
	stringstream S;
	S << "channel_" << player_id;
	mixer = new audiomixer();
	player = new audioplayer(S.str());
	player->attachMixer(mixer);
	
	state_mutex.lock();
	state = STATE_STOP;
	active_ch = 0;
	state_mutex.unlock();

	while (!stopped)
		sleep(1000);
}

void audiowallthread::stop() {
	stopped_mutex.lock();
	stopped = TRUE;
	stopped_mutex.unlock();
	delete e_smpl;
	delete e_stop;
	delete e_play;
	delete player;
	delete mixer; 
}

// START Playback control functions ===========================================
void audiowallthread::do_load(QString *md5_hash,long int start,long int end) {
	string md5 = md5_hash->ascii();
	audiochannel *ch = mixer->createChannel();
	if (ch) cout << "YES!" << endl;
	ch->setVolume(100);
	ch->addCounter(audiowallthread::callback_counter, (void*)this);
	ch->autoReload(true);
	if (md5 == "") return;
	ch->load(md5,start,end);
	do_updateCounter(0);
}

void audiowallthread::do_play(unsigned short index) {
	do_stop(active_ch);
	
	state_mutex.lock();
	state = STATE_PLAY;
	active_ch = index;
	mixer->channel(index)->play();
	e_play->index = index;
	QCustomEvent *e = new QCustomEvent(QEvent::Type(EVENT_ID),e_play);
	QApplication::postEvent(receiver,e);
	state_mutex.unlock();
}

void audiowallthread::do_stop(unsigned short index) {

//	if (index == -1) return;
	state_mutex.lock();
	if (state == STATE_PLAY || state == STATE_PAUSE) {
		state = STATE_STOP;
		active_ch = -1;
		state_mutex.unlock();
		mixer->channel(index)->stop();
		e_stop->index = index;
		QCustomEvent *e = new QCustomEvent(QEvent::Type(EVENT_ID),e_stop);
		QApplication::postEvent(receiver, e);
	}
	else {
		state_mutex.unlock();
	}	
}

void audiowallthread::do_updateCounter(int smpl) {
	if (active_ch < 0) return;
	
	state_mutex.lock();
	if (smpl == 0) {
		e_stop->index = active_ch;
		state = STATE_STOP;
		active_ch = -1;	
		QCustomEvent *e = new QCustomEvent(QEvent::Type(EVENT_ID),e_stop);
		QApplication::postEvent(receiver, e);
		state_mutex.unlock();
		return;
	}
	e_smpl->smpl = mixer->channel(active_ch)->getLength() - smpl;
	e_smpl->index = active_ch;
	QCustomEvent *e = new QCustomEvent(QEvent::Type(EVENT_ID),e_smpl);
	QApplication::postEvent(receiver, e);
	state_mutex.unlock();
}

int audiowallthread::get_state() {
	return state;
}

void audiowallthread::callback_counter(long ms, void *obj) {
	audiowallthread *me = (audiowallthread *)obj;
	me->do_updateCounter(ms);
}
