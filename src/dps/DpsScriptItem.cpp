/*
 * DPS Script Item
 * DpsScriptItem.cpp
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
#include <iostream>
using namespace std;

#include "DpsScriptItem.h"

/**
 * Constructor.
 * Creates a new script unassociated with a database entry.
 */
DpsScriptItem::DpsScriptItem() {
	
}


/**
 * Constructor.
 * Retrieves a script from the database with given ID.
 * @param	pId			ID of the entry to retrieve.
 */
DpsScriptItem::DpsScriptItem(unsigned int pId) {
	string SQL;
	PqxxResult R;
	try {
		SQL = "SELECT * FROM v_scripts WHERE id=" + itoa(pId);
		R = mDB->exec("DpsLoadScriptItem", SQL);
		mDB->abort("DpsLoadScriptItem");
	}
	catch (...) {
		throw SQLError(MKEX(itoa(pId)));
	}
	if (R.size() != 1) {
		throw DataError(MKEX(itoa(pId)));
	}
	mId = atoi(R[0]["id"].c_str());
	mTitle = string(R[0]["name"].c_str());
	mContent = string(R[0]["contents"].c_str());
	mLength = DpsTime(atoi(R[0]["length"].c_str()), DpsTime::Samples);
}


/**
 * Constructor.
 * Copies an existing script object.
 * @param	pSrc		Script to copy.
 */
DpsScriptItem::DpsScriptItem(const DpsScriptItem& pSrc) 
		: mId			(pSrc.mId),
		  mTitle		(pSrc.mTitle),
		  mContent		(pSrc.mContent),
		  mLength		(pSrc.mLength) {

}


/**
 * Destructor.
 */
DpsScriptItem::~DpsScriptItem() {
	
}


/**
 * Determine if two DpsScriptItems are the same.
 * @param	pSrc		DpsScriptItem to compare with.
 * @return				True if the DpsScriptItems are equal.
 */
bool DpsScriptItem::operator==(const DpsScriptItem& pSrc) const {
	if (mId == pSrc.mId &&
	    mTitle == pSrc.mTitle &&
		mContent == pSrc.mContent &&
		mLength == pSrc.mLength) {
			return true;
	}
	return false;
}


/**
 * Determine if two DpsScriptItems differ.
 * @param	pSrc		DpsScriptItem to compare with.
 * @return				True if the DpsScriptItems differ.
 */
bool DpsScriptItem::operator!=(const DpsScriptItem& pSrc) const {
	return !operator==(pSrc);	
}


/**
 * Sets a DpsScriptItem equal to another.
 * @param	pSrc		The DpsScriptItem to copy.
 * @returns				This script.
 */
DpsScriptItem& DpsScriptItem::operator=(const DpsScriptItem& pSrc) {
	mId = pSrc.mId;
	mTitle = pSrc.mTitle;
	mContent = pSrc.mContent;
	mLength = pSrc.mLength;
	return *this;
}


/**
 * Returns the ID of the script.
 * @returns				ID.
 */
unsigned int DpsScriptItem::getId() const {
	return mId;
}


/**
 * Returns the title of the script.
 * @returns				Title.
 */
std::string DpsScriptItem::getTitle() const {
	return mTitle;
}


/**
 * Returns the content of the script.
 * @returns				Content.
 */
std::string DpsScriptItem::getContent() const {
	return mContent;
}


/**
 * Returns the length of the script.
 * @returns				Length.
 */
DpsTime DpsScriptItem::getLength() const {
	return mLength;
}
