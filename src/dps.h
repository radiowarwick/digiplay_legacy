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
	unsigned short id;
	enum eventType t;
	long smpl;
	short index;
};

track dps_getTrack(Connection *C, string md5);
string dps_itoa(long num);
string dps_strTrim(string *Str);
string dps_strPcase(string *Str);
string dps_strNum(long num, unsigned int digits);
long dps_current_time();
#endif
