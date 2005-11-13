/* Configuration setting class
 */

#include "config_reader.h"

config_reader::config_reader(string filename) {
	names = new vector<string>;
	values = new vector<string>;

	string f = "/etc/" + filename;
	ifstream config_file(f.c_str(), ios::in);
	if (config_file.is_open() && config_file.good()) {
		config_file.seekg(0);
		string str;
		int y = 0;
		
		while (!config_file.eof()) {
			y++;
			getline(config_file, str);
			if (str.substr(0,1) == "#") continue;
			unsigned int x = str.find_first_of("=",0);
			if (x == string::npos) {
			}
			else {
				names->push_back(str.substr(0,x));
				values->push_back(str.substr(x+1,str.length()));
			}
		}
	}
	else {
		cout << "Unable to find configuration file " << f << endl;
	}
	config_file.close();
}

config_reader::~config_reader() {
	delete names;
	delete values;
}

bool config_reader::isDefined(string name) {
	for (unsigned short i = 0; i < names->size(); i++) {
		if (names->at(i) == name)
			return true;
	}
	return false;
}

string config_reader::getParam(string name) {
	for (unsigned short i = 0; i < names->size(); i++) {
		if (names->at(i) == name)
			return values->at(i);
	}
	return "";
}
