#include "Output.h"

#include <alsa/asoundlib.h>

namespace Audio {
    /// Local sub-class of Output to implement ALSA interface
    class OutputDspAlsa : public Output {
        public:
            OutputDspAlsa(string device);
            virtual ~OutputDspAlsa();

        protected:
            virtual void receiveMessage(PORT inPort, MESSAGE message);
            virtual void onPatch(PORT localPort);
            virtual void onUnpatch(PORT localPort);
            virtual void threadExecute();

        private:
            void initialise(string device);

            enum STATE audioState;
            snd_pcm_t *audio;
    };
};
