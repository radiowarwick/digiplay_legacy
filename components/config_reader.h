#ifndef CLASS_CONFIG
#define CLASS_CONFIG
    
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "dirent.h"
#include "sys/types.h"

class config_reader {
	public:
		config_reader(string filename);
		~config_reader();
		bool isDefined(string name);
		string getParam(string name);

	private:
		vector<string>* names;
		vector<string>* values;
};

#endif
