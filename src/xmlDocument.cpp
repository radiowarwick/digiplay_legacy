/*
 * XML Document class
 * xmlDocument.cpp
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
#include "xmlDocument.h"

#include <iostream>
using namespace std;

#include "dps.h"

xmlDocument::xmlDocument() {
	root = new xmlElement();
	header = "<?xml version=\"1.0\"?>";
	doctype = "";
}

xmlDocument::xmlDocument(string filename) {
	root = new xmlElement();

	ifstream *f_in = new ifstream(filename.c_str());
	if (!f_in->is_open() || !f_in->good()) {
		cout << "Failed to open file: " << filename << endl;
		delete this;
	}
	getline((*f_in),header);
	getline((*f_in),doctype);

	string buffer,data;
	while (!f_in->eof()) {
		getline((*f_in),buffer);
		while (buffer.c_str()[0] == '\t') 
			buffer = buffer.substr(1,buffer.size() - 1);
		data += " " + buffer;
	}
	read_element(root,&data,0,data.size());
}

xmlDocument::~xmlDocument() {
	delete root;
}

void xmlDocument::set_header(string text) {
	header = text;
}

void xmlDocument::set_doctype(string text) {
	doctype = text;
}

xmlElement *xmlDocument::get_root() {
	return root;
}

void xmlDocument::write_file(string filename) {
	ofstream *f_out = new ofstream(filename.c_str());
	(*f_out) << header << endl;
	(*f_out) << doctype << endl;
	write_element(root,f_out,0);
	f_out->close();
	delete f_out;
}

void xmlDocument::read_element(xmlElement *E, string *content, unsigned int start, unsigned int end) {
	unsigned short depth = 0;
	unsigned short i = start;
	bool element_open = false;
	string attr_name = "", text = "";
	bool attr_equals = false;
	
	unsigned short data_start = start;
	bool quotes = false;

	// Extract element name
	while (i < end) {
		// discard text until we open first element
		if (!element_open) {
			if (content->at(i) == '<') element_open = true;
			i++; continue;
		}
		if (content->at(i) == ' ' || content->at(i) == '>') break;
		text += content->at(i);
		i++;
	}
	E->set_name(dps_strTrim(text));
	text = "";
//	cout << "[" << E->get_name() << "]" << endl;
//	cout << " -> " << (*content).substr(start, end - start) << endl;

	// Extract attributes
	while (i < end) {
		// Ensure we disregard whitespace within quotes
		if (content->at(i) == '\"') {
			if (quotes) quotes = false;
			else quotes = true;
			i++;
			continue;
		}

		// If we've hit whitespace out of quotes, we have a new attribute
		if ((content->at(i) == ' ' || content->at(i) == '/' 
					|| content->at(i) == '>') && !quotes) {
			// if it's actually an attribute, add it
			if (attr_name != "") {
//				cout << attr_name << " == " << text << endl;
				E->add_attribute(attr_name, text);
				attr_equals = false;
			}
			attr_name = "";
			text = "";
			
			// Check if we've got all the attributes
			if (content->at(i) == '>') break;

			i++;
			continue;
		}

		// Got attribute name, now get it's value
		if (content->at(i) == '=') {
			attr_equals = true;
			i++;
			continue;
		}
		if (!attr_equals) attr_name += content->at(i);
		else text += content->at(i);
		i++;
	}
	i++;

	// Extract and CDATA if present
	text = "";
	while (i < end && content->at(i) != '<'){
		text += content->at(i);
		i++;
	}
	E->set_cdata(dps_strTrim(text));
	if (E->get_cdata() != "") {
	//	cout << "CDATA: [" << E->get_cdata() << "]" << endl;
		return;
	}
	
	// If there's no CDATA, look for subelements
	// Assign weights to the special characters <, >, / so that when a
	// subelement is completed, the sum of weights will be zero.
	data_start = i;
	while (i < end) {
		if (content->at(i) == '<') depth += 2;
		if (content->at(i-1) == '<' && content->at(i) == '/') depth -= 2;
		if (content->at(i) == '>') depth -= 1;
		if (content->at(i-1) == '/' && content->at(i) == '>') depth -= 1;
		i++;
		// When weight is zero, add a new element and recursively parse.
		if (depth == 0) {
			xmlElement *E_new = E->add_element(new xmlElement());
			read_element(E_new,content,data_start,i);
			data_start = i;
			while (i < end && content->at(i) == ' ') i++;
			// if next characters are '</' we've got to the end so end
			if (content->at(i) == '<' && content->at(i+1) == '/') break;
		}
	}
}

void xmlDocument::write_element(xmlElement *E, ofstream *f_out, unsigned int indent) {
	for (unsigned int i = 0; i < indent; i++) (*f_out) << "\t";

	(*f_out) << "<" << E->get_name();
	for (unsigned int i = 0; i < E->count_attributes(); i++) {
		if (i == 0) (*f_out) << " ";
		(*f_out) <<  E->get_attribute(i).name << "=\"" 
					<< E->get_attribute(i).value << "\"";
		if (i < E->count_attributes() - 1) {
			(*f_out) << endl;
			for (unsigned int j = 0; j < indent+2; j++) (*f_out) << "\t";
		}
	}
	// If it's simply CDATA
	if (E->get_cdata() != "") {
		(*f_out) << ">" << E->get_cdata() 
					<< "</" << E->get_name() << ">" << endl;
	}
	// If there are child elements
	else if (E->count_elements() > 0) {
		(*f_out) << ">" << endl;
		for (unsigned int i = 0; i < E->count_elements(); i++) {
			write_element(E->get_element(i),f_out,indent+1);
		}
		for (unsigned int i = 0; i < indent; i++) (*f_out) << "\t";
		(*f_out) << "</" << E->get_name() << ">" << endl;
	}
	// Otherwise, just attributes, so close with shorthand
	else {
		(*f_out) << " />" << endl;
	}
}
