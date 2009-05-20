#include "ProcessLink.h"
using Audio::ProcessLink;
#include <iostream>
#include <cmath>
using namespace std;

/**
 * Construct a new audio fader.
 */
ProcessLink::ProcessLink() {

}


/**
 * Destructor
 */
ProcessLink::~ProcessLink() {

}


/**
 * Passes audio through the component.
 * @param   audioData       The AudioPacket to process.
 */ 
void ProcessLink::getAudio(AudioPacket* audioData) {
    connectedDevice(IN0)->getAudio(audioData);
}


/**
 * Receive messages from other components. Messages are just "passed-on"
 * downstream.
 * @param   inPort      Port on which the message is received.
 * @param   message     The message which is received.
 */
void ProcessLink::receiveMessage(PORT inPort, MESSAGE message) {
    if (inPort == IN0) {
        send(OUT0,message);
    }
}