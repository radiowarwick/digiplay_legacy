#include <iostream>
using std::cout;
using std::endl;

#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>

#include "Security.h"

unsigned int getDigiplayUser(std::string user) {
    struct passwd *digiplay_user;
    digiplay_user = getpwnam(user.c_str());

	if (!digiplay_user) {
		if (ruid == 0) {
			cout << endl;
			cout << "SECURITY WARNING: This program should not be run as root!";
			cout << endl;
		}
		cout << endl;
		cout << "ERROR: No digiplay user account exists!" << endl;
		cout << " Please create the account '" << user << "'" << endl << endl;
		abort();
	}
    return digiplay_user->pw_uid;
}

void dropPrivilage(std::string user) {
    if (ruid == -1) {
        ruid = getuid();
        euid = geteuid();
    }
    unsigned int newuid = getDigiplayUser(user);
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
    unsigned int x = getuid();
    unsigned int y = geteuid();
    struct passwd *z = getpwuid(x);
    cout << "Real User: " << z->pw_name << endl;
    z = getpwuid(y);
    cout << "Effe User: " << z->pw_name << endl;
}
