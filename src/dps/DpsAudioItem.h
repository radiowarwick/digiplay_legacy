#ifndef DPSAUDIOITEM_H_
#define DPSAUDIOITEM_H_

#include <string>
#include <map>

#include "DpsObject.h"
#include "DpsTime.h"

/**
 * Represents an audio item on the Digital Playout System.
 */
class DpsAudioItem : public DpsObject {
	public:
		DpsAudioItem();
		DpsAudioItem(unsigned int pId);
		DpsAudioItem(std::string pMd5);
		DpsAudioItem(const DpsAudioItem& pSrc);
		virtual ~DpsAudioItem();
		
		bool operator==(const DpsAudioItem& pSrc) const;
		bool operator!=(const DpsAudioItem& pSrc) const;
		DpsAudioItem& operator=(const DpsAudioItem& pSrc);
		std::string operator[](std::string pKey) const;
		
		// Getters
		unsigned int getId() const;
		DpsTime getLength() const;
		
	protected:
		typedef std::map<std::string, std::string> TData;
		typedef TData::iterator TDataIt;
		typedef TData::const_iterator TDataConstIt;
		std::map<std::string, std::string> mData;		
};


#endif /*DPSAUDIOITEM_H_*/
