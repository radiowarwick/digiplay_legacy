#include <string>
#include <vector>
using namespace std;

#include <openssl/md5.h>
#include <dlfcn.h>

#include "Logger.h"
#include "DataAccess.h"
#include "DbDefine.h"
#include "DpsLdap.h"

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
    const char* routine = "UserManager::add";

    bool standalone = false;
    if (T == "UMAdd") standalone = true;

    std::string SQL;
    std::string user_id;
    std::string dir_id;
    u.username = DB->esc(u.username);

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
                + user_id + "," + CONFIG_DEFAULTAWSET + ",'')";
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
    const char* routine = "UserManager::remove";

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
        // The user
        SQL = "DELETE FROM users WHERE username='" + u.username + "'";
        DB->exec(T,SQL);
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
    const char* routine = "UserManager::get";

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
    for (unsigned int i = 0; i < users.size(); i++) {
        if (users.at(i).username == username) {
            return users.at(i);
        }
    }
    throw 0;
}


/**
 * Sets a users password
 */
void UserManager::setPassword(User u, std::string password, std::string T) {
    const char* routine = "UserManager::setPassword";

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
    const char* routine = "UserManager::grantAdmin";

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
    const char* routine = "UserManager::revokeAdmin";

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


/**
 * Parses an LDAP directory and adds users to the database.
 */
std::vector<std::string> UserManager::parseLdap(std::string host, int port,
        std::string dn, std::string filter, std::string T) {
    const char* routine = "UserManager::parseLdap";
   
    // LDAP structure
    LDAP* _myLdap;
    
    // Handle on libldap.so
    void* ldap_h;
    
    // Declare local ldap function names
    // These will point to the dynamically loaded symbols from libldap.so
    ldap_init_t ldap_init;
    ldap_set_option_t ldap_set_option;
    ldap_simple_bind_s_t ldap_simple_bind_s;
    ldap_err2string_t ldap_err2string;
    ldap_search_s_t ldap_search_s;
    ldap_count_entries_t ldap_count_entries;
    ldap_first_entry_t ldap_first_entry;
    ldap_next_entry_t ldap_next_entry;
    ldap_first_attribute_t ldap_first_attribute;
    ldap_next_attribute_t ldap_next_attribute;
    ldap_get_values_t ldap_get_values;
    ldap_value_free_t ldap_value_free;
    ldap_memfree_t ldap_memfree;

    // Attempt to load the ldap shared library
    ldap_h = dlopen("libldap.so", RTLD_LAZY);
    if (!ldap_h) {
        L_CRITICAL(LOG_AUTH,"Cannot open LDAP library");
        L_CRITICAL(LOG_AUTH,string(dlerror()));
        throw;
    }

    // Load the symbols we need
    ldap_init = (ldap_init_t) dlsym(ldap_h, "ldap_init");
    ldap_set_option = (ldap_set_option_t) dlsym(ldap_h, "ldap_set_option");
    ldap_simple_bind_s
        = (ldap_simple_bind_s_t) dlsym(ldap_h, "ldap_simple_bind_s");
    ldap_err2string = (ldap_err2string_t) dlsym(ldap_h, "ldap_err2string");
    ldap_search_s = (ldap_search_s_t) dlsym(ldap_h, "ldap_search_s");
    ldap_count_entries 
        = (ldap_count_entries_t) dlsym(ldap_h,"ldap_count_entries");
    ldap_first_entry = (ldap_first_entry_t) dlsym(ldap_h, "ldap_first_entry");
    ldap_next_entry = (ldap_next_entry_t) dlsym(ldap_h, "ldap_next_entry");
    ldap_first_attribute 
        = (ldap_first_attribute_t) dlsym(ldap_h, "ldap_first_attribute");
    ldap_next_attribute
        = (ldap_next_attribute_t) dlsym(ldap_h, "ldap_next_attribute");
    ldap_get_values
        = (ldap_get_values_t) dlsym(ldap_h, "ldap_get_values");
    ldap_value_free = (ldap_value_free_t) dlsym(ldap_h, "ldap_value_free");
    ldap_memfree = (ldap_memfree_t) dlsym(ldap_h, "ldap_memfree");
    // Now the ldap routines can be used as if linked as normal

    // Initiate a connection to the LDAP server
    try {
        _myLdap = ldap_init(host.c_str(),port);
    }
    catch (...) {
        L_ERROR(LOG_AUTH,"Failed to create LDAP connection.");
        throw;
    }

    // Bind as an anonymous user
    int version = LDAP_VERSION3;
    int ret = 0;
    ldap_set_option(_myLdap, LDAP_OPT_PROTOCOL_VERSION, &version);
    if ((ret = ldap_simple_bind_s(_myLdap, NULL, NULL)) != LDAP_SUCCESS) {
        L_ERROR(LOG_DB,"Failed to connect to LDAP server anonymously.");
        L_ERROR(LOG_DB,"Server returned: " + string(ldap_err2string(ret)));
        throw;
    }

    // Search for all users matching provided filter
    LDAPMessage *res;
    if ((ret = ldap_search_s(_myLdap, dn.c_str(), LDAP_SCOPE_SUBTREE,
                    filter.c_str(), NULL, 0, &res)) != LDAP_SUCCESS) {
        L_ERROR(LOG_DB,"Failed while searching for usernames.");
        L_ERROR(LOG_DB,"Server returned: " + string(ldap_err2string(ret)));
        throw;
    }

    // Get all the uid's for the list of users returned
    // Declare some pointers
    LDAPMessage* e;
    BerElement* ber;
    char* a;
    char** vals;
    // store usernames in a vector
    std::vector<std::string> userlist;
    // Process each entry from the results
    for (e = ldap_first_entry(_myLdap, res); e != 0; 
            e = ldap_next_entry(_myLdap, e)) {
        // Process each attribute in the entry
        for (a = ldap_first_attribute(_myLdap, e, &ber); a != 0;
                a = ldap_next_attribute(_myLdap, e, ber)) {
            // Unless it's the uid field, continue to next entry
            if (strcmp(a,"uid")) continue;
            // Get the value of the uid field and add it to vector
            if ((vals = ldap_get_values(_myLdap, e, a)) != 0) {
                for (unsigned int i = 0; vals[i] != 0; i++) {
                    userlist.push_back(string(vals[i]));
                }
            }
            // free the memory
            ldap_value_free(vals);
            // no need to keep looking at this entry
            break;
        }
        // free the attribute
        ldap_memfree(a);
    }
    return userlist;
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
    const char* routine = "UserManager::refresh";

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
    const char* routine = "UserManager::userExists";

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
