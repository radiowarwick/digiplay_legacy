#ifndef NS_AUDIO
#define NS_AUDIO
namespace Audio {
	class Component;

	class Input;
	class InputRaw;
	class InputWav;
	class InputMp3;
	class InputDsp;
	
	class Output;
	class OutputRaw;
	class OutputDsp;

	class Process;
    class ProcessMixer;

	class Counter;
}

typedef unsigned int PORT;
#define IN0 0
#define IN1 1
#define IN2 2
#define IN3 3
#define OUT0 0
#define OUT1 1
#define OUT2 2
#define OUT3 3

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
