/*
 * DPS Date
 * DpsDate.cpp
 * Stores and formats a date.
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
#include "DpsDate.h"

DpsDate::DpsDate() 
		: mYear		(0),
		  mMonth	(0),
		  mDay		(0),
		  mTime		(0, DpsTime::Samples) {

}

DpsDate::DpsDate(time_t pEpoch) {
	struct tm * tstruct;
	tstruct = localtime( &pEpoch );
	mYear = tstruct->tm_year + 1900;
	mMonth = tstruct->tm_mon;
	mDay = tstruct->tm_mday;
	unsigned int vHour = tstruct->tm_hour;
	unsigned int vMin = tstruct->tm_min;
	unsigned int vSec = tstruct->tm_sec;
	mTime = DpsTime(vHour, vMin, vSec);
}

DpsDate::DpsDate(unsigned int pYears, unsigned int pMonths, 
				unsigned int pDays, DpsTime pTime) {
	mYear = pYears;
	mMonth = pMonths;
	mDay = pDays;
	mTime = pTime;
}

DpsDate::DpsDate(const DpsDate& pSrc) 
		: mYear		(pSrc.mYear),
		  mMonth	(pSrc.mMonth),
		  mDay		(pSrc.mDay),
		  mTime		(pSrc.mTime) {

}

DpsDate::~DpsDate() {
	
}

bool DpsDate::operator==(const DpsDate& pSrc) const {
	if (mYear == pSrc.mYear &&
		mMonth == pSrc.mMonth &&
		mDay == pSrc.mDay &&
		mTime == pSrc.mTime) {
			return true;
	}
	return false;
}

bool DpsDate::operator!=(const DpsDate& pSrc) const {
	return !operator==(pSrc);
}

DpsDate& DpsDate::operator=(const DpsDate& pSrc) {
	mYear = pSrc.mYear;
	mMonth = pSrc.mMonth;
	mDay = pSrc.mDay;
	mTime = pSrc.mTime;
	return *this;
}

unsigned int DpsDate::getYears() const {
	return mYear;
}

unsigned int DpsDate::getMonths() const {
	return mMonth;
}

unsigned int DpsDate::getDays() const {
	return mDay;
}

DpsTime DpsDate::getTime() const {
	return mTime;
}

