#include "systemmanager.h"
#include "archivemanager.h"
#include "Logger.h"
#include <FLAC++/encoder.h>
#include <sys/stat.h>
#include <fstream.h>

using namespace FLAC::Encoder;

int main() {
	cout << "Digital Playout System FLAC Encoder" << endl;
	cout << "Copyright (c) 2005-2006 Radio Warwick" << endl;
	char* routine = "FLACcompress::main";
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
	
/*	Logger::log(INFO,routine,"Compress run started.",1);
	Logger::log(INFO,routine,"Loading music archives",1);
	systemmanager *Sys = new systemmanager();
	for (unsigned short i = 0; i < Sys->sizeArchive(); i++){
		Logger::log(INFO,routine,"Loading archive '" + Sys->atArchive(i)->spec().name + "'",1);
		Sys->atArchive(i)->load();
	}
	Logger::log(INFO,routine,"Adding new music",1);
	for (unsigned short i = 0; i < Sys->sizeArchive(); i++){
		archivemanager *A = Sys->atArchive(i);
		unsigned int count = A->size(DPS_INBOX);
		for (unsigned short j = 0; j < count; j++){

                        Logger::log(INFO,routine,"Importing " + A->at(DPS_INBOX,0).md5 + " [" + A->at($
                        A->add(0);

		}
		Logger::log(INFO,routine,"Compress of archive complete '" + A->spec().name + "'",1);
		Logger::log(INFO,routine,dps_itoa(A->size(DPS_DB)) + " tracks in archive",1);
	}
*/
	E->set_filename("/mnt/audio/73f06f6f6e5799134b625d1b676215d8.FLAC");
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

	if (stat("/mnt/audio/73f06f6f6e5799134b625d1b676215d8", &results) == 0) {	
		inFile.open("/mnt/audio/73f06f6f6e5799134b625d1b676215d8", ios::in | ios::binary);
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
		stat("/mnt/audio/73f06f6f6e5799134b625d1b676215d8.FLAC", &results);
		cout << "Read: " << read << endl;
		cout << "Written: " << results.st_size << endl;
	}

	Logger::log(INFO,routine,"Cleaning up.",1);
//	delete Sys;
	Logger::log(INFO,routine,"Import complete.",1);
}
