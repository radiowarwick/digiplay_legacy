#include <iostream>
using namespace std;

#include "Component.h"

Audio::Component::~Component() {
	// Remove any mappings to this object.
	// Although the mapping structures will all be dealt with, we have to
	// tell all other mapped components that this component is being destroyed
	for (unsigned int i = 0; i < portMap.size(); i++)
		destroyMapping(portMap.at(i).port);
}

bool Audio::Component::connect(PORT localPort, Component *c, 
								PORT remotePort) {
	for (unsigned int i = 0; i < portMap.size(); i++) {
		if (portMap.at(i).port == localPort) {
			cout << "Port " << localPort << " is already mapped." << endl;
			return false;
		}
	}
	if (c->connectRequest(remotePort, this, localPort) == false) {
		cout << "Remote Port " << remotePort << " is already mapped." << endl;
		return false;
	}
	createMapping(localPort, c, remotePort);
	return true;
}

bool Audio::Component::connectRequest(PORT localPort, Component *c,
								PORT remotePort) {
	createMapping(localPort, c, remotePort);
	return true;
}

void Audio::Component::disconnect(PORT localPort) {
	destroyMapping(localPort);
}

void Audio::Component::getAudio(short *audioData, int samples) {

}

void Audio::Component::send(PORT outPort, MESSAGE message) {

}

void Audio::Component::receive(PORT inPort, MESSAGE message) {

}

Audio::Component* Audio::Component::connectedDevice(PORT inPort) {
	for (unsigned int i = 0; i < portMap.size(); i++) {
		if (portMap.at(i).port == inPort) {
			return portMap.at(i).component;
		}
	}
	return 0;
}

void Audio::Component::createMapping(PORT localPort, Component *c,
										PORT remotePort) {
	ConnectionMapping CM;
	CM.port = localPort;
	CM.component = c;
	CM.remotePort = remotePort;
	portMap.push_back(CM);
}

void Audio::Component::destroyMapping(PORT localPort) {

}

void Audio::Component::destroyMapping(Component *c, PORT remotePort) {

}
