#include <iostream>
using namespace std;

#include "audio/Audio.h"
#include "audio/InputRaw.h"
#include "audio/OutputDsp.h"
using namespace Audio;

int main() {
	InputRaw* filereader = new InputRaw();
	OutputDsp* player = new OutputDsp("/dev/dsp");
	filereader->connect(OUT0,player,IN0);
	filereader->load("/mnt/dps0-0/audio/0/0081e2e29d0aebdada5b5bf5e448c515",0,441000);
    sleep(5);
	filereader->play();
	sleep(10);
//	filereader->stop();
}
