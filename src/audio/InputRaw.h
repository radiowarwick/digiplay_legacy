#ifndef CLASS_AUDIO_INPUT_RAW
#define CLASS_AUDIO_INPUT_RAW

#include <iostream>
#include <fstream>
using namespace std;

#include "Input.h"

class Audio::InputRaw : public Audio::Input {
	public:
		InputRaw();
		~InputRaw();

		void getAudio(short *audioData, int samples);

		void load(string filename, long start_smpl, long end_smpl);
		void play();		// play track
		void stop();		// stop track and seek to start
		void pause();		// pause track
		void seek(long sample);

		void addCounter(Audio::Counter *counter);
		void removeCounter(Audio::Counter *counter);
		
		void receive(PORT inPort, MESSAGE message);

		void threadExecute();

	private:
		ifstream f;
		string f_filename;
		char *audioBuffer, *cacheStart, *cacheEnd, *cacheWrite, *cacheRead;
		unsigned long cacheSize, cacheFree;
		unsigned long f_start_byte, f_end_byte, f_pos_byte, f_length_byte;
		vector<Audio::Counter*> countersList;
		STATE state;

		void updateCounters(long sample);
};

#endif
