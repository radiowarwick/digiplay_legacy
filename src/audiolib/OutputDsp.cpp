/**
 * Patched to be a facade for the actual (dynamically-loaded)
 * implementations.
 * @author Phil Ashby
 * @date June-2009
 */

#include <iostream>
using namespace std;

#include <dlfcn.h>

#include "OutputDsp.h"

namespace Audio {
    /**
     * Creates a new output object to write to a DSP device.
     *
     * This facade loads the implementation identified by the
     * channel name in the format <type>:<device>, by using the
     * <type> name to form a shared object filename, and passes
     * the <device> name to the implementation.
     *
     * @param   channel     <type>:<DSP device to use>
     */
    OutputDsp::OutputDsp(string channel) {
        int o = channel.find(":");
        if (o < 0) {
            cerr << "Invalid channel (no type specifier): " << channel << endl;
            throw 0;
        }
        string soName = "libdpsaudio-" + channel.substr(0, o) + ".so";
        deviceName = channel.substr(o+1);

        // Try $DPSDIR/modules first, then LD_LIBRARY_PATH search..
        string tmpName = soName;
        dlHandle = dlopen(tmpName.c_str(), RTLD_NOW | RTLD_GLOBAL);
        if (!dlHandle) {
            dlHandle = dlopen(soName.c_str(), RTLD_NOW | RTLD_GLOBAL);
        }
        if (!dlHandle) {
            cerr << "No such module: " << soName << endl;
            throw 0;
        }
        OutputDspSO_Entry entry
                        = (OutputDspSO_Entry)dlsym(dlHandle, OUTPUT_SO_SYM);
        if (!entry) {
            cerr << "No entry point function in module: " << soName << endl;
            dlclose(dlHandle);
            throw 0;
        }

        pImpl = entry(deviceName.c_str(), this);
        if (!pImpl) {
            cerr << "Module failed to create output object: "
                 << deviceName << endl;
            dlclose(dlHandle);
            throw 0;
        }
    }


    /**
     * Destroy implementation object and close dynamic binding.
     */
    OutputDsp::~OutputDsp() {
        if (pImpl) {
            delete pImpl;
        }
        if (dlHandle)
            dlclose(dlHandle);
    }


    /**
     * @param   audioData       Storage for audio data.
     */
    void OutputDsp::getAudio(AudioPacket *audioData) {
        dynamic_cast<ComponentAudio*>(connectedDevice(IN0))
                                                        ->getAudio(audioData);
    }


    /**
     * @param   inPort          Port of connected component.
     * @param   message         Message from connected component.
     */
    void OutputDsp::receiveMessage(PORT inPort, MESSAGE message) {
        if (pImpl) {
            if (inPort != IN0) {
                cout << "OutputDspOss::receive: only use IN0" << endl;
                return;
            }
            send(OUT0, message);
        }
    }


    /**
     * @param   localPort       Port on which component is patched.
     */
    void OutputDsp::onPatch(PORT localPort) {
        if (localPort == IN0) {
            patch(OUT0, pImpl, IN0);
        }
    }


    /**
     * @param   localPort       Port on which component is unpatched.
     */
    void OutputDsp::onUnpatch(PORT localPort) {
        if (localPort == IN0) {
            unpatch(OUT0);
        }
    }

}
