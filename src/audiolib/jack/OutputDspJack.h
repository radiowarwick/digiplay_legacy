#include "Output.h"

namespace Audio {
    /**
     * Local sub-class of Output to implement JACK interface
     */
    class OutputDspJack : public Output {
        public:
            OutputDspJack(string device);
            virtual ~OutputDspJack();

            virtual void receiveMessage(PORT inPort, MESSAGE message);
            virtual void onPatch(PORT localPort);
            virtual void onUnpatch(PORT localPort);
            virtual void threadExecute();

        private:
            void initialise(string device);
            static int jack_callback(jack_nframes_t nframes, void *arg);
            int process(jack_nframes_t nframes);

            jack_client_t *client;
            jack_port_t *left;
            jack_port_t *right;
            jack_default_audio_sample_t *dbuf;
            jack_nframes_t bufSize;
            volatile int bufReady;
            enum STATE audioState;
            pthread_cond_t *sync;
    };
};
