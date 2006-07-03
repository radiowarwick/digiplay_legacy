#include "xmlElement.h"

#include <iostream>
#include <string>
using namespace std;

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
	if (index >= 0 && index < attributes->size()) {
		return attributes->at(index);
	}
	else {
		cout << "Attribute " << index << " out of range in " << name << endl;
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
	for (unsigned int i = 0; i < attributes->size(); i++)
		if (attributes->at(i).name == name)
			return attributes->at(i);
	cout << "Attribute " << name << " does not exist in " << this->name << endl;
	xmlAttribute A;
	return A;
}

void xmlElement::remove_attribute(unsigned int index) {
	if (index >= 0 && index < attributes->size()) {
		attributes->erase(attributes->begin() + index);
	}
	else {
		cout << "Attribute " << index << " out of range in " << name << endl;
	}
}

void xmlElement::remove_attribute(string name) {
	for (unsigned int i = 0; i < attributes->size(); i++)
		if (attributes->at(i).name == name) {
			attributes->erase(attributes->begin() + i);
			return;
		}
	cout << "Attribute " << name << " does not exist in " << this->name << endl;
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
	if (index >= 0 && index < elements->size())
		return elements->at(index);
	cout << "Element " << index << " out of range in " << name << endl;
	return NULL;
}

xmlElement *xmlElement::get_element(string name) {
	for (unsigned int i = 0; i < elements->size(); i++)
		if (elements->at(i)->name == name)
			return elements->at(i);
	cout << "Element " << name << " does not exist in " << this->name << endl;
	return NULL;
}

void xmlElement::remove_element(unsigned int index) {
	if (index >= 0 && index < elements->size())
		elements->erase(elements->begin() + index);
	else
		cout << "Element " << index << " out of range in " << name << endl;
}

void xmlElement::remove_element(string name) {
	for (unsigned int i = 0; i < elements->size(); i++)
		if (elements->at(i)->name == name) {
			elements->erase(elements->begin() + i);
			return;
		}
	cout << "Element " << name << " does not exist in " << this->name << endl;
}

unsigned int xmlElement::count_elements() {
	return elements->size();
}
