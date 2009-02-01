/*
 * DPS Date
 * DpsDate.h
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
#ifndef DPSDATE_H_
#define DPSDATE_H_

#include "DpsObject.h"
#include "DpsTime.h"

/**
 * Represents a date and time.
 */
class DpsDate : public DpsObject {
	public:
		SUB_EXCEPTION(		Error,		DpsObject::Error);
		SUB_EXCEPTION_MSG(	RangeError,	Error,
					"Data out of valid range: ");

		DpsDate();
		DpsDate(time_t pEpoch);
		DpsDate(unsigned int pYears, unsigned int pMonths, unsigned int pDays,
					DpsTime pTime = DpsTime(0, DpsTime::Samples));
		DpsDate(const DpsDate& pSrc);
		virtual ~DpsDate();
		
		bool operator==(const DpsDate& pSrc);
		bool operator!=(const DpsDate& pSrc);
		DpsDate& operator=(const DpsDate& pSrc);
		
		// Getters
		unsigned int getYears();
		unsigned int getMonths();
		unsigned int getDays();
		DpsTime getTime();
		
	private:
		unsigned int mYear;
		unsigned int mMonth;
		unsigned int mDay;
		DpsTime mTime;
};

#endif
