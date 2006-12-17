/*
 * Sustainer Scheduler
 * scheduler.h
 * Selects tracks from schedule bins and adds them to a schedule calculating
 * timings, etc
 *
 * Copyright (c) 2004-2005 Chris Cantwell
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
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

#define BIN6_SQL "SELECT audio.id,audio.md5,audio.length_smpl,audio.start_smpl,audio.end_smpl,audio.intro_smpl,audio.extro_smpl,audio.title FROM audio,audiojinglepkgs,jinglepkgs,jingletypes WHERE audiojinglepkgs.jinglepkg=jinglepkgs.id AND audiojinglepkgs.audio=audio.id AND audiojinglepkgs.jingletype=0 AND jinglepkgs.enabled='t' AND sustainer='t' AND audio.type=1 ORDER BY audio.title"

#define BIN7_SQL "SELECT audio.id,audio.md5,audio.length_smpl,audio.start_smpl,audio.end_smpl,audio.intro_smpl,audio.extro_smpl,audio.title FROM audio WHERE sustainer='t' AND audio.type=2 ORDER BY audio.title"

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
