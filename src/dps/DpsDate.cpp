#include "DpsDate.h"

/* =======================================================================
 * DpsDate
 * =======================================================================
 */
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

bool DpsDate::operator==(const DpsDate& pSrc) {
	if (mYear == pSrc.mYear &&
		mMonth == pSrc.mMonth &&
		mDay == pSrc.mDay &&
		mTime == pSrc.mTime) {
			return true;
	}
	return false;
}

bool DpsDate::operator!=(const DpsDate& pSrc) {
	return !operator==(pSrc);
}

DpsDate& DpsDate::operator=(const DpsDate& pSrc) {
	mYear = pSrc.mYear;
	mMonth = pSrc.mMonth;
	mDay = pSrc.mDay;
	mTime = pSrc.mTime;
	return *this;
}

unsigned int DpsDate::getYears() {
	return mYear;
}

unsigned int DpsDate::getMonths() {
	return mMonth;
}

unsigned int DpsDate::getDays() {
	return mDay;
}

DpsTime DpsDate::getTime() {
	return mTime;
}

