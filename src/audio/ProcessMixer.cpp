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
 * @param   buffer      Audio packet to fill.
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
                factor *= (1.0 - fabs(double(chs[j][k])/M));
            }
            // Scale and add this channel to the mix
			mix[k] += short(chs[i][k]*factor);
        }
    }
    delete[] chs;

	// move channels which have now become inactive
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
 * @param   inPort      Port on which a message is received.
 * @param   message     The message received.
 */
void Audio::ProcessMixer::receiveMessage(PORT inPort, MESSAGE message) {
	if (!channels[inPort]) {
		cout << "ERROR: Channel has not been initialised!" << endl;
		pthread_mutex_unlock(&channelLock);
		exit(-1);
	}
	if (message == STOP) {
		channels[inPort]->state = STATE_STOP;
	}
	else if (message == PLAY) {
		channels[inPort]->state = STATE_PLAY;
		ch_inactive.erase(inPort);
		ch_active[inPort] = channels[inPort];
	}
	if (ch_active.size() == 1 && message == PLAY) {
		send(OUT0,PLAY);
	}
	else if (ch_active.size() == 0) {
		send(OUT0,STOP);
	}
}


/**
 * Performs tasks when a component is connected.
 * When a component source is added (to an IN port), a new MixerChannel
 * is created which associates, a component pointer, component state,
 * an AudioPacket, and attached port. These MixerChannels are stored in
 * the channels map, which maps local ports to a MixerChannel. Initially
 * all channels are marked inactive.
 * \todo Set channel active if it's playing
 * @param   localPort   Port on which component is attached
 */
void Audio::ProcessMixer::onPatch(PORT localPort) {
	if (localPort <= 0) return;
    
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


/**
 * Perform tasks when a component is disconnected.
 * Deletes the associated MixerChannel and frees the associated AudioPacket.
 * @param   localPort   Port from which component is disconnected.
 */
void Audio::ProcessMixer::onUnpatch(PORT localPort) {
	if (localPort <= 0) return;

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

unsigned int Audio::ProcessMixer::activeChannels() {
    return ch_active.size();
}