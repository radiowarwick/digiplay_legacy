#ifndef CLASS_GROUPMANAGER
#define CLASS_GROUPMANAGER

#include <string>
#include <vector>

#include "UserManager.h"

struct Group {
    std::string id;
    std::string name;
};

class DataAccess;

class GroupManager {
    public:
        GroupManager();
        ~GroupManager();

        void add(Group g, std::string T = "GMAdd");
        void remove(Group g, std::string T = "GMRemove");
        void addToGroup(User u, Group g, std::string T = "GMAddToGroup");
        void removeFromGroup(User u, Group g, 
                                    std::string T = "GMRemoveFromGroup");
        unsigned int count();
        Group get(unsigned int index);
        Group get(std::string name);

    private:
        std::string groupId(Group g, std::string T = "GMGroupId");
        void refresh(std::string T = "GMRefresh");

        DataAccess* DB;
        std::vector<Group> groups;
};

#endif
