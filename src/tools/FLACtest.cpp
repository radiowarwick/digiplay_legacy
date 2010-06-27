#include "FLACdecompress.h"

int main(int argc,char *argv[]) {
	cout << "Digital Playout System FLAC Decoder" << endl;
	cout << "Copyright (c) 2005-2006 Radio Warwick" << endl;
	char* routine = "FLACtest::main";
	char* filename = argv[1];
	FLACdecompress *E = new FLACdecompress(string(argv[2]));
	struct stat results;

	string temp = "Decompresssion of " + string(filename) + ".FLAC started.";

	cout<<temp<<endl;

	temp = string(filename) + ".FLAC";
	E->set_filename(temp.c_str());
	E->init();
	
	E->process_until_end_of_file();
	E->finish();
	temp = "Decompresssion of " + string(filename) + ".FLAC finished.";
	cout<<temp<<endl;
	
}
