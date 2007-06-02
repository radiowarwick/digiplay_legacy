#include <iostream>
using std::cout;
using std::endl;

#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>

#include "Security.h"

unsigned int getDigiplayUser(std::string user) {
	// Get the uid of the specified normal user account
    struct passwd *digiplay_user;
    digiplay_user = getpwnam(user.c_str());

	// If it's null, the account doesn't exist.
	if (!digiplay_user) {
		if (ruid == 0) {
			cout << endl;
			cout << "SECURITY WARNING: This program should not be run as root!";
			cout << endl;
		}
		cout << endl;
		cout << "ERROR: The user account you specified doesn't exist!" << endl;
		cout << " Please create the account '" << user << "', or correct " << 
					"digiplay.conf" << endl << endl;
		abort();
	}
    return digiplay_user->pw_uid;
}

void dropPrivilage(std::string user) {
	// if first time, get our current uid
    if (ruid == -1) {
        ruid = getuid();
        euid = geteuid();
    }
	// if we're not root, we can't drop privilages, so return
	if (ruid != 0) return;
	
	// if root, get the uid of the user specified in the config to drop to
	unsigned int newuid = getDigiplayUser(user);

	// change user to the specified normal user account
    #ifdef _POSIX_SAVED_IDS
    int status = setuid(newuid);
    #else
    int status = setreuid(ruid,newuid);
    #endif
    if (status != 0) {
        cout << "ERROR: Could not change to required unprivilaged user" << endl;
        cout << " Make sure ownership is by unprivilaged user" << endl;
        cout << " and the setuid bit is set, or run as root" << endl;
        abort();
    }
	cout << "Dropped to unprivilaged user '" << user << "'" << endl;
}

void gainPrivilage() {
	// Get back the privilages we started with (usually root)
    #ifdef _POSIX_SAVED_IDS
    int status = setuid(ruid);
    #else
    int status = setreuid(ruid,euid);
    #endif
    if (status != 0) {
        cout << "ERROR: Could not regain privilages for some reason." << endl;
    }
}

void showPrivilage() {
	// Print the current privilages to screen
    unsigned int x = getuid();
    unsigned int y = geteuid();
    struct passwd *z = getpwuid(x);
    cout << "Real User: " << z->pw_name << endl;
    z = getpwuid(y);
    cout << "Effe User: " << z->pw_name << endl;
}

bool isRoot() {
	// Check if we're running as root
	if (getuid() == 0) return true;
	return false;
}
