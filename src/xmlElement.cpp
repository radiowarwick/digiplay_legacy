#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "Logger.h"

#include "xmlElement.h"

/** Constructor: Createse a new XML Element node
 */
xmlElement::xmlElement() {
	attributes = new vector<xmlAttribute>;
	elements = new vector<xmlElement*>;
	name = "";
	cdata = "";
}

/** Constructor: Creates a new XML Element node with the given name
 */
xmlElement::xmlElement(string name) {
    attributes = new vector<xmlAttribute>;
    elements = new vector<xmlElement*>;
	this->name = name;
	cdata = "";
}

/** Destructor
 */
xmlElement::~xmlElement() {
	for (unsigned int i = 0; i < elements->size(); i++) {
		delete elements->at(i);
	}
	delete elements;
	delete attributes;
}

/** Sets the name of the element node
 * @param	text	The new name for the element node
 */
void xmlElement::set_name(string text) {
	name = text;
}

/** Sets the cdata for the element node
 * @param 	text	The new cdata for the element node
 */
void xmlElement::set_cdata(string text) {
	cdata = text;
}

/** Gets the name of the element node
 * @return	Name of the element
 */
string xmlElement::get_name() {
	return name;
}

/** Gets the cdata associated with the element node
 * @return	CDATA associated with the element
 */
string xmlElement::get_cdata() {
	return cdata;
}

/** Adds a new attribute to the element
 * @param	name	Name of the attribute
 * @param	value	Value of the attribute
 * @return	xmlAttribute structure for the added attribute
 */
xmlAttribute xmlElement::add_attribute(string name, string value) {
	xmlAttribute A;
	A.name = name;
	A.value = value;
	return add_attribute(A);
}

/** Adds a new attribute to the element
 * @param	attr	xmlAttribute structure containing the required data
 * @return	xmlAttribute structure for the added attribute
 */
xmlAttribute xmlElement::add_attribute(xmlAttribute attr) {
	attributes->push_back(attr);
	return attr;
}

/** Gets the attribute at a given index
 * @param	index	Index position of the attribute to get
 * @return	xmlAttribute structure for the requested attribute or an empty
 * 			structure if index out of range
 */
xmlAttribute xmlElement::get_attribute(unsigned int index) {
	char* routine = "xmlElement::get_attribute";
	if (index >= 0 && index < attributes->size()) {
		return attributes->at(index);
	}
	else {
		stringstream S;
		S << "Attribute " << index << " out of range in " << name;
		Logger::log(ERROR,routine,S.str(),1);
		xmlAttribute A;
		return A;
	}
}

/** Gets the attribute with the given name
 * @param	name	Name of attribute to retrieve
 * @return	xmlAttribute structure for the requested attribute or an empty
 * 			structure if attribute does not exist
 */
xmlAttribute xmlElement::get_attribute(string name) {
	char* routine = "xmlElement::get_attribute";
	for (unsigned int i = 0; i < attributes->size(); i++)
		if (attributes->at(i).name == name)
			return attributes->at(i);
	stringstream S;
	S << "Attribute " << name << " does not exist in " << this->name;
	Logger::log(ERROR,routine,S.str(),5);
	xmlAttribute A;
	return A;
}

void xmlElement::remove_attribute(unsigned int index) {
	char* routine = "xmlElement::remove_attribute";
	if (index >= 0 && index < attributes->size()) {
		attributes->erase(attributes->begin() + index);
	}
	else {
		stringstream S;
		S << "Attribute " << index << " out of range in " << name;
		Logger::log(ERROR,routine,S.str(),5);
	}
}

void xmlElement::remove_attribute(string name) {
	char* routine = "xmlElement::remove_attribute";
	for (unsigned int i = 0; i < attributes->size(); i++)
		if (attributes->at(i).name == name) {
			attributes->erase(attributes->begin() + i);
			return;
		}
	stringstream S;
	S << "Attribute " << name << " does not exist in " << this->name;
	Logger::log(ERROR,routine,S.str(),5);
}

unsigned int xmlElement::count_attributes() {
	return attributes->size();
}

xmlElement *xmlElement::add_element(string name) {
	xmlElement *E = new xmlElement(name);
	return add_element(E);
}

xmlElement *xmlElement::add_element(xmlElement *elem) {
	elements->push_back(elem);
	return elem;
}

xmlElement *xmlElement::get_element(unsigned int index) {
	char* routine = "xmlElement::get_element";
	if (index >= 0 && index < elements->size())
		return elements->at(index);
	stringstream S;
	S << "Element " << index << " out of range in " << name;
	Logger::log(ERROR,routine,S.str(),5);
	return NULL;
}

xmlElement *xmlElement::get_element(string name) {
	char* routine = "xmlElement::get_element";
	for (unsigned int i = 0; i < elements->size(); i++)
		if (elements->at(i)->name == name)
			return elements->at(i);
	stringstream S;
	S << "Element " << name << " does not exist in " << this->name;
	Logger::log(ERROR,routine,S.str(),5);
	return NULL;
}

void xmlElement::remove_element(unsigned int index) {
	char* routine = "xmlElement::remove_element";
	if (index >= 0 && index < elements->size())
		elements->erase(elements->begin() + index);
	else {
		stringstream S;
		S << "Element " << index << " out of range in " << name;
		Logger::log(ERROR,routine,S.str(),5);
	}
}

void xmlElement::remove_element(string name) {
	char* routine = "xmlElement::remove_element";
	for (unsigned int i = 0; i < elements->size(); i++)
		if (elements->at(i)->name == name) {
			elements->erase(elements->begin() + i);
			return;
		}
	stringstream S;
	S << "Element " << name << " does not exist in " << this->name;
	Logger::log(ERROR,routine,S.str(),5);
}

unsigned int xmlElement::count_elements() {
	return elements->size();
}
