#ifndef NS_AUDIO
#define NS_AUDIO
// Audio namespace
namespace Audio {
    class AudioPacket;

    class Thread;
	class Component;
	class Input;
	class InputRaw;
        class InputFlac;
	class InputWav;
	class InputMp3;
	class InputDsp;
	
	class Output;
	class OutputRaw;
	class OutputDsp;

	class Process;
    class ProcessMixer;
    class ProcessFader;

	class Counter;
	class CounterTrigger;
}

// Basic audio typedefs and definitions
typedef unsigned long   SAMPLE;
typedef short           SAMPLEVAL;
typedef int             PORT;
#define OTHER 0
#define IN0 1
#define IN1 2
#define IN2 3
#define IN3 4
#define OUT0 -1
#define OUT1 -2
#define OUT2 -3
#define OUT3 -4

#define AUDIO_BUFFER 512
#define PACKET_MULTIPLIER 8

#define PACKET_SAMPLES AUDIO_BUFFER/2*PACKET_MULTIPLIER
#define FADER_STEPS 16
#define FADER_GRANULARITY PACKET_SAMPLES/FADER_STEPS
#define PACKET_BYTES PACKET_SAMPLES*2

#ifndef ENUM_MESSAGE
#define ENUM_MESSAGE
enum MESSAGE {  NONE = 0,
                PLAY = 1,
                STOP = 2,
                PAUSE = 3 };
#endif

#ifndef ENUM_STATE
#define ENUM_STATE
enum STATE {	STATE_STOP = 0,
				STATE_PLAY = 1,
				STATE_PAUSE = 2 };
#endif

struct ConnectionMapping {
    PORT port;
    Audio::Component *component;
    STATE state;
    PORT remotePort;
};

#endif
