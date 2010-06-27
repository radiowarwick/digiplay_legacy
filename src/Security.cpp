#include <iostream>
using std::cout;
using std::endl;

#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>

#include "Logger.h"
#include "Security.h"

static int ruid = -1;
static int euid = -1;

unsigned int getDigiplayUser(std::string user) {
	// Get the uid of the specified normal user account
    struct passwd *digiplay_user;
    digiplay_user = getpwnam(user.c_str());

	// If it's null, the account doesn't exist, return 0.
	if (!digiplay_user) {
		return 0;
	}
    return digiplay_user->pw_uid;
}

void dropPrivilage() {
    const char* routine = "security::dropPrivilage";
	// if first time, get our current uid
    if (ruid == -1) {
        ruid = getuid();
        euid = geteuid();
    }
	// if we're not root, we can't drop privilages, so return
	if (ruid != 0) return;
	
	// if root, get the uid of the user specified in the config to drop to
	unsigned int newuid = getDigiplayUser("dps");
	if (newuid == 0) {
		L_WARNING(LOG_SECURITY, "SECURITY WARNING: This program should not" 
                " be run as root!");
		L_WARNING(LOG_SECURITY, "However, the unprivilaged user 'dps' does" 
                " not exist.");
		L_WARNING(LOG_SECURITY, "You should create the user 'dps' by doing," 
                " as root:");
		L_WARNING(LOG_SECURITY, "  adduser --system dps");
		exit(-1);
	}

	// change user to the specified normal user account
    #ifdef _POSIX_SAVED_IDS
    int status = seteuid(newuid);
    #else
    int status = setreuid(ruid,newuid);
    #endif
    if (status != 0) {
        L_ERROR(LOG_SECURITY, "ERROR: Could not change to required"  
                " unprivilaged user");
        L_ERROR(LOG_SECURITY, " Make sure ownership is by unprivilaged user");
        L_ERROR(LOG_SECURITY, " and the setuid bit is set, or run as root");
        abort();
    }
	L_INFO(LOG_SECURITY, "Dropped to unprivilaged user 'dps'");
}

void gainPrivilage() {
    const char* routine = "security::gainPrivilage";
    if (isRoot()) {
    	L_INFO(LOG_SECURITY, "gainPrivilage: already root!");
    	return;
    }
    
    unsigned int x = getuid();
    if (x != 0) {
    	L_ERROR(LOG_SECURITY, "Can't regain lost privilages");
    	return;
    }
    
	// Get back the privilages we started with (usually root)
    #ifdef _POSIX_SAVED_IDS
    int status = seteuid(ruid);
    #else
    int status = setreuid(ruid,euid);
    #endif
    if (status != 0) {
        L_ERROR(LOG_SECURITY, "Could not regain privilages.");
    }
    else {
    	L_INFO(LOG_SECURITY, "Regained root privilages.");
    }
}

void showPrivilage() {
    const char* routine = "security::showPrivilage";
	// Print the current privilages to screen
    unsigned int x = getuid();
    unsigned int y = geteuid();
    struct passwd *z = getpwuid(x);
    L_INFO(LOG_SECURITY, "Real User: " + std::string(z->pw_name));
    z = getpwuid(y);
    L_INFO(LOG_SECURITY, "Effe User: " + std::string(z->pw_name));
}

void losePrivilage() {
    const char* routine = "security::losePrivilage";
	// if first time, get our current uid
    if (ruid == -1) {
        ruid = getuid();
        euid = geteuid();
    }

	// if we're not root, we can't drop privilages, so return
	if (ruid != 0) return;
	// we need to have effective root before we can setuid
	gainPrivilage();
	
	// if root, get the uid of the user specified in the config to drop to
	unsigned int newuid = getDigiplayUser("dps");
	if (newuid == 0) {
		L_WARNING(LOG_SECURITY, "SECURITY WARNING: This program should not" 
                " be run as root!");
		L_WARNING(LOG_SECURITY, "However, the unprivilaged user 'dps' does" 
                " not exist.");
		L_WARNING(LOG_SECURITY, "You should create the user 'dps' by doing," 
                " as root:");
		L_WARNING(LOG_SECURITY, "  adduser --system dps");
		exit(-1);
	}

	// change user to the specified normal user account
    #ifdef _POSIX_SAVED_IDS
    int status = setuid(newuid);
    #else
    int status = setreuid(ruid,newuid);
    #endif
    if (status != 0) {
        L_ERROR(LOG_SECURITY, "ERROR: Could not change to required"  
                " unprivilaged user");
        L_ERROR(LOG_SECURITY, " Make sure ownership is by unprivilaged user");
        L_ERROR(LOG_SECURITY, " and the setuid bit is set, or run as root");
        abort();
    }
	L_INFO(LOG_SECURITY, "Lost privilages and dropped to user 'dps'");
}

bool isRoot() {
	// Check if we're running as root
	if (geteuid() == 0) return true;
	return false;
}
