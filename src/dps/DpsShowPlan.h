#ifndef DPSSHOWPLAN_H_
#define DPSSHOWPLAN_H_

#include <string>
#include <vector>

/**
 * Represents a show plan.
 *
 * This class stores the items of a showplan, along with its database id and
 * name. An object of this type may load an existing showplan from the database
 * using the \a load routine, and save to the database using the \a save
 * routine. Standard operators are provided to allow access to individual
 * \a DpsShowItem.
 */

class DpsShowPlan : public DpsObject {
	public:
		// Constructors/Destructor
		DpsShowPlan();
		DpsShowPlan(const unsigned int pId);
		DpsShowPlan(const DpsShowPlan& pSrc);
		virtual ~DpsShowPlan();
		
		// Operators
		virtual bool operator==(const DpsShowPlan& pSrc);
		virtual bool operator!=(const DpsShowPlan& pSrc);
		virtual DpsShowPlan& operator=(const DpsShowPlan& pSrc);
		virtual DpsShowItem& operator[](unsigned int pIdx);
		
		// Get showplan information
		unsigned int getId();
		unsigned int getSize();
		DpsUser getOwner();
		DpsDate getCreationDate();
		DpsDate getShowDate();
		DpsTime getLength();
		bool isCompleted();
		bool isStored();
		bool isChanged();
		
		DpsShowItem& getItem(unsigned int pIdx);
		DpsShowItem& getItemByHash(const DpsHash& pHash);
		DpsShowItem& getNextItem(const DpsShowItem& pSrc);
		DpsShowItem& getFirstItem();
		DpsShowItem& getLastItem();
		
		// Items
		virtual void append(const DpsShowItem& pSrc);
		virtual void insert(const DpsShowItem& pSrc, unsigned int pPos);
		virtual void erase(unsigned int pPos);
		virtual void erase(const DpsShowItem& pSrc);
		virtual void clear();
		virtual void moveUp(const DpsShowItem& pSrc);
		virtual void moveDown(const DpsShowItem& pSrc);
		virtual void moveTop(const DpsShowItem& pSrc);
		virtual void moveBottom(const DpsShowItem& pSrc);
		
		// Operations
		void load(unsigned int pId);
		void save();
		void save(unsigned int pId);
	
	protected:
		virtual void showplanUpdated();
		
	private:
		typedef std::vector<DpsShowItem>::iterator TItemIt;
		std::vector<DpsShowItem> mItems;
		
		unsigned int mId;
		std::string mName;
		DpsUser mOwner;
		DpsDate	mCreationDate;
		DpsDate mShowDate;
		bool mCompleted;
		bool mStored;
		bool mChanged;
};

#endif /*DPSSHOWPLAN_H_*/
