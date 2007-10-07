#include "ProcessMixer.h"

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

Audio::ProcessMixer::ProcessMixer() {
	pthread_mutex_init(&channelLock,NULL);
}

Audio::ProcessMixer::~ProcessMixer() {

}

/**
 * Retrieves audio from each attached input component and mixes it together
 * according to the formula described.
 */
void Audio::ProcessMixer::getAudio(AudioPacket* buffer) {
	pthread_mutex_lock(&channelLock);
    unsigned short N = ch_active.size();
    // request audio for each channel into separate buffers
	map<PORT,MixerChannel*>::iterator x = ch_active.begin();
    while (x != ch_active.end()) {
		(*x).second->cmpt->getAudio((*x).second->data);
		x++;
    }
   
	// Short arrays used to access channel audio data
	short **chs = new short*[N];
	// Short array used to access output audio data
	short *mix = buffer->getData();
	// Get a pointer to each audio data array and store in chs
	x = ch_active.begin();
	unsigned int i = 0;
    while (x != ch_active.end()) {
        chs[i] = (*x).second->data->getData();
		x++;
		i++;
    }

    // perform mix
    short M = 32768;
    double factor;
    // process each sample in turn
    for (unsigned int k = 0; k < PACKET_SAMPLES; k++) {
        // start with zero sample
        mix[k] = 0;
        for (unsigned int i = 0; i < N; i++) {
            // Set the scale factor for each channel to unity to start with
            factor = 1.0;
            // Compute scale factor for each channel based on the amplitude
            // of the remaining channels in the mix
            for (unsigned int j = i+1; j < N; j++) {
                factor *= (1.0 - abs(double(chs[j][k])/M));
            }
            // Scale and add this channel to the mix
            mix[k] += short(chs[i][k]*factor);
        }
    }
    delete[] chs;

	x = ch_active.begin();
	while (x != ch_active.end()) {
		if ((*x).second->state == STATE_STOP) {
			PORT p = (*x).second->port;
			ch_inactive[p] = ch_active[p];
			ch_active.erase(p);
		}
		x++;
	}

	pthread_mutex_unlock(&channelLock);
}

/** 
 * Receives messages to this component after they've been preprocessed by the
 * component base class. 
 */
void Audio::ProcessMixer::receiveMessage(PORT inPort, MESSAGE message) {
	if (!channels[inPort]) {
		cout << "Channel has not been initialised!" << endl;
		exit(-1);
	}
	if (message == STOP) {
		//cout << "ProcessMixer: Stopping channel " << inPort << endl;
		channels[inPort]->state = STATE_STOP;
	}
	else if (message == PLAY) {
		//cout << "ProcessMixer: Starting channel " << inPort << endl;
		channels[inPort]->state = STATE_PLAY;
		ch_inactive.erase(inPort);
		ch_active[inPort] = channels[inPort];
	}
	if (ch_active.size() == 1 && message == PLAY) {
		//cout << "ProcessMixer: Setting mixer to play" << endl;
		send(OUT0,PLAY);
	}
	else if (ch_active.size() == 0) {
		//cout << "ProcessMixer: Setting mixer to stop" << endl;
		send(OUT0,STOP);
	}
	//cout << "Done processmixer::receive message" << endl;
}

void Audio::ProcessMixer::onConnect(PORT localPort) {
	if (localPort <= 0) return;
	//cout << "ProcessMixer: OnConnect " << localPort << endl;
	pthread_mutex_lock(&channelLock);
	MixerChannel *C = new MixerChannel;
	C->state = STATE_STOP;
	C->cmpt = connectedDevice(localPort);
	C->data = new AudioPacket(PACKET_SAMPLES);
	C->port = localPort;
	channels[localPort] = C;
	ch_inactive[localPort] = C;
	pthread_mutex_unlock(&channelLock);
}

void Audio::ProcessMixer::onDisconnect(PORT localPort) {
	if (localPort <= 0) return;
	//cout << "ProcessMixer: OnDisconnect" << endl;
	// Lock mutex to prevent access to channels while removing one
	pthread_mutex_lock(&channelLock);
	// remove links in active and inactive maps
	ch_inactive.erase(localPort);
	ch_active.erase(localPort);
	// delete the data off the heap and remove the channel
	delete channels[localPort]->data;
	delete channels[localPort];
	channels.erase(localPort);
	// unlock channels again
	pthread_mutex_unlock(&channelLock);
}

void Audio::ProcessMixer::threadExecute() {

}
