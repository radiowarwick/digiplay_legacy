#ifndef CLASS_XMLDOCUMENT
#define CLASS_XMLDOCUMENT

#include <string>
#include <fstream>
using namespace std;

#include "xmlElement.h"

class xmlDocument {
	public:
		xmlDocument();
		xmlDocument(string filename);
		~xmlDocument();

		void set_header(string text);
		void set_doctype(string text);
		xmlElement *get_root();
		void write_file(string filename);

	private:
		string header;
		string doctype;
		xmlElement *root;

		void read_element(xmlElement *E, string *content, unsigned int start, unsigned int end);
		void write_element(xmlElement *E, ofstream *f_out, unsigned int indent);
};

#endif
