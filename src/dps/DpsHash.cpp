#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

#include "DpsHash.h"

/* =======================================================================
 * DpsHash
 * =======================================================================
 */
DpsHash::DpsHash() 
		: DpsObject	() {
	mType = DPS_HASH;
	mData.push_back(itoa(rand()));
}

DpsHash::DpsHash(const string& pStr) 
		: DpsObject () {
	mType = DPS_HASH;
	mData.push_back(itoa(rand()));
	mData.push_back(pStr);
}

DpsHash::DpsHash(const unsigned int& pInt)
		: DpsObject () {
	mType = DPS_HASH;
	mData.push_back(itoa(rand()));
	mData.push_back(itoa(pInt));
}

DpsHash::DpsHash(const DpsHash& pSrc) 
		: DpsObject (),
		  mData		(pSrc.mData) {
	mType = DPS_HASH;
}

DpsHash::~DpsHash() {
	
}

bool DpsHash::operator==(const DpsHash& pSrc) const {
	if (mData == pSrc.mData) {
		return true;
	}
	return false;
}

bool DpsHash::operator!=(const DpsHash& pSrc) const {
	return !operator==(pSrc);
}

DpsHash& DpsHash::operator=(const DpsHash& pSrc) {
	mData = pSrc.mData;
	return *this;
}

DpsHash& operator<<(DpsHash& pDest, string pStr) {
	pDest.mData.push_back(pStr);
	return pDest;
}

DpsHash& operator<<(DpsHash& pDest, unsigned int pInt) {
	pDest.mData.push_back(DpsObject::itoa(pInt));
	return pDest;
}
