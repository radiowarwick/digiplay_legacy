#ifndef SECURITY
#define SECURITY

unsigned int getDigiplayUser(std::string user);
void dropPrivilage(std::string user);
void gainPrivilage();
void showPrivilage();
bool isRoot();

#endif
