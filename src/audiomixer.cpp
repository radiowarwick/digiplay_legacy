
#include "audiomixer.h"
audiomixer::audiomixer() {
	channels = new vector<audiochannel*>;
	buffers = new vector<char*>;
}

audiomixer::~audiomixer() {
	for (unsigned short i = 0; i < channels->size(); i++)
		delete channels->at(i);
	delete channels;
	delete buffers;
}

/** This creates a new audiochannel object and returns it.
 * This audiochannel can later be accessed using the channel routine
 */
audiochannel* audiomixer::createChannel() {
	audiochannel *ch = new audiochannel();
	channels->push_back(ch);
	buffers->push_back(new char[BUFFER_SIZE]);
	return ch;
}

/** The associated audiochannel object is deleted and memory freed
 *  @param index Specifies the index of the channel to delete
 */
//TODO: delete any triggers relating to this channel
void audiomixer::destroyChannel(unsigned short index) {
	if (index >= channels->size()) {
		cout << "Requested mixer channel out of range!" << endl;
		abort();
	}
	delete channels->at(index);
	delete[] buffers->at(index);
	channels->erase(channels->begin() + index);
	buffers->erase(buffers->begin() + index);
}

short audiomixer::size() {
	return channels->size();
}

/** This allows access to the audiochannel object for a given index
 * This is needed to allow audio to be loaded, and to perform operations
 * such as play, pause, stop, seek, etc
 * @param index Specifies the index of the channel required
 * @returns Pointer to audiochannel object
 */
audiochannel* audiomixer::channel(unsigned short index) {
	cout << "index is: " << index << " channels: " << channels->size() << endl;
    if (index >= channels->size()) { 
        cout << "Requested mixer channel "<<index<<" out of range!" << endl;
        abort();
    }
	return channels->at(index);	
}

/** 
 * Returns a block of mixed audio samples of user specified size
 * into a user allocated buffer. It is guaranteed to fill the
 * buffer, filling it with zero-ed samples if there is no input to
 * the mixer. 
 * @param mix_buffer a user allocated buffer of length size
 * @param size length of mix_buffer in octets. 
 */
//TODO :: implement variable size buffer as given by 'size'
void audiomixer::getAudio(char* mix_buffer, unsigned int size) {
	// Get an audio packet from each channel
	for (unsigned int i = 0; i < channels->size(); i++)
		channels->at(i)->getAudio(buffers->at(i),BUFFER_SIZE);

	short* left;
	short* right;
	unsigned long currentPos = 0;
	float vol = 0.0;
	
	// Reset the output buffer
	memset(mix_buffer, 0, BUFFER_SIZE);
	// Transform the audio on each channel based on mixer settings
	for (unsigned short j = 0; j < channels->size(); j++) {
		if ((currentPos = channels->at(j)->getPos()) < 64) continue;
		currentPos -= BUFFER_SIZE/4 - 1;
		for (unsigned long i = 0; i < BUFFER_SIZE/4; i++) {
			currentPos++;
			vol = channels->at(j)->getVolume(currentPos);

			left = (short*)(buffers->at(j) + 4*i);
			right = (short*)(buffers->at(j) + 4*i + 2);
			*left = (short)(*left * vol / 100);
			*right = (short)(*right * vol / 100);

			channels->at(j)->trigger(currentPos);
		}
	}

	// Sum together audio
	// TODO: Compression if sum of volumes > 100%
	for (unsigned short i = 0; i < BUFFER_SIZE; i++)
		for (unsigned short j = 0; j < channels->size(); j++)
			mix_buffer[i] += buffers->at(j)[i];
	
	return;
}
