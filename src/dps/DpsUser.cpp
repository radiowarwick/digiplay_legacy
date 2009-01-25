#include <string>
using namespace std;

#include "DpsUser.h"

/* =======================================================================
 * DpsUser
 * =======================================================================
 */
DpsUser::DpsUser(unsigned int pId) {
	
}

DpsUser::DpsUser(const DpsUser& pSrc) {
	
}

DpsUser::~DpsUser() {
	
}

bool DpsUser::operator==(const DpsUser& pSrc) {
	if (mId == pSrc.mId &&
		mName == pSrc.mName) {
			return true;
	}
	return false;
}

bool DpsUser::operator!=(const DpsUser& pSrc) {
	return !operator==(pSrc);
}

DpsUser& DpsUser::operator=(const DpsUser& pSrc) {
	mId = pSrc.mId;
	mName = pSrc.mName;
	return *this;
}
