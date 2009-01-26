/*
 * DPS Hash
 * DpsHash.cpp
 * A hash for uniquely identifying instances of objects.
 *
 * Copyright (c) 2009 Chris Cantwell
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
#include <vector>
#include <cstdlib>
using namespace std;

#include "DpsHash.h"

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
