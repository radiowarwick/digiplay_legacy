#ifndef CLASS_LOCATIONMANAGER
#define CLASS_LOCATIONMANAGER

#include <map>
#include <vector>
#include <string>

struct Location {
    unsigned int location;
    std::map<std::string,std::string> data;
};

class DataAccess;

class LocationManager {
    public:
        LocationManager();
        ~LocationManager();
        void add(unsigned int loc_index, std::string T = "LMAdd");
        void remove(unsigned int loc_index, std::string T = "LMRemove");
        void setValue(unsigned int loc_index, std::string parameter,
                std::string value, std::string T = "LMSetValue");

        unsigned int count(std::string T = "LMCount");
        Location get(unsigned int index, std::string T = "LMGet");

    private:
        void getLocations();

        DataAccess* DB;
        std::map<std::string,std::string> defaults;
        std::vector<std::string> locations;
};

#endif
