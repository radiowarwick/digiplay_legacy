/*
 * XML Element class
 * XmlElement.cpp
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
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "Logger.h"

#include "XmlElement.h"

/** Constructor: Createse a new XML Element node
 */
XmlElement::XmlElement() {
	attributes = new vector<xmlAttribute>;
	elements = new vector<XmlElement*>;
	name = "";
	cdata = "";
}

/** Constructor: Creates a new XML Element node with the given name
 */
XmlElement::XmlElement(string name) {
    attributes = new vector<xmlAttribute>;
    elements = new vector<XmlElement*>;
	this->name = name;
	cdata = "";
}

/** Destructor
 */
XmlElement::~XmlElement() {
	for (unsigned int i = 0; i < elements->size(); i++) {
		delete elements->at(i);
	}
	delete elements;
	delete attributes;
}

/** Sets the name of the element node
 * @param	text	The new name for the element node
 */
void XmlElement::set_name(string text) {
	name = text;
}

/** Sets the cdata for the element node
 * @param 	text	The new cdata for the element node
 */
void XmlElement::set_cdata(string text) {
	cdata = text;
}

/** Gets the name of the element node
 * @return	Name of the element
 */
string XmlElement::get_name() {
	return name;
}

/** Gets the cdata associated with the element node
 * @return	CDATA associated with the element
 */
string XmlElement::get_cdata() {
	return cdata;
}

/** Adds a new attribute to the element
 * @param	name	Name of the attribute
 * @param	value	Value of the attribute
 * @return	xmlAttribute structure for the added attribute
 */
xmlAttribute XmlElement::add_attribute(string name, string value) {
	xmlAttribute A;
	A.name = name;
	A.value = value;
	return add_attribute(A);
}

/** Adds a new attribute to the element
 * @param	attr	xmlAttribute structure containing the required data
 * @return	xmlAttribute structure for the added attribute
 */
xmlAttribute XmlElement::add_attribute(xmlAttribute attr) {
	attributes->push_back(attr);
	return attr;
}

/** Gets the attribute at a given index
 * @param	index	Index position of the attribute to get
 * @return	xmlAttribute structure for the requested attribute or an empty
 * 			structure if index out of range
 */
xmlAttribute XmlElement::get_attribute(unsigned int index) {
	char* routine = "XmlElement::get_attribute";
	if (index < attributes->size()) {
		return attributes->at(index);
	}
	else {
		stringstream S;
		S << "Attribute " << index << " out of range in " << name;
		L_ERROR(LOG_XML,S.str());
		xmlAttribute A;
		return A;
	}
}

/** Gets the attribute with the given name
 * @param	name	Name of attribute to retrieve
 * @return	xmlAttribute structure for the requested attribute or an empty
 * 			structure if attribute does not exist
 */
xmlAttribute XmlElement::get_attribute(string name) {
	char* routine = "XmlElement::get_attribute";
	for (unsigned int i = 0; i < attributes->size(); i++)
		if (attributes->at(i).name == name)
			return attributes->at(i);
	stringstream S;
	S << "Attribute " << name << " does not exist in " << this->name;
	L_ERROR(LOG_XML,S.str());
	xmlAttribute A;
	return A;
}

void XmlElement::remove_attribute(unsigned int index) {
	char* routine = "XmlElement::remove_attribute";
	if (index < attributes->size()) {
		attributes->erase(attributes->begin() + index);
	}
	else {
		stringstream S;
		S << "Attribute " << index << " out of range in " << name;
		L_ERROR(LOG_XML,S.str());
	}
}

void XmlElement::remove_attribute(string name) {
	char* routine = "XmlElement::remove_attribute";
	for (unsigned int i = 0; i < attributes->size(); i++)
		if (attributes->at(i).name == name) {
			attributes->erase(attributes->begin() + i);
			return;
		}
	stringstream S;
	S << "Attribute " << name << " does not exist in " << this->name;
	L_ERROR(LOG_XML,S.str());
}

bool XmlElement::has_attribute(string name) {
    char* routine = "XmlElement::has_attribute";
    for (unsigned int i = 0; i < attributes->size(); i++) {
        if (attributes->at(i).name == name) {
            return true;
        }
    }
    return false;
}

unsigned int XmlElement::count_attributes() {
	return attributes->size();
}

XmlElement *XmlElement::add_element(string name) {
	XmlElement *E = new XmlElement(name);
	return add_element(E);
}

XmlElement* XmlElement::add_element(std::string name, std::string cdata) {
    XmlElement *E = new XmlElement(name);
    E->set_cdata(cdata);
    return add_element(E);
}

XmlElement *XmlElement::add_element(XmlElement *elem) {
	elements->push_back(elem);
	return elem;
}

XmlElement *XmlElement::get_element(unsigned int index) {
	char* routine = "XmlElement::get_element";
	if (index < elements->size())
		return elements->at(index);
	stringstream S;
	S << "Element " << index << " out of range in " << name;
	L_ERROR(LOG_XML,S.str());
	return NULL;
}

XmlElement *XmlElement::get_element(string name) {
	char* routine = "XmlElement::get_element";
	for (unsigned int i = 0; i < elements->size(); i++)
		if (elements->at(i)->name == name)
			return elements->at(i);
	stringstream S;
	S << "Element " << name << " does not exist in " << this->name;
	L_ERROR(LOG_XML,S.str());
	return NULL;
}

void XmlElement::remove_element(unsigned int index) {
	char* routine = "XmlElement::remove_element";
	if (index < elements->size())
		elements->erase(elements->begin() + index);
	else {
		stringstream S;
		S << "Element " << index << " out of range in " << name;
		L_ERROR(LOG_XML,S.str());
	}
}

void XmlElement::remove_element(string name) {
	char* routine = "XmlElement::remove_element";
	for (unsigned int i = 0; i < elements->size(); i++)
		if (elements->at(i)->name == name) {
			elements->erase(elements->begin() + i);
			return;
		}
	stringstream S;
	S << "Element " << name << " does not exist in " << this->name;
	L_ERROR(LOG_XML,S.str());
}

unsigned int XmlElement::count_elements() {
	return elements->size();
}
