#ifndef CLASS_AUTH
#define CLASS_AUTH

#include <string>
#include <vector>
#include <map>
using namespace std;

#define AUTH_FAILED					10000
#define AUTH_INVALID_CREDENTIALS 	10001


class Auth {
	public:
		Auth();
		virtual ~Auth() = 0;
		bool isPermitted(string privilage);
		bool isAuthenticated();
		string getUser();
		virtual void authSession(string username, string password) = 0;
		void closeSession();

	protected:
		void addPrivilage(string privilage);
		void addUserInfo(string item, string value);

	private:
		Auth(Auth &A);

		vector<string> _privilages;
		map<string,string> _userInfo;
};	
#endif
