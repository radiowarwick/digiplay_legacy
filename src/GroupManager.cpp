#include "UserManager.h"
#include "Logger.h"
#include "DataAccess.h"

#include "GroupManager.h"

/**
 * Initialises a group manager object
 */
GroupManager::GroupManager() {
    DB = new DataAccess();
    refresh();
}


/**
 * Cleans up a group manager object
 */
GroupManager::~GroupManager() {
    delete DB;
}


/**
 * Adds a new group. An optional transaction name may be supplied to allow the
 * operation to be performed as part of a larger single operation.
 */
void GroupManager::add(Group g, std::string T) {
    char* routine = "GroupManager::add";

    bool standalone = false;
    if (T == "GMAdd") standalone = true;

    if (groupId(g,T) != "0") {
        L_ERROR(LOG_DB,"Group '" + g.name + "' already exists.");
        throw;
    }

    std::string SQL;

    try {
        SQL = "INSERT INTO groups (name) VALUES ('" + g.name + "')";
        DB->exec(T,SQL);
        if (standalone) DB->commit(T);
    }
    catch (...) {
        if (standalone) DB->abort(T);
        L_ERROR(LOG_DB,"Failed to add group.");
        throw;
    }
    refresh();
}


/**
 * Removes a group and all associated links from the system. An optional
 * transaction name may be supplied to allow the operation to be performed as
 * part of a larger single operation.
 */
void GroupManager::remove(Group g, std::string T) {
    char* routine = "GroupManager::remove";

    bool standalone = false;
    if (T == "GMRemove") standalone = true;

    if (groupId(g,T) == "0") {
        L_ERROR(LOG_DB,"Group '" + g.name + "' does not exist.");
        throw;
    }

    std::string SQL;
    std::string id = groupId(g,T);

    try {
        SQL = "DELETE FROM usersgroups WHERE groupid=" + id;
        DB->exec(T,SQL);
        SQL = "DELETE FROM audiogroups WHERE groupid=" + id;
        DB->exec(T,SQL);
        SQL = "DELETE FROM cartsetsgroups WHERE groupid=" + id;
        DB->exec(T,SQL);
        SQL = "DELETE FROM dirgroups WHERE groupid=" + id;
        DB->exec(T,SQL);
        SQL = "DELETE FROM scriptsgroups WHERE groupid=" + id;
        DB->exec(T,SQL);
        SQL = "DELETE FROM showplangroups WHERE groupid=" + id;
        DB->exec(T,SQL);
        SQL = "DELETE FROM groups WHERE name='" + g.name + "'";
        DB->exec(T,SQL);
        if (standalone) DB->commit(T);
    }
    catch (...) {
        if (standalone) DB->abort(T);
        L_ERROR(LOG_DB,"Failed to remove group.");
        throw;
    }
    refresh();
}


/**
 * Adds a user to a group. An optional transaction name may be supplied to
 * allow the operation to be performed as part of a larger single operation.
 */
void GroupManager::addToGroup(User u, Group g, std::string T) {
    char* routine = "GroupManager::addToGroup";

    bool standalone = false;
    if (T == "GMAddToGroup") standalone = true;

    std::string SQL;

    try {
        SQL = "SELECT * FROM usersgroups WHERE userid=" + u.id
                + " AND groupid=" + g.id;
        if (DB->exec(T,SQL).size() > 0) {
            L_ERROR(LOG_DB,"User '" + u.username + "' is already in group '"
                            + g.name + "'");
            throw;
        }
        SQL = "INSERT INTO usersgroups (userid, groupid) VALUES ("
                + u.id + "," + g.id + ")";
        DB->exec(T,SQL);
        if (standalone) DB->commit(T);
    }
    catch (...) {
        if (standalone) DB->abort(T);
        L_ERROR(LOG_DB,"Failed to add user to group.");
        throw;
    }
}


/**
 * Removes the user from the group.
 */
void GroupManager::removeFromGroup(User u, Group g, std::string T) {
    char* routine = "GroupManager::removeFromGroup";

    bool standalone = false;
    if (T == "GMRemoveFromGroup") standalone = true;

    std::string SQL;

    try {
        SQL = "SELECT id FROM usersgroups WHERE userid=" + u.id
                + " AND groupid=" + g.id;
        if (DB->exec(T,SQL).size() == 0) {
            L_ERROR(LOG_DB,"User '" + u.username + "' is not in this group.");
            throw;
        }
        SQL = "DELETE FROM usersgroups WHERE userid=" + u.id
                + " AND groupid=" + g.id;
        DB->exec(T,SQL);
        if (standalone) DB->commit(T);
    }
    catch (...) {
        if (standalone) DB->abort(T);
        L_ERROR(LOG_DB,"Failed to remove user from group.");
        throw;
    }
}


/**
 * Returns the total number of groups in the system.
 */
unsigned int GroupManager::count() {
    return groups.size();
}


/**
 * Returns the group at \a index
 */
Group GroupManager::get(unsigned int index) {
    char* routine = "GroupManager::get";

    if (index >= groups.size()) {
        L_ERROR(LOG_DB,"Index out of range.");
        throw;
    }
    return groups.at(index);
}


/**
 * Returns the group named \a name.
 */
Group GroupManager::get(std::string name) {
    char* routine = "GroupManager::get";

    for (unsigned int i = 0; i < groups.size(); i++) {
        if (name == groups.at(i).name)
            return groups.at(i);
    }
    L_ERROR(LOG_DB,"Group '" + name + "' does not exist.");
    throw;
}


/**
 * Returns the id number for a given group. An optional transaction name may be
 * supplied to allow the operation to be performed as part of a larger single
 * operation.
 */
std::string GroupManager::groupId(Group g, std::string T) {
    char* routine = "GroupManager::groupId";

    bool standalone = false;
    if (T == "GMGroupId") standalone = true;

    std::string SQL;
    PqxxResult R;

    try {
        SQL = "SELECT id FROM groups WHERE name='" + g.name + "'";
        R = DB->exec(T,SQL);
        if (standalone) DB->abort(T);
        if (R.size() > 0) return R[0][0].c_str();
        else return "0";
    }
    catch (...) {
        if (standalone) DB->abort(T); 
        L_ERROR(LOG_DB,"Failed to get group id.");
        throw;
    }
}


/**
 * Refreshes the internal list of groups on the system. An optional transaction
 * name may be supplied to allow the operation to be performed as part of a
 * larger single operation.
 */
void GroupManager::refresh(std::string T) {
    char* routine = "GroupManager::refresh";

    bool standalone = false;
    if (T == "GMRefresh") standalone = true;

    groups.clear();

    std::string SQL;
    PqxxResult R;

    try {
        SQL = "SELECT id, name FROM groups";
        R = DB->exec(T,SQL);
        if (standalone) DB->abort(T);
    }
    catch (...) {
        if (standalone) DB->abort(T);
        L_ERROR(LOG_DB,"Unable to refresh group list.");
        throw;
    }

    for (unsigned int i = 0; i < R.size(); ++i) {
        Group g;
        g.id = R[i]["id"].c_str();
        g.name = R[i]["name"].c_str();
        groups.push_back(g);
    }
}
