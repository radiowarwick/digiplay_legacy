/*
 * DPS User 
 * DpsUser.h
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
#ifndef DPSUSER_H_
#define DPSUSER_H_

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

#endif
