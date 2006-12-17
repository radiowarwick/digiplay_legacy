/*
 * Common DPS routines
 * dps.h
 * Provides common structure definitions and routines for all applications
 *
 * Copyright (c) 2005-2006 Chris Cantwell
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
#ifndef DPS_H
#define DPS_H

#include <string>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#define DPS_DB 0
#define DPS_INBOX 1
#define DPS_TRASH 2

// Error types
enum LOG_TYPE {
	LOG_DB = 0,
	LOG_AUDIOHW = 1,
	LOG_AUDIOPROC = 2,
	LOG_PLAYOUT = 4,
	LOG_CONFIG = 8,
	LOG_AUTH = 16,
	LOG_SHOWPLAN = 32,
	LOG_TAB = 64,
	LOG_TABINFO = 128,
	LOG_TABSEARCH = 256,
	LOG_TABEMAIL = 512,
	LOG_TABLOGGING = 1024,
	LOG_TABPLAYLIST = 2048,
	LOG_TABFILES = 4096,
	LOG_TABSCRIPT = 8192,
	LOG_XML = 16384
};

struct archive {
    bool isNull;
    unsigned long id;
    string name;
    string localPath;
    string remotePath;
};

struct track {
    bool isNull;
    unsigned short bin;
    unsigned int index;
    unsigned long audio_id;
    string md5;
	archive md5_archive;
    string title;
    string artist;
	string album;
	unsigned short tracknum;
	string reclibid;
	string origin;
	string release_date;
	bool censor;
    unsigned long length_smpl;
    unsigned long trim_start_smpl;
    unsigned long trim_end_smpl;
    unsigned long fade_in_smpl;
    unsigned long fade_out_smpl;
};

struct jingle {
	bool isNull;
	string md5;
	archive md5_archive;
	string title;
	string package;
	unsigned long length_smpl;
	unsigned long trim_start_smpl;
	unsigned long trim_end_smpl;
	unsigned long fade_in_smpl;
	unsigned long fade_out_smpl;
};

struct advert {
	bool isNull;
};

struct script {
	bool isNull;
	string title;
	string owner;
	string summary;
	string content;
	unsigned long length_smpl;
};

struct email {
    string from;
    string subject;
    string received;
    string body;
    bool flag;
    string id;
};

enum eventType { 
	EVENT_TYPE_PLAY, 
	EVENT_TYPE_STOP, 
	EVENT_TYPE_SMPL,
	EVENT_TYPE_MAX_SMPL,
	EVENT_TYPE_END};

struct eventData {
	unsigned short id; //shouldnt be needed now
	enum eventType t;
	long smpl;
	unsigned short page;
	unsigned short index;
};

enum showPlanState {
	SHOWPLAN_STATE_UNLOADED,
	SHOWPLAN_STATE_LOADED,
	SHOWPLAN_STATE_FINISHED};

track dps_getTrack(Connection *C, string md5);
string dps_itoa(long num);
string dps_strTrim(string *Str);
string dps_strPcase(string *Str);
string dps_strNum(long num, unsigned int digits);
string dps_prettyTime(long samples);
long dps_current_time();
#endif
