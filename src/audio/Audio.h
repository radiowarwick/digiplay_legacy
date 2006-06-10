#ifndef NS_AUDIO
#define NS_AUDIO
namespace Audio {
	class Component;
	class Input;
	class InputRaw;
	class InputWav;
	class InputMp3;
	class InputDsp;
}

enum PORT { IN0, IN1, IN2, IN3, IN4, IN5, IN6, IN7, 
            OUT0, OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7 };

struct ConnectionMapping {
    PORT port;
    Audio::Component *component;
    PORT remotePort;
};

#ifndef ENUM_MESSAGE
#define ENUM_MESSAGE
enum MESSAGE {  NONE = 0,
                PLAY = 1,
                STOP = 2,
                PAUSE = 3 };
#endif

#endif