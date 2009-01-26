/*
 * DPS User 
 * DpsUser.cpp
 * Represents a user on the DPS system
 *
 * Copyright (c) 2006-2009 Chris Cantwell
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
using namespace std;

#include "DpsUser.h"

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
