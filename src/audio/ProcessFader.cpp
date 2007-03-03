#include "ProcessFader.h"
using Audio::ProcessFader;
#include <iostream>
#include <cmath>
using namespace std;

ProcessFader::ProcessFader() {

}

ProcessFader::~ProcessFader() {

}

void ProcessFader::getAudio(AudioPacket& audioData) {
    connectedDevice(IN0)->getAudio(audioData);
//    for (SAMPLE i = 0; i < audioData.getSize(); i++) {
//        audioData[i] = static_cast<short>(audioData[i]*1.0);
//            
//    }
}

void ProcessFader::receiveMessage(PORT inPort, MESSAGE message) {
    send(OUT0,message);
}

void ProcessFader::threadExecute() {

}

void ProcessFader::addFade(Fade& F) {

}

void ProcessFader::clearFades() {

}

// ProcessFader::Fade -----------------------------------------
ProcessFader::Fade::Fade(SAMPLE start, SAMPLE end, double startpct, double endpct) {
    if (start > end) throw;
    _start = start;
    _end = end;
    _startpct = startpct;
    _endpct = endpct;
}

ProcessFader::Fade::~Fade() {

}

ProcessFader::Fade::Fade(const Fade& F) {

}

ProcessFader::Fade& ProcessFader::Fade::operator=(const Fade& F) {
    return (*this);
}
