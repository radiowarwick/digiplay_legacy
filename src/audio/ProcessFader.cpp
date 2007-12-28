#include "ProcessFader.h"
using Audio::ProcessFader;
#include <iostream>
#include <cmath>
using namespace std;

ProcessFader::ProcessFader() {
	vol = 1.0;
	pthread_mutex_init(&nodes_lock,NULL);
}

ProcessFader::~ProcessFader() {

}

void ProcessFader::getAudio(AudioPacket* audioData) {
    connectedDevice(IN0)->getAudio(audioData);
	SAMPLEVAL* mix = audioData->getData();
	SAMPLE smpl;
	map<SAMPLE,double>::iterator i_a, i_b;
	SAMPLE a,b;
	double av, bv;

	// Set up an array of pointers to reduce access time to fade parameters
	pthread_mutex_lock(&nodes_lock);
	for (SAMPLE i = 0; i < FADER_STEPS; i++) {
		smpl = audioData->getStart() + i*FADER_GRANULARITY;
		i_a = i_b = nodes.lower_bound(smpl);
		if (i_a != nodes.end()) {
			i_a--;
			a = (*i_a).first;
			b = (*i_b).first;
			av = (*i_a).second;
			bv = (*i_b).second;
			vol = (smpl - a)*(bv - av)/(b - a) + av;
		}
		else {
			i_a--;
			vol = (*i_a).second;
		}

		for (unsigned int k = 0; k < FADER_GRANULARITY; k++) {
			mix[i*FADER_GRANULARITY + k] = 
				static_cast<SAMPLEVAL>(mix[i*FADER_GRANULARITY + k] * vol);
		}
	}
	pthread_mutex_unlock(&nodes_lock);
}


void ProcessFader::receiveMessage(PORT inPort, MESSAGE message) {
    send(OUT0,message);
}

void ProcessFader::threadExecute() {

}

void ProcessFader::addNode(SAMPLE smpl, double pct) {
	pthread_mutex_lock(&nodes_lock);
	nodes[smpl] = pct;
	pthread_mutex_unlock(&nodes_lock);
}

void ProcessFader::clearNodes() {
	pthread_mutex_lock(&nodes_lock);
	nodes.clear();
	pthread_mutex_unlock(&nodes_lock);
}

void ProcessFader::setLevel(double pct) {
	vol = pct;
}
