/*
 * DPS Showplan Item
 * DpsShowItem.cpp
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
#include <iostream>
#include <string>
using namespace std;

#include "DpsShowItem.h"

DpsShowItem::DpsShowItem() 
		: DpsObject		(),
		  mId			(0),
		  mName         (""),
		  mComment      (""),
		  mLength       (DpsTime(0, DpsTime::Samples)),
		  mHasAudioItem (false),
		  mHasScriptItem(false),
		  mAudioItem	(DpsAudioItem()),
		  mScriptItem	(DpsScriptItem()), 
		  mStored		(false),
		  mState		(DpsShowItem::Unloaded) {
	mType = DPS_SHOWITEM;
	makeHash();
}

DpsShowItem::DpsShowItem(const unsigned int pId) 
		: DpsObject		(),
		  mId			(pId),
		  mHasAudioItem	(false),
		  mHasScriptItem(false),
		  mState		(DpsShowItem::Unloaded) {
	mType = DPS_SHOWITEM;
	loadItem(pId);
	makeHash();
}

DpsShowItem::DpsShowItem(const DpsAudioItem& pAudio) 
		: DpsObject		(),
		  mId			(0),
		  mName			(pAudio["title"] + " (" + pAudio["artist"] + ")"),
		  mComment		(""),
		  mLength 		(pAudio.getLength()),
		  mHasAudioItem	(true),
		  mHasScriptItem(false),
		  mAudioItem	(pAudio),
		  mScriptItem	(DpsScriptItem()),
		  mStored		(false),
		  mState		(DpsShowItem::Unloaded) {
	mType = DPS_SHOWITEM;
	makeHash();
}

DpsShowItem::DpsShowItem(const DpsScriptItem& pScript) 
		: DpsObject		(),
		  mId			(0),
		  mName			(pScript.getTitle()),
		  mComment		(""),
		  mLength		(pScript.getLength()),
		  mHasAudioItem	(false),
		  mHasScriptItem(true),
		  mAudioItem	(DpsAudioItem()),
		  mScriptItem	(pScript),
		  mStored		(false),
		  mState		(DpsShowItem::Unloaded) {
	mType = DPS_SHOWITEM;
	makeHash();
}

DpsShowItem::DpsShowItem(const DpsAudioItem& pAudio, 
						 const DpsScriptItem& pScript) 
		: DpsObject		(),
		  mId			(0),
		  mName			(pAudio["title"] + " (" + pAudio["artist"] + ")"),
		  mComment		("Script: " + pScript.getTitle()),
		  mLength		(pAudio.getLength()),
		  mHasAudioItem (true),
		  mHasScriptItem(true),
		  mAudioItem	(pAudio),
		  mScriptItem	(pScript),
		  mStored		(false),
		  mState		(DpsShowItem::Unloaded) {
	mType = DPS_SHOWITEM;
	if (pAudio.getLength() > pScript.getLength()) {
		mLength = pAudio.getLength();
	}
	else {
		mLength = pScript.getLength();
	}
	makeHash();
}

DpsShowItem::DpsShowItem(const DpsShowItem& pSrc) 
        : DpsObject		(pSrc),
          mObjectHash	(pSrc.mObjectHash),
          mId			(pSrc.mId),
          mName			(pSrc.mName),
          mComment		(pSrc.mComment),
          mLength		(pSrc.mLength),
          mHasAudioItem	(pSrc.mHasAudioItem),
          mHasScriptItem(pSrc.mHasScriptItem),
          mAudioItem	(pSrc.mAudioItem),
          mScriptItem	(pSrc.mScriptItem),
          mStored		(pSrc.mStored), 
          mState		(pSrc.mState) {

}

DpsShowItem::~DpsShowItem() {

}

bool DpsShowItem::operator==(const DpsShowItem& pSrc) {
	if (mObjectHash == pSrc.mObjectHash) {
		return true;
	}
	return false;
/*	if (mName == pSrc.mName 
			&& mComment == pSrc.mComment
			&& mHasAudioItem == pSrc.mHasAudioItem
			&& mHasScriptItem == pSrc.mHasScriptItem ) {
		if (mHasAudioItem) {
			if (mAudioItem != pSrc.mAudioItem) {
				return false;
			}
		}
		if (mHasScriptItem) {
			if (mScriptItem != pSrc.mScriptItem) {
				return false;
			}
		}
		return true;
	}
	return false;
*/}

bool DpsShowItem::operator!=(const DpsShowItem& pSrc) {
    return !(operator==(pSrc));
}

DpsShowItem& DpsShowItem::operator=(const DpsShowItem& pSrc) {
	mObjectHash = pSrc.mObjectHash;
	mName = pSrc.mName;
	mComment = pSrc.mComment;
	mLength = pSrc.mLength;
	mHasAudioItem = pSrc.mHasAudioItem;
	mHasScriptItem = pSrc.mHasScriptItem;
	mAudioItem = pSrc.mAudioItem;
	mScriptItem = pSrc.mScriptItem;
	mStored = pSrc.mStored;
	mState = pSrc.mState;
	return *this;
}

DpsHash DpsShowItem::getHash() const {
	return mObjectHash;
}

unsigned int DpsShowItem::getId() const {
	if ( ! mStored ) {
		throw -1;
	}
    return mId;
}

string DpsShowItem::getName() const {
	return mName;
}

string DpsShowItem::getComment() const {
	return mComment;
}

DpsTime DpsShowItem::getLength() const {
	return mLength;
}

bool DpsShowItem::hasAudio() const {
	return mHasAudioItem;
}

bool DpsShowItem::hasScript() const {
	return mHasScriptItem;
}

DpsAudioItem DpsShowItem::getAudioItem() {
	return mAudioItem;
}

DpsScriptItem DpsShowItem::getScriptItem() {
	return mScriptItem;
}

bool DpsShowItem::isStored() const {
	return mStored;
}

enum DpsShowItem::EDpsShowItemState DpsShowItem::getState() const {
	return mState;
}

void DpsShowItem::setName(const string pName) {
	mName = pName;
}

void DpsShowItem::setComment(const string pComment) {
	mComment = pComment;
}

void DpsShowItem::setLength(const DpsTime pLength) {
	mLength = pLength;
}

void DpsShowItem::setAudioItem(const DpsAudioItem& pAudioItem) {
	mAudioItem = pAudioItem;
}

void DpsShowItem::setScriptItem(const DpsScriptItem& pScriptItem) {
	mScriptItem = pScriptItem;
}

void DpsShowItem::setState(const enum EDpsShowItemState pState) {
	mState = pState;
}

void DpsShowItem::makeHash() {
	mObjectHash << itoa(time(NULL)) 
				<< (mHasAudioItem ? "true" : "false")
				<< (mHasScriptItem ? "true" : "false") 
				<< mName << mComment;
}

void DpsShowItem::loadItem(const unsigned int pId) {
	string SQL;
	PqxxResult R;
	try {
		SQL = "SELECT * FROM showitems WHERE id=" + itoa(pId);
		R = mDB->exec("DpsShowPlanLoad", SQL);
		if (R.size() != 1) {
			throw -1;
		}
		mName = string(R[0]["title"].c_str());
		mComment = R[0]["comment"].c_str();
		mLength = DpsTime(atoi(R[0]["length"].c_str()), DpsTime::Seconds);
		mHasAudioItem = (string(R[0]["audioid"].c_str()) != "");
		mHasScriptItem = (string(R[0]["scriptid"].c_str()) != "");
		if (mHasAudioItem) {
			mAudioItem = DpsAudioItem(atoi(R[0]["audioid"].c_str()));
		}
		if (mHasScriptItem) {
			mScriptItem = DpsScriptItem(atoi(R[0]["scriptid"].c_str()));
		}
	}
	catch (...) {
		cout << "Error occured loading showplan item " << pId << endl;
		throw -1;
	}
}
