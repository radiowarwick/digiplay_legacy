#include "DpsObject.h"

/**
 * Represents a group of users on the Digital Playout System.
 */
class DpsGroup : public DpsObject {
	public:
		DpsGroup(unsigned int pId = 0);
		DpsGroup(const DpsGroup& pSrc);
		virtual ~DpsGroup();
		
		bool operator==(const DpsGroup& pSrc);
		bool operator!=(const DpsGroup& pSrc);
		DpsGroup& operator=(const DpsGroup& pSrc);
		
	private:
		unsigned int mId;
		std::string mName;
};
