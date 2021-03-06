#include <iostream>
#include <cstring>
using namespace std;

#include "Thread.h"
#include "CircularCache.h"
using Audio::CircularCache;


/**
 * Creates a new cache with a given size.
 */
CircularCache::CircularCache(const unsigned long pSize) {
    mCacheSize = pSize;
    mCacheFree = mCacheSize;
    
    mCacheStart = new char[mCacheSize];
    if (mCacheStart == 0) {
        cout << "ERROR: Cannot allocate memory for mCache" << endl;
        throw -1;
    }
    mCacheEnd = mCacheStart + mCacheSize;
    mCacheRead = mCacheStart;
    mCacheWrite = mCacheStart;   
}


/**
 * Creates a new cache as a copy of another cache.
 */
CircularCache::CircularCache(const CircularCache& pSrc) {
    mCacheSize = pSrc.mCacheSize;
    mCacheFree = mCacheSize;
    
    mCacheStart = new char[mCacheSize];
    if (mCacheStart == 0) {
        cout << "ERROR: Cannot allocate memory for mCache" << endl;
        throw -1;
    }
    mCacheEnd = mCacheStart + mCacheSize;

    memcpy(mCacheStart, pSrc.mCacheStart, mCacheSize);
    mCacheRead = mCacheStart + (pSrc.mCacheRead - pSrc.mCacheStart);
    mCacheWrite = mCacheStart + (pSrc.mCacheWrite - pSrc.mCacheStart);
    
}


/**
 * Destructor.
 */
CircularCache::~CircularCache() {
    if (mCacheStart) delete[] mCacheStart;
}


/**
 * Assigns the contents of another cache to this one, adjusting the size if
 * necessary.
 */
CircularCache& CircularCache::operator=(const CircularCache& pSrc) {
    mCacheLock.lock();
    if (mCacheSize != pSrc.mCacheSize) {
        if (mCacheStart) delete[] mCacheStart;
        mCacheSize = pSrc.mCacheSize;
        mCacheStart = new char[mCacheSize];
        if (mCacheStart == 0) {
            cout << "ERROR: Cannot allocate memory for mCache: "
                 << mCacheSize << endl;
            mCacheLock.unlock();
            return *this;
        }
        mCacheEnd = mCacheStart + mCacheSize;
    }
    memcpy(mCacheStart, pSrc.mCacheStart, mCacheSize);
    mCacheRead = mCacheStart + (pSrc.mCacheRead - pSrc.mCacheStart);
    mCacheWrite = mCacheStart + (pSrc.mCacheWrite - pSrc.mCacheStart);
    mCacheLock.unlock();
    return *this;
}


/**
 * Puts data into the mCache.
 */
unsigned long CircularCache::write(unsigned long pSize, const char * pData) {
    //cout << "Write to cache" << endl;
    // lock the mCache
    mCacheLock.lock();

    if (mCacheFree < pSize) {
        pSize = mCacheFree;
    }
    
    if (mCacheRead > mCacheWrite) {
        memcpy(mCacheWrite, pData, pSize);
        mCacheWrite += pSize;
        mCacheFree -= pSize;
    }
    else {
        if ((unsigned long)(mCacheEnd - mCacheWrite) > pSize) {
            memcpy(mCacheWrite, pData, pSize);
            mCacheWrite += pSize;
            mCacheFree -= pSize;
        }
        else {
            unsigned int vRemain = mCacheEnd - mCacheWrite;
            memcpy(mCacheWrite, pData, vRemain);
            memcpy(mCacheStart, pData + vRemain, pSize - vRemain);
            mCacheWrite = mCacheStart + pSize - vRemain;
            mCacheFree -= pSize;
        }
    }
    mCacheLock.unlock();
    return pSize;
}


/**
 * Retrieves data from the mCache.
 */
unsigned long CircularCache::read(unsigned long pSize, char * pData) {
    // lock the mCache while we read from it
    mCacheLock.lock();

    // Check if there is enough audio
    if (mCacheSize - mCacheFree < pSize) {
        pSize = mCacheSize - mCacheFree;
    }

    // Memcpy the correct portions of the mCache depending on the location
    // of the read and write pointers. We know now there is at least pSize
    // data available to read.
    // First case is that write pointer is still in front of read pointer
    if (mCacheWrite > mCacheRead) {
        memcpy(pData, mCacheRead, pSize);
        mCacheRead += pSize;
        mCacheFree += pSize;
    }
    // Otherwise write pointer has looped behind read pointer.
    else {
        // If there's enough data before end of mCache, just copy
        if ((unsigned long)(mCacheEnd - mCacheRead) > pSize) {
            memcpy(pData, mCacheRead, pSize);
            mCacheRead += pSize;
            mCacheFree += pSize;
        }
        // Otherwise copy remaining data at end of mCache, and rest from the
        // beginning
        else {
            unsigned int vRemain = mCacheEnd - mCacheRead;
            memcpy(pData, mCacheRead, vRemain);
            memcpy(pData + vRemain, mCacheStart, pSize - vRemain);
            mCacheRead = mCacheStart + pSize - vRemain;
            mCacheFree += pSize;
        }
    }
    
    // unlock mCache
    mCacheLock.unlock();
    
    return pSize;
}


/**
 * Returns the free space in the mCache.
 */
unsigned long CircularCache::free() {
    return mCacheFree;
}


/**
 * Returns the size of the mCache.
 */
unsigned long CircularCache::size() {
    return mCacheSize;
}


/**
 * Clears the mCache.
 */
void CircularCache::clear() {
    mCacheRead = mCacheStart;
    mCacheWrite = mCacheStart;
    mCacheFree = mCacheSize;
}


/**
 * Seek forward/backwards a given number of bytes in the cache.
 */
void CircularCache::seek(int pShift) {
    if (pShift > int(mCacheSize - mCacheFree) || -pShift > int(mCacheFree)) {
        throw -1;
    }
    if (mCacheRead + pShift < mCacheStart) {
        mCacheRead = mCacheEnd + (mCacheRead - mCacheStart) + pShift;
    }
    else {
        mCacheRead += pShift;
    }
    mCacheFree += pShift;
}


/**
 * Locks the cache.
 */
void CircularCache::lock() {
    mCacheLock.lock();
}

/**
 * Unlock the cache.
 */
void CircularCache::unlock() {
    mCacheLock.unlock();
}
 
