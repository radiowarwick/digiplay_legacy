#include "Output.h"

namespace Audio {
    /**
     * Local sub-class of Output to implement OSS interface
     */
    class OutputDspOss : public Output {
        public:
            /// Create new OSS output module.
            OutputDspOss(string device);
            /// Destroy module.
            virtual ~OutputDspOss();

        protected:
            /// %Process messages received from other components.
            virtual void receiveMessage(PORT inPort __attribute__((unused)), 
                                    MESSAGE message __attribute__((unused)));
            /// Event when component is patched.
            virtual void onPatch(PORT localPort);
            /// Event when component is unpatched.
            virtual void onUnpatch(PORT localPort);

        private:
            /// Initialise the audio device.
            void initialise(string device);
            /// Component-specific thread.
            virtual void threadExecute();

            enum STATE audioState;
            string deviceName;
            int audio;
    };
};
