#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include "AudioWallManager.h"

AudioWallManager::AudioWallManager( Connection *C ) {

}

AudioWallManager::~AudioWallManager() {

}

void AudioWallManager::setUser( string username ) {
	_username = username;
}
