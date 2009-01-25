using namespace std;

#include "DpsScriptItem.h"

/* =======================================================================
 * DpsScriptItem
 * =======================================================================
 */
DpsScriptItem::DpsScriptItem() {
	
}

DpsScriptItem::DpsScriptItem(unsigned int pId) {
	
}

DpsScriptItem::DpsScriptItem(const DpsScriptItem& pSrc) {
	
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
