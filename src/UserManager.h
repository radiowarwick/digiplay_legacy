#ifndef CLASS_USERMANAGER
#define CLASS_USERMANAGER

#include <string>
#include <vector>

struct User {
    std::string id;
    std::string username;
    bool isAdmin;
    bool isEnabled;
    unsigned long lastLogin;
};

class DataAccess;

class UserManager {
    public:
        UserManager();
        ~UserManager();

        void add(User u, std::string T = "UMAdd");
        void remove(User u, std::string T = "UMRemove");
        
        unsigned int count();
        User get(unsigned int index);
        User get(std::string username);
        
        void setPassword(User u, std::string password,
                                    std::string T = "UMSetPassword");
        void grantAdmin(User u, std::string T = "UMGrantAdmin");
        void revokeAdmin(User u, std::string T = "UMRevokeAdmin");

    private:
        void refresh(std::string T = "UMRefresh");
        unsigned int userExists(User u, std::string T = "UMUserExists");

        DataAccess* DB;
        std::vector<User> users;
};

#endif
