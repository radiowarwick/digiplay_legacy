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
	InputRaw* filereader1 = new InputRaw();
    InputRaw* filereader2 = new InputRaw();
	    
	// Create faders
	ProcessFader* fader1 = new ProcessFader();
	fader1->addNode(0,0.0);
	fader1->addNode(220500,1.0);
	fader1->addNode(441000,1.0);
	fader1->addNode(661500,0.0);
	fader1->addNode(2646000,0.0);
	fader1->addNode(2866500,1.0);

	ProcessFader* fader2 = new ProcessFader();
	fader2->addNode(0,0.0);
	fader2->addNode(220500,1.0);

	// Create a trigger
	CounterTrigger* trig = new CounterTrigger();
	trig->setTriggerTarget(filereader2);
	filereader1->addCounter(trig);


	// Create a mixer
	ProcessMixer* mixer = new ProcessMixer();

	// Create a DSP output
	OutputDsp* player = new OutputDsp("/dev/dsp");
	
	// Connect everything up
	filereader1->patch(OUT0,fader1,IN0);
	filereader2->patch(OUT0,fader2,IN0);
    fader1->patch(OUT0,mixer,IN0);
	fader2->patch(OUT0,mixer,IN1);
	mixer->patch(OUT0,player,IN0);

	filereader1->load("/tmp/output.raw"
						,0,44100000);
	trig->setTriggerSample(44100000);
	filereader1->play();
//	sleep(50);
//	filereader2->play();

    sleep(30);
//    filereader1->stop();
//	filereader2->stop();
}
