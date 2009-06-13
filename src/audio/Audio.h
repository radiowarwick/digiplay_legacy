#ifndef NS_AUDIO
#define NS_AUDIO

/**
 * Audio namespace contains all Audio Components
 */
namespace Audio {
    class AudioPacket;
    class CircularCache;
    
	class Component;
    class ComponentAudio;
    class ComponentMonitor;
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
    class ProcessLink;

	class Counter;
	class CounterTrigger;
}

// Basic audio typedefs and definitions
typedef unsigned long   SAMPLE;
typedef short           SAMPLEVAL;
typedef int             PORT;
// Audio component ports
#define OTHER 0
#define IN0 1
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define OUT0 -1
#define OUT1 -2
#define OUT2 -3
#define OUT3 -4

// Audio packet size definitions
#define AUDIO_BUFFER 512
#define PACKET_MULTIPLIER 2
// Audio packet size parameters
#define PACKET_SAMPLES AUDIO_BUFFER/2*PACKET_MULTIPLIER
#define FADER_STEPS 16
#define FADER_GRANULARITY PACKET_SAMPLES/FADER_STEPS
#define PACKET_BYTES PACKET_SAMPLES*2

/*enum PORT {     OTHER = 0,
                IN0,IN1,IN2,IN3,IN4,IN5,IN6,IN7,
                OUT0,OUT1,OUT2,OUT3,OUT4,OUT5,OUT6,OUT7,
                MON0,MON1,MON2,MON3,MON4,MON5,MON6,MON7 };
*/
#ifndef ENUM_MESSAGE
#define ENUM_MESSAGE

enum MESSAGE {  NONE = 0,
                PLAY = 1,
                STOP = 2,
                PAUSE = 3,
                START = 4,
                SEEK = 5 };
#endif

#ifndef ENUM_STATE
#define ENUM_STATE
enum STATE {	STATE_STOP = 0,
				STATE_PLAY = 1,
				STATE_PAUSE = 2 };
#endif

/**
 * Maps a foreign component, port and its state to a local port.
 */
struct ConnectionMapping {
    PORT port;
    Audio::Component *component;
    STATE state;
    PORT remotePort;
};

/**
 * Possible Cache states
 */
enum CACHE_STATE {
    CACHE_STATE_ACTIVE = 0,
    CACHE_STATE_INACTIVE = 1
};

/**
 * Possible cache control commands
 */
enum CACHE_COMMAND {
    CACHE_COMMAND_NONE = 0,
    CACHE_COMMAND_GO = 1,
    CACHE_COMMAND_STOP = 2
};

#endif
