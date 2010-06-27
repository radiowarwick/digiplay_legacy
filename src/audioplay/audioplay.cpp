#include <iostream>
using namespace std;

#include "audiolib/Audio.h"
#include "audiolib/InputFile.h"
#include "audiolib/OutputDsp.h"
#include "audiolib/ProcessMixer.h"
#include "audiolib/ProcessFader.h"
#include "audiolib/CounterTrigger.h"
using namespace Audio;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Error: no file specified" << endl;
    }
	// Create input sources and load
	InputFile* filereader1 = new InputFile();
    ProcessMixer* mixer = new ProcessMixer();
	// Create a DSP output
	OutputDsp* player = new OutputDsp("oss:/dev/dsp");
	
	// Connect everything up
    filereader1->load(string(argv[1]),0,441000000);
	filereader1->patch(OUT0,mixer,IN0);
    mixer->patch(OUT0,player,IN0);
    // Load track, and play it

	filereader1->play();
	sleep(1000);
}
