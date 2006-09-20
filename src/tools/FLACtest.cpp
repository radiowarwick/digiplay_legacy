#include "Logger.h"
#include "FLACdecompress.h"

int main(int argc,char *argv[]) {
	cout << "Digital Playout System FLAC Decoder" << endl;
	cout << "Copyright (c) 2005-2006 Radio Warwick" << endl;
	char* routine = "FLACtest::main";
	char* filename = argv[1];
	FLACdecompress *E = new FLACdecompress();
	struct stat results;

    // Configure logging
	Logger::setAppName("FLACtest");
	Logger::setLogLevel(3);
	Logger::setDisplayLevel(2);
	
	string temp = "Decompresssion of " + string(filename) + ".FLAC started.";
	Logger::log(INFO,routine,temp.c_str(),1);

	temp = string(filename) + ".FLAC";
	E->set_filename(temp.c_str());
	E->init();
	
	E->process_until_end_of_file();

	temp = "Decompresssion of " + string(filename) + ".FLAC finished.";
	Logger::log(INFO,routine,temp.c_str(),1);

	Logger::log(INFO,routine,"Cleaning up.",1);
	Logger::log(INFO,routine,"Import complete.",1);
}
