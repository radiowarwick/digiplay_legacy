#include "DpsGroup.h"

/* =======================================================================
 * DpsGroup
 * =======================================================================
 */
DpsGroup::DpsGroup(unsigned int pId) {
	
}

DpsGroup::DpsGroup(const DpsGroup& pSrc) {
	
}

DpsGroup::~DpsGroup() {
	
}

bool DpsGroup::operator==(const DpsGroup& pSrc) {
	if (mId == pSrc.mId &&
		mName == pSrc.mName) {
			return true;
	}
	return false;
}

bool DpsGroup::operator!=(const DpsGroup& pSrc) {
	return !operator==(pSrc);
}

DpsGroup& DpsGroup::operator=(const DpsGroup& pSrc) {
	mId = pSrc.mId;
	mName = pSrc.mName;
	return *this;
}
