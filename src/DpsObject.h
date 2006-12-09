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
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "dps.h"

#define DB_NOT_CONNECTED 1
#define DB_NO_SUCH_TRACK 2

enum DpsObjectType {
    DPS_OBJECT, DPS_SHOWPLAN, DPS_SHOWITEM, 
    DPS_TRACK, DPS_JINGLE, DPS_ADVERT, DPS_NOTE,
    DPS_CARTSET
};

class DpsObject {
    public:
        DpsObject();
        virtual ~DpsObject();
        
        static void dbInit();
        virtual enum DpsObjectType getType() {return _type;}

    protected:
        static Transaction* db();
        void commit();
        
        int _id;
        enum DpsObjectType _type;

    private:
        static void dbConnect();
        static Connection *C;
        static Transaction *T;
};

class DpsShowItem;
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
        DpsShowItem& operator[](string md5);

        int getId();
        string getName();
        void setName(string name);
        DpsShowItem* at(unsigned int index);
        void save();
        void load(int id);

        DpsShowItem& firstItem();
        DpsShowItem& lastItem();

    protected:
        void insert(const DpsShowItem& x);
        void insert(const DpsShowItem& x, const DpsShowItem& after);
        void drop(DpsShowItem* x);

        int _id;
        string _name;
        vector<DpsShowItem*> _items;
};


class DpsShowItem : public DpsObject {
    public:
        DpsShowItem();
        DpsShowItem(const DpsShowplan& parent);
        DpsShowItem(const DpsShowplan& parent, const DpsShowItem& after);
        DpsShowItem(const DpsShowItem& x);
        virtual ~DpsShowItem();

        bool operator==(const DpsShowItem& item);
        bool operator!=(const DpsShowItem& item);
        DpsShowItem& operator=(const DpsShowItem& item);
        string operator[](string item);

        int getId();
        enum showPlanState getState();
        void setState(enum showPlanState state);
        DpsShowplan* parent();

    protected:
        void setData(string name, string value);

    private:
        enum showPlanState _state;
        map<string,string> _data;
        DpsShowplan* _parent;
};


class DpsShowTrack : public DpsShowItem {
    public:
        DpsShowTrack(string md5);
        DpsShowTrack(const DpsShowplan& parent, string md5);
        DpsShowTrack(const DpsShowplan& parent, const DpsShowItem& after, string md5);
        virtual ~DpsShowTrack();

        
    private:
        DpsShowTrack();
        void load(string md5);
};


class DpsShowJingle : public DpsShowItem {
    public:
        DpsShowJingle(string md5);
        DpsShowJingle(const DpsShowplan& parent, string md5);
        DpsShowJingle(const DpsShowplan& parent, const DpsShowItem& after, string md5);
        virtual ~DpsShowJingle();

    private:
        DpsShowJingle();
        void load(string md5);
};


class DpsShowAdvert : public DpsShowItem {
    public:
        DpsShowAdvert(string md5);
        DpsShowAdvert(const DpsShowplan& parent, string md5);
        DpsShowAdvert(const DpsShowplan& parent, const DpsShowItem& after, string md5);
        virtual ~DpsShowAdvert();
    
    private:
        DpsShowAdvert();
        void load(string md5);
};

class DpsShowNote : public DpsShowItem {
    public:
        DpsShowNote(DpsShowplan* parent);
        virtual ~DpsShowNote();

    private:
};


class DpsCartset : public DpsObject {
    private:
        DpsCartset();
        virtual ~DpsCartset();

    private:
};

#endif
