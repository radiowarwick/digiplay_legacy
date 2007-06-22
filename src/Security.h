#ifndef SECURITY
#define SECURITY

unsigned int getDigiplayUser(std::string user);
void dropPrivilage();
void gainPrivilage();
void showPrivilage();
bool isRoot();

#endif
