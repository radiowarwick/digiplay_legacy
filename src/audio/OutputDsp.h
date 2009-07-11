#ifndef CLASS_AUDIO_OUTPUT_DSP
#define CLASS_AUDIO_OUTPUT_DSP

#include <string>
using std::string;

#include "Output.h"

/** 
 * Class to output audio to a DSP device.
 * This class reads audio from it's connected component and writes it to the
 * specified dsp device. A facade for the dynamically loaded implementations
 */
class Audio::OutputDsp : public Audio::Output {
	public:
        /// Output to a DSP device
		OutputDsp(string channel);
        /// Destructor
		~OutputDsp();
		
	protected:
        /// Process messages received from other components
		void receiveMessage(PORT inPort, MESSAGE message);
		
        /// Perform tasks when a component is connected
		virtual void onPatch(PORT localPort);
        /// Perform tasks when a component is disconnected
		virtual void onUnpatch(PORT localPort);

	private:
		  /// Dynamically loaded implementation object + handle
		Audio::Output *pImpl;
		string deviceName;
		void *dlHandle;
};

#endif
