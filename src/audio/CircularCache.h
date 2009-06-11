#ifndef CIRCULARCACHE_H_
#define CIRCULARCACHE_H_

#include "Audio.h"

/** A FIFO cache for storing audio.
 * This class is used where the caching of audio is required. This is primarily
 * used in the input stages of an audio component chain, but may be used to
 * effect components such as a delay.
 */
class Audio::CircularCache {
    public:
        /// Construct a new circular cache of a given size.
        CircularCache(const unsigned long pSize);
        /// Construct a new circular cache by copying another one.
        CircularCache(const CircularCache& pSrc);
        /// Destructor
        ~CircularCache();
        
        /// Assigns the contents of one circular cache to another.
        CircularCache& operator=(const CircularCache &pSrc);
        
        /// Pushes data into the cache.
        unsigned long pushData(unsigned long pSize, const char * pData);
        /// Pulls the oldest data from the cache
        unsigned long popData(unsigned long pSize, char * pData);
        /// Reports the available space in the cache.
        unsigned long free();
        /// Reports the total size of the cache.
        unsigned long size();
        /// Clears the cache.
        void clear();
        /// Lock the cache.
        void lock();
        /// Unlock the cache.
        void unlock();
        
    private:
        char *mCacheStart;
        char *mCacheEnd;
        char *mCacheWrite;
        char *mCacheRead;
        unsigned long mCacheSize;
        unsigned long mCacheFree;
        CACHE_STATE mCacheState;
        ThreadMutex mCacheLock;
};

#endif
