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
#include "DataAccess.h"

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
    std::string name;
    std::string localPath;
    std::string remotePath;
};

enum ARCHIVE_COMPONENT {
    DPS_DB = 0,
    DPS_INBOX = 1,
    DPS_TRASH = 2
};

enum AUDIO_TYPE {
    AUDIO_TYPE_MUSIC = 0,
    AUDIO_TYPE_JINGLE = 1,
    AUDIO_TYPE_ADVERT = 2,
    AUDIO_TYPE_PREREC = 3
};

struct track {
    std::string id;
    bool isNull;
    unsigned short bin;
    unsigned int index;
    unsigned long audio_id;
    std::string md5;
	archive md5_archive;
    std::string title;
    std::string artist;
    std::string album;
	unsigned short tracknum;
    std::string reclibid;
    std::string origin;
    std::string release_date;
	bool censor;
    unsigned long length_smpl;
    unsigned long trim_start_smpl;
    unsigned long trim_end_smpl;
    unsigned long fade_in_smpl;
    unsigned long fade_out_smpl;
    enum AUDIO_TYPE type;
};

struct jingle {
	bool isNull;
    std::string md5;
	archive md5_archive;
    std::string title;
    std::string package;
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
    std::string title;
    std::string owner;
    std::string summary;
    std::string content;
	unsigned long length_smpl;
};

struct email {
    std::string from;
    std::string subject;
    std::string received;
    std::string body;
    bool flag;
    std::string id;
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

track dps_getTrack(std::string md5);
std::string dps_itoa(long num);
std::string& dps_strTrim(std::string& s);
std::string& dps_strLcase(std::string& s);
std::string dps_strPcase(std::string *Str);
std::string dps_strNum(long num, unsigned int digits);
std::string dps_prettyTime(long samples);
long dps_current_time();

#endif
