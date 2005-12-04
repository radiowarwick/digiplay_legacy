#ifndef CLASS_SCHEDULER
#define CLASS_SCHEDULER

#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "schedule.h"
#include "config.h"

#define BIN1_SQL "SELECT audio.id,audio.md5,audio.length_smpl,audio.start_smpl,audio.end_smpl,audio.intro_smpl,audio.extro_smpl,audio.title,artists.name AS artist FROM audio,artists,audioartists WHERE audioartists.audio=audio.id AND audioartists.artist=artists.id AND sustainer='t' AND type=0 ORDER BY audio.title"

#define BIN2_SQL "SELECT audio.id,audio.md5,audio.length_smpl,audio.start_smpl,audio.end_smpl,audio.intro_smpl,audio.extro_smpl,audio.title,artists.name AS artist FROM audio,artists,audioartists WHERE audioartists.audio=audio.id AND audioartists.artist=artists.id AND sustainer='t' AND type=0 ORDER BY audio.title"

#define BIN3_SQL "SELECT audio.id,audio.md5,audio.length_smpl,audio.start_smpl,audio.end_smpl,audio.intro_smpl,audio.extro_smpl,audio.title,artists.name AS artist FROM audio,artists,audioartists WHERE audioartists.audio=audio.id AND audioartists.artist=artists.id AND sustainer='t' AND type=0 ORDER BY audio.title"

#define BIN4_SQL "SELECT audio.id,audio.md5,audio.length_smpl,audio.start_smpl,audio.end_smpl,audio.intro_smpl,audio.extro_smpl,audio.title,artists.name AS artist FROM audio,artists,audioartists WHERE audioartists.audio=audio.id AND audioartists.artist=artists.id AND sustainer='t' AND type=0 ORDER BY audio.title"

#define BIN5_SQL "SELECT audio.id,audio.md5,audio.length_smpl,audio.start_smpl,audio.end_smpl,audio.intro_smpl,audio.extro_smpl,audio.title,artists.name AS artist FROM audio,artists,audioartists WHERE audioartists.audio=audio.id AND audioartists.artist=artists.id AND sustainer='t' AND type=0 ORDER BY audio.title"

#define BIN6_SQL "SELECT audio.id,audio.md5,audio.length_smpl,audio.start_smpl,audio.end_smpl,audio.intro_smpl,audio.extro_smpl,audio.title FROM audio,jinglepackage,jingletypes WHERE jinglepackage.id=audio.jingle_package AND audio.jingle_type=0 AND jinglepackage.enabled='t' AND sustainer='t' AND type=1 ORDER BY audio.title"

#define BIN7_SQL "SELECT audio.id,audio.md5,audio.length_smpl,audio.start_smpl,audio.end_smpl,audio.intro_smpl,audio.extro_smpl,audio.title FROM audio WHERE sustainer='t' AND type=2 ORDER BY audio.title"

#define AUDIO_TYPE_MUSIC "0"
#define AUDIO_TYPE_JINGLE "1"
#define AUDIO_TYPE_ADVERT "2"

#define BINS 7
#define ONE_SECOND 44100

class scheduler {
	public:
		scheduler();
		~scheduler();
		void doSchedule(long seconds);
		unsigned int getPlaylistSize();
		unsigned long getPlaylistLength();
		unsigned int getScheduleRemainSize();
		unsigned long getScheduleRemainTime();

	private:
		Connection *C;
		Transaction *T;
		schedule *S;
		vector<sched_bin*> *bins;
		int bin_w[BINS];

		long start_time;
		unsigned long target_length_smpl;

		bool initialise();
		bool complete();

		bool doFill();
		bool doMinimise();
		bool doCrossfades();
		bool doFadeOut();
	
		string getConfigParam(string name);
};

#endif
