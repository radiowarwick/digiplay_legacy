#include <iostream>
using namespace std;

#include "audio/Audio.h"
#include "audio/InputRaw.h"
#include "audio/OutputDsp.h"
#include "audio/ProcessMixer.h"
#include "audio/ProcessFader.h"
#include "audio/CounterTrigger.h"
using namespace Audio;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Error: no file specified" << endl;
    }
	// Create input sources and load
	InputRaw* filereader1 = new InputRaw();
    ProcessMixer* mixer = new ProcessMixer();
	// Create a DSP output
	OutputDsp* player = new OutputDsp("/dev/dsp");
	
	// Connect everything up
	filereader1->patch(OUT0,mixer,IN0);
    mixer->patch(OUT0,player,IN0);
    // Load track, and play it
    filereader1->load(string(argv[1]),0,441000000);
	filereader1->play();
	sleep(1000);
}
