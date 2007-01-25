#ifndef CLASS_COMPONENT
#define CLASS_COMPONENT

#include <vector>
using namespace std;

#include "Audio.h"
#include "Thread.h"

/** Audio Component base class.
 * This provides a base for all audio components and implements functionality
 * such as interconnection of components and message passing.
 */
class Audio::Component : public Thread {
	public:
        /// Clean up all component mappings
		virtual ~Component();
        /// Places \c samples stereo samples of audio into \c audioData.
		virtual void getAudio(short *audioData, unsigned long samples) =0;

        /// Connect a local port on this component to another component.
		bool connect(PORT localPort, Component *c, PORT remotePort);
        /// Disconnect a components connected to a local port
		void disconnect(PORT localPort);

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
        const vector<ConnectionMapping>* connectedDevices() {return portMap;}

	private:
        /// Process a reverse connection request from another component
		bool connectRequest(PORT localPort, Component *c, PORT remotePort);
        /// Add a component mapping to this components mapping list
		void createMapping(PORT localPort, Component *c, 
							PORT remotePort);
        /// Remove a component mapping from this components mapping list
		void destroyMapping(PORT localPort);
        /// Remove a component mapping from this components mapping list
		void destroyMapping(Component *c, PORT remotePort);
		vector<ConnectionMapping>* portMap;
};
#endif
