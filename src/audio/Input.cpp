#include <iostream>
using namespace std;

#include "Input.h"

Audio::Input::~Input() {

}

void Audio::Input::getAudio(short *audioData, unsigned long samples) {
    cout << "Input::getAudio" << endl;
}

void Audio::Input::receiveMessage(PORT inPort, MESSAGE message) {
    cout << "Input::receive" << endl;
}

void Audio::Input::play() {

}

void Audio::Input::stop() {

}

void Audio::Input::pause() {

}

void Audio::Input::seek(long sample) {

}

void Audio::Input::threadExecute() {

}
