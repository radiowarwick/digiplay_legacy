#ifndef CLASS_AUDIO_INPUT_RAW
#define CLASS_AUDIO_INPUT_RAW

#include <iostream>
#include <fstream>
#include "FLAC++/decoder.h"

using namespace std;
using namespace FLAC::Decoder;

#include "Input.h"

class Audio::Counter;

class Audio::InputFlac : public FLAC::Decoder::File, public Audio::Input {
	public:
		InputFlac();
		~InputFlac();

		virtual void getAudio(AudioPacket& audioData);

		void load(string filename, long start_smpl, long end_smpl);
		void play();		// play track
		void stop();		// stop track and seek to start
		void pause();		// pause track
		void seek(long sample);

		void addCounter(Audio::Counter *counter);
		void removeCounter(Audio::Counter *counter);
		
		void receiveMessage(PORT inPort, MESSAGE message);

		void threadExecute();

	protected:
		::FLAC__StreamDecoderWriteStatus write_callback(const::FLAC__Frame *frame, const FLAC__int32 *const buffer[]);
                void metadata_callback(const::FLAC__StreamMetadata *metadata);
                void error_callback(::FLAC__StreamDecoderErrorStatus status);

	private:
		ifstream f;
		string f_filename;
		char *audioBuffer, *cacheStart, *cacheEnd, *cacheWrite, *cacheRead;
		unsigned long cacheSize, cacheFree;
		unsigned long f_start_byte, f_end_byte, f_pos_byte, f_length_byte;
		vector<Audio::Counter*> countersList;
		STATE state;

		void updateCounters(unsigned long sample);
};

#endif
