#ifndef SECURITY
#define SECURITY

static int ruid = -1;
static int euid = -1;

unsigned int getDigiplayUser(std::string user);
void dropPrivilage(std::string user);
void gainPrivilage();
void showPrivilage();

#endif
