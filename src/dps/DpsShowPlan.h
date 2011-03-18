/*
 * DPS Showplan
 * DpsShowPlan.h
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
#ifndef DPSSHOWPLAN_H_
#define DPSSHOWPLAN_H_

#include <string>
#include <vector>

#include "DpsHash.h"
#include "DpsTime.h"
#include "DpsDate.h"
#include "DpsUser.h"
#include "DpsShowItem.h"

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
		SUB_EXCEPTION(		Error, 		DpsObject::Error);
		SUB_EXCEPTION_MSG(	SQLError, 	Error,
						"Failed to retrieve item: ");
		SUB_EXCEPTION_MSG(	DataError,	Error,
						"Multiple items returned for: ");
	    SUB_EXCEPTION_MSG(  EmptyPlan,  Error,
                        "The showplan is empty.");
        SUB_EXCEPTION_MSG(  NotFound,   Error,
                        "The item cannot be found in the showplan: ");
        SUB_EXCEPTION_MSG(  LastItem,   Error,
                        "This is the last item: ");
        SUB_EXCEPTION_MSG(  OutOfRange, Error,
                        "Requested item is out of range.");
                        
		// Constructors/Destructor
		DpsShowPlan();
		DpsShowPlan(const unsigned int pId);
		DpsShowPlan(const DpsShowPlan& pSrc);
		virtual ~DpsShowPlan();
		
		// Operators
		virtual bool operator==(const DpsShowPlan& pSrc) const;
		virtual bool operator!=(const DpsShowPlan& pSrc) const;
		virtual DpsShowPlan& operator=(const DpsShowPlan& pSrc);
		virtual DpsShowItem& operator[](unsigned int pIdx);
		
		// Get showplan information
		unsigned int getId() const;
		unsigned int getSize() const;
		DpsUser getOwner() const;
		DpsDate getCreationDate() const;
		DpsDate getShowDate() const;
		DpsTime getLength() const;
		bool isCompleted() const;
		bool isStored() const;
		bool isChanged() const;
		
		DpsShowItem& getItem(unsigned int pIdx);
		const DpsShowItem& getItem(const unsigned int pIdx) const;
		DpsShowItem& getItemByHash(const DpsHash& pHash);
		unsigned int getItemIndex(const DpsShowItem& pSrc);
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
