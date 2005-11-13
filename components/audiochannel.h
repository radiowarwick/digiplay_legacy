#ifndef CLASS_AUDIOCHANNEL
#define CLASS_AUDIOCHANNEL

#include <vector>
#include <iostream>
#include <fstream>
#include "fcntl.h"
#include <string>
#include <algorithm>
#include "pthread.h"
using namespace std;

#include "config_reader.h"

#define CACHE_SIZE 1764000

class audiochannel;

/** Defines the parameters for a fade
 */
struct fadeSpecification {
	/// Sample at which the fade begins
    unsigned long start_smpl;
	/// Sample at which the fade ends
    unsigned long end_smpl;
	/// Amplitude at which to start the fade (in percent)
    float start_pct;
	/// Amplitude at which the fade should end
    float end_pct;
	/// Indicates whether the fade has been started
    bool started;
};

/** Defines the parameters for triggering another channel to play
 */
struct triggerSpecification {
	/// A Pointer to the audiochannel which is to be triggered
    audiochannel *ch;
	/// The sample this channel should reach before triggering
    unsigned long smpl;
};

/** Represents an audio channel \ audio source on a conventional mixer
 */
class audiochannel {
	    public:
			audiochannel();
			~audiochannel();

			/// Loads an audio file
			void load(string filename, long start_smpl, long end_smpl);

			/// Returns the state of the loaded audio track
			bool isLoaded();

			/// Initiates playing of the loaded audio file.
			void play();

			/// Pauses playback
			void pause();

			/// Resume playback
			void resume();

			/// Stops playback
			void stop();

			/// Seeks to the required sample in the audio file
			void seek(long position);

			/// Gets audio from the cache
			short getAudio(char* buffer, unsigned long bytes);

			/// Gets the current position in the audio file
			unsigned long getPos();
		
			/// Schedules a fade
			void scheduleFade(unsigned long start_smpl, float start_pct, unsigned long end_smpl, float end_pct);

			/// Schedules a trigger
			void scheduleTrigger(unsigned long smpl, audiochannel *ch);
			
			/// Sets the current volume setting
			void setVolume(float vol);

			/// Gets the current volume setting
			float getVolume(unsigned long smpl);
		
			/// Triggers other channels if appropriate
			void trigger(unsigned long smpl);

			/// Notify when playback has finished
			void notify();

			/// Notify when caching of the file has finished
			void notify_cache();
			
			void cache();
			
		private:
			char *audio_buffer;
			char *Cache_Start;
			char *Cache_End;
			char *Cache_Read;
			char *Cache_Write;
			unsigned long Cache_Free;
			pthread_t *Thread_Cache;
			bool mode_play;
			bool mode_cache;

			ifstream *f_handle;
			long f_start_byte;
			long f_end_byte;
			long f_length_byte;
			long f_pos_byte;
			long packet_size;

			vector<fadeSpecification*>* fades;
			vector<triggerSpecification*>* trigs;
			float volume;
};

void *thread_cache(void *ptr);

#endif
