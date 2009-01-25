#ifndef DPSTIME_H_
#define DPSTIME_H_

#include <string>

#include "DpsObject.h"

/**
 * Represents a time.
 */
class DpsTime: public DpsObject {
	public:
		enum ETimeType {
			Hours,
			Minutes,
			Seconds,
			Samples
		};
		
		DpsTime();
		DpsTime(unsigned int pTime, enum ETimeType pType);
		DpsTime(unsigned int pHours, unsigned int pMinutes, 
				unsigned int pSeconds);
		DpsTime(const DpsTime& pSrc);
		virtual ~DpsTime();
		
		bool operator==(const DpsTime& pSrc) const;
		bool operator!=(const DpsTime& pSrc) const;
		bool operator>(const DpsTime& pSrc) const;
		bool operator>=(const DpsTime& pSrc) const;
		bool operator<(const DpsTime& pSrc) const;
		bool operator<=(const DpsTime& pSrc) const;
		DpsTime& operator=(const DpsTime& pSrc);
		
		// Getters
		unsigned int getHours() const;
		unsigned int getMinutes() const;
		unsigned int getSeconds() const;
		unsigned int getSamples() const;
		std::string  getHms() const;
		std::string  getHmsd() const;
		
	private:
		unsigned long inSeconds() const;
		unsigned long inSamples() const;
		
		unsigned int mHour;
		unsigned int mMinute;
		unsigned int mSecond;
		unsigned int mSample;
};

#endif
