#ifndef DPSSCRIPTITEM_H_
#define DPSSCRIPTITEM_H_

#include <string>

#include "DpsObject.h"
#include "DpsHash.h"
#include "DpsTime.h"

/**
 * Represents a script item in the Digital Playout System.
 */
class DpsScriptItem : public DpsObject {
	public:
		DpsScriptItem();
		DpsScriptItem(unsigned int pId);
		DpsScriptItem(const DpsScriptItem& pSrc);
		virtual ~DpsScriptItem();
		
		bool operator==(const DpsScriptItem& pSrc) const;
		bool operator!=(const DpsScriptItem& pSrc) const;
		DpsScriptItem& operator=(const DpsScriptItem& pSrc);
		
		std::string getTitle() const;
		std::string getContent() const;
		DpsTime getLength() const;
		
	protected:
		std::string mTitle;
		std::string mContent;
		DpsTime mLength;
		
};

#endif /*DPSSCRIPTITEM_H_*/
