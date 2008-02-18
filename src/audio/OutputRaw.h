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
        /// Create an output component to write to a file
		OutputRaw(std::string filename);
        /// Destructor
		~OutputRaw();

        /// Process messages received from other components
		void receiveMessage(PORT inPort, MESSAGE message);
		
        /// Perform tasks when a component is connected
		virtual void onConnect(PORT localPort);
        /// Perform tasks when a component is disconnected
		virtual void onDisconnect(PORT localPort);

        /// Thread to process audio into file
		void threadExecute();

	private:
		string filename;
        enum STATE audioState;
		int audio;
};

#endif
