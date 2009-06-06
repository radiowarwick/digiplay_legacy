/*
 * DPS Showplan
 * DpsShowPlan.cpp
 * Manages and manipulates a showplan on the system.
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
#include <vector>
#include <algorithm>
using namespace std;

#include "DpsObject.h"
#include "DpsShowPlan.h"

DpsShowPlan::DpsShowPlan() 
		: DpsObject		(),
		  mId			(0),
		  mName			(""),
		  mStored		(false),
		  mChanged		(false) {
	mType = DPS_SHOWPLAN;
}

DpsShowPlan::DpsShowPlan(const unsigned int pId) 
		: DpsObject		(),
		  mId			(0),
		  mStored		(false),
		  mChanged		(false) {
	load(pId);
}

DpsShowPlan::DpsShowPlan(const DpsShowPlan& pSrc) 
        : DpsObject(pSrc) {

}

DpsShowPlan::~DpsShowPlan() {

}

bool DpsShowPlan::operator==(const DpsShowPlan& pSrc) {
	if (mId == pSrc.mId &&
		mOwner == pSrc.mOwner && 
		mCreationDate == pSrc.mCreationDate &&
		mShowDate == pSrc.mShowDate &&
		mCompleted == pSrc.mCompleted) {
			return true;
	}
	return false;
}

bool DpsShowPlan::operator!=(const DpsShowPlan& pSrc) {
    return !(operator==(pSrc));
}

DpsShowPlan& DpsShowPlan::operator=(const DpsShowPlan& pSrc) {
    mItems = pSrc.mItems;
    mId = pSrc.mId;
    mOwner = pSrc.mOwner;
    mCreationDate = pSrc.mCreationDate;
    mShowDate = pSrc.mShowDate;
    mCompleted = pSrc.mCompleted;
    mStored = pSrc.mStored;
    mChanged = pSrc.mChanged;
    showplanUpdated();
    return *this;
}

DpsShowItem& DpsShowPlan::operator[](unsigned int pIdx) {
	if (pIdx >= mItems.size()) {
		throw OutOfRange(MKEX(""));
	}
    return mItems[pIdx];
}

unsigned int DpsShowPlan::getId() {
    return mId;
}

unsigned int DpsShowPlan::getSize() {
	return mItems.size();
}

DpsUser DpsShowPlan::getOwner() {
	return mOwner;
}

DpsDate DpsShowPlan::getCreationDate() {
	return mCreationDate;
}

DpsDate DpsShowPlan::getShowDate() {
	return mShowDate;
}

bool DpsShowPlan::isCompleted() {
	return mCompleted;
}

bool DpsShowPlan::isStored() {
	return mStored;
}

bool DpsShowPlan::isChanged() {
	return mChanged;
}

DpsShowItem& DpsShowPlan::getItem(unsigned int pIdx) {
	return operator[](pIdx);
}

DpsShowItem& DpsShowPlan::getItemByHash(const DpsHash& pHash) {
	for (unsigned int i = 0; i < mItems.size(); ++i) {
		if (mItems[i].getHash() == pHash) {
			return mItems[i];
		}
	}
	throw NotFound(MKEX(""));
}

DpsShowItem& DpsShowPlan::getNextItem(const DpsShowItem& pSrc) {
    TItemIt x = find(mItems.begin(), mItems.end(), pSrc);
	if (x == mItems.end()) {
		throw NotFound(MKEX(pSrc.getName()));
	}
	x++;
	if (x == mItems.end()) {
		throw LastItem(MKEX(pSrc.getName()));
	}
	return *x; 
}

DpsShowItem& DpsShowPlan::getFirstItem() {
	if (mItems.size() == 0) {
		throw EmptyPlan(MKEX(""));
	}
	return mItems[0];
}

DpsShowItem& DpsShowPlan::getLastItem() {
	if (mItems.size() == 0) {
		throw EmptyPlan(MKEX(""));
	}
	return mItems[mItems.size() - 1];
}

void DpsShowPlan::append(const DpsShowItem& pSrc) {
	mItems.push_back(pSrc);
	showplanUpdated();
}

void DpsShowPlan::insert(const DpsShowItem& pSrc, unsigned int pPos) {
	if (pPos >= mItems.size()) {
		throw -1;
	}
	mItems.insert(mItems.begin() + pPos, pSrc);
	showplanUpdated();
}

void DpsShowPlan::erase(unsigned int pPos) {
	if (pPos >= mItems.size()) {
		throw -1;
	}
	mItems.erase(mItems.begin() + pPos);
	showplanUpdated();
}

void DpsShowPlan::erase(const DpsShowItem& pSrc) {
	TItemIt vItem = find(mItems.begin(), mItems.end(), pSrc);
	if (vItem == mItems.end()) {
		return;
	}
	mItems.erase(vItem);
	showplanUpdated();
}

void DpsShowPlan::moveUp(const DpsShowItem& pSrc) {
	TItemIt vEnd = find(mItems.begin(), mItems.end(), pSrc);
	if (vEnd == mItems.begin() || vEnd == mItems.end()) {
		return;
	}
	TItemIt vStart = vEnd - 1;
	iter_swap(vStart, vEnd);
	showplanUpdated();
}

void DpsShowPlan::moveDown(const DpsShowItem& pSrc) {
	TItemIt vStart = find(mItems.begin(), mItems.end(), pSrc);
	if (vStart == mItems.end() - 1 || vStart == mItems.end()) {
		return;
	}
	TItemIt vEnd = vStart + 1;
	iter_swap(vStart, vEnd);
	showplanUpdated();
}

void DpsShowPlan::moveTop(const DpsShowItem& pSrc) {
	TItemIt vPos = find(mItems.begin(), mItems.end(), pSrc);
    TItemIt vStart = mItems.begin();
	if (vPos == mItems.begin() || vPos == mItems.end()) { 
		return;
	}
    while (vStart != mItems.end() 
            && vStart->getState() != DpsShowItem::Unloaded) {
        vStart++;
    }
	rotate(vStart, vPos, vPos + 1);
	showplanUpdated();
}

void DpsShowPlan::moveBottom(const DpsShowItem& pSrc) {
	TItemIt vPos = find(mItems.begin(), mItems.end(), pSrc);
	if (vPos == mItems.end() - 1 || vPos == mItems.end()) { 
		return;
	}
	rotate(vPos, vPos + 1, mItems.end());
	showplanUpdated();
}

void DpsShowPlan::clear() {
	mItems.clear();
	showplanUpdated();
}

void DpsShowPlan::load(unsigned int pId) {
	string SQL;
	PqxxResult R;
	try {
		// Check showplan exists in Database
		SQL = "SELECT * FROM showplans WHERE id=" + itoa(pId);
		R = mDB->exec("DpsShowPlanLoad",SQL);
	}
	catch (...) {
		throw SQLError(MKEX(itoa(pId)));
	}
	if (R.size() == 0) {
		throw DataError(MKEX(itoa(pId)));
	}
	mId = pId;
	mName = R[0]["name"].c_str();
	mOwner = DpsUser(atoi(R[0]["userid"].c_str()));
	mCreationDate = DpsDate(atoi(R[0]["creationdate"].c_str()));
	mShowDate = DpsDate(atoi(R[0]["showdate"].c_str()));
	mCompleted = (string(R[0]["completed"].c_str()) == "t");
	mStored = true;
	// Load items
	try {
		SQL = "SELECT id FROM showitems WHERE showplanid=" + itoa(pId) 
                + " ORDER BY position";
		R = mDB->exec("DpsShowPlanLoad",SQL);
    	mDB->abort("DpsShowPlanLoad");
	}
	catch (...) {
		throw SQLError(
				MKEX("Failed to load items from showplan ID " + itoa(pId)));
	}
    for (unsigned int i = 0; i < R.size(); i++) {
    	mItems.push_back(DpsShowItem(atoi(R[i]["id"].c_str())));
    }
	showplanUpdated();
}

void DpsShowPlan::save() {
	if ( ! mStored ) {
		throw -1;
	}
}

void DpsShowPlan::showplanUpdated() {
	
}
