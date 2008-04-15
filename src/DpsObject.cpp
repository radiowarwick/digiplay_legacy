/*
 * DPS Objects
 * DpsObject.cpp
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
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "DataAccess.h"
#include "Logger.h"

#include "DpsObject.h"

/* =======================================================================
 * DpsObject
 * =======================================================================
 */
// ----- DpsObject Constructors -----
DataAccess* DpsObject::DB = 0;

DpsObject::DpsObject() {
    _type = DPS_OBJECT;
}

DpsObject::~DpsObject() {

}

// ----- DpsObject Operators -----

// ----- DpsObject Member routines -----

/* =======================================================================
 * DpsShowplan
 *  - derived from DpsObject
 * =======================================================================
 */
// ----- DpsShowplan Constructors -----
DpsShowplan::DpsShowplan() {
    _type = DPS_SHOWPLAN;
    _id = -1;
    _name = "";
}

DpsShowplan::DpsShowplan(const DpsShowplan& x) 
        : DpsObject(x) {

}

DpsShowplan::~DpsShowplan() {
    for (unsigned int i = 0; i < _items.size(); i++) {
        delete _items[i];
    }
}

// ----- DpsShowplan Operators -----
bool DpsShowplan::operator==(const DpsShowplan& item) {
    if (_id == item._id
            && _name == item._name
            && _items == item._items)
        return true;
    return false;
}

bool DpsShowplan::operator!=(const DpsShowplan& item) {
    return !(operator==(item));
}

DpsShowplan& DpsShowplan::operator=(const DpsShowplan& item) {
    unsigned int size = ((DpsShowplan&)item).size();
    _id = item._id;
    _name = item._name;
    for (unsigned int i = 0; i < size; i++) {
        new DpsShowItem(((DpsShowplan&)item)[i]);
    }
    // TODO: Need to actually copy showplanitems here
    return *this;
}

DpsShowItem& DpsShowplan::operator[](unsigned int index) {
    return *at(index);
}

DpsShowItem& DpsShowplan::operator[](string md5) {
    for (vector<DpsShowItem*>::iterator i = _items.begin();
                i < _items.end(); i++) {
        if ((**i)["md5"] == md5) {
            return **i;
        }
    }
    throw;
}

// ----- DpsShowplan Member routines -----
int DpsShowplan::getId() {
    return _id;
}

string DpsShowplan::getName() {
    return _name;
}

void DpsShowplan::setName(string name) {
    _name = name;
}

DpsShowItem* DpsShowplan::at(unsigned int index) {
    if (index < _items.size()) {
        return _items[index];
    }
    throw;
}

DpsShowItem* DpsShowplan::at(string md5) {
//    if (md5 != "") {
        return &operator[](md5);
//    }
//    return NULL;
}

void DpsShowplan::save() {

}

void DpsShowplan::load(int id) {
    _id = id;
    string SQL = "SELECT * FROM v_showplan WHERE id=" + dps_itoa(id);
    PqxxResult R = DB->exec("DpsShowplanLoad",SQL);
    DB->abort("DpsShowplanLoad");
    
    for (unsigned int i = 0; i < R.size(); i++) {
        if (string(R[i]["itemtype"].c_str()) == "audio") {
            if (string(R[i]["audiotype"].c_str()) == "Music") {
                new DpsShowTrack(*this,string(R[i]["key"].c_str()));
                lastItem().setData("comment",R[i]["comment"].c_str());
            }
            if (string(R[i]["audiotype"].c_str()) == "Jingle") {
                new DpsShowJingle(*this,string(R[i]["key"].c_str()));
                lastItem().setData("comment",R[i]["comment"].c_str());
            }
            if (string(R[i]["audiotype"].c_str()) == "Advert") {
                new DpsShowAdvert(*this,string(R[i]["key"].c_str()));
                lastItem().setData("comment",R[i]["comment"].c_str());
            }
        }
        if (string(R[i]["itemtype"].c_str()) == "script") {
            new DpsShowScript(*this,atoi(R[i]["key"].c_str()));
            lastItem().setData("comment",R[i]["comment"].c_str());
        }
        if (string(R[i]["itemtype"].c_str()) == "note") {
            new DpsShowNote(*this,atoi(R[i]["key"].c_str()));
            lastItem().setData("comment",R[i]["comment"].c_str());
        }
    }
}

DpsShowItem& DpsShowplan::firstItem() {
    if (_items.size() > 0) {
        return *_items[0];
    }
    else {
        throw;
    }
}

DpsShowItem& DpsShowplan::lastItem() {
    if (_items.size() > 0) {
        return *_items[_items.size() - 1];
    }
    else {
        throw;
    }
}

void DpsShowplan::insert(const DpsShowItem* x) {
    _items.push_back((DpsShowItem*)x);
}

void DpsShowplan::insert(const DpsShowItem* x, const DpsShowItem& after) {
    for (vector<DpsShowItem*>::iterator i = _items.begin(); 
                i < _items.end(); i++) {
        if (*i == &after) {
            _items.insert(i+1,(DpsShowItem*)x);
            break;
        }
    }
}

void DpsShowplan::drop(DpsShowItem* x) {
    if (x && x->parent() == this) {
        for (vector<DpsShowItem*>::iterator i = _items.begin();
                    i < _items.end(); i++) {
            if (*i == x) {
                _items.erase(i);
                break;
            }
        }
    }
}

/* =======================================================================
 * DpsShowItem
 *  - derived from DpsObject
 * =======================================================================
 */
// ----- DpsShowItem Constructors -----
DpsShowItem::DpsShowItem() {
    _type = DPS_SHOWITEM;
    _parent = 0;
}

DpsShowItem::DpsShowItem(const DpsShowplan& parent) {
    _type = DPS_SHOWITEM;
    _parent = &(DpsShowplan&)parent;
    _parent->insert(this);
}

DpsShowItem::DpsShowItem(const DpsShowplan& parent, const DpsShowItem& after) {
    _type = DPS_SHOWITEM;
    _parent = &(DpsShowplan&)parent;
    _parent->insert(this,after);
}

DpsShowItem::DpsShowItem(const DpsShowItem& x) 
        : DpsObject(x) {
    _type = DPS_SHOWITEM;
    _parent = 0;
    _data = x._data;
}

DpsShowItem::DpsShowItem(const DpsShowItem& x, const DpsShowplan& parent) 
        : DpsObject(x) {
    _type = DPS_SHOWITEM;
    _parent = &(DpsShowplan&)parent;
    _parent->insert(this);
    _data = x._data;
}

DpsShowItem::~DpsShowItem() {
    if (_parent) {
        _parent->drop(this);
    }
}

// ----- DpsShowItem Operators -----
bool DpsShowItem::operator==(const DpsShowItem& item) {
    return _type == item._type
            && _id == item._id
            && _data == item._data;
}

bool DpsShowItem::operator!=(const DpsShowItem& item) {
    return !(operator==(item));
}

DpsShowItem& DpsShowItem::operator=(const DpsShowItem& item) {
    if (*this != item) {
        this->DpsObject::operator=(item);
        _id = item._id;
        _data = item._data;
        _parent = 0;
    }
    return *this;
}

string DpsShowItem::operator[](string item) {
    const char* routine = "DpsShowItem::operator[]";
    if (_data.count(item) == 0) {
        L_ERROR(LOG_SHOWPLAN, "Item " + item + " doesn't exist!");
        return "";
    }
    return _data[item];
}

// ----- DpsShowItem Member routines -----
int DpsShowItem::getId() {
    return _id;
}

enum showPlanState DpsShowItem::getState() {
    return _state;
}

void DpsShowItem::setState(enum showPlanState state) {
    _state = state;
}

DpsShowplan* DpsShowItem::parent() {
    return _parent;
}

void DpsShowItem::setData(string name, string value) {
    _data[name] = value;
}

/* =======================================================================
 * DpsShowTrack
 * =======================================================================
 */
// ----- DpsShowTrack Constructors -----
DpsShowTrack::DpsShowTrack(string id)
        : DpsShowItem() {
    load(id);
    _type = DPS_SHOWTRACK;
}

DpsShowTrack::DpsShowTrack(const DpsShowplan& parent, string id) 
        : DpsShowItem(parent) {
    load(id);
    _type = DPS_SHOWTRACK;
}

DpsShowTrack::DpsShowTrack(const DpsShowplan& parent, const DpsShowItem& after,
                            string id)
        : DpsShowItem(parent,after) {
    load(id);
    _type = DPS_SHOWTRACK;
}

DpsShowTrack::~DpsShowTrack() {

}

// ----- DpsShowTrack Operators -----

DpsShowTrack& DpsShowTrack::operator=(const DpsShowTrack& item) {
    this->DpsShowItem::operator=(item);
    return *this;
}

// ----- DpsShowTrack Member routines -----
void DpsShowTrack::load(string id) {
    const char* routine = "DpsShowTrack::load";
    string SQL;
    PqxxResult R;

    try {
        SQL = "SELECT type FROM audio WHERE id='" + id + "'";
        R = DB->exec("DpsShowTrackLoad",SQL);
        if (R.size() == 0 || string(R[0]["type"].c_str()) != "1") {
            DB->abort("DpsShowTrackLoad");
            L_ERROR(LOG_DB,"ID: " + id + " is not a music track.");
            throw DB_NO_SUCH_TRACK;
        }
        SQL = "SELECT * FROM v_audio_music WHERE id='" + id + "'";
        R = DB->exec("DpsShowTrackLoad",SQL);
        DB->abort("DpsShowTrackLoad");
    }
    catch (int e) {
        DB->abort("DpsShowTrackLoad");
        if (e == DB_NOT_CONNECTED) {
            L_ERROR(LOG_DB,"Unable to connect to database.");
        }
        else {
            L_ERROR(LOG_DB,"Failed to execute SQL: " + SQL);
        }
    }
    if (R.size() > 0) {
        for (unsigned int i = 0; i < R[0].size(); i++) {
            if (string(R[0][i].name()) == "id") {
                _id = atoi(R[0][i].c_str());
            }
            else {
                setData(R[0][i].name(), R[0][i].c_str());
            }
        }
    }
}

/* =======================================================================
 * DpsShowJingle
 * =======================================================================
 */
// ----- DpsShowJingle Constructors -----
DpsShowJingle::DpsShowJingle(string id)
        : DpsShowItem() {
    load(id);
    _type = DPS_SHOWJINGLE;
}

DpsShowJingle::DpsShowJingle(const DpsShowplan& parent, string id) 
        : DpsShowItem(parent) {
    load(id);
    _type = DPS_SHOWJINGLE;
}

DpsShowJingle::DpsShowJingle(const DpsShowplan& parent, const DpsShowItem& after, string id)
        : DpsShowItem(parent,after) {
    load(id);
    _type = DPS_SHOWJINGLE;
}

DpsShowJingle::~DpsShowJingle() {

}

// ----- DpsShowJingle Operators -----

// ----- DpsShowJingle Member routines -----
void DpsShowJingle::load(string id) {
    const char* routine = "DpsShowJingle::load";
    string SQL;
    PqxxResult R;

    try {
        SQL = "SELECT type FROM audio WHERE id='" + id + "'";
        R = DB->exec("DpsShowJingleLoad",SQL);
        if (R.size() == 0 || string(R[0]["type"].c_str()) != "2") {
            DB->abort("DpsShowJingleLoad");
            L_ERROR(LOG_DB,"ID: " + id + " is not a jingle.");
            throw DB_NO_SUCH_TRACK;
        }
        SQL = "SELECT * FROM v_audio_jingles WHERE id='" + id + "'";
        R = DB->exec("DpsShowJingleLoad",SQL);
        DB->abort("DpsShowJingleLoad");
    }
    catch (int e) {
        DB->abort("DpsShowJingleLoad");
        if (e == DB_NOT_CONNECTED) {
            L_ERROR(LOG_DB,"Unable to connect to database.");
        }
        else {
            L_ERROR(LOG_DB,"Failed to execute SQL: " + SQL);
        }
    }
    if (R.size() > 0) {
        for (unsigned int i = 0; i < R[0].size(); i++) {
            if (string(R[0][i].name()) == "id") {
                _id = atoi(R[0][i].c_str());
            }
            else {
                setData(R[0][i].name(), R[0][i].c_str());
            }
        }
    }
}


/* =======================================================================
 * DpsShowAdvert
 * =======================================================================
 */
// ----- DpsShowAdvert Constructors -----
DpsShowAdvert::DpsShowAdvert(string id)
        : DpsShowItem() {
    load(id);
    _type = DPS_SHOWADVERT;
}

DpsShowAdvert::DpsShowAdvert(const DpsShowplan& parent, string id) 
        : DpsShowItem(parent) {
    load(id);
    _type = DPS_SHOWADVERT;
}

DpsShowAdvert::DpsShowAdvert(const DpsShowplan& parent, const DpsShowItem& after, string id) : DpsShowItem(parent,after) {
    load(id);
    _type = DPS_SHOWADVERT;
}

DpsShowAdvert::~DpsShowAdvert() {

}

// ----- DpsShowAdvert Operators -----

// ----- DpsShowAdvert Member routines -----
void DpsShowAdvert::load(string id) {
    const char* routine = "DpsShowAdvert::load";
    string SQL;
    PqxxResult R;

    try {
        SQL = "SELECT type FROM audio WHERE id='" + id + "'";
        R = DB->exec("DpsShowAdvertLoad",SQL);
        if (R.size() == 0 || string(R[0]["type"].c_str()) != "3") {
            L_ERROR(LOG_DB,"ID: " + id + " is not an advert.");
            throw DB_NO_SUCH_TRACK;
        }
        SQL = "SELECT * FROM v_audio_adverts WHERE id='" + id + "'";
        R = DB->exec("DpsShowAdvertLoad",SQL);
        DB->abort("DpsShowAdvertLoad");
    }
    catch (int e) {
        DB->abort("DpsShowAdvertLoad");
        if (e == DB_NOT_CONNECTED) {
            L_ERROR(LOG_DB,"Unable to connect to database.");
        }
        else {
            L_ERROR(LOG_DB,"Failed to execute SQL: " + SQL);
        }
    }
    if (R.size() > 0) {
        for (unsigned int i = 0; i < R[0].size(); i++) {
            if (string(R[0][i].name()) == "id") {
                _id = atoi(R[0][i].c_str());
            }
            else {
                setData(R[0][i].name(), R[0][i].c_str());
            }
        }
    }
}


/* =======================================================================
 * DpsShowScript
 * =======================================================================
 */
// ----- DpsShowScript Constructors -----
DpsShowScript::DpsShowScript(unsigned int id)
        : DpsShowItem() {
    load(id);
    _type = DPS_SHOWSCRIPT;
}

DpsShowScript::DpsShowScript(const DpsShowplan& parent, unsigned int id) 
        : DpsShowItem(parent) {
    load(id);
    _type = DPS_SHOWSCRIPT;
}

DpsShowScript::DpsShowScript(const DpsShowplan& parent, const DpsShowItem& after, unsigned int id) : DpsShowItem(parent,after) {
    load(id);
    _type = DPS_SHOWSCRIPT;
}

DpsShowScript::~DpsShowScript() {

}

// ----- DpsShowScript Operators -----

// ----- DpsShowScript Member routines -----
void DpsShowScript::load(unsigned int id) {
    const char* routine = "DpsShowScript::load";
    string SQL;
    PqxxResult R;

    try {
        SQL = "SELECT * FROM v_scripts WHERE id=" + dps_itoa(id);
        R = DB->exec("DpsShowScriptLoad",SQL);
        DB->abort("DpsShowScriptLoad");
    }
    catch (int e) {
        DB->abort("DpsShowScriptLoad");
        if (e == DB_NOT_CONNECTED) {
            L_ERROR(LOG_DB,"Unable to connect to database.");
        }
        else {
            L_ERROR(LOG_DB,"Failed to execute SQL: " + SQL);
        }
    }
    if (R.size() > 0) {
        for (unsigned int i = 0; i < R[0].size(); i++) {
            if (string(R[0][i].name()) == "id") {
                _id = atoi(R[0][i].c_str());
            }
            else {
                setData(R[0][i].name(), R[0][i].c_str());
            }
        }
    }
}

DpsShowNote::DpsShowNote(unsigned int id)
        : DpsShowItem() {
    load(id);
    _type = DPS_SHOWNOTE;
}

DpsShowNote::DpsShowNote(const DpsShowplan& parent, unsigned int id)
        : DpsShowItem(parent) {
    load(id);
    _type = DPS_SHOWNOTE;
}

DpsShowNote::DpsShowNote(const DpsShowplan& parent, const DpsShowItem& after, unsigned int id) : DpsShowItem(parent, after) {
    load(id);
    _type = DPS_SHOWNOTE;
}

DpsShowNote::~DpsShowNote() {

}

void DpsShowNote::load(unsigned int id) {
    const char* routine = "DpsShowNote::load";
    string SQL;
    PqxxResult R;

    try {
        SQL = "SELECT key,comment FROM v_showplan WHERE key=" + dps_itoa(id);
        R = DB->exec("DpsShowNoteLoad",SQL);
        DB->abort("DpsShowNoteLoad");
    }
    catch (...){
        DB->abort("DpsShowNoteLoad");
    }
    if (R.size() > 0) {
        for (unsigned int i = 0; i < R[0].size(); ++i) {
            if (string(R[0][i].name()) == "key") {
                _id = atoi(R[0][i].c_str());
            }
            else {
                setData(R[0][i].name(), R[0][i].c_str());
            }
        }
    }    
}
