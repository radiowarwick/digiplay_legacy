/*
 * DPS Time
 * DpsTime.cpp
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
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "DpsTime.h"

DpsTime::DpsTime() 
		: mHour		(0),
		  mMinute	(0),
		  mSecond	(0),
		  mSample   (0) {

}

DpsTime::DpsTime(unsigned int pTime, enum ETimeType pType) {
	mHour = 0;
	mMinute = 0;
	mSecond = 0;
	mSample = 0;
	if (pType >= DpsTime::Samples) {
		mSample = (pTime % 44100);
		pTime = (pTime - mSample)/44100;
	}
	if (pType >= DpsTime::Seconds) {
		mSecond = (pTime % 60);
		pTime = (pTime - mSecond)/60;
	}
	if (pType >= DpsTime::Minutes) {
		mMinute = (pTime % 60);
		pTime = (pTime - mMinute)/60;	
	}
	mHour = pTime;
}

DpsTime::DpsTime(unsigned int pHours, unsigned int pMinutes,
					unsigned int pSeconds) {
	mHour = pHours;
	mMinute = pMinutes;
	mSecond = pSeconds;
	mSample = 0;
}

DpsTime::DpsTime(const DpsTime& pSrc)
		: mHour		(pSrc.mHour),
		  mMinute	(pSrc.mMinute),
		  mSecond	(pSrc.mSecond),
		  mSample	(pSrc.mSample) {

}

DpsTime::~DpsTime() {
	
}

bool DpsTime::operator==(const DpsTime& pSrc) const {
	if (mHour == pSrc.mHour &&
		mMinute == pSrc.mMinute &&
		mSecond == pSrc.mSecond &&
		mSample == pSrc.mSample) {
			return true;
	}
	return false;
}

bool DpsTime::operator!=(const DpsTime& pSrc) const {
	return !operator==(pSrc);
}

bool DpsTime::operator>(const DpsTime& pSrc) const {
	return (inSamples() > pSrc.inSamples());
}

bool DpsTime::operator>=(const DpsTime& pSrc) const {
	return operator>(pSrc) || operator==(pSrc);
}

bool DpsTime::operator<(const DpsTime& pSrc) const {
	return (inSamples() < pSrc.inSamples());
}

bool DpsTime::operator<=(const DpsTime& pSrc) const {
	return operator<(pSrc) || operator==(pSrc);
}

DpsTime& DpsTime::operator=(const DpsTime& pSrc) {
	mHour = pSrc.mHour;
	mMinute = pSrc.mMinute;
	mSecond = pSrc.mSecond;
	mSample = pSrc.mSample;
	return *this;
}

unsigned int DpsTime::getHours() const {
	return mHour;
}

unsigned int DpsTime::getMinutes() const {
	return mMinute;
}

unsigned int DpsTime::getSeconds() const {
	return mSecond;
}

unsigned int DpsTime::getSamples() const {
	return mSample;
}

std::string DpsTime::getHms() const {
	return itoa(mHour) + ":" + itoa(mMinute,2) + ":" + itoa(mSecond,2);
}

std::string DpsTime::getHmsd() const {
	return getHms() + ":" + itoa(mSample/441);
}

unsigned long DpsTime::inSeconds() const {
	return 3600*mHour + 60*mMinute + mSecond;
}

unsigned long DpsTime::inSamples() const {
	return 44100*inSeconds() + mSample;
}
