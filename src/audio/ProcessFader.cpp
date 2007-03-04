#include "ProcessFader.h"
using Audio::ProcessFader;
#include <iostream>
#include <cmath>
using namespace std;

ProcessFader::ProcessFader() {
	vol = 1.0;
}

ProcessFader::~ProcessFader() {

}

void ProcessFader::getAudio(AudioPacket& audioData) {
    connectedDevice(IN0)->getAudio(audioData);
	SAMPLE smpl;
	double x;
	for (SAMPLE i = 0; i < audioData.getSize(); i++) {
		x = static_cast<double>(audioData[i]);
		smpl = audioData.getStart() + i;
		for (unsigned int j = 0; j < Fades.size(); j++) {
			Fade F = Fades.at(j);
			if (F._start <= smpl && F._end > smpl) {
				vol = ((smpl - F._start)*(F._endpct - F._startpct))
						/ (F._end - F._start) + F._startpct;
				if (vol > 0.99) vol = 1.0;
				if (vol < 0.01) vol = 0.0;
			}
		}
		audioData[i] = static_cast<SAMPLEVAL>(x * vol);
	}
}

void ProcessFader::receiveMessage(PORT inPort, MESSAGE message) {
    send(OUT0,message);
}

void ProcessFader::threadExecute() {

}

void ProcessFader::addFade(Fade F) {
	Fades.push_back(F);
}

void ProcessFader::clearFades() {
	Fades.clear();
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
	operator=(F);
}

ProcessFader::Fade& ProcessFader::Fade::operator=(const Fade& F) {
	_start = F._start;
	_end = F._end;
	_startpct = F._startpct;
	_endpct = F._endpct;
    return (*this);
}
