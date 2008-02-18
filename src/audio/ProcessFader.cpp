#include "ProcessFader.h"
using Audio::ProcessFader;
#include <iostream>
#include <cmath>
using namespace std;

/**
 * Construct a new audio fader.
 */
ProcessFader::ProcessFader() {
	vol = 1.0;
	pthread_mutex_init(&nodes_lock,NULL);
}


/**
 * Destructor
 */
ProcessFader::~ProcessFader() {

}


/**
 * Performs audio fading on an audio packet.
 * Audio is requested from the component connected to port IN0. The amplitude
 * of each sample is adjusted according to the piecewise-linear function 
 * specified by the node list.
 * @param   audioData       The AudioPacket to process.
 */ 
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


/**
 * Receive messages from other components. Messages are just "passed-on"
 * downstream.
 * @param   inPort      Port on which the message is received.
 * @param   message     The message which is received.
 */
void ProcessFader::receiveMessage(PORT inPort, MESSAGE message) {
    if (inPort == IN0) {
        send(OUT0,message);
    }
}


/**
 * Adds a node to the piecewise-linear amplitude function or changes the value
 * of an existing node. Nodes are stored in an STL map indexed by their sample
 * index. Each node has a percentage amplitude associated with it which forms 
 * the function.
 * @param   smpl        The sample at which to create a node.
 * @param   pct         The percentage of full amplitude of the function at
 *                      this node.
 */
void ProcessFader::addNode(SAMPLE smpl, double pct) {
	pthread_mutex_lock(&nodes_lock);
	nodes[smpl] = pct;
	pthread_mutex_unlock(&nodes_lock);
}


/**
 * Clears all nodes. The amplitude function will then be considered full
 * amplitude at all samples.
 */
void ProcessFader::clearNodes() {
	pthread_mutex_lock(&nodes_lock);
	nodes.clear();
	pthread_mutex_unlock(&nodes_lock);
}


/**
 * Fix the amplitude function to a specific value.
 */
void ProcessFader::setLevel(double pct) {
	vol = pct;
}
