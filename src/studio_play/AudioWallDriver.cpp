#include <string>

#include "Config.h"
#include "dps.h"

#include "AudioWall.h"

#include "AudioWallDriver.h"

AudioWallDriver::AudioWallDriver(unsigned short playerId) {
    count = 1;
    Config* conf = new Config("digiplay");
    std::string id = dps_itoa(playerId);
    std::string device = conf->getParam("channel_" + id);

    mixer = new Audio::ProcessMixer();
    player = new Audio::OutputDsp(device);
    mixer->connect(OUT0,player,IN0);
}

AudioWallDriver::~AudioWallDriver() {

}

void AudioWallDriver::addAudioWall(AudioWall *A) {
    bool result = mixer->connect(count,A,OUT0);
    if (result) ++count;
}
