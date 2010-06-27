#include "FLAC++/encoder.h"
#include "sys/stat.h"
#include <fstream>
#include <iostream>
using namespace std;

using namespace FLAC::Encoder;

int main(int argc,char *argv[]) {
	cout << "Digital Playout System FLAC Encoder" << endl;
	cout << "Copyright (c) 2005-2006 Radio Warwick" << endl;
//	char* routine = "FLACcompress::main";
	char* filename = argv[1];
	File *E = new File();
	int samples=0;
//	int blocksize=4608;
	int blocksize=8192;
	FLAC__int32* buffer = new FLAC__int32[blocksize];
	unsigned short *buffer_pointer = (unsigned short*)(buffer);
	ifstream inFile;
//	short *inBuffer16 = new short[blocksize];
	char *inBuffer = new char[blocksize*2];
	int read=0;
//	char inBuffer[blocksize*2];
	struct stat results;

	string temp = "Compresssion of " + string(filename) + " started.";
	cout << temp << endl;
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
		E->set_total_samples_estimate( results.st_size/4 );
		while ( results.st_size - read > 0 ) {
			if ( results.st_size-read >= blocksize*2) {
				inFile.read(inBuffer, blocksize*2);
				samples = blocksize/2;
				read+=blocksize*2;
			}
			else {
				inFile.read(inBuffer, results.st_size - read);
				cout << "Size: " << results.st_size << endl;
				cout << "Read before: " << read << endl;
				samples = (results.st_size - read) / 4;
				cout << "Samples: " << samples << endl;
				read = results.st_size;
				cout << "Read after: " << read << endl;
//				for (int i=samples*2; i<blocksize*2; i++){	//nice bodges :)
//					inBuffer[i]=0;
//				}
//				samples = blocksize/2;				//to here`
				buffer = new FLAC__int32[samples*2];
			}
			for (int i=0; i < samples*2; i++) {
				buffer[i]=inBuffer[i*2+1]*256;
				if (inBuffer[i*2] < 0)
					buffer[i]+=256;
				buffer[i]+=inBuffer[i*2];
//				printf("%X\n", buffer[i]);
		//		printf("Byte: %X Buffer: %d In buffer: %d\n", read-(samples-i)*4, buffer[i], inBuffer16[i]);
			}
//			cout << E->get_blocksize() << endl;
//			cout << "Samples: " << samples << endl;
			bool retval=E->process_interleaved(buffer, samples);
	//		cout << "Encoding returned: " << retval << endl;
			if ( !retval )
				cout << "Encoding error!" << endl;
		}
		E->finish();
		temp = string(filename) + ".FLAC";
		stat(temp.c_str(), &results);
		cout << "MB read: " << read/1024/1024 << endl;
		cout << "MB written: " << results.st_size/1024/1024 << endl;
		cout << "Compression ratio: " << 100-(results.st_size*100/read) << "%" << endl;
	}

	temp = "Compresssion of " + string(filename) + " finished.";
	cout << temp << endl;
}
