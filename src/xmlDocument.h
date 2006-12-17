/*
 * XML Document class
 * xmlDocument.h
 * Representation of an XML document
 *
 * Copyright (c) 2005-2006 Chris Cantwell
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
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
