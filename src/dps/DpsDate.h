#include "DpsObject.h"
#include "DpsTime.h"

/**
 * Represents a date and time.
 */
class DpsDate : public DpsObject {
	public:
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
