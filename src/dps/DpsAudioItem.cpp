/*
 * DPS Audio Item
 * DpsAudioItem.cpp
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
#include <string>
#include <map>
using namespace std;

#include "DpsAudioItem.h"

/**
 * Constructor.
 * Creates a new audio item containing no data and unassocated with an entry
 * in the database.
 */
DpsAudioItem::DpsAudioItem() {
	
}


/**
 * Constructor.
 * Retrieves an audio item from the database with a given ID.
 * @param	pId			ID of the audio item to retrieve.
 */
DpsAudioItem::DpsAudioItem(unsigned int pId) {
	string SQL;
	PqxxResult R;
	try {
		SQL = "SELECT * FROM v_audio WHERE id=" + itoa(pId);
		R = mDB->exec("DpsLoadAudioItem", SQL);
		mDB->abort("DpsLoadAudioItem");
	}
	catch (...) {
		throw SQLError(MKEX(itoa(pId)));
	}
	if (R.size() != 1) {
		throw DataError(MKEX(itoa(pId)));
	}
	for (unsigned int i = 0; i < R.columns(); ++i) {
		mData[R[0][i].name()] = R[0][i].c_str();
	}
}


/**
 * Constructor.
 * Retrieve an audio item from the database with a given MD5.
 * @param	pMd5		MD5 hash of audio item to retrieve.
 */
DpsAudioItem::DpsAudioItem(string pMd5) {
	string SQL;
	PqxxResult R;
	try {
		SQL = "SELECT * FROM v_audio WHERE md5='" + pMd5 + "'";
		R = mDB->exec("DpsLoadAudioItem", SQL);
		mDB->abort("DpsLoadAudioItem");
	}
	catch (...) {
		throw SQLError(MKEX(pMd5));
	}	
	if (R.size() != 1) {
		throw DataError(MKEX(pMd5));
	}
	for (unsigned int i = 0; i < R.columns(); ++i) {
		mData[R[0][i].name()] = R[0][i].c_str();
	}
}


/**
 * Constructor.
 * Creates a copy of an existing DpsAudioItem.
 * @param	pSrc		An existing DpsAudioItem to copy.
 */
DpsAudioItem::DpsAudioItem(const DpsAudioItem& pSrc) 
		: mData		(pSrc.mData) {
	
}


/**
 * Destructor.
 */
DpsAudioItem::~DpsAudioItem() {
	
}


/**
 * Determine if another DpsAudioItem is the same as this one.
 * @param	pSrc		DpsAudioItem to compare with.
 * @returns				True if item is the same as this one.
 */
bool DpsAudioItem::operator==(const DpsAudioItem& pSrc) const {
	if (mData == pSrc.mData) {
		return true;
	}
	return false;
}


/**
 * Determine if another DpsAudioItem differs from this one.
 * @param	pSrc		DpsAudioItem to compare with.
 * @returns				True if the item differs from this one.
 */
bool DpsAudioItem::operator!=(const DpsAudioItem& pSrc) const {
	return !operator==(pSrc);
}


/**
 * Replaces the data of this DpsAudioItem with the data of another. Note that
 * after this operation the current DpsAudioItem will operate on the database
 * entry associated with the other DpsAudioItem. Thus, this operation makes no
 * changes to entries in the database.
 * @param	pSrc		Source DpsAudioItem.
 * @returns				Reference to this item.
 */
DpsAudioItem& DpsAudioItem::operator=(const DpsAudioItem& pSrc) {
	mData = pSrc.mData;
	return *this;
}


/**
 * Returns the requested data element.
 * @param	pKey		Name of the requested item.
 * @returns				The value associated with the name.
 */
string DpsAudioItem::operator[](string pKey) const {
	TDataConstIt x = mData.find(pKey);
	if (x == mData.end()) {
		throw Error(MKEX("No such data item '" + pKey + "'"));
	}
	return x->second;
}


/**
 * Returns the items database ID.
 * @returns				ID of the item in the DB.
 */
unsigned int DpsAudioItem::getId() const {
	return atoi(operator[]("id"));
}


/**
 * Returns the length of an audio item.
 * @returns				DpsTime containing the length.
 */
DpsTime DpsAudioItem::getLength() const {
	unsigned int smpl = atoi(operator[]("end_smpl"))
						- atoi(operator[]("start_smpl"));
	return DpsTime(smpl, DpsTime::Samples);
}
