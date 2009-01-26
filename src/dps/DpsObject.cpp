/*
 * DPS Object
 * DpsObject.h
 * Base class for all DPS objects
 *
 * Copyright (c) 2006-2009 Chris Cantwell
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
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

#include "DataAccess.h"
#include "Logger.h"

#include "DpsObject.h"

DataAccess* DpsObject::mDB = 0;

DpsObject::DpsObject() 
		: mType		(DPS_OBJECT) {

}

DpsObject::~DpsObject() {

}

enum DpsObjectType DpsObject::getType() {
	return mType;
}

std::string DpsObject::itoa(unsigned int pValue, unsigned int pLength) {
	stringstream S;
	S << pValue;
	string vStr = S.str();
	if (pLength == 0) {
		return vStr;
	}
	for (unsigned int i = vStr.size(); i < pLength; ++i) {
		vStr = "0" + vStr;
	}
	return vStr;
}

unsigned int DpsObject::atoi(std::string pString) {
	return std::atoi(pString.c_str());
}

