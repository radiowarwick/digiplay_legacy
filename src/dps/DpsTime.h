/*
 * DPS Time
 * DpsTime.h
 * Stores and formats a time.
 *
 * Copyright (c) 2006-2009 Chris Cantwell
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
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
