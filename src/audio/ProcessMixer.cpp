#include "ProcessMixer.h"

#include <algorithm>
using namespace std;

Audio::ProcessMixer::ProcessMixer() {
    audioBuffer = new short[256];
    cacheStart = audioBuffer;
    cacheEnd = audioBuffer + 256;
    cacheRead = audioBuffer;
    cacheWrite = audioBuffer;
}

Audio::ProcessMixer::~ProcessMixer() {

}

void Audio::ProcessMixer::receiveMessage(PORT inPort, MESSAGE message) {
    for (unsigned int i = 0; i < connectedDevices()->size(); i++) {
        if (connectedDevices()->at(i).state == STATE_PLAY 
                && !isThreadActive()) {
            if (find(channelFlags.begin(), channelFlags.end(), int(inPort))
                    == channelFlags.end()) {
                channelFlags.push_back(int(inPort));
            }
            threadStart();
            break;
        }
        else {
            vector<int>::iterator x;
            if ((x=find(channelFlags.begin(), channelFlags.end(), int(inPort)))
                    != channelFlags.end()) {
                channelFlags.erase(x);
            }
        }
    }
}

void Audio::ProcessMixer::threadExecute() {
    for (unsigned int ch = 0; ch < channelFlags.size(); ch++) {
        

    }
}
