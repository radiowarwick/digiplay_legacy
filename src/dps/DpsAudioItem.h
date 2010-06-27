/*
 * DPS Audio Item
 * DpsAudioItem.h
 * Manages an audio item on the DPS system.
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
#ifndef CLASS_DPSAUDIOITEM
#define CLASS_DPSAUDIOITEM

#include <string>
#include <map>

#include "Exception.h"
#include "DpsObject.h"
#include "DpsTime.h"



/**
 * Represents an audio item on the Digital Playout System. This class manages
 * the storage, retrieval and manipulation of data associated to a particular
 * audio item on the system (track, jingle, advert, prerec, etc).
 */
class DpsAudioItem : public DpsObject {
	public:
		SUB_EXCEPTION(		Error,		DpsObject::Error);
		SUB_EXCEPTION_MSG(	SQLError, 	Error,
						"Failed to retrieve item: ");
		SUB_EXCEPTION_MSG(	DataError,	Error,
						"Multiple items returned for: ");

		DpsAudioItem();
		DpsAudioItem(unsigned int pId);
		DpsAudioItem(std::string pMd5);
		DpsAudioItem(const DpsAudioItem& pSrc);
		virtual ~DpsAudioItem();
		
		bool operator==(const DpsAudioItem& pSrc) const;
		bool operator!=(const DpsAudioItem& pSrc) const;
		DpsAudioItem& operator=(const DpsAudioItem& pSrc);
		std::string operator[](std::string pKey) const;
		
		unsigned int getId() const;
		DpsTime getLength() const;
		
	protected:
		typedef std::map<std::string, std::string> TData;
		typedef TData::iterator TDataIt;
		typedef TData::const_iterator TDataConstIt;
		std::map<std::string, std::string> mData;		
};


#endif
