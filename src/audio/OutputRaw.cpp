#include <iostream>
#include <fstream>
using std::ofstream;
using std::cout;
using std::endl;

#include "OutputRaw.h"
using Audio::OutputRaw;

OutputRaw::OutputRaw(string filename) {
	this->filename = filename;
}

OutputRaw::~OutputRaw() {

}

void OutputRaw::receiveMessage(PORT inPort, MESSAGE message) {
    //cout << "Message on port " << inPort << ", message " << message << endl;
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
		
void OutputRaw::onConnect(PORT localPort) {
	
}

void OutputRaw::onDisconnect(PORT localPort) {
	
}

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

