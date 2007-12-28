#ifndef CLASS_AUDIO_OUTPUT_RAW
#define CLASS_AUDIO_OUTPUT_RAW

#include <string>

#include "Output.h"

/** Class to output audio to a DSP device.
 * This class reads audio from it's connected component and writes it to the
 * specified dsp device.
 */
class Audio::OutputRaw : public Audio::Output {
	public:
		OutputRaw(std::string filename);
		~OutputRaw();

		void receiveMessage(PORT inPort, MESSAGE message);
		
		virtual void onConnect(PORT localPort);
		virtual void onDisconnect(PORT localPort);

		void threadExecute();

	private:
		string filename;
        enum STATE audioState;
		int audio;
};

#endif
