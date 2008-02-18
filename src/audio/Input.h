#ifndef CLASS_AUDIO_INPUT
#define CLASS_AUDIO_INPUT

#include "Component.h"

/** 
 * Pure virtual base class for input components.
 * This class provides a base class from which to derive input components.
 */
class Audio::Input : public Audio::Component {
	public:
        /// Destructor
		virtual ~Input();
        /// Fills AudioPacket with data
		virtual void getAudio(AudioPacket* audioData) = 0;
        /// Changes to STATE_PLAY
		virtual void play() = 0;
        /// Changes to STATE_STOP
		virtual void stop() = 0;
        /// Changes to STATE_PAUSE
		virtual void pause() = 0;
        /// Seeks to a position in an input source
		virtual void seek(long sample) = 0;
        /// Process when a component is connected
		virtual void onConnect(PORT localPort) = 0;
        /// Process when a component is disconnected
		virtual void onDisconnect(PORT localPort) = 0;

	protected:
        /// Only allow derived classes to be created
        Input() {}
        /// Process messages received from other components
		virtual void receiveMessage(PORT inPort, MESSAGE message);

	private:

};

#endif
