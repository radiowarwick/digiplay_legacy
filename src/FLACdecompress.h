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
