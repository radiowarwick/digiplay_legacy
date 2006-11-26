#include <string>
#include <map>
using namespace std;

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"
using namespace pqxx;

class Auth;

class UserConfig {
    public:
        UserConfig(Auth *authModule);
        ~UserConfig();
        string get(string param);
        void set(string param, string val);

    private:
        Connection *C;
        void retrieveConfig();
        string _username;
        map<string,string> _userInfo;
};
