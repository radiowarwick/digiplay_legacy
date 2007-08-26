/*
 * XML Document class
 * XmlDocument.h
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

#include "XmlElement.h"

class XmlDocument {
	public:
		XmlDocument();
		XmlDocument(std::string filename);
		~XmlDocument();

		void set_header(std::string text);
		void set_doctype(std::string text);
		XmlElement *get_root();
		void write_file(std::string filename);

	private:
        std::string header;
        std::string doctype;
		XmlElement *root;

		void read_element(XmlElement *E, std::string *content, 
                            unsigned int start, unsigned int end);
		void write_element(XmlElement *E, std::ofstream *f_out, 
                            unsigned int indent);
};

#endif
