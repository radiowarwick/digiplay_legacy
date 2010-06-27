#ifndef CLASS_AUDIO_AUDIOPACKET
#define CLASS_AUDIO_AUDIOPACKET

#include "Audio.h"

/** Container class for a packet of audio.
 * This class is used to pass audio between components along with information
 * about its context. This includes its start position in samples. The size of
 * the packet is customisable in Audio.h
 */
class Audio::AudioPacket {
    public:
        /// Constructs a new AudioPacket of a given size.
        AudioPacket(SAMPLE size);
        /// Copy constructor.
        AudioPacket(const AudioPacket &A);
        /// Destructor.
        ~AudioPacket();

        /// Copies an AudioPacket.
        AudioPacket& operator=(const AudioPacket &A);

        /// Retrieves a sample from an AudioPacket.
        SAMPLEVAL& operator[](SAMPLE index);

        /// Returns the number of samples in the AudioPacket.
        SAMPLE getSize() {return _size;}
        /// Returns the absolute index of the first sample in the AudioPacket
		SAMPLE getStart() {return _start;}
        /// Returns a pointer to the storage
		SAMPLEVAL* getData() {return _data;}
        /// Set the absolute index of the first sample in the AudioPacket
		void setStart(SAMPLE start) {_start = start;}
        /// Sets the number of valid samples stored in the AudioPacket
		void setSize(SAMPLE size);

    private: 
        SAMPLEVAL * _data;
        SAMPLE _start;
        SAMPLE _size;
		SAMPLE _allocated;
};

#endif
