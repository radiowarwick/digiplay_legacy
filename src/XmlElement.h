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

struct xmlAttribute {
    std::string name;
    std::string value;
};

class XmlElement {
	public:
		XmlElement();
		XmlElement(std::string name);
		~XmlElement();

		void set_name(std::string text);
		void set_cdata(std::string text);
        std::string get_name();
        std::string get_cdata();

		xmlAttribute add_attribute(std::string name, std::string value);
		xmlAttribute add_attribute(xmlAttribute attr);
		xmlAttribute get_attribute(unsigned int index);
		xmlAttribute get_attribute(std::string name);
		void remove_attribute(unsigned int index);
		void remove_attribute(std::string name);
        bool has_attribute(std::string name);
		unsigned int count_attributes();

		XmlElement *add_element(std::string name);
        XmlElement *add_element(std::string name, std::string cdata);
		XmlElement *add_element(XmlElement *elem);
		XmlElement *get_element(unsigned int index);
		XmlElement *get_element(std::string name);
		void remove_element(unsigned int index);
		void remove_element(std::string name);
		unsigned int count_elements();
		
	private:
        std::string name;
        std::string cdata;
        std::vector<xmlAttribute> *attributes;
        std::vector<XmlElement*> *elements;
};

#endif
