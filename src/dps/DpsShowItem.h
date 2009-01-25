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
