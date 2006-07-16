#include <iostream>
using namespace std;

#include "AudioWallManager.h"

AudioWallManager::AudioWallManager( Connection *C ) {

}

AudioWallManager::~AudioWallManager() {

}

AudioWallItem& AudioWallManager::operator[] (unsigned int index) {
	try {
		return at(index);
	}
	catch (int e) {
		throw e;
	}
}

AudioWallItem& AudioWallManager::at(unsigned int index) {
	if (index < _items.size()) {
		return _items.at(index);
	}
	else {
		throw AUDIOWALL_INDEX_OUT_OF_BOUNDS;
	}
}

void AudioWallManager::setUser( QString username ) {
	_username = username;
}

void AudioWallManager::changeWall( unsigned int index ) {

}
