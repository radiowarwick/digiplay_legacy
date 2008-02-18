#include <iostream>
#include <fstream>
using std::ofstream;
using std::cout;
using std::endl;

#include "OutputRaw.h"
using Audio::OutputRaw;

/**
 * Create a new output module to write to file.
 * @param   filename    File to write to
 */
OutputRaw::OutputRaw(string filename) {
	this->filename = filename;
}


/**
 * Destructor
 */
OutputRaw::~OutputRaw() {

}


/**
 * Process messages received from other components.
 * @param   inPort      Port on which message is received
 * @param   message     Message received
 */
void OutputRaw::receiveMessage(PORT inPort, MESSAGE message) {
    if (inPort != IN0) {
        cout << "OutputRaw::receive: only use IN0 on a FILE" << endl;
        return;
    }
    switch (message) {
        case PLAY:
            audioState = STATE_PLAY;
            if (!isThreadActive()) threadStart();
            break;
        case STOP:
        	threadKill();
        	threadWait();
        	break;
        case PAUSE:
            audioState = STATE_PAUSE;
            break;
        default:
            break;
    }
}


/**
 * Perform tasks when a component is connected
 * @param   localPort   Port on which component is connected
 */	
void OutputRaw::onConnect(PORT localPort) {
	
}


/**
 * Perform tasks when a component is disconnected
 * @param   localPort   Port on which component is disconnected
 */
void OutputRaw::onDisconnect(PORT localPort) {
	
}


/**
 * Request audio from upstream and write it to file
 */
void OutputRaw::threadExecute() {
    if (!connectedDevice(IN0)) 
		cout << "CONNECTED DEVICE IS NULL" << endl;

    AudioPacket *buffer = new AudioPacket(PACKET_SAMPLES);
    const char* d = (char*)(buffer->getData());
	Component *C = connectedDevice(IN0);
	
	// Create and open output file
	ofstream f_out(filename.c_str());
	if (!f_out.good()) {
		cout << "Failed to open file: " << filename << endl;
		return;
	}
	
	while (audioState != STATE_STOP) {
        if (audioState == STATE_PAUSE) {
            usleep(100);
            
            continue;
        }
		C->getAudio(buffer);
		f_out.write(d, PACKET_BYTES);
		if (f_out.bad()) {
			cout << "Failed to write audio data to file." << endl;
		}
	}
	
	// Close file
	f_out.close();
	
	// Clean up memory
	delete buffer;

}
