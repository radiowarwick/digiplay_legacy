#ifndef CLASS_AUDIO_PROCESS_FADER
#define CLASS_AUDIO_PROCESS_FADER

#include <vector>
#include <map>
using std::vector;
using std::map;

#include "Process.h"
#include "Counter.h"

/** Audio fader processing module
 */
class Audio::ProcessFader : public Audio::Process {
    public:
        ProcessFader();
        ~ProcessFader();

        virtual void getAudio(AudioPacket* audioData);

        virtual void receiveMessage(PORT inPort, MESSAGE message);
		
		virtual void onConnect(PORT localPort) {}
		virtual void onDisconnect(PORT localPort) {}

        virtual void threadExecute();

		void setLevel(double pct);
		void addNode(SAMPLE smpl, double pct);
		void clearNodes();

		void onSetSample() {}
		void onSetState() {}
		void onSetTotalSamples() {}

    private:
		pthread_mutex_t nodes_lock;
		map<SAMPLE,double> nodes;
        SAMPLEVAL * data;
		double vol;
};

#endif
