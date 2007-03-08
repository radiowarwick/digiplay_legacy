#include <iostream>
using std::cout;
using std::endl;

#include "Counter.h"
#include "InputFlac.h"
using Audio::InputFlac;

InputFlac::InputFlac() {
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


//	f_pos_byte = 0;
//	f_start_byte = 0;
//	f_end_byte = 0;
//	f_length_byte = 0;

//	audioBuffer = new char[256];
}

InputFlac::~InputFlac() {

}

void InputFlac::getAudio(AudioPacket& audioData) {
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

void InputFlac::load(string filename, long start_smpl, long end_smpl) {

	if (filename == "") return;
	state = STATE_STOP;
	threadWait();
	finish();
//	reset();

	set_filename(filename.c_str());
	int retval = init();
//	if ( retval != FLAC__STREAM_DECODER_INIT_STATUS_OK ) {
//		cout << "This file cannot be opened." <<endl;
//		return;
//	}
	if ( get_channels()!=2 && get_bits_per_sample() != 16 && get_sample_rate()!= 44100 ) {
		cout << "This file is not a 44100, 16 bit, stereo file." << endl;
		return;
	}
	seek_absolute((FLAC__uint64)(start_smpl));
	
//	if (filename == "") return;
//	state = STATE_STOP;
//	threadWait();

//	f.close();
//	f.clear();
//	f.open(filename.c_str(), ios::in|ios::binary);
//	if (f.is_open() && f.good() == false) return;
//	f.seekg(0,ios::end);
//	f_filename = filename;

	f_start_byte = start_smpl * 4;
//	f_end_byte = end_smpl * 4;
//	f_length_byte = f_end_byte - f_start_byte;
	f_pos_byte = f_start_byte;

	cacheRead = cacheStart;
	cacheWrite = cacheStart;
	cacheFree = cacheSize;

	retval = threadStart();
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

void InputFlac::play() {
	state = STATE_PLAY;
	send(OUT0,PLAY);
}

void InputFlac::stop() {
	state = STATE_STOP;
	send(OUT0,STOP);
}

void InputFlac::pause() {
	state = STATE_PAUSE;
	send(OUT0,PAUSE);
}

void InputFlac::seek(long sample) {
	sample -= (sample % 64);		//WTF is this?
	bool retval = seek_absolute((FLAC__uint64)(sample));
	if (!retval)
		cout << "Error seeking to stream position " << sample << endl;
//	f_pos_byte = sample*4;
//	f.seekg(f_pos_byte, ios::beg);
	cacheWrite = cacheRead;
	cacheFree = cacheSize;
}

void InputFlac::addCounter(Audio::Counter *counter) {
	vector<Audio::Counter *>::iterator i 
		= find(countersList.begin(), countersList.end(), counter);
	if (i == countersList.end()) {
		countersList.push_back(counter);
	}
}

void InputFlac::removeCounter(Audio::Counter *counter) {
	vector<Audio::Counter *>::iterator i 
		= find(countersList.begin(), countersList.end(), counter);
	if (i != countersList.end()) {
		countersList.erase(i);
	}
	else {
		cout << "Counter does not exist" << endl;
	}
}

void InputFlac::updateCounters(unsigned long sample) {
	for (unsigned int i = 0; i < countersList.size(); i++) {
		countersList.at(i)->setSample(sample);
	}
}

void InputFlac::receiveMessage(PORT inPort, MESSAGE message) {

}

void InputFlac::threadExecute() {
//	f.clear();
//	f.seekg(f_start_byte, ios::beg);

//	int read_bytes = 256;
//	char *ptr;

	while (1) {
		if (threadReceive() == STOP) {
			break;
		}
		if (cacheFree < 32768) {
			usleep(100);
			continue;
		}
		if (!process_single())
			cout << "A fatal error occured.  Its now dead." <<endl;

//		usleep(100);
		
//		if (f_end_byte - f.tellg() < 256) {
//			read_bytes = f_end_byte - f.tellg();
//			if (read_bytes == 0) break;
//		}

//		f.read(audioBuffer, read_bytes);
//		read_bytes = f.gcount();

//		if (read_bytes == 0) {
//			cout << "ERROR: Unable to read from file or unexpected end" 
//				<< endl;
//			break;
//		}
		
//		ptr = audioBuffer;
//		for (int i = 0; i < read_bytes; i++) {
//			*cacheWrite = *ptr;
//			cacheWrite++;
//			ptr++;
//			cacheFree--;
//			if (cacheWrite > cacheEnd) {
//				cacheWrite = cacheStart;
//			}
//		}
	}
}

::FLAC__StreamDecoderWriteStatus InputFlac::write_callback(const::FLAC__Frame *frame, const FLAC__int32 *const buffer[]) {
	int i;
//	unsigned char j,k,l,m;
	unsigned char *left=(unsigned char*)buffer[0];
        unsigned char *right=(unsigned char*)buffer[1];
	for(i=0; i<frame->header.blocksize; i++) {
		*cacheWrite=left[4*i];
		cacheWrite++;
		*cacheWrite=left[4*i+1];
		cacheWrite++;
		*cacheWrite=right[4*i];
		cacheWrite++;
		*cacheWrite=right[4*i+1];
		cacheWrite++;
	}
//	pos+=frame->header.blocksize;
	return ::FLAC__StreamDecoderWriteStatus(FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE);
}

void InputFlac::metadata_callback(const::FLAC__StreamMetadata *metadata) {
	return;
}

void InputFlac::error_callback(::FLAC__StreamDecoderErrorStatus status) {
	cout << "Error " << status << endl;
	return;
}

