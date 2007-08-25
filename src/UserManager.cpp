#include <openssl/md5.h>

#include "Logger.h"
#include "DataAccess.h"
#include "DbDefine.h"

#include "UserManager.h"

UserManager::UserManager() {
    DB = new DataAccess();
    refresh();
}

UserManager::~UserManager() {
    delete DB;
}

/**
 * Adds a new user to the system.
 * Creates the user a home directory, and assigns appropriate permisisons.
 * Adds user to the Everyone group.
 * Enters default configuration values for userconfigs.
 */
void UserManager::add(User u, std::string T) {
    char* routine = "UserManager::add";

    bool standalone = false;
    if (T == "UMAdd") standalone = true;

    std::string SQL;
    std::string user_id;
    std::string dir_id;

    if (userExists(u,T)) {
        L_ERROR(LOG_DB,"User '" + u.username + "' already exists.");
        throw;
    }

    try {
        // Add user
        SQL = "INSERT INTO users (username, password, enabled) "
                "VALUES ('" + u.username + "','','t')";
        DB->exec(T,SQL);
        SQL = "SELECT id FROM users WHERE username='" + u.username + "'";
        user_id = DB->exec(T,SQL)[0][0].c_str();
        // Add user to groups
        SQL = "INSERT INTO usersgroups (userid, groupid) VALUES ("
                + user_id + "," GROUP_EVERYONE ")";
        DB->exec(T,SQL);
        if (u.isAdmin) {
            SQL = "INSERT INTO usersgroups (userid, groupid) VALUES ("
                + user_id + "," GROUP_ADMINISTRATORS ")";
            DB->exec(T,SQL);
        }
        // Create home directory
        SQL = "INSERT INTO dir (parent, name, inherit) VALUES ("
                DIR_USERS ",'" + u.username + "','f')";
        DB->exec(T,SQL);
        SQL = "SELECT id FROM dir WHERE name='" + u.username 
                + "' AND parent=" + DIR_USERS;
        dir_id = DB->exec(T,SQL)[0][0].c_str();
        // Set permissions on home directory
        SQL = "INSERT INTO dirusers (dirid, userid, permissions) VALUES ("
                + dir_id + "," + user_id + ",'11100000')";
        DB->exec(T,SQL);
        SQL = "INSERT INTO dirgroups (dirid, groupid, permissions) VALUES ("
                + dir_id + "," + GROUP_ADMINISTRATORS + ",'11000000')";
        DB->exec(T,SQL);
        // Set default user config values
        SQL = "INSERT INTO usersconfigs (userid, configid, val) VALUES ("
                + user_id + "," + CONFIG_DEFAULTCARTSET + ",'')";
        DB->exec(T,SQL);

        // Commit new user
        if (standalone) DB->commit(T);
    }
    catch (...) {
        if (standalone) DB->abort(T);
        L_ERROR(LOG_DB,"Failed to add user. SQL: " + SQL);
        throw;
    }
    refresh();
}


/**
 * Remove a user from the system and all links.
 * Also removes the users home directory.
 * \todo remove all files and stuff in directory.
 */
void UserManager::remove(User u, std::string T) {
    char* routine = "UserManager::remove";

    bool standalone = false;
    if (T == "UMRemove") standalone = true;

    std::string SQL;
    std::string id;

    if (!userExists(u,T)) {
        L_ERROR(LOG_DB,"User '" + u.username + "' does not exist.");
        throw;
    }

    if (u.username == "System") {
        L_ERROR(LOG_DB,"The System user must not be removed.");
        throw;
    }
    if (u.username == "Guest") {
        L_ERROR(LOG_DB,"The Guest user must not be removed.");
        throw;
    }

    try {
        SQL = "SELECT id FROM users WHERE username='" + u.username + "'";
        id = DB->exec(T,SQL)[0][0].c_str();
        // User configuration data
        SQL = "DELETE FROM usersconfigs WHERE userid=" + id;
        DB->exec(T,SQL);
        // Group memberships
        SQL = "DELETE FROM usersgroups WHERE userid=" + id;
        DB->exec(T,SQL);
        // Object permissions
        SQL = "DELETE FROM audiousers WHERE userid=" + id;
        DB->exec(T,SQL);
        SQL = "DELETE FROM cartsetsusers WHERE userid=" + id;
        DB->exec(T,SQL);
        SQL = "DELETE FROM dirusers WHERE userid=" + id;
        DB->exec(T,SQL);
        SQL = "DELETE FROM scriptsusers WHERE userid=" + id;
        DB->exec(T,SQL);
        SQL = "DELETE FROM showplanusers WHERE userid=" + id;
        DB->exec(T,SQL);
        // The user
        SQL = "DELETE FROM users WHERE username='" + u.username + "'";
        DB->exec(T,SQL);
        // The user's home directory
        SQL = "SELECT id FROM dir WHERE name='" + u.username + "' "
                "AND parent=" DIR_USERS;
        id = DB->exec(T,SQL)[0][0].c_str();
        SQL = "DELETE FROM dirgroups WHERE dirid=" + id;
        DB->exec(T,SQL);
        SQL = "DELETE FROM dir WHERE name='" + u.username + "' "
                "AND parent=" DIR_USERS;
        DB->exec(T,SQL);

        // Commit all changes
        if (standalone) DB->commit(T);
    }
    catch (...) {
        if (standalone) DB->abort(T);
        L_ERROR(LOG_DB,"Failed to delete user. SQL: " + SQL);
        throw;
    }
    refresh();
}


/**
 * Returns the number of users on the system.
 */
unsigned int UserManager::count() {
    return users.size();
}


/**
 * Returns the user at \a index
 */
User UserManager::get(unsigned int index) {
    char* routine = "UserManager::get";

    if (index >= users.size()) {
        L_ERROR(LOG_DB,"Index out of range");
        throw;
    }
    return users.at(index);
}


/**
 * Returns the user named \a username
 */
User UserManager::get(std::string username) {
    char* routine = "UserManager::get";

    for (unsigned int i = 0; i < users.size(); i++) {
        if (users.at(i).username == username) {
            return users.at(i);
        }
    }
    L_ERROR(LOG_DB,"Unknown user '" + username + "'");
    throw;
}


/**
 * Sets a users password
 */
void UserManager::setPassword(User u, std::string password, std::string T) {
    char* routine = "UserManager::setPassword";

    bool standalone = false;
    if (T == "UMSetPassword") standalone = true;

    if (!userExists(u,T)) {
        L_ERROR(LOG_DB,"Unknown user '" + u.username + "'");
        throw;
    }

    // MD5 hash user-supplied password
    MD5_CTX context;
    unsigned char digest[16];
    char encrypt[32];
    MD5_Init(&context);
    MD5_Update(&context, password.c_str(), password.size());
    MD5_Final(digest, &context);
    for (unsigned int i = 0; i < 16; ++i) {
        sprintf(encrypt + i*2, "%02x", digest[i]);
    }
    std::string hash(encrypt);

    std::string SQL;

    try {
        SQL = "UPDATE users SET password='" + hash + "' "
              "WHERE username='" + u.username + "'";
        DB->exec(T,SQL);
        if (standalone) DB->commit(T);
    }
    catch (...) {
        if (standalone) DB->abort(T);
        L_ERROR(LOG_DB,"Failed to update user password.");
        return;
    }
}


/**
 * Adds a user to the administrators group
 */
void UserManager::grantAdmin(User u, std::string T) {
    char* routine = "UserManager::grantAdmin";

    bool standalone = false;
    if (T == "UMGrantAdmin") standalone = true;

    if (!userExists(u)) {
        L_ERROR(LOG_DB,"Unknown user '" + u.username + "'");
        throw;
    }

    std::string SQL;
    std::string user_id;

    try {
        SQL = "SELECT users.id FROM users, usersgroups "
              "WHERE users.id = usersgroups.userid "
              "AND usersgroups.groupid=" GROUP_ADMINISTRATORS;
        if (DB->exec(T,SQL).size() > 0) {
            L_WARNING(LOG_DB,"User already has administrator privilages");
            return;
        }
        SQL = "SELECT users.id FROM users WHERE username='" + u.username
              + "'";
        user_id = DB->exec(T,SQL)[0][0].c_str();
        SQL = "INSERT INTO usersgroups (userid, groupid) VALUES ("
              + user_id + "," GROUP_ADMINISTRATORS ")";
        DB->exec(T,SQL);
        if (standalone) DB->commit(T);
    }
    catch (...) {
        if (standalone) DB->abort(T);
        L_ERROR(LOG_DB,"Failed to grant administrator privilages.");
        throw;
    }
}


/**
 * Removes a user from the administrators group
 */
void UserManager::revokeAdmin(User u, std::string T) {
    char* routine = "UserManager::revokeAdmin";

    bool standalone = false;
    if (T == "UMRevokeAdmin") standalone = true;

    if (!userExists(u)) {
        L_ERROR(LOG_DB,"Unknown user '" + u.username + "'");
        throw;
    }

    std::string SQL;
    std::string user_id;

    try {
        SQL = "SELECT id FROM users WHERE username='" + u.username + "'";
        user_id = DB->exec(T,SQL)[0][0].c_str();
        SQL = "DELETE FROM usersgroups WHERE userid=" + user_id;
        DB->exec(T,SQL);
        if (standalone) DB->commit(T);
    }
    catch (...) {
        if (standalone) DB->abort(T);
        L_ERROR(LOG_DB,"Failed to revoke administrator privilages.");
        throw;
    }
}

/*
 * ------------------------------------------------------------------
 * PRIVATE
 *
 */

/**
 * Rebuilds the internal list of users on the system.
 */
void UserManager::refresh(std::string T) {
    char* routine = "UserManager::refresh";

    bool standalone = false;
    if (T == "UMRefresh") standalone = true;

    users.clear();

    User u;
    std::string SQL;
    PqxxResult R1, R2;

    try {
        SQL = "SELECT id, username, enabled FROM users";
        R1 = DB->exec(T,SQL);
        SQL = "SELECT users.username, usersgroups.groupid "
                "FROM users, usersgroups WHERE users.id = usersgroups.userid "
                "AND usersgroups.groupid=" GROUP_ADMINISTRATORS;
        R2 = DB->exec(T,SQL);
        if (standalone) DB->abort(T);
    }
    catch (...) {
        if (standalone) DB->abort(T);
        L_ERROR(LOG_DB,"Failed to query for user list.");
        throw;
    }

    for (unsigned int i = 0; i < R1.size(); ++i) {
        u.id = R1[i]["id"].c_str();
        u.username = R1[i]["username"].c_str();
        u.isEnabled = (string(R1[i]["enabled"].c_str()) == "t");
        u.isAdmin = false;
        users.push_back(u);
    }
    for (unsigned int i = 0; i < R2.size(); ++i) {
        for (unsigned int j = 0; j < users.size(); ++j) {
            if (users.at(j).username == string(R2[i]["username"].c_str())) {
                users.at(j).isAdmin = true;
            }
        }
    }
}


/**
 * Checks if the user specifed by \a u exists on the system
 */
unsigned int UserManager::userExists(User u, std::string T) {
    char* routine = "UserManager::userExists";

    bool standalone = false;
    if (T == "UMUserExists") standalone = true;

    std::string SQL;

    try {
        SQL = "SELECT id FROM users WHERE username='" + u.username + "'";
        PqxxResult R = DB->exec(T,SQL);
        if (standalone) DB->abort(T);
        if (R.size() > 0) {
            return true;
        }
    }
    catch (...) {
        if (standalone) DB->abort(T);
        L_ERROR(LOG_DB,"Failed to check for user. SQL: " + SQL);
        throw;
    }
    return false;
}
