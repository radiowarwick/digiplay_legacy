/*
 * DPS Hash
 * DpsHash.h
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
#ifndef DPSHASH_H_
#define DPSHASH_H_

#include <string>
#include <vector>

#include "DpsObject.h"

/**
 * A Hash object for uniquely identifying other objects. The hash stores a
 * vector of items which are considered to uniquely identify an associated
 * object. The hash also adds a random element to help ensure uniqueness.
 */
class DpsHash : public DpsObject {
	public:
		SUB_EXCEPTION(		Error,		DpsObject::Error);
		
		DpsHash();
		DpsHash(const std::string& pStr);
		DpsHash(const unsigned int& pInt);
		DpsHash(const DpsHash& pSrc);
		~DpsHash();
		
		bool operator==(const DpsHash& pSrc) const;
		bool operator!=(const DpsHash& pSrc) const;
		DpsHash& operator=(const DpsHash& pSrc);
		
		friend DpsHash& operator<<(DpsHash& pDest, std::string pStr);
		friend DpsHash& operator<<(DpsHash& pDest, unsigned int pInt);
		
	private:
		std::vector<std::string> mData;
};

/// Augment a hash with a string.
DpsHash& operator<<(DpsHash& pDest, std::string pStr);

/// Augment a hash with an integer value.
DpsHash& operator<<(DpsHash& pDest, unsigned int pInt);

#endif
