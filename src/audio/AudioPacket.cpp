#include <iostream>
using namespace std;

#include "AudioPacket.h"
using Audio::AudioPacket;

/**
 * Creates a new AudioPacket of a given size. Memory is allocated to store
 * at most this number of samples.
 * @param   size    The size of the AudioPacket to create (mono samples).
 */
AudioPacket::AudioPacket(SAMPLE size) {
    _size = size;
	_allocated = size;
    _start = 0;
    _data = new SAMPLEVAL[_size];
}

/**
 * Creates a copy of an existing AudioPacket
 * @param   A       The existing AudioPacket to copy
 */
AudioPacket::AudioPacket(const AudioPacket &A) {
    _size = A._size;
    _start = A._start;
    _data = new SAMPLEVAL[_size];
    for (SAMPLE i = 0; i < _size; i++) {
        _data[i] = A._data[i];
    }
}

/**
 * Deallocates memory and cleans up.
 */
AudioPacket::~AudioPacket() {
    delete[] _data;
}

/**
 * Copies one AudioPacket into another.
 * @param   A       An existing AudioPacket
 * @returns         This AudioPacket
 */
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

/**
 * Returns a sample at a given index.
 * @param   index   The index of the requested sample.
 * @returns         Value of the requested sample.
 */
SAMPLEVAL& AudioPacket::operator[] (SAMPLE index) {
    if (index >= _size) {
        cout << "OUT OF RANGE: " << index << endl;
    }
    return _data[index];
}

/**
 * Sets the number of valid samples. This must be less than or equal to
 * the size of the AudioPacket on creation, or else an exception will occur.
 * @param   size    Number of valid samples.
 */
void AudioPacket::setSize(SAMPLE size) {
	if (size > _allocated) {
		throw;
	}
	_size = size;
}
