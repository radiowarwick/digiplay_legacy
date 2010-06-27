#include <iostream>
using std::cout;
using std::endl;

#include "Component.h"
#include "Counter.h"
using Audio::Component;

/**
 * Creates a new component. This should not be called directly.
 */
Component::Component() {

}


/** 
 * Processes the components mapping lists and removes and mappings to this
 * object. Each component map is processed in turn and the connected
 * component is sent a destroyMapping() request.
 */
Component::~Component() {
	for (unsigned int i = 0; i < portMap.size(); i++) {
        portMap.at(i).component->destroyMapping(portMap.at(i).remotePort, this);
    }
}


/** 
 * Establishes a connection between a local port and a port on a remote
 * component. Validation is performed to check that the local port or the
 * port on the remote component is not already in use. A mapping is then added
 * to this components mapping list, and the remote component is instructed to
 * add a reverse mapping.
 * @param localPort The local port on which the remote component is connected.
 * @param c A pointer to the remote component
 * @param remotePort The port on the remote component to connect to
 * @return Success or failure of connection
 */
bool Component::patch(PORT localPort, Component *c, 
								PORT remotePort) {
    // Need to check the local port is only mapped once if it's non-zero.
    if (localPort != OTHER) {
    	for (unsigned int i = 0; i < portMap.size(); i++) {
    		if (portMap.at(i).port == localPort) {
    			cout << "Port " << localPort << " is already mapped." << endl;
    			return false;
    		}
    	}
    }
    // Request the reverse mapping from the other component
    // if it fails, we should not add a mapping and fail ourself
    if (c->createMapping(remotePort, this, localPort) == false) {
    	cout << "Remote Port " << remotePort << " is already mapped." 
                << endl;
    	return false;
    }
    // If all is good, add the mapping
	createMapping(localPort, c, remotePort);
	return true;
}


/** 
 * Disconnect all components connected to a port on this component
 * @param localPort The local port which is disconnected
 */
void Component::unpatch(PORT localPort) {
    unsigned int i = 0;
    while (i < portMap.size()) {
        if (portMap.at(i).port == localPort) {
            portMap.at(i).component->destroyMapping(
                portMap.at(i).remotePort, this);
	        destroyMapping(localPort,portMap.at(i).component);
        }
        i++;
    }
	onUnpatch(localPort);
}


/** 
 * Adds a counter component to this components counter update list
 * @param C The counter component to be added to be updated during getAudio
 */
void Component::addCounter(Counter* C) {
    for (unsigned int i = 0; i < _counters.size(); i++) {
        if (_counters.at(i) == C) {
            return;
        }
    }
    _counters.push_back(C);
}


/** 
 * Removes a counter component from the list of components to be updated
 * @param C The counter component to be removed
 */
void Component::removeCounter(Counter* C) {
    for (unsigned int i = 0; i < _counters.size(); i++) {
        if (_counters.at(i) == C) {
            _counters.erase(_counters.begin() + i);
            return;
        }
    }
}


/** 
 * Sends a message from one component to another. The local OUT port is
 * specified and the destination component is then looked up from this in the
 * mapping table. The message is then transmitted using the remote components
 * receive() routine.
 * @param outPort Specify the port on which to send the message
 * @param message Specify the message to send
 */
void Component::send(PORT outPort, MESSAGE message) {
    for (unsigned int i = 0; i < portMap.size(); i++) {
        if (portMap.at(i).port == outPort) {
            portMap.at(i).component->receive(portMap.at(i).remotePort,
                                                message);
            // Multiple components may be connected to OTHER port
            if (outPort != OTHER) return;
        }
    }
    if (outPort != OTHER) {
        cout << "Component::send: No such port: " << outPort << endl;
    }
}


/** 
 * Processes received message for this component. This is a virtual function
 * and should be reimplemented in each derived class to handle messages as
 * required.
 * @param inPort Specifies the port on which the message is received
 * @param message Specifies the message received.
 */
void Component::receive(PORT inPort, MESSAGE message) {
    for (unsigned int i = 0; i < portMap.size(); i++) {
        if (portMap.at(i).port == inPort) {
            switch (message) {
                case PLAY:
                    portMap.at(i).state = STATE_PLAY;
                    break;
                case STOP:
                    portMap.at(i).state = STATE_STOP;
                    break;
                case PAUSE:
                    portMap.at(i).state = STATE_PAUSE;
                    break;
                default:
                    break;
            }
            receiveMessage(inPort,message);
            return;
        }
    }
    cout << "Component::receive: No such port: " << inPort << endl;
}


/** 
 * A pointer to the connected component on the specified port is returned
 * @param inPort The port to get the connected component for.
 * @return The component connected to \c inPort.
 */
Component* Component::connectedDevice(PORT inPort) {
	for (unsigned int i = 0; i < portMap.size(); i++) {
		if (portMap.at(i).port == inPort) {
			return portMap.at(i).component;
		}
	}
	return 0;
}


/** 
 * Adds a new component mapping to this components mapping list specifying
 * the remote component and port connected to a local port.
 * @param localPort The local port the component \c is connected to
 * @param c The component connected to this component
 * @param remotePort The port on the remote component this is connected to.
 * @return Success or failure of the mapping.
 */
bool Component::createMapping(PORT localPort, Component *c,
										PORT remotePort) {
    // Fail if this port has already been mapped
    if (localPort != OTHER) {
        for (unsigned int i = 0; i < portMap.size(); i++) {
            if (portMap.at(i).port == localPort) {
                return false;
            }
        }
    }
	ConnectionMapping CM;
	CM.port = localPort;
	CM.component = c;
	CM.remotePort = remotePort;
	portMap.push_back(CM);

    // See if the other component is also a counter
    Counter *C =  dynamic_cast<Counter*>(c);
    if (C) addCounter(C);
	onPatch(localPort);
    return true;
}


/** 
 * Removes a mapping
 * @param   localPort   The port from which to remove mapping
 * @param   c           The component with which we destroy the mapping
 * @returns             True if successful
 */
bool Component::destroyMapping(PORT localPort, Component *c) {
    // if it's a counter, remove it from the list
    Counter *C = dynamic_cast<Counter*>(c);
    if (C) removeCounter(C);
    
    for (unsigned int i = 0; i < portMap.size(); i++) {
        if (portMap.at(i).port == localPort
                && portMap.at(i).component == c) {
            portMap.erase(portMap.begin() + i);
            return true;
        }
    }
    return false;
}
