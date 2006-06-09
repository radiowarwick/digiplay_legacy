#ifndef CLASS_COMPONENT
#define CLASS_COMPONENT

#include <vector>
using namespace std;

#include "Audio.h"
#include "Thread.h"

class Audio::Component : public Thread {
	public:
		virtual ~Component();
		virtual void getAudio(short *audioData, int samples) =0;


		bool connect(PORT localPort, Component *c, PORT remotePort);
		bool connectRequest(PORT localPort, Component *c, PORT remotePort);
		void disconnect(PORT localPort);

	protected:
		virtual void threadExecute() =0;
		virtual void receive(PORT inPort, MESSAGE message) =0;
		
		void send(PORT outPort, MESSAGE message);

	private:
		void createMapping(PORT localPort, Component *c, 
							PORT remotePort);
		void destroyMapping(PORT localPort);
		void destroyMapping(Component *c, PORT remotePort);
		vector<ConnectionMapping> portMap;
};
#endif
