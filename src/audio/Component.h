#ifndef CLASS_COMPONENT
#define CLASS_COMPONENT

#include <vector>
using std::vector;

#include "Audio.h"
#include "Thread.h"
#include "AudioPacket.h"

class Counter;

/** Audio Component base class.
 * This provides a base for all audio components and implements functionality
 * such as interconnection of components and message passing.
 */
class Audio::Component : public Thread {
	public:
        /// Clean up all component mappings
		virtual ~Component();
        /// Places \c samples stereo samples of audio into \c audioData.
		virtual void getAudio(AudioPacket& audioData) =0;

        /// Connect a local port on this component to another component.
		bool connect(PORT localPort, Component *c, PORT remotePort);
        /// Disconnect a components connected to a local port
		void disconnect(PORT localPort);
        
        /// Stores a pointer to a counter object to update on getAudio
        void addCounter(Counter* C);
        /// Attempts to remove the counter from the list
        void removeCounter(Counter* C);

	protected:
        Component();
		virtual void threadExecute() =0;
        virtual void receiveMessage(PORT inPort, MESSAGE message) =0;
		
        /// Receive a message from a connected component
        void receive(PORT inPort, MESSAGE message);
        /// Send a message to a connected component
		void send(PORT outPort, MESSAGE message);

        /// Access a connected component
		Audio::Component* connectedDevice(PORT inPort);
        /// Access the list of connected component mappings
        const vector<ConnectionMapping>& connectedDevices() {return portMap;}
        const vector<Counter*>& connectedCounters() {return _counters;}

	private:
        /// Add a component mapping to this components mapping list
		bool createMapping(PORT localPort, Component *c, 
							PORT remotePort);
        /// Remove a component mapping from this components mapping list
		bool destroyMapping(PORT localPort, Component *c);

        /// Store the components port map and connected components
		vector<ConnectionMapping> portMap;
        /// Holds the current sample (exact specification dependant on context)
        SAMPLE _currentSample;
        /// Store the counters attached to this component
        vector<Counter*> _counters;
};
#endif
