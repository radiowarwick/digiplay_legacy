#ifndef CLASS_XMLELEMENT
#define CLASS_XMLELEMENT

#include <string>
#include <vector>
using namespace std;

struct xmlAttribute {
	string name;
	string value;
};

class xmlElement {
	public:
		xmlElement();
		xmlElement(string name);
		~xmlElement();

		void set_name(string text);
		void set_cdata(string text);
		string get_name();
		string get_cdata();

		xmlAttribute add_attribute(string name, string value);
		xmlAttribute add_attribute(xmlAttribute attr);
		xmlAttribute get_attribute(unsigned int index);
		xmlAttribute get_attribute(string name);
		void remove_attribute(unsigned int index);
		void remove_attribute(string name);
		unsigned int count_attributes();

		xmlElement *add_element(string name);
		xmlElement *add_element(xmlElement *elem);
		xmlElement *get_element(unsigned int index);
		xmlElement *get_element(string name);
		void remove_element(unsigned int index);
		void remove_element(string name);
		unsigned int count_elements();
		
	private:
		string name;
		string cdata;
		vector<xmlAttribute> *attributes;
		vector<xmlElement*> *elements;
};

#endif
