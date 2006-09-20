#include "FLACdecompress.h"

	FLACdecompress::FLACdecompress() {
	}

	::FLAC__StreamDecoderWriteStatus FLACdecompress::write_callback(const::FLAC__Frame *frame, const FLAC__int32 *const 
buffer[]) {

		int i;
		unsigned char j,k,l,m;
		unsigned char *left=(unsigned char*)buffer[0];
		unsigned char *right=(unsigned char*)buffer[1];
		for(i=0; i<frame->header.blocksize; i++) {
			k=left[4*i];
			j=left[4*i+1];
			m=right[4*i];
			l=right[4*i+1];
			cout << j << k << l << m;
		}

		return ::FLAC__StreamDecoderWriteStatus(FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE);
	}
	void FLACdecompress::metadata_callback(const::FLAC__StreamMetadata *metadata) {
	}
	void FLACdecompress::error_callback(::FLAC__StreamDecoderErrorStatus status) {
	cout << "Error " << status << endl;
	}
