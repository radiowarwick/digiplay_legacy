/*
 * DPS Object
 * DpsObject.h
 * Base class for all DPS objects
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
#ifndef CLASS_DPS_OBJECT
#define CLASS_DPS_OBJECT

#include <string>
#include <vector>
#include <map>

#include "dps.h"

#define DB_NOT_CONNECTED 1
#define DB_NO_SUCH_TRACK 2

class DataAccess;

enum DpsObjectType {
    DPS_OBJECT, 
    DPS_HASH, DPS_TIME, DPS_DATE, DPS_USER, DPS_GROUP,
    DPS_SHOWPLAN, DPS_SHOWITEM, 
    DPS_AUDIOITEM, DPS_SCRIPTITEM
};

typedef unsigned int TDpsId;

/**
 * Base class for the Dps class hierarchy.
 */
class DpsObject {
    public:
        DpsObject();
        virtual ~DpsObject();
        
        virtual enum DpsObjectType getType();

    	static std::string itoa(unsigned int pValue, unsigned int pLength = 0);
    	static unsigned int atoi(std::string pString);

    protected:
        static DataAccess* mDB;
        
        //int mId;
        enum DpsObjectType mType;

    private:

};



#endif
