#ifndef DPS_H
#define DPS_H

#include <string>
using namespace std;

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
    unsigned long length_smpl;
    unsigned long trim_start_smpl;
    unsigned long trim_end_smpl;
    unsigned long fade_in_smpl;
    unsigned long fade_out_smpl;
};

enum eventType { 
	EVENT_TYPE_PLAY, 
	EVENT_TYPE_STOP, 
	EVENT_TYPE_SMPL,
	EVENT_TYPE_MAX_SMPL };

struct eventData {
	unsigned short id;
	enum eventType t;
	long smpl;
	short index;
};

#endif
