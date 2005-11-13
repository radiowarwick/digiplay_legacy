/* Track info Editor Header
 * trackedit.h
 *
 * Imports track data from .info file, allows updates, and saves back to
 * .info file and inserts into database
 * (c) Copyright Chris Cantwell 2005
 */

#ifndef CLASS_TRACKINFO
#define CLASS_TRACKINFO

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "config_reader.h"

class trackinfo {
	public:
		trackinfo(Connection *newC, string md5);
		~trackinfo();
		string md5();
		string title();
		void title(string value);
		string artist();
		void artist(string value);
		string album();
		void album(string value);
		string reclibid();
		void reclibid(string value);
		short tracknum();
		void tracknum(short value);
		long length_ms();
		long trim_start();
		long trim_end();
	
		// File Processing Routines
		void readFromFile(); //Check for XML over INFO
		void readFromDB();
		void saveToFile();	//XML file
		void saveToDB();
		bool inDB();
		bool hasAudio();
		void flushMem();
		void clean();
		void audio_trim();
		
	private:
		string strTrim(string *Str);
		string strPcase(string *Str);
		string itoa(long num);

		string AUDIO_PATH;
		Connection *C;
		string strMD5;
		long lngArchive;
		long lngLengthSmpl;
		long lngStartSmpl;
		long lngEndSmpl;
		long lngIntroSmpl;
		long lngExtroSmpl;
		string *strTitle;
		string *strArtist;
		string *strAlbum;
		string *strRecLib;
		string *strOrigin;
		string *strTrack;
		string *strReleased;
		string *strLength;
};

#endif
