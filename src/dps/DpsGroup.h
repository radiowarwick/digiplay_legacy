/*
 * DPS Group 
 * DpsGroup.h
 * Represents a group on the DPS system
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
#ifndef DPSGROUP_H_
#define DPSGROUP_H_

#include "DpsObject.h"

/**
 * Represents a group of users on the Digital Playout System.
 */
class DpsGroup : public DpsObject {
	public:
		SUB_EXCEPTION(		Error,		DpsObject::Error);
		
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

#endif
