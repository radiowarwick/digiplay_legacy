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

}

void InputRaw::getAudio(AudioPacket& audioData) {
    // Fills audioData with the requested number of samples
    // 2 bytes per sample, and 2 channels
    // => get 4xsamples bytes
    char *ptr = (char*)&audioData[0];
    unsigned long bytes = audioData.getSize() * 2;
    long pos = static_cast<long>((f_pos_byte - f_start_byte) / 4);
    short count = 0;

	if ((state == STATE_PLAY)  && cacheSize - cacheFree < 1024) {
        cout << "Out of cached audio: " << cacheSize - cacheFree << endl;
		stop();
	}
    
	for (unsigned long i = 0; i < bytes; i++) {
        if (state == STATE_STOP) {
            *ptr = 0;
        }
        else {
            *ptr = *cacheRead; 
            cacheRead++;
            cacheFree++;
            f_pos_byte++;
        	if (cacheRead > cacheEnd) {
				cacheRead = cacheStart;
			}
        }
        ptr++;
        count++;
    }
	audioData.setStart(pos);

    if ((state == STATE_PLAY) && countersList.size() > 0) {
        if ((pos - (pos % 64)) % 8192 == 0) {
            updateCounters(pos/4);
		}
    }

    return;
}

void InputRaw::load(string filename, long start_smpl, long end_smpl) {
	if (filename == "") return;
	state = STATE_STOP;
	threadWait();

	f.close();
	f.clear();
	f.open(filename.c_str(), ios::in|ios::binary);
	if (f.is_open() && f.good() == false) return;
	f.seekg(0,ios::end);
	f_filename = filename;

	f_start_byte = start_smpl * 4;
	f_end_byte = end_smpl * 4;
	f_length_byte = f_end_byte - f_start_byte;
	f_pos_byte = f_start_byte;

	cacheRead = cacheStart;
	cacheWrite = cacheStart;
	cacheFree = cacheSize;

	int retval = threadStart();
	if (retval != 0) {
		cout << "Error creating thread" << endl;
		return;
	}
	if (countersList.size() > 0) updateCounters(0);
    while ( cacheSize - cacheFree < 4096 ) {
        cout << cacheSize - cacheFree << endl;
        usleep(100);
    }
}

void InputRaw::play() {
	state = STATE_PLAY;
	send(OUT0,PLAY);
}

void InputRaw::stop() {
	state = STATE_STOP;
	send(OUT0,STOP);
}

void InputRaw::pause() {
	state = STATE_PAUSE;
	send(OUT0,PAUSE);
}

void InputRaw::seek(long sample) {
	sample -= (sample % 64);
	f_pos_byte = sample*4;
	f.seekg(f_pos_byte, ios::beg);
	cacheWrite = cacheRead;
	cacheFree = cacheSize;
}

void InputRaw::addCounter(Audio::Counter *counter) {
	vector<Audio::Counter *>::iterator i 
		= find(countersList.begin(), countersList.end(), counter);
	if (i == countersList.end()) {
		countersList.push_back(counter);
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

void InputRaw::receiveMessage(PORT inPort, MESSAGE message) {

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
	}
}
