/*
 * System Management module
 * SystemManager.cpp
 * Provides global archive management operations on a DPS system
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
#include "SystemManager.h"

SystemManager::SystemManager() {
	Config *Conf = new Config("digiplay");
	try {
		C = new Connection(Conf->getDBConnectString());
	}
	catch (...) {
		cout << "Failed to connect to database" << endl;
		exit(-1);
	}

	archives = new vector<ArchiveManager*>;

	/* Load archives */
	T = new Transaction(*C,"");
	archive A;
	Result R = T->exec("SELECT * FROM archives ORDER BY id");
	for (unsigned short i = 0; i < R.size(); i++) {
		A.id = atoi(R[i]["id"].c_str());
		A.name = R[i]["name"].c_str();
		A.localPath = R[i]["localPath"].c_str();
		A.remotePath = R[i]["remotePath"].c_str();
		archives->push_back(new ArchiveManager(A));
	}
	T->abort();
	delete T;
}

SystemManager::~SystemManager() {

}

ArchiveManager* SystemManager::atArchive(unsigned int index) {
    if (index > archives->size() - 1) {
        cout << "ArchiveManager::atArchive: index " << index 
                        << " out of range." << endl;
    	return NULL;
	}
    return archives->at(index);
}

ArchiveManager* SystemManager::atArchive(string name) {
	for (unsigned short i = 0; i < archives->size(); i++) {
		if (name == archives->at(i)->spec().name)
			return archives->at(i);
	}
	return NULL;
}

short SystemManager::sizeArchive() {
	return archives->size();
}

void SystemManager::addArchive(string name, string localPath, 
										string remotePath) {
	string SQL;
	if (atArchive(name)) {
		cout << "SystemManager::addArchive: Named archive exists!" << endl;
		return;
	}
	try {
		T = new Transaction(*C,"addArchive");
		SQL = "INSERT INTO archives (name, localPath, remotePath) "
			"VALUES ('" + escape_binary(name) + "','" 
			+ escape_binary(localPath) + "','" + escape_binary(remotePath) 
			+ "')";
		T->exec(SQL);
		SQL = "SELECT * FROM archives WHERE name='" + name + "'";
		Result R = T->exec(SQL);
		T->commit();
		delete T;

		archive A;
        A.id = atoi(R[0]["id"].c_str());
        A.name = R[0]["name"].c_str();
	    A.localPath = R[0]["localPath"].c_str();
        A.remotePath = R[0]["remotePath"].c_str();
        archives->push_back(new ArchiveManager(A));							
	}
	catch (...) {
		cout << "SystemManager::addArchive: Failed to add archive" << endl;
		cout << " -> SQL: " << SQL << endl;
	}
}

void SystemManager::createArchive(string name, string localPath, 
										string remotePath) {

}

void SystemManager::dropArchive(unsigned int index) {
	if (index > archives->size() - 1) {
		cout << "SystemManager::dropArchive: Index out of range!" << endl;
		return;
	}
	
	string SQL = "DELETE FROM archives WHERE name='" 
						+ archives->at(index)->spec().name + "'";
	try {
		T = new Transaction(*C,"dropArchive");
		T->exec(SQL);
		T->commit();
		delete T;

		archives->erase(archives->begin() + index);
	}
	catch (...) {
		cout << "SystemManager::dropArchive: Failed to delete archive" << endl;
		cout << SQL << endl;
	}
}

/*
 * PRIVATE
 */
void SystemManager::loadArchives() {

}
