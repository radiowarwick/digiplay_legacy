#include <iostream>
#include <string>
#include <map>
using namespace std;

#include "DpsAudioItem.h"

/* =======================================================================
 * DpsAudioItem
 * =======================================================================
 */
DpsAudioItem::DpsAudioItem() {
	
}

DpsAudioItem::DpsAudioItem(unsigned int pId) {
	string SQL;
	try {
		SQL = "SELECT * FROM v_audio WHERE id=" + itoa(pId);
		PqxxResult R = mDB->exec("DpsLoadAudioItem", SQL);
		mDB->abort("DpsLoadAudioItem");
		if (R.size() != 1) {
			cout << "Multiple items returned!" << endl;
			throw -1;
		}
		for (unsigned int i = 0; i < R.columns(); ++i) {
			mData[R[0][i].name()] = R[0][i].c_str();
		}
	}
	catch (...) {
		cout << "Error retrieving data for audioitem" << endl;
		throw -1;
	}
}

DpsAudioItem::DpsAudioItem(string pMd5) {
	string SQL;
	try {
		SQL = "SELECT * FROM v_audio WHERE md5='" + pMd5 + "'";
		PqxxResult R = mDB->exec("DpsLoadAudioItem", SQL);
		mDB->abort("DpsLoadAudioItem");
		if (R.size() != 1) {
			cout << "Multiple items returned!" << endl;
			throw -1;
		}
		for (unsigned int i = 0; i < R.columns(); ++i) {
			mData[R[0][i].name()] = R[0][i].c_str();
		}
	}
	catch (...) {
		cout << "Error retrieving data for audioitem" << endl;
		throw -1;
	}	
}

DpsAudioItem::DpsAudioItem(const DpsAudioItem& pSrc) 
		: mData		(pSrc.mData) {
	
}

DpsAudioItem::~DpsAudioItem() {
	
}

bool DpsAudioItem::operator==(const DpsAudioItem& pSrc) const {
	if (mData == pSrc.mData) {
		return true;
	}
	return false;
}

bool DpsAudioItem::operator!=(const DpsAudioItem& pSrc) const {
	return !operator==(pSrc);
}

DpsAudioItem& DpsAudioItem::operator=(const DpsAudioItem& pSrc) {
	mData = pSrc.mData;
	return *this;
}

string DpsAudioItem::operator[](string pKey) const {
/*	cout << "FIND [" << pKey << "]" << endl;
	for (TDataConstIt x = mData.begin(); x != mData.end(); x++) {
		cout << x->first << " = " << x->second << endl;
	} 
*/	TDataConstIt x = mData.find(pKey);
	if (x == mData.end()) {
		cout << "Failed to retrieve item " << pKey << endl;
		throw -1;
	}
	return x->second;
}

unsigned int DpsAudioItem::getId() const {
	return atoi(operator[]("id"));
}

DpsTime DpsAudioItem::getLength() const {
	unsigned int smpl = atoi(operator[]("end_smpl"))
						- atoi(operator[]("start_smpl"));
	return DpsTime(smpl, DpsTime::Samples);
}
