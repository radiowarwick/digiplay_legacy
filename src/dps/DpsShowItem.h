/*
 * DPS Showplan Item
 * DpsShowItem.h
 * Manages a single showplan item and associated audio/script components.
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
#ifndef DPSSHOWITEM_H_
#define DPSSHOWITEM_H_

#include <iostream>
#include <string>

#include "DpsObject.h"
#include "DpsTime.h"
#include "DpsAudioItem.h"
#include "DpsScriptItem.h"

/**
 * Represents an item in a show plan.
 * 
 * An item may have both a DpsAudioItem and a DpsScriptItem associated with it.
 * Both are optional. Each item still has a name, comment and length.
 */
class DpsShowItem : public DpsObject {
	public:
		SUB_EXCEPTION(		Error, 		DpsObject::Error);
		SUB_EXCEPTION_MSG(	SQLError, 	Error,
						"Failed to retrieve showitem: ");
		SUB_EXCEPTION_MSG(	DataError,	Error,
						"Multiple items returned for showitem: ");

		enum EDpsShowItemState {
			Unloaded,
			Loaded,
			Finished
		};
	
		DpsShowItem();
		DpsShowItem(const unsigned int pId);
		DpsShowItem(const DpsAudioItem& pAudio);
		DpsShowItem(const DpsScriptItem& pScript);
		DpsShowItem(const DpsAudioItem& pAudio, const DpsScriptItem& pScript);
		DpsShowItem(const DpsShowItem& pSrc);
		virtual ~DpsShowItem();
		
		bool operator==(const DpsShowItem& pSrc);
		bool operator!=(const DpsShowItem& pSrc);
		DpsShowItem& operator=(const DpsShowItem& pSrc);
		
		// Getters
		DpsHash getHash() const;
		unsigned int getId() const;
		std::string getName() const;
		std::string getComment() const;
		DpsTime getLength() const;
		bool hasAudio() const;
		bool hasScript() const;
		DpsAudioItem getAudioItem();
		DpsScriptItem getScriptItem();
		bool isStored() const;
		enum EDpsShowItemState getState() const;
		
		// Setters
		void setName(const std::string pName);
		void setComment(const std::string pComment);
		void setLength(const DpsTime pLength);
		void setAudioItem(const DpsAudioItem& pAudioItem);
		void setScriptItem(const DpsScriptItem& pScriptItem);
		void setState(const enum EDpsShowItemState pState);
		
	private:
		void makeHash();
		void loadItem(const unsigned int pId);
		
		DpsHash mObjectHash;
		unsigned int mId;
		std::string mName;
		std::string mComment;
		DpsTime mLength;
		bool mHasAudioItem;
		bool mHasScriptItem;
		DpsAudioItem mAudioItem;
		DpsScriptItem mScriptItem;
		bool mStored;
		enum EDpsShowItemState mState;
};

#endif /*DPSSHOWITEM_H_*/
