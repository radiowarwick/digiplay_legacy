#include <iostream>
using namespace std;

#include "audio/Audio.h"
#include "audio/InputRaw.h"
#include "audio/OutputDsp.h"
#include "audio/ProcessMixer.h"
#include "audio/ProcessFader.h"
using namespace Audio;

int main() {
	InputRaw* filereader = new InputRaw();
//    InputRaw* filereader2 = new InputRaw();
//    InputRaw* filereader3 = new InputRaw();
    ProcessFader* fader1 = new ProcessFader();
	OutputDsp* player = new OutputDsp("/dev/dsp");
//    ProcessMixer* mixer = new ProcessMixer();
    cout << "== Connect filereader" << endl;
	filereader->connect(OUT0,fader1,IN0);
    fader1->connect(OUT0,player,IN0);
//	filereader->connect(OUT0,player,IN0);
//    cout << "== Connect filereader2" << endl;
//    filereader2->connect(OUT0,mixer,IN1);
//    cout << "== Connect filereader3" << endl;
//    filereader3->connect(OUT0,mixer,IN2);
//    cout << "== Connect mixer" << endl;
//    mixer->connect(OUT0,player,IN0);
    cout << "== Load filereader" << endl;
	filereader->load("/mnt/dps0-0/audio/0/06b4bfbfe7f57d98d9f0f1fe5c8cde4f",0,10526376);
//    cout << "== Load filereader2" << endl;
//	filereader2->load("/mnt/dps0-0/audio/0/0081e2e29d0aebdada5b5bf5e448c515",0,4410000);
//    cout << "== Load filereader3" << endl;
//    filereader3->load("/mnt/dps0-0/audio/0/06d84e4e532d82138a55edcc0b553810",0,4410000);
    cout << "== Play filereader" << endl;
	filereader->play();
//    sleep(3);
//    cout << "== Play filereader2" << endl;
//    filereader2->play();
//    sleep(3);
//    cout << "== Play filereader3" << endl;
//    filereader3->play();
    sleep(300);
//    cout << "== Stop filereader" << endl;
//	filereader2->stop();
//    sleep(10);
    filereader->stop();
//    sleep(5);
}
