/* Audio Playout Handler Header
 * playout.h
 *
 * Handles playback of audio from file or Line In sources, providing
 * crossfading facilities.
 * (c) Copyright Chris Cantwell 2004
 */

#ifndef CLASS_PLAYOUT
#define CLASS_PLAYOUT

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "fcntl.h"          //File Control Operations
#include <string>
#include <algorithm>
#include "pthread.h"
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include <sys/soundcard.h>
#include <sys/ioctl.h>

#include "config_reader.h"

class playout {
	public:
		playout(string Device = "CHANNEL1");
		~playout();
		void load(string *md5);
		void play(long start_smpl, long end_smpl);
		void play_crossfade(string *md5_1, string *md5_2,
								long start1_ms, long start2_ms, long length_ms);
		void stop();			//stops playback thread (flush cache)
		void pause();			//pause playback thread
		void resume();
		void seek(long position);	//flush cache, and move read position
		void notify();
		void notify_cache();	//waits until track finished, then returns
		void addCounter(void (*f_setCounter)(long,void*), void *obj);

		//pseudo-public
		void cache();
		void cache_crossfade();
		void play_cache();

		long getPosition_ms();
		long getLength_ms();
		
	private:
		Connection *C;
		Transaction *T;

		bool mode_play;
		bool mode_cache;

		long getFileLength(string *md5);
		long getFileLength_ms(string *md5);
		string getFileTitle(string *md5);

		//Threads
		pthread_t Thread_Cache;
		pthread_t Thread_Cache_Crossfade;
		pthread_t Thread_Play;

		//Thread shared
		char *Cache_Start;
		char *Cache_End;
		char *Cache_Read;
		char *Cache_Write;
		long Cache_Free;
		
		ifstream *current_file_handle; //Standard caching
		long current_start_byte;
		long current_end_byte;
		long b_current_pos; // position of playback in bytes
		long b_current_length;

		ifstream *current_file_handle1; //Crossfade caching
		ifstream *current_file_handle2;
		long current_start1_byte;
		long current_start2_byte;
		long current_length_byte;

		//Callbacks
		void (*f_counters)(long,void*);
		void *f_obj;

		//Others
		string DB_CONNECT, AUDIO_PATH;
		long CACHE_SIZE;
		int DSP_SPEED;
		int audio;
		int dsp_speed;
		void Initialise_Hardware(string Device);
};

void *thread_fill_cache(void *ptr);
void *thread_play_cache(void *ptr);
void *thread_fill_cache_crossfade(void *ptr);
#endif
