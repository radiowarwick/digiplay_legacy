#ifndef DPSHASH_H_
#define DPSHASH_H_

#include <string>
#include <vector>

#include "DpsObject.h"

/**
 * A Hash object for uniquely identifying other objects
 */
class DpsHash : public DpsObject {
	public:
		DpsHash();
		DpsHash(const std::string& pStr);
		DpsHash(const unsigned int& pInt);
		DpsHash(const DpsHash& pSrc);
		~DpsHash();
		
		bool operator==(const DpsHash& pSrc) const;
		bool operator!=(const DpsHash& pSrc) const;
		DpsHash& operator=(const DpsHash& pSrc);
		friend DpsHash& operator<<(DpsHash& pDest, std::string pStr);
		friend DpsHash& operator<<(DpsHash& pDest, unsigned int pInt);
		
	private:
		std::vector<std::string> mData;
};
DpsHash& operator<<(DpsHash& pDest, std::string pStr);
DpsHash& operator<<(DpsHash& pDest, unsigned int pInt);

#endif
