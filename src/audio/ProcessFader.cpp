#include "ProcessFader.h"
using Audio::ProcessFader;
#include <iostream>
#include <cmath>
using namespace std;

ProcessFader::ProcessFader() {
	vol = 1.0;
//	pthread_mutex_init(&fades_lock,NULL);
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
//	pthread_mutex_lock(&fades_lock);
	for (SAMPLE i = 0; i < FADER_STEPS; i++) {
		smpl = audioData->getStart() + i*FADER_GRANULARITY;
		i_a = i_b = nodes.lower_bound(smpl);
		i_a--;
		a = (*i_a).first;
		b = (*i_b).first;
		av = (*i_a).second;
		bv = (*i_b).second;
		vol = (smpl - a)*(bv - av)/(b - a) + av;

		for (unsigned int k = 0; k < FADER_GRANULARITY; k++) {
			mix[i*FADER_GRANULARITY + k] = 
				static_cast<SAMPLEVAL>(mix[i*FADER_GRANULARITY + k] * vol);
		}
	}
//	pthread_mutex_unlock(&fades_lock);
}

void ProcessFader::receiveMessage(PORT inPort, MESSAGE message) {
    send(OUT0,message);
}

void ProcessFader::threadExecute() {

}

void ProcessFader::addNode(SAMPLE smpl, double pct) {
	nodes[smpl] = pct;
}

void ProcessFader::clearNodes() {
	nodes.clear();
}

void ProcessFader::setLevel(double pct) {
	vol = pct;
}