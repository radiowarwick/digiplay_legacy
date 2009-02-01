/*
 * DPS Script Item
 * DpsScriptItem.h
 * Manages a script item on the DPS system.
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
#ifndef CLASS_DPSSCRIPTITEM
#define CLASS_DPSSCRIPTITEM

#include <string>

#include "DpsObject.h"
#include "DpsHash.h"
#include "DpsTime.h"


/**
 * Represents a script item in the Digital Playout System.
 */
class DpsScriptItem : public DpsObject {
	public:
		SUB_EXCEPTION(		Error, 		DpsObject::Error);
		SUB_EXCEPTION_MSG(	SQLError, 	Error,
						"Failed to retrieve item: ");
		SUB_EXCEPTION_MSG(	DataError,	Error,
						"Multiple items returned for: ");

		DpsScriptItem();
		DpsScriptItem(unsigned int pId);
		DpsScriptItem(const DpsScriptItem& pSrc);
		virtual ~DpsScriptItem();
		
		bool operator==(const DpsScriptItem& pSrc) const;
		bool operator!=(const DpsScriptItem& pSrc) const;
		DpsScriptItem& operator=(const DpsScriptItem& pSrc);
		
		unsigned int getId() const;
		std::string getTitle() const;
		std::string getContent() const;
		DpsTime getLength() const;
		
	protected:
		unsigned int mId;
		std::string mTitle;
		std::string mContent;
		DpsTime mLength;
		
};

#endif
