/*
 * DPS Objects
 * DpsObject.h
 * The hierarchy of DPS objects based on the DpsObject base class
 *
 * Copyright (c) 2006 Chris Cantwell
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
    DPS_OBJECT, DPS_SHOWPLAN, DPS_SHOWITEM, 
    DPS_SHOWTRACK, DPS_SHOWJINGLE, DPS_SHOWADVERT, DPS_SHOWNOTE,
    DPS_SHOWSCRIPT, DPS_AWSET
};

/**
 * Base class for the Dps class hierarchy.
 */
class DpsObject {
    public:
        DpsObject();
        virtual ~DpsObject();
        
        virtual enum DpsObjectType getType() {return _type;}

    protected:
        static DataAccess* DB;
        
        int _id;
        enum DpsObjectType _type;

    private:

};

// Forward declare DpsShowItem for DpsShowplan class
class DpsShowItem;

/**
 * Represent a show plan.
 * This class stores the items of a showplan, along with its database id and
 * name. An object of this type may load an existing showplan from the database
 * using the \a load routine, and save to the database using the \a save
 * routine. Standard operators are provided to allow access to individual
 * \a DpsShowItem.
 */
class DpsShowplan : public DpsObject {
    friend class DpsShowItem;
    public:
        DpsShowplan();
        DpsShowplan(const DpsShowplan& x);
        virtual ~DpsShowplan();

        bool operator==(const DpsShowplan& item);
        bool operator!=(const DpsShowplan& item);
        DpsShowplan& operator=(const DpsShowplan& item);
        DpsShowItem& operator[](unsigned int index);
        DpsShowItem& operator[](std::string md5);

        int getId();
        std::string getName();
        void setName(std::string name);
        DpsShowItem* at(unsigned int index);
        DpsShowItem* at(std::string md5);
        unsigned int size() {return _items.size();}
        void save();
        void load(int id);

        DpsShowItem& firstItem();
        DpsShowItem& lastItem();

    protected:
        void insert(const DpsShowItem* x);
        void insert(const DpsShowItem* x, const DpsShowItem& after);
        void drop(DpsShowItem* x);

        int _id;
        std::string _name;
        std::vector<DpsShowItem*> _items;
};

/**
 * Base class representing a single showplan item.
 * This base class is used to derive individual items for each type of showplan
 * entry.
 */
class DpsShowItem : public DpsObject {
    public:
        DpsShowItem();
        DpsShowItem(const DpsShowplan& parent);
        DpsShowItem(const DpsShowplan& parent, const DpsShowItem& after);
        DpsShowItem(const DpsShowItem& x);
        DpsShowItem(const DpsShowItem& x, const DpsShowplan& parent);
        virtual ~DpsShowItem();

        bool operator==(const DpsShowItem& item);
        bool operator!=(const DpsShowItem& item);
        DpsShowItem& operator=(const DpsShowItem& item);
        std::string operator[](std::string item);

        int getId();
        enum showPlanState getState();
        void setState(enum showPlanState state);
        DpsShowplan* parent();
        void setData(std::string name, std::string value);

    protected:


    private:
        enum showPlanState _state;
        std::map<std::string,std::string> _data;
        DpsShowplan* _parent;
};

/**
 * Showplan item representing an audio track.
 */
class DpsShowTrack : public DpsShowItem {
    public:
        DpsShowTrack(std::string md5);
        DpsShowTrack(const DpsShowplan& parent, std::string md5);
        DpsShowTrack(const DpsShowplan& parent, const DpsShowItem& after, std::string md5);
        virtual ~DpsShowTrack();
        DpsShowTrack& operator=(const DpsShowTrack& item);

    private:
        DpsShowTrack();
        void load(std::string md5);
};

/**
 * Showplan item representing a jingle.
 */
class DpsShowJingle : public DpsShowItem {
    public:
        DpsShowJingle(std::string md5);
        DpsShowJingle(const DpsShowplan& parent, std::string md5);
        DpsShowJingle(const DpsShowplan& parent, const DpsShowItem& after, std::string md5);
        virtual ~DpsShowJingle();

    private:
        DpsShowJingle();
        void load(std::string md5);
};

/**
 * Showplan item representing an advert.
 */
class DpsShowAdvert : public DpsShowItem {
    public:
        DpsShowAdvert(std::string md5);
        DpsShowAdvert(const DpsShowplan& parent, std::string md5);
        DpsShowAdvert(const DpsShowplan& parent, const DpsShowItem& after, std::string md5);
        virtual ~DpsShowAdvert();
    
    private:
        DpsShowAdvert();
        void load(std::string md5);
};

/**
 * Showplan item representing a script.
 */
class DpsShowScript: public DpsShowItem {
    public:
        DpsShowScript(unsigned int id);
        DpsShowScript(const DpsShowplan& parent, unsigned int id);
        DpsShowScript(const DpsShowplan& parent, const DpsShowItem& after, unsigned int id);
        virtual ~DpsShowScript();

    private:
        DpsShowScript();
        void load(unsigned int id);
};

/**
 * Showplan item representing a note or comment
 */
class DpsShowNote : public DpsShowItem {
    public:
        DpsShowNote(unsigned int id);
        DpsShowNote(const DpsShowplan& parent, unsigned int id);
        DpsShowNote(const DpsShowplan& parent, const DpsShowItem& after, unsigned int id);
        virtual ~DpsShowNote();

    private:
        DpsShowNote();
        void load(unsigned int id);
};

/**
 * Representation of a awset.
 * \todo implement.
 */
class DpsAwSet : public DpsObject {
    private:
        DpsAwSet();
        virtual ~DpsAwSet();

    private:
};

#endif
