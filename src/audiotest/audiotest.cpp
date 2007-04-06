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
	fader1->addFade(ProcessFader::Fade(0,220500,0.0,1.0));
	fader1->addFade(ProcessFader::Fade(441000,661500,1.0,0.0));
	fader1->addFade(ProcessFader::Fade(2646000,2866500,0.0,1.0));

	ProcessFader* fader2 = new ProcessFader();
	fader2->addFade(ProcessFader::Fade(0,220500,0.0,1.0));

	// Create a trigger
	CounterTrigger* trig = new CounterTrigger();
	trig->setTriggerTarget(filereader2);
	filereader1->addCounter(trig);


	// Create a mixer
	ProcessMixer* mixer = new ProcessMixer();

	// Create a DSP output
	OutputDsp* player = new OutputDsp("/dev/dsp");
	
	// Connect everything up
	filereader1->connect(OUT0,fader1,IN0);
	filereader2->connect(OUT0,fader2,IN0);
    fader1->connect(OUT0,mixer,IN0);
	fader2->connect(OUT0,mixer,IN1);
	mixer->connect(OUT0,player,IN0);

	filereader1->load("/home/admin/06b4bfbfe7f57d98d9f0f1fe5c8cde4f"
						,0,1052637);
	filereader2->load("/home/admin/06b4bfbfe7f57d98d9f0f1fe5c8cde4f"
						,5000000,10526376);
	trig->setTriggerSample(441000);
	filereader1->play();
//	sleep(50);
//	filereader2->play();

    sleep(30);
//    filereader1->stop();
//	filereader2->stop();
}
