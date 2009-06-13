#ifndef CLASS_COMPONENT
#define CLASS_COMPONENT

#include <vector>
using std::vector;

#include "Audio.h"
#include "Thread.h"
//#include "AudioPacket.h"

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
//		virtual void getAudio(AudioPacket* audioData __attribute__((unused)) ) {}

        /// Connect a local port on this component to another component.
		bool patch(PORT localPort, Component *c, PORT remotePort);
        /// Disconnect a components connected to a local port
		void unpatch(PORT localPort);
		/// Pure virtual function called when a connect has been made
		virtual void onPatch(PORT localPort __attribute__((unused))) {}
		/// Pure virtual function called when a disconnection has been made
		virtual void onUnpatch(PORT localPort __attribute__((unused))) {}

        /// Stores a pointer to a counter object to update on getAudio
        void addCounter(Counter* C);
        /// Attempts to remove the counter from the list
        void removeCounter(Counter* C);

	protected:
        /// Only derived classes from component can be created
        Component();
        /// Empty routine for thread by default
		virtual void threadExecute() {}
        /// Process messages received from other components
        virtual void receiveMessage(PORT inPort __attribute__((unused)), 
                                    MESSAGE message __attribute__((unused))) {}
		
        /// Receive a message from a connected component
        void receive(PORT inPort, MESSAGE message);
        /// Send a message to a connected component
		void send(PORT outPort, MESSAGE message);

        /// Access a connected component
		Audio::Component* connectedDevice(PORT inPort);
        /// Access the list of connected component mappings
        const vector<ConnectionMapping>& connectedDevices() {return portMap;}
        /// Access the list of connected counters
        const vector<Counter*>& connectedCounters() {return _counters;}

	private:
        /// Add a component mapping to this components mapping list
		bool createMapping(PORT localPort, Component *c, 
							PORT remotePort);
        /// Remove a component mapping from this components mapping list
		bool destroyMapping(PORT localPort, Component *c);

        /// Store the components port map and connected components
		vector<ConnectionMapping> portMap;
        /// Store the counters attached to this component
        vector<Counter*> _counters;
};
#endif
