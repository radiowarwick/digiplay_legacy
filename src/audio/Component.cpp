#include <iostream>
using namespace std;

#include "Component.h"

Audio::Component::Component() {
    portMap = new vector<ConnectionMapping>;
}

/** Processes the components mapping lists and removes and mappings to this
 * object. Each component map is processed in turn and the connected
 * component is sent a destroyMapping() request.
 */
Audio::Component::~Component() {
	for (unsigned int i = 0; i < portMap->size(); i++)
		destroyMapping(portMap->at(i).port);
    delete portMap;
}

/** Establishes a connection between a local port and a port on a remote
 * component. Validation is performed to check that the local port or the
 * port on the remote component is not already in use. A mapping is then added
 * to this components mapping list, and the remote component is instructed to
 * add a reverse mapping.
 * @param localPort The local port on which the remote component is connected.
 * @param c A pointer to the remote component
 * @param remotePort The port on the remote component to connect to
 * @return Success or failure of connection
 */
bool Audio::Component::connect(PORT localPort, Component *c, 
								PORT remotePort) {
	for (unsigned int i = 0; i < portMap->size(); i++) {
		if (portMap->at(i).port == localPort) {
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

void Audio::Component::getAudio(short *audioData, unsigned long samples) {
    cout << "Component getAudio" << endl;
}

/** Sends a message from one component to another. The local OUT port is
 * specified and the destination component is then looked up from this in the
 * mapping table. The message is then transmitted using the remote components
 * receive() routine.
 * @param outPort Specify the port on which to send the message
 * @param message Specify the message to send
 */
void Audio::Component::send(PORT outPort, MESSAGE message) {
    cout << "Component::send" << endl;
    for (unsigned int i = 0; i < portMap->size(); i++) {
        if (portMap->at(i).port == outPort) {
            portMap->at(i).component->receive(portMap->at(i).remotePort,
                                                message);
            return;
        }
    }
    cout << "No such port: " << outPort << endl;
}

/** Processes received message for this component. This is a virtual function
 * and should be reimplemented in each derived class to handle messages as
 * required.
 * @param inPort Specifies the port on which the message is received
 * @param message Specifies the message received.
 */
void Audio::Component::receive(PORT inPort, MESSAGE message) {
    cout << "Component::receive" << endl;
    for (unsigned int i = 0; i < portMap->size(); i++) {
        if (portMap->at(i).port == inPort) {
            switch (message) {
                case PLAY:
                    portMap->at(i).state = STATE_PLAY;
                    break;
                case STOP:
                    portMap->at(i).state = STATE_STOP;
                    break;
                case PAUSE:
                    portMap->at(i).state = STATE_PAUSE;
                    break;
                default:
                    break;
            }
            cout << "ReceiveMessage(" << inPort << ")" << endl;
            cout << "ReceiveMessage(" << message << ")" << endl;
            receiveMessage(inPort,message);
            return;
        }
    }
    cout << "No such port: " << inPort << endl;
}

/** A pointer to the connected component on the specified port is returned
 * @param inPort The port to get the connected component for.
 * @return The component connected to \c inPort.
 */
Audio::Component* Audio::Component::connectedDevice(PORT inPort) {
	for (unsigned int i = 0; i < portMap->size(); i++) {
		if (portMap->at(i).port == inPort) {
			return portMap->at(i).component;
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
	portMap->push_back(CM);
}

void Audio::Component::destroyMapping(PORT localPort) {

}

void Audio::Component::destroyMapping(Component *c, PORT remotePort) {

}
