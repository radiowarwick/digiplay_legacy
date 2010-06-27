#ifndef CLASS_AUDIO_PROCESS_FADER
#define CLASS_AUDIO_PROCESS_FADER

#include <fstream>
#include <vector>
#include <map>
using std::vector;
using std::map;

#include "Process.h"
#include "Counter.h"

/** 
 * Audio fader processing module.
 * This module modifies the amplitude of audio pulled from the IN0 port
 * based on a piecewise linear function created by the specification of 
 * amplitude values at a set of user-specified nodes.
 * 
 * Nodes are added using the addNode member function.
 */
class Audio::ProcessFader : public Audio::Process {
    public:
        /// Create a new fader
        ProcessFader();
        /// Destructor
        ~ProcessFader();

        /// Retrieve a packet of audio from the component connected to IN0
        virtual void getAudio(AudioPacket* audioData);
        /// Process a message received from another component
        virtual void receiveMessage(PORT inPort, MESSAGE message);
		
        /// Perform tasks when a component is connected
		virtual void onPatch(PORT localPort) {}
        /// Perform tasks when a component is disconnected
		virtual void onUnpatch(PORT localPort) {}

        /// Set the amplitude as a percentage.
		void setLevel(double pct);
        /// Add a node to the amplitude function
		void addNode(SAMPLE smpl, double pct);
        /// Clear all nodes (Reset)
		void clearNodes();

   private:
		pthread_mutex_t nodes_lock;
		map<SAMPLE,double> nodes;
		double vol;
};

#endif
