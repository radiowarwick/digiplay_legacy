#include "Logger.h"
#include <FLAC++/encoder.h>
#include <sys/stat.h>
#include <fstream.h>

using namespace FLAC::Encoder;

int main(int argc,char *argv[]) {
	cout << "Digital Playout System FLAC Encoder" << endl;
	cout << "Copyright (c) 2005-2006 Radio Warwick" << endl;
	char* routine = "FLACcompress::main";
	char* filename = argv[1];
	File *E = new File();
	int samples=0;
	int blocksize=4608;
	FLAC__int32 buffer[blocksize];
	ifstream inFile;
	int read=0;
	char inBuffer[blocksize*2];
	struct stat results;

    // Configure logging
	Logger::setAppName("FLACcompress");
	Logger::setLogLevel(3);
	Logger::setDisplayLevel(2);
	
	string temp = "Compresssion of " + string(filename) + " started.";
	Logger::log(INFO,routine,temp.c_str(),1);

	temp = string(filename) + ".FLAC";
	E->set_filename(temp.c_str());
	E->set_channels(2);
	E->set_bits_per_sample(16);
	E->set_sample_rate(44100);
	E->set_blocksize(blocksize);
	E->set_max_lpc_order(8);
	E->set_min_residual_partition_order(3);
	E->set_max_residual_partition_order(3);
	E->set_do_mid_side_stereo(1);
	E->set_do_exhaustive_model_search(0);
	E->set_do_qlp_coeff_prec_search(0);
	E->set_verify(1);
	E->init();

	if (stat(filename, &results) == 0) {	
		inFile.open(filename, ios::in | ios::binary);
		while ( results.st_size - read > 0 ) {
			if ( results.st_size-read >= blocksize*2) {
				inFile.read(inBuffer, blocksize*2);
				samples = blocksize/2;
				read+=blocksize*2;
			}
			else {
				inFile.read(inBuffer, results.st_size - read);
				samples = (results.st_size - read) / 4;
				read = results.st_size;
			}
			for (int i=0; i < samples*2; i++) {
				buffer[i]=inBuffer[i*2]+inBuffer[i*2+1]*256;
			}
			E->process_interleaved(buffer, samples);
		}
		temp = string(filename) + ".FLAC";
		stat(temp.c_str(), &results);
		cout << "MB read: " << read/1024/1024 << endl;
		cout << "MB written: " << results.st_size/1024/1024 << endl;
		cout << "Compression ratio: " << 100-(results.st_size*100/read) << "%" << endl;
	}


	temp = "Compresssion of " + string(filename) + " finished.";
	Logger::log(INFO,routine,temp.c_str(),1);

	Logger::log(INFO,routine,"Cleaning up.",1);
	Logger::log(INFO,routine,"Import complete.",1);
}
