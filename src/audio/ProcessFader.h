#ifndef CLASS_AUDIO_PROCESS_FADER
#define CLASS_AUDIO_PROCESS_FADER

#include <vector>
using std::vector;

#include "Process.h"
#include "Counter.h"

/** Audio fader processing module
 */
class Audio::ProcessFader : public Audio::Process,
                            public Audio::Counter {
    public:
        class Fade {
            public:
                Fade(SAMPLE start, SAMPLE end, double startpct, double endpct);
                ~Fade();
                Fade(const Fade& F);
                Fade& operator=(const Fade& F);
                SAMPLE _start;
                SAMPLE _end;
                double _startpct;
                double _endpct;
        };
        ProcessFader();
        ~ProcessFader();

        virtual void getAudio(AudioPacket& audioData);

        virtual void receiveMessage(PORT inPort, MESSAGE message);

        virtual void threadExecute();

        void addFade(Fade&);
        void clearFades();

    private:
        vector<Fade> Fades;
        SAMPLEVAL * data;
};

#endif
