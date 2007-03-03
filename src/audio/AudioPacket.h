#ifndef CLASS_AUDIO_AUDIOPACKET
#define CLASS_AUDIO_AUDIOPACKET

#include "Audio.h"

class Audio::AudioPacket {
    public:
        AudioPacket(SAMPLE size);
        ~AudioPacket();
        AudioPacket(const AudioPacket &A);

        AudioPacket& operator=(const AudioPacket &A);

        SAMPLEVAL& operator[](SAMPLE index);

        SAMPLE getSize() {return _size;}

    private: 
        SAMPLEVAL * _data;
        SAMPLE _start;
        SAMPLE _size;
};

#endif
