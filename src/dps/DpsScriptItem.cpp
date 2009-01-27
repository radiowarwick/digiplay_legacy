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

DpsScriptItem::DpsScriptItem() {
	
}

DpsScriptItem::DpsScriptItem(unsigned int pId) {
	string SQL;
	try {
		SQL = "SELECT * FROM v_scripts WHERE id=" + itoa(pId);
		PqxxResult R = mDB->exec("DpsLoadScriptItem", SQL);
		mDB->abort("DpsLoadScriptItem");
		if (R.size() != 1) {
			cout << "Multiple items returned!" << endl;
			throw -1;
		}
		mTitle = string(R[0]["name"].c_str());
		mContent = string(R[0]["contents"].c_str());
		mLength = DpsTime(atoi(R[0]["length"].c_str()), DpsTime::Samples);
	}
	catch (...) {
		cout << "Error retrieving data for audioitem" << endl;
		throw -1;
	}
}

DpsScriptItem::DpsScriptItem(const DpsScriptItem& pSrc) 
		: mTitle		(pSrc.mTitle),
		  mContent		(pSrc.mContent),
		  mLength		(pSrc.mLength) {

}

DpsScriptItem::~DpsScriptItem() {
	
}

bool DpsScriptItem::operator==(const DpsScriptItem& pSrc) const {
	if (mTitle == pSrc.mTitle &&
		mContent == pSrc.mContent &&
		mLength == pSrc.mLength) {
			return true;
	}
	return false;
}

bool DpsScriptItem::operator!=(const DpsScriptItem& pSrc) const {
	return !operator==(pSrc);	
}

DpsScriptItem& DpsScriptItem::operator=(const DpsScriptItem& pSrc) {
	mTitle = pSrc.mTitle;
	mContent = pSrc.mContent;
	mLength = pSrc.mLength;
	return *this;
}

std::string DpsScriptItem::getTitle() const {
	return mTitle;
}

std::string DpsScriptItem::getContent() const {
	return mContent;
}

DpsTime DpsScriptItem::getLength() const {
	return mLength;
}
