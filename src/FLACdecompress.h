/*
 * FLAC decompression test class
 * FLACdecompress.h
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
#include "Logger.h"
#include "FLAC++/decoder.h"
#include "sys/stat.h"
#include <fstream>
using namespace std;

using namespace FLAC::Decoder;
using namespace std;

class FLACdecompress : public FLAC::Decoder::File {

	public:
		FLACdecompress();
		~FLACdecompress() {
		return;
		}
	protected:
		::FLAC__StreamDecoderWriteStatus write_callback(const::FLAC__Frame *frame, const FLAC__int32 *const buffer[]);
		void metadata_callback(const::FLAC__StreamMetadata *metadata);
		void error_callback(::FLAC__StreamDecoderErrorStatus status);
//	private:
			
};
