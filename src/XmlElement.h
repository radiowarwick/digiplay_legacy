/*
 * XML Element class
 * XmlElement.h
 * Representation of a hierarchial XML element.
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
#ifndef CLASS_XMLELEMENT
#define CLASS_XMLELEMENT

#include <string>
#include <vector>
using namespace std;

struct xmlAttribute {
	string name;
	string value;
};

class XmlElement {
	public:
		XmlElement();
		XmlElement(string name);
		~XmlElement();

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

		XmlElement *add_element(string name);
		XmlElement *add_element(XmlElement *elem);
		XmlElement *get_element(unsigned int index);
		XmlElement *get_element(string name);
		void remove_element(unsigned int index);
		void remove_element(string name);
		unsigned int count_elements();
		
	private:
		string name;
		string cdata;
		vector<xmlAttribute> *attributes;
		vector<XmlElement*> *elements;
};

#endif
