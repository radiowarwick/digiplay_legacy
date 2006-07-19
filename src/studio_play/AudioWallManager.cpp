#include <iostream>
using namespace std;

#include "dps.h"

#include "AudioWallManager.h"

AudioWallManager::AudioWallManager( AudioWall *A,  Connection *C ) {
	_A = A;
	_C = C;
}

AudioWallManager::~AudioWallManager() {

}

void AudioWallManager::load(unsigned int cartset) {
	cout << "Running load" << endl;
	Transaction T(*_C,"");
	short pagecount = atoi(T.exec("SELECT max(cartwalls.page) "
                             "FROM cartwalls,cartsets "
                             "WHERE cartwalls.cartset = 0")[0][0].c_str()) + 1;
	_pages.resize(pagecount);
	for (unsigned int i = 0; i < _pages.size(); i++) {
		_pages[i].items.resize(_A->getSize());
	}
	
	Result R = T.exec("SELECT audio.md5 AS md5, audio.start_smpl AS start, "
           "audio.end_smpl AS end, cartsaudio.cart AS cart, "
           "cartsaudio.text AS text, cartwalls.name AS name, "
           "cartwalls.description AS desc, cartsets.name AS cartset, "
           "cartwalls.page AS page, "
           "cartsets.description AS cartset_desc, cartsets.userid AS userid, "
           "cartsets.directory AS dir, cartproperties.id AS property, "
           "cartstyleprops.value AS prop_value, archives.localpath AS path, "
           "configuration.val AS cartset "
           "FROM audio, cartsaudio, cartwalls, cartsets, cartstyle, "
           "cartstyleprops, cartproperties, archives, configuration "
           "WHERE cartsaudio.audio = audio.id "
           "AND cartsaudio.cartwall = cartwalls.id "
           "AND cartwalls.cartset = cartsets.id "
           "AND cartsaudio.style = cartstyle.id "
           "AND cartstyleprops.style = cartstyle.id "
           "AND cartstyleprops.property = cartproperties.id "
           "AND audio.archive = archives.id "
		   "AND cartsets.id = " + dps_itoa(cartset)
//           "AND configuration.parameter = 'station_cartset' "
  //         "AND configuration.val = cartsets.id "
           + "ORDER BY cartwalls.id, cartsaudio.cart, cartproperties.id;");
	T.abort();

	string file = "";
	string md5 = "";
	string text = "";
	string title = "";
	unsigned long start = 0;
	unsigned long end = 0;
	QColor fgColor;
	QColor bgColor;
	short item = 0;
	short page = 0;
	short p = 0;
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

		if (_pages[page].items[item].file != file) change = true;
		_pages[page].items[item].file = file;
		if (_pages[page].items[item].start != start) change = true;
		_pages[page].items[item].start = start;
		if (_pages[page].items[item].end != end) change = true;
		_pages[page].items[item].end = end;
		if (_pages[page].items[item].text != text) change = true;
		_pages[page].items[item].text = text;
		if (_pages[page].title != title) {
			_pages[page].title = R[i]["cartset"].c_str();
			_A->setCaption(page,title);
		}
		//_pages[page].description = R[i]["desc"].c_str();

		while (i < R.size() && atoi(R[i]["page"].c_str()) == page
							&& atoi(R[i]["cart"].c_str()) == item) {
			p = atoi(R[i]["property"].c_str());
			switch (p) {
				case 0:
					fgColor = QRgb(atoi(R[i]["prop_value"].c_str()));
					if (_pages[page].items[item].fgColor != fgColor) 
						change = true;
					_pages[page].items[item].fgColor = fgColor;
					break;
				case 1:
					bgColor = QRgb(atoi(R[i]["prop_value"].c_str()));
					if (_pages[page].items[item].bgColor != bgColor)
						change = true;
					_pages[page].items[item].bgColor = bgColor;
					break;
			}
			i++;
		}
		if (change) {
			cout << "Setting button " << page << "/" << item << endl; 
			_A->setButton(page,item,_pages[page].items[item]);
		}
	}	
}

