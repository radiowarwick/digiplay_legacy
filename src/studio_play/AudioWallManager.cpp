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
using namespace std;

#include "dps.h"
#include "DataAccess.h"
#include "AudioWall.h"

#include "AudioWallManager.h"

AudioWallManager::AudioWallManager( AudioWall *A ) {
	_A = A;
    DB = new DataAccess();
    cout << "Completed AudioWallManager constructor" << endl;
}

AudioWallManager::~AudioWallManager() {

}

void AudioWallManager::load(unsigned int cartset) {
    cout << "AudioWallManager:: Loading cartset " << cartset << endl;
	_cartset = cartset;
	for (unsigned int i = 0; i < _pages.size(); i++) {
		for (unsigned int j = 0; j < _A->getSize(); j++) {
			delete _pages[i]->items[j];
		}
		delete _pages[i];
	}
	_pages.resize(0);
	
	short pagecount = atoi(DB->exec("AudioWallManagerLoad",
                            "SELECT max(cartwalls.page) "
                            "FROM cartwalls,cartsets "
                            "WHERE cartwalls.cartsetid = " 
							 	+ dps_itoa(cartset))[0][0].c_str()) + 1;
	for (int i = 0; i < pagecount; i++) {
		_pages.push_back(new Page);
		for (int j = 0; j < _A->getSize(); j++) {
			_pages[i]->items.push_back(new AudioWallItemSpec);
		}
	}
    PqxxResult R = DB->exec("AudioWallManagerLoad",
                        "SELECT * FROM v_cartwalls WHERE cartset_id = "
                        + dps_itoa(cartset) + " ORDER BY page, prop_name");
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
	bool change;

	unsigned int i = 0;
	while (i < R.size()) {
		change = false;
		file = R[i]["path"].c_str();
		md5 = R[i]["md5"].c_str();
		file += "/" + md5.substr(0,1) + "/" + md5;
		item = atoi(R[i]["cart"].c_str());
		page = atoi(R[i]["page"].c_str());
		text = R[i]["text"].c_str();
		start = atoi(R[i]["start"].c_str());
		end = atoi(R[i]["end"].c_str());
		title = R[i]["wall_desc"].c_str();

        AudioWallItemSpec* I = _pages[page]->items[item];
		if (I->file != file) change = true;
		I->file = file;
		if (I->start != start) change = true;
		I->start = start;
		if (I->end != end) change = true;
		I->end = end;
		if (I->text != text) change = true;
		I->text = text;

		if (_pages[page]->title != title) {
			_pages[page]->title = title;
			_A->setCaption(page,title);
		}

		while (i < R.size() && atoi(R[i]["page"].c_str()) == page
							&& atoi(R[i]["cart"].c_str()) == item) {
			p = R[i]["prop_name"].c_str();
            if (p == "ForeColourRGB") {
				fgColour = QRgb(atoi(R[i]["prop_value"].c_str()));
				if (I->fgColour != fgColour) 
					change = true;
				I->fgColour = fgColour;
            }
            else if (p == "BackColourRGB") {
				bgColour = QRgb(atoi(R[i]["prop_value"].c_str()));
				if (I->bgColour != bgColour)
					change = true;
				I->bgColour = bgColour;
			}
			i++;
		}
		if (change) {
            cout << "Detected a change on page " << page << " item " << item
                << endl;
            _A->setButton(page,item,*I);
		}
	}
}

