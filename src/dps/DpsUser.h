#include <string>

#include "DpsObject.h"

/**
 * Represents a user on the Digital Playout System.
 */
class DpsUser : public DpsObject {
	public:
		DpsUser(unsigned int pId = 0);
		DpsUser(const DpsUser& pSrc);
		virtual ~DpsUser();
		
		bool operator==(const DpsUser& pSrc);
		bool operator!=(const DpsUser& pSrc);
		DpsUser& operator=(const DpsUser& pSrc);
		
	private:
		unsigned int mId;
		std::string mName;
		
};
