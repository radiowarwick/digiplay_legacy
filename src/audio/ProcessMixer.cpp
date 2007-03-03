#include "ProcessMixer.h"

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

Audio::ProcessMixer::ProcessMixer() {

}

Audio::ProcessMixer::~ProcessMixer() {

}

/** Receives messages to this component after they've been preprocessed by the
 * component base class. 
 */
void Audio::ProcessMixer::receiveMessage(PORT inPort, MESSAGE message) {
    // Determine if the current channel is already playing
    // see if it's in our active channel flag list
    vector<int>::iterator x;
    if ((x=find(channelFlags.begin(), channelFlags.end(), int(inPort)))
            == channelFlags.end() && message == PLAY) {
        // if it's not, and the message is PLAY, add it to list and allocate
        // the audio buffer
        cout << "Adding port " << inPort << endl;
        channelFlags.push_back(int(inPort));
        channelBuffers.push_back(AudioPacket(512));
    }
    else if (message == STOP) {
        // otherwise it exists so if message is STOP we disable this channel 
        // in the mixer and free it's resources
        cout << "Disabling port " << inPort << endl;
        int i = x - channelFlags.begin();
        channelFlags.erase(x);
        channelBuffers.erase(channelBuffers.begin() + i);
    }
    if (channelFlags.size() == 1 && message == PLAY) {
        cout << "Setting mixer state to play." << endl;
        send(OUT0,PLAY);
    }
    else if (channelFlags.size() == 0) {
        cout << "Setting mixer state to stop." << endl;
        send(OUT0,STOP);
    }
}

void Audio::ProcessMixer::getAudio(AudioPacket& buffer) {
    unsigned short N = channelFlags.size();
    short **chs = new short*[N];
    for (unsigned short i = 0; i < N; i++) {
//        channelBuffers.at(i)._size = 512;
        chs[i] = &(channelBuffers.at(i)[0]);
    }

    // request audio for each channel into separate buffers
    for (unsigned int i = 0; i < N; i++) {
        Component *ch = connectedDevice(channelFlags.at(i));
        ch->getAudio(channelBuffers.at(i));
    }
    // perform mix
    short M = 32768;
    double factor;
    // process each sample in turn
    for (unsigned int k = 0; k < buffer.getSize(); k++) {
        // start with zero sample
        buffer[k] = 0;
        for (unsigned int i = 0; i < N; i++) {
            // Set the scale factor for each channel to unity to start with
            factor = 1.0;
            // Compute scale factor for each channel based on the amplitude
            // of the remaining channels in the mix
            for (unsigned int j = i+1; j < N; j++) {
                factor *= (1.0 - abs(double(chs[j][k])/M));
            }
            // Scale and add this channel to the mix
            buffer[k] += short(chs[i][k]*factor);
        }
    }
    delete[] chs;
}


void Audio::ProcessMixer::threadExecute() {

}
