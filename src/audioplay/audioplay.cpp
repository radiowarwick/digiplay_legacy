#include <iostream>
using namespace std;

#include "audio/Audio.h"
#include "audio/InputRaw.h"
#include "audio/OutputDsp.h"
#include "audio/ProcessMixer.h"
#include "audio/ProcessFader.h"
#include "audio/CounterTrigger.h"
using namespace Audio;

int main() {
	// Create input sources and load
	InputRaw* filereader1 = new InputRaw("/dev/null");
	// Create a DSP output
	OutputDsp* player = new OutputDsp("/dev/dsp");
	
	// Connect everything up
	filereader1->connect(OUT0,player,IN0);

//	filereader1->load("/mnt/music/0/00131818d2c415982e341539abac6fdb"
	filereader1->load("/tmp/channel1.raw"
						,0,44100000);
	filereader1->play();
	sleep(1000);
}
