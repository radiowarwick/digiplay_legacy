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
#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

#include "Logger.h"
#include "config.h"

#include "DpsObject.h"

/* =======================================================================
 * DpsObject
 * =======================================================================
 */
// ----- DpsObject Constructors -----
Connection* DpsObject::C = 0;
Transaction* DpsObject::T = 0;

DpsObject::DpsObject() {
    _type = DPS_OBJECT;
}

DpsObject::~DpsObject() {

}

// ----- DpsObject Operators -----

// ----- DpsObject Member routines -----
void DpsObject::dbInit() {
    dbConnect();
}

Transaction* DpsObject::db() {
    if (!T) dbConnect();
    return T;
}

void DpsObject::commit() {
    if (!T) throw DB_NOT_CONNECTED;
    T->commit();
    delete T;
    T = new Transaction(*C,"");
}

void DpsObject::dbConnect() {
    try {
        config* conf = new config("digiplay");
        C = new Connection(conf->getDBConnectString());
        delete conf;
        T = new Transaction(*C,"");
    }
    catch (...) {
        throw DB_NOT_CONNECTED;
    };
}

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
    string SQL;
    SQL =   "SELECT showitems.position, audio.id as key, audio.md5 as md5, "
                "'audio' as type, audiotypes.name as audiotype "
            "FROM audio,audiotypes,showitems "
            "WHERE showitems.audio = audio.id "
                "AND audiotypes.id = audio.type "
                "AND showitems.showplanid=" + dps_itoa(id) + " "
            "UNION "
            "SELECT showitems.position, scripts.id as key, "
                "'' as md5, 'script' as type, '' as audiotype "
            "FROM scripts, showitems " 
            "WHERE showitems.script = scripts.id "
                "AND showitems.showplanid=11 "
            "ORDER BY position";
    Result R = db()->exec(SQL);
    for (unsigned int i = 0; i < R.size(); i++) {
        if (string(R[i]["type"].c_str()) == "audio") {
            if (string(R[i]["audiotype"].c_str()) == "music")
                new DpsShowTrack(*this,string(R[i]["md5"].c_str()));
            if (string(R[i]["audiotype"].c_str()) == "jingle")
                new DpsShowJingle(*this,string(R[i]["md5"].c_str()));
            if (string(R[i]["audiotype"].c_str()) == "advert")
                new DpsShowAdvert(*this,string(R[i]["md5"].c_str()));
        }
        if (string(R[i]["type"].c_str()) == "script") {
            new DpsShowScript(*this,atoi(R[i]["key"].c_str()));
        }
        if (string(R[i]["type"].c_str()) == "note") {
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
    if (_data.count(item) == 0) {
        cout << "Item " << item << " doesn't exist!" << endl;;
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
DpsShowTrack::DpsShowTrack(string md5)
        : DpsShowItem() {
    load(md5);
    _type = DPS_SHOWTRACK;
}

DpsShowTrack::DpsShowTrack(const DpsShowplan& parent, string md5) 
        : DpsShowItem(parent) {
    load(md5);
    _type = DPS_SHOWTRACK;
}

DpsShowTrack::DpsShowTrack(const DpsShowplan& parent, const DpsShowItem& after,
                            string md5)
        : DpsShowItem(parent,after) {
    load(md5);
    _type = DPS_SHOWTRACK;
}

DpsShowTrack::~DpsShowTrack() {

}

// ----- DpsShowTrack Operators -----

// ----- DpsShowTRack Member routines -----
void DpsShowTrack::load(string md5) {
    char *routine = "DpsShowTrack::load";
    string SQL;
    Result R;

    try {
        SQL = "SELECT audio.type AS type FROM audio WHERE md5='" + md5 + "'";
        R = db()->exec(SQL);
        if (R.size() == 0 || string(R[0]["type"].c_str()) != "0") {
            L_ERROR(LOG_DB,"MD5: " + md5 + " is not a music track.");
            throw DB_NO_SUCH_TRACK;
        }
        SQL = "SELECT audio.id AS id, audio.md5 AS md5, audio.title AS title, "
                    "artists.name AS artist, albums.name AS album, "
                    "archives.name AS archive, audio.music_track AS track, "
                    "audio.music_released AS released, "
                    "audio.length_smpl AS length, audio.start_smpl AS start, "
                    "audio.end_smpl AS end, audio.intro_smpl AS fade_in, "
                    "audio.extro_smpl AS fade_out, audio.censor AS censor "
                "FROM audio, audioartists, artists, albums, archives "
                "WHERE audioartists.audio = audio.id "
                    "AND audioartists.artist = artists.id "
                "AND audio.archive = archives.id "
                "AND audio.music_album = albums.id "
                "AND audio.md5 = '" + md5 + "'";
        R = db()->exec(SQL);
    }
    catch (int e) {
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
DpsShowJingle::DpsShowJingle(string md5)
        : DpsShowItem() {
    load(md5);
    _type = DPS_SHOWJINGLE;
}

DpsShowJingle::DpsShowJingle(const DpsShowplan& parent, string md5) 
        : DpsShowItem(parent) {
    load(md5);
    _type = DPS_SHOWJINGLE;
}

DpsShowJingle::DpsShowJingle(const DpsShowplan& parent, const DpsShowItem& after,
                            string md5)
        : DpsShowItem(parent,after) {
    load(md5);
    _type = DPS_SHOWJINGLE;
}

DpsShowJingle::~DpsShowJingle() {

}

// ----- DpsShowJingle Operators -----

// ----- DpsShowJingle Member routines -----
void DpsShowJingle::load(string md5) {
    char *routine = "DpsShowJingle::load";
    string SQL;
    Result R;

    try {
        SQL = "SELECT audio.type AS type FROM audio WHERE md5='" + md5 + "'";
        R = db()->exec(SQL);
        if (R.size() == 0 || string(R[0]["type"].c_str()) != "1") {
            L_ERROR(LOG_DB,"MD5: " + md5 + " is not a jingle.");
            throw DB_NO_SUCH_TRACK;
        }
        SQL = "SELECT audio.id AS id, audio.md5 AS md5, audio.title AS title, "
                    "jinglepkgs.name AS package, "
                    "archives.name AS archive, "
                    "audio.length_smpl AS length, audio.start_smpl AS start, "
                    "audio.end_smpl AS end, audio.intro_smpl AS fade_in, "
                    "audio.extro_smpl AS fade_out, audio.censor AS censor "
                "FROM audio, audiojinglepkgs, jinglepkgs, archives "
                "WHERE audiojinglepkgs.audio = audio.id "
                    "AND audiojinglepkgs.jinglepkg = jinglepkgs.id "
                "AND audio.archive = archives.id "
                "AND audio.md5 = '" + md5 + "'";
        R = db()->exec(SQL);
    }
    catch (int e) {
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
DpsShowAdvert::DpsShowAdvert(string md5)
        : DpsShowItem() {
    load(md5);
    _type = DPS_SHOWADVERT;
}

DpsShowAdvert::DpsShowAdvert(const DpsShowplan& parent, string md5) 
        : DpsShowItem(parent) {
    load(md5);
    _type = DPS_SHOWADVERT;
}

DpsShowAdvert::DpsShowAdvert(const DpsShowplan& parent, const DpsShowItem& after, string md5) : DpsShowItem(parent,after) {
    load(md5);
    _type = DPS_SHOWADVERT;
}

DpsShowAdvert::~DpsShowAdvert() {

}

// ----- DpsShowAdvert Operators -----

// ----- DpsShowAdvert Member routines -----
void DpsShowAdvert::load(string md5) {
    char *routine = "DpsShowAdvert::load";
    string SQL;
    Result R;

    try {
        SQL = "SELECT audio.type AS type FROM audio WHERE md5='" + md5 + "'";
        R = db()->exec(SQL);
        if (R.size() == 0 || string(R[0]["type"].c_str()) != "2") {
            L_ERROR(LOG_DB,"MD5: " + md5 + " is not an advert.");
            throw DB_NO_SUCH_TRACK;
        }
        SQL = "SELECT audio.id AS id, audio.md5 AS md5, audio.title AS title, "
                    "artists.name AS artist, albums.name AS album, "
                    "archives.name AS archive, audio.music_track AS track, "
                    "audio.music_released AS released, "
                    "audio.length_smpl AS length, audio.start_smpl AS start, "
                    "audio.end_smpl AS end, audio.intro_smpl AS fade_in, "
                    "audio.extro_smpl AS fade_out, audio.censor AS censor "
                "FROM audio, audioartists, artists, albums, archives "
                "WHERE audioartists.audio = audio.id "
                    "AND audioartists.artist = artists.id "
                "AND audio.archive = archives.id "
                "AND audio.music_album = albums.id "
                "AND audio.md5 = '" + md5 + "'";
        R = db()->exec(SQL);
    }
    catch (int e) {
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
    char *routine = "DpsShowScript::load";
    string SQL;
    Result R;

    try {
        SQL =   "SELECT scripts.name, scripts.contents, scripts.length, "
                    "users.username AS creator "
                "FROM scripts, users "
                "WHERE scripts.creator=users.id "
                    "AND scripts.id = " + dps_itoa(id);
        R = db()->exec(SQL);
    }
    catch (int e) {
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


