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

/**
 * Default constructor.
 * Just add an initial random number.
 */
DpsHash::DpsHash() 
		: DpsObject	() {
	mType = DPS_HASH;
	mData.push_back(itoa(rand()));
}


/**
 * Constructor.
 * Creates a new hash with a random number and given string.
 * @param	pStr		String to add to hash.
 */
DpsHash::DpsHash(const string& pStr) 
		: DpsObject () {
	mType = DPS_HASH;
	mData.push_back(itoa(rand()));
	mData.push_back(pStr);
}


/**
 * Constructor.
 * Creates a new hash with a random number and a given integer.
 * @param	pInt		Integer to add to hash.
 */
DpsHash::DpsHash(const unsigned int& pInt)
		: DpsObject () {
	mType = DPS_HASH;
	mData.push_back(itoa(rand()));
	mData.push_back(itoa(pInt));
}


/**
 * Copy constructor.
 * Copies an existing hash, but adds a random number to make it unique.
 * @param	pSrc		Existing hash to copy.
 */
DpsHash::DpsHash(const DpsHash& pSrc) 
		: DpsObject (),
		  mData		(pSrc.mData) {
	mType = DPS_HASH;
}


/**
 * Destructor.
 */
DpsHash::~DpsHash() {
	
}


/**
 * Determines if two hashes are identical.
 * @param	pSrc		Hash to compare with.
 * @returns				True if hashes are equal.
 */
bool DpsHash::operator==(const DpsHash& pSrc) const {
	if (mData == pSrc.mData) {
		return true;
	}
	return false;
}


/**
 * Determines if two hashes differ.
 * @param	pSrc		Hash to compare with.
 * @returns				True if hashes differ.
 */
bool DpsHash::operator!=(const DpsHash& pSrc) const {
	return !operator==(pSrc);
}


/**
 * Assignment. Assigns another hash to this one.
 * @param	pSrc		The Hash to assign.
 * @returns				A reference to the current hash.
 */
DpsHash& DpsHash::operator=(const DpsHash& pSrc) {
	mData = pSrc.mData;
	return *this;
}


/**
 * Add a string to the hash. (non-member function)
 * @param	pDest		The hash to augment.
 * @param	pStr		The string to add to the hash.
 * @returns				A reference to the hash.
 */
DpsHash& operator<<(DpsHash& pDest, string pStr) {
	pDest.mData.push_back(pStr);
	return pDest;
}


/**
 * Add an integer to the hash. (non-member function)
 * @param	pDest		The hash to augment.
 * @param	pInt		The integer to add to the hash.
 * @returns				A reference to the hash.
 */
DpsHash& operator<<(DpsHash& pDest, unsigned int pInt) {
	pDest.mData.push_back(DpsObject::itoa(pInt));
	return pDest;
}
