#include <iostream>
using std::cout;
using std::endl;

#include "Counter.h"
#include "InputRaw.h"
using Audio::InputRaw;

InputRaw::InputRaw() {
	state = STATE_STOP;

	// Configure cache
	cacheSize = 1760000;
	cacheStart = new char[cacheSize];
	if (cacheStart == 0) {
		cout << "ERROR: Cannot allocate memory for cache" << endl;
		exit(-1);
	}
	cacheEnd = cacheStart + cacheSize;
	cacheRead = cacheStart;
	cacheWrite = cacheStart;
	cacheFree = cacheSize;

	f_pos_byte = 0;
	f_start_byte = 0;
	f_end_byte = 0;
	f_length_byte = 0;

	audioBuffer = new char[256];
}

InputRaw::~InputRaw() {
    delete[] cacheStart;
    delete[] audioBuffer;
}

void InputRaw::getAudio(AudioPacket* audioData) {
    // Fills audioData with the requested number of samples
    char *ptr = (char*)(audioData->getData());
    unsigned long bytes = PACKET_BYTES;
	// pos is in stereo samples
    long pos = static_cast<long>((f_pos_byte - f_start_byte) / 4);
    short count = 0;

	if (cacheSize - cacheFree < bytes) {
		bytes = cacheSize - cacheFree;
		audioData->setSize(bytes/4);
	}
	for (unsigned long i = 0; i < PACKET_BYTES; i++) {
        if (state == STATE_STOP || bytes == 0) {
            *ptr = 0;
        }
        else {
            *ptr = *cacheRead; 
            cacheRead++;
            cacheFree++;
            f_pos_byte++;
			bytes--;
        	if (cacheRead > cacheEnd) {
				cacheRead = cacheStart;
			}
        }
        ptr++;
        count++;
    }
	// set the absolute position (relative to the start point) of this
	// block of audio in terms of stereo samples.
	audioData->setStart(pos);
	
	// removed check to see if state == STATE_PLAY
	if (cacheSize == cacheFree) {
        if (f_end_byte - f_pos_byte > 256) {
            //cout << "Out of cached audio" << endl;
        }
		stop();
	}

	// if we're playing, update all the attached counters with our current
	// position in terms of stereo samples.
    if (state == STATE_PLAY) {
        updateCounters(pos);
    }
    return;
}

void InputRaw::load(string filename, long start_smpl, long end_smpl) {
    cout << "Begin load" << endl;
	if (filename == "") throw;
	state = STATE_STOP;
    cout << "a" << endl;
	updateStates(STATE_STOP);
    cout << "b" << endl;
	threadKill();
    cout << "1" << endl;
	f.close();
	f.clear();
	f.open(filename.c_str(), ios::in|ios::binary);
	if (f.is_open() && f.good() == false) {
        cout << "Failed to open file '" << filename << "'" << endl;
        throw;
    }
	f.seekg(0,ios::end);
	f_filename = filename;

	f_start_byte = start_smpl * 4;
	f_end_byte = end_smpl * 4;
	f_length_byte = f_end_byte - f_start_byte;
	f_pos_byte = f_start_byte;

	cacheRead = cacheStart;
	cacheWrite = cacheStart;
	cacheFree = cacheSize;
    cout << "2" << endl;

	if (countersList.size() > 0) {
		updateCounters(0);
		updateTotals(f_length_byte/4);
	}
	cout << "3" << endl;
	int retval = threadStart();
	if (retval != 0) {
		cout << "Error creating thread" << endl;
		return;
	}
    cout << "4" << endl;	
	// Wait until the cache has been half filled
    while ( cacheSize < 2*cacheFree 
			&& cacheSize - cacheFree < f_length_byte) {
        usleep(100);
    }
    cout << "5" << endl;
}

void InputRaw::play() {
	state = STATE_PLAY;
	send(OUT0,PLAY);
	updateStates(STATE_PLAY);
}

void InputRaw::stop() {
	state = STATE_STOP;
    threadKill();
	send(OUT0,STOP);
	updateStates(STATE_STOP);
    load(f_filename, f_start_byte/4, f_end_byte/4);
}

void InputRaw::pause() {
	state = STATE_PAUSE;
	send(OUT0,PAUSE);
	updateStates(STATE_PAUSE);
}

void InputRaw::seek(long sample) {
	sample -= (sample % 64);
	f_pos_byte = sample*4;
	f.seekg(f_pos_byte, ios::beg);
	long pos = static_cast<long>((f_pos_byte - f_start_byte) / 4);
	updateCounters(pos);
	cacheWrite = cacheRead;
	cacheFree = cacheSize;
}

bool InputRaw::isLoaded() {
	return (f.is_open() && f.good());
}

void InputRaw::addCounter(Audio::Counter *counter) {
	vector<Audio::Counter *>::iterator i 
		= find(countersList.begin(), countersList.end(), counter);
	if (i == countersList.end()) {
		countersList.push_back(counter);
        counter->setSample(0);
        counter->setTotalSamples(f_length_byte/4);
        counter->setState(state);
	}
}

void InputRaw::removeCounter(Audio::Counter *counter) {
	vector<Audio::Counter *>::iterator i 
		= find(countersList.begin(), countersList.end(), counter);
	if (i != countersList.end()) {
		countersList.erase(i);
	}
	else {
		cout << "Counter does not exist" << endl;
	}
}

void InputRaw::updateCounters(unsigned long sample) {
	for (unsigned int i = 0; i < countersList.size(); i++) {
		countersList.at(i)->setSample(sample);
	}
}

void InputRaw::updateTotals(unsigned long samples) {
	for (unsigned int i = 0; i < countersList.size(); i++) {
		countersList.at(i)->setTotalSamples(samples);
	}
}

void InputRaw::updateStates(enum STATE state) {
	for (unsigned int i = 0; i < countersList.size(); i++) {
		countersList.at(i)->setState(state);
	}
}
void InputRaw::receiveMessage(PORT inPort, MESSAGE message) {

}

void InputRaw::onConnect(PORT localPort) {

}

void InputRaw::onDisconnect(PORT localPort) {

}

void InputRaw::threadExecute() {
	f.clear();
	f.seekg(f_start_byte, ios::beg);

	int read_bytes = 256;
	char *ptr;

	while (read_bytes == 256) {
		if (threadReceive() == STOP) {
			break;
		}
		if (cacheFree < 1024) {
			usleep(100);
			continue;
		}
		if (f_end_byte - f.tellg() < 256) {
			read_bytes = f_end_byte - f.tellg();
			if (read_bytes == 0) break;
		}

		f.read(audioBuffer, read_bytes);
		read_bytes = f.gcount();

		if (read_bytes == 0) {
			cout << "ERROR: Unable to read from file or unexpected end" 
				<< endl;
			break;
		}
		
		ptr = audioBuffer;
		for (int i = 0; i < read_bytes; i++) {
			*cacheWrite = *ptr;
			cacheWrite++;
			ptr++;
			cacheFree--;
			if (cacheWrite > cacheEnd) {
				cacheWrite = cacheStart;
			}
		}
		threadTestKill();
	}
}
