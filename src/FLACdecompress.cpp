/*
 * FLAC decompression test class
 * FLACdecompress.cpp
 * Decompress flac audio stream to file
 *
 * Copyright (c) 2006 Ian Liverton
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
