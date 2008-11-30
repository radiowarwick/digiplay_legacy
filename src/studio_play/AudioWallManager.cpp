/*
 * Audiowall Management Class
 * AudioWallManager.cpp
 * Interfaces the AudioWall widget to the database
 *
 * Copyright (c) 2006 Chris Cantwell
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
#include <cstdlib>
using namespace std;

#include "dps.h"
#include "DataAccess.h"
#include "AudioWall.h"

#include "AudioWallManager.h"

AudioWallManager::AudioWallManager( AudioWall *A ) {
	_A = A;
    DB = new DataAccess();
}

AudioWallManager::~AudioWallManager() {

}

void AudioWallManager::load(unsigned int awset) {
	_awset = awset;
    if (awset == 0) {
    	for (unsigned int i = 0; i < _pages.size(); i++) {
    		for (unsigned int j = 0; j < _A->getSize(); j++) {
    			delete _pages[i]->items[j];
    		}
    		delete _pages[i];
            _A->deletePage(0);
    	}
    	_pages.resize(0);
        return;
    }
	short pagecount = atoi(DB->exec("AudioWallManagerLoad",
                            "SELECT max(aw_walls.page) "
                            "FROM aw_walls,aw_sets "
                            "WHERE aw_walls.set_id = " 
							 	+ dps_itoa(awset))[0][0].c_str()) + 1;
    for (int i = _pages.size() - 1; i > pagecount - 1; i--) {
        for (int j = 0; j < _A->getSize(); j++) {
            delete _pages[i]->items[j];
        }
        _A->deletePage(i);
        delete _pages[i];
        _pages.erase(_pages.begin() + i);
    }
	for (int i = _pages.size(); i < pagecount; i++) {
		_pages.push_back(new Page);
        _A->addPage();
		for (int j = 0; j < _A->getSize(); j++) {
			_pages[i]->items.push_back(new AudioWallItemSpec);
		}
	}
	
    PqxxResult R = DB->exec("AudioWallManagerLoad",
                        "SELECT * FROM v_audiowalls WHERE set_id = "
                        + dps_itoa(awset) + " ORDER BY page, prop_name");
	DB->abort("AudioWallManagerLoad");
	
	string file = "";
	string md5 = "";
	string text = "";
	string title = "";
	unsigned long start = 0;
	unsigned long end = 0;
	QColor fgColour;
	QColor bgColour;
	short item = 0;
	short page = 0;
	string p;
	
	// Configure changetable - assume we need to change nothing, and nothing
	// exists
	vector< vector<bool> > changeTable(_pages.size());
	vector< vector<bool> > existsTable(_pages.size());
	for (unsigned int i = 0; i < changeTable.size(); ++i) {
		changeTable[i].resize(_pages[i]->items.size());
		existsTable[i].resize(_pages[i]->items.size());
		for (unsigned int j = 0; j < changeTable[i].size(); ++j) {
			changeTable[i][j] = false;
			existsTable[i][j] = false;
		}
	}

	unsigned int i = 0;
	while (i < R.size()) {
		file = R[i]["path"].c_str();
		md5 = R[i]["md5"].c_str();
		file += "/" + md5.substr(0,1) + "/" + md5;
		item = atoi(R[i]["item"].c_str());
		page = atoi(R[i]["page"].c_str());
		text = R[i]["text"].c_str();
		start = atoi(R[i]["start"].c_str());
		end = atoi(R[i]["end"].c_str());
		title = R[i]["wall_desc"].c_str();
		// this item exists
		existsTable[page][item] = true;

        AudioWallItemSpec* I = _pages[page]->items[item];
		if (I->file != file) changeTable[page][item] = true;
		I->file = file;
		if (I->start != start) changeTable[page][item] = true;
		I->start = start;
		if (I->end != end) changeTable[page][item] = true;
		I->end = end;
		if (I->text != text) changeTable[page][item] = true;
		I->text = text;

		if (_pages[page]->title != title) {
			_pages[page]->title = title;
			_A->setCaption(page,title);
		}

		while (i < R.size() && atoi(R[i]["page"].c_str()) == page
							&& atoi(R[i]["item"].c_str()) == item) {
			p = R[i]["prop_name"].c_str();
            if (p == "ForeColourRGB") {
				fgColour = QRgb(atoi(R[i]["prop_value"].c_str()));
				if (I->fgColour != fgColour) 
					changeTable[page][item] = true;
				I->fgColour = fgColour;
            }
            else if (p == "BackColourRGB") {
				bgColour = QRgb(atoi(R[i]["prop_value"].c_str()));
				if (I->bgColour != bgColour)
					changeTable[page][item] = true;
				I->bgColour = bgColour;
			}
			i++;
		}
	}

	// Add to change list, those elements which now don't exist
	for (unsigned int page = 0; page < existsTable.size(); ++page) {
		for (unsigned int item = 0; item < existsTable[page].size(); ++item) {
			if (!existsTable[page][item]) {
				AudioWallItemSpec* I = _pages[page]->items[item];
				if (I->file != "" || I->text != "") {
					changeTable[page][item] = true;
					I->file = "";
					I->text = "";
				}
			}
		}
	}
	
	// Apply changes
	for (unsigned int page = 0; page < changeTable.size(); ++page) {
		for (unsigned int item = 0; item < changeTable[page].size(); ++item) {
			if (changeTable[page][item]) {
            	_A->setButton(page, item, *_pages[page]->items[item]);
			}
		}
	}

}
