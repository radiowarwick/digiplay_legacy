#include "sched_bin.h"

sched_bin::sched_bin(Transaction *T, string SQL, unsigned short b) {
	bin = T->exec(SQL);
	if (bin.size() == 0) {
		cout << " -> WARNING: bin " << b << " is empty!" << endl;
		cout << "   -> SQL: " << SQL << endl;
	}
	bin_id = b;
	t_null.isNull = true;
}

sched_bin::~sched_bin() {

}

unsigned int sched_bin::size() {
	return bin.size();
}

track sched_bin::at(unsigned int index) {
	track t;
	if (index > size() - 1 || index < 0) {
		cout << "sched_bin::title : ERROR index " << index 
					<< " out of range" << endl;
		return t_null;
	}
	t.isNull = false;
	t.bin = bin_id;
	t.index = index;
	t.audio_id = atoi(bin[index]["id"].c_str());
	t.md5 = bin[index]["md5"].c_str();
	t.title = bin[index]["title"].c_str();
	if (bin_id < 5) t.artist = bin[index]["artist"].c_str();
	t.trim_start_smpl = atoi(bin[index]["start_smpl"].c_str());
	t.trim_end_smpl = atoi(bin[index]["end_smpl"].c_str());
	t.length_smpl = t.trim_end_smpl - t.trim_start_smpl;
	t.fade_in_smpl = atoi(bin[index]["intro_smpl"].c_str());
	t.fade_out_smpl = atoi(bin[index]["extro_smpl"].c_str());
	if (t.fade_out_smpl > t.trim_end_smpl)
		t.fade_out_smpl = t.trim_end_smpl;
	return t;
}

track sched_bin::getRandom() {
	int x = (int)((float)bin.size() * rand()/(RAND_MAX+1.0));
	return at(x);
}

track sched_bin::getShorter(track t_old, unsigned long min_smpl) {
	track t;
	unsigned short count = 0;
	do {
		t = getRandom();
		count++;
		if (count > 100) return t_old;
	} while (t.length_smpl > t_old.length_smpl || t.length_smpl < min_smpl);
	return t;
}
