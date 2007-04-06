#include "AudioPacket.h"
using Audio::AudioPacket;

#include <iostream>
using namespace std;

AudioPacket::AudioPacket(SAMPLE size) {
    _size = size;
	_allocated = size;
    _start = 0;
    _data = new SAMPLEVAL[_size];
}

AudioPacket::~AudioPacket() {
    delete[] _data;
}

AudioPacket::AudioPacket(const AudioPacket &A) {
    _size = A._size;
    _start = A._start;
    _data = new SAMPLEVAL[_size];
    for (SAMPLE i = 0; i < _size; i++) {
        _data[i] = A._data[i];
    }
}

AudioPacket& AudioPacket::operator=(const AudioPacket &A) {
    if (_size != A._size) {
        delete[] _data;
        _data = new SAMPLEVAL[_size];
        _size = A._size;
    }
    _start = A._start;
    for (SAMPLE i = 0; i < _size; i++) {
        _data[i] = A._data[i];
    }
    return (*this);
}

SAMPLEVAL& AudioPacket::operator[] (SAMPLE index) {
    if (index >= _size) {
        cout << "OUT OF RANGE: " << index << endl;
    }
    return _data[index];
}

void AudioPacket::setSize(SAMPLE size) {
	if (size > _allocated) {
		throw;
	}
	_size = size;
}
