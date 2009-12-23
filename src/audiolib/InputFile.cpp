#include "InputFile.h"
using Audio::InputFile;

#include <vector>
#include <algorithm>
#include <dlfcn.h>

/**
 * Store cachesize. No implementation is chosen until file is loaded.
 * @param   cacheSize           Size of cache to use.
 */
InputFile::InputFile(unsigned int cacheSize) :
        Input(cacheSize) {
    cache_size = cacheSize;
    pImpl = 0;
}


/**
 * Destroy implementation and clean up.
 */
InputFile::~InputFile() {
    if (pImpl) {
        delete pImpl;
    }
    if (dlHandle) {
        dlclose(dlHandle);
    }
}


/**
 * Loads an audio file. The format is determined from the filename extension.
 */
void InputFile::load(string filename, long start_smpl, long end_smpl) {
    if (filename == "") return;
    unsigned int len = filename.size();
    string soName = "";

    // Determine file type from extension
    if (filename.substr(len-5,5) == ".flac") {
        soName = "libdpsaudio-flac.so";
    }
    else if (filename.substr(len-4,4) == ".mp3") {
        soName = "libdpsaudio-mp3.so";
    }
    else {
        soName = "libdpsaudio-raw.so";
    }

    // Dynmically load the required shared library for this file format.
    dlHandle = dlopen(soName.c_str(), RTLD_NOW | RTLD_GLOBAL);
    if (!dlHandle) {
        cerr << "No such module: " << soName << endl;
        throw 0;
    }

    // Retrieve the library handle for creating class instance.
    InputFileSO_Entry entry = (InputFileSO_Entry)dlsym(dlHandle, INPUT_SO_SYM);
    if (!entry) {
        cerr << "No entry point in module: " << soName << endl;
        dlclose(dlHandle);
        throw 0;
    }

    // Remove old implementation if one has been created before.
    if (pImpl) {
        unpatch(IN0);
        delete pImpl;
    }

    // Create instance of format-specific file reader.
    pImpl = entry(cache_size, this);
    if (!pImpl) {
        cerr << "Module failed to create input file object." << endl;
        dlclose(dlHandle);
        throw 0;
    }

    // Patch implementation through to this objects first input.
    patch(IN0, pImpl, OUT0);

    // Add all the counters
    for (unsigned int i = 0; i < facadeCounters.size(); ++i) {
        pImpl->addCounter(facadeCounters[i]);
    }

    // Load the file
    pImpl->load(filename, start_smpl, end_smpl);
}

/**
 * Pass-through routine for retrieving audio.
 */
void InputFile::getAudio(AudioPacket * audioData) {
    if (pImpl) {
        pImpl->getAudio(audioData);
    }
}


void InputFile::play() {
    if (pImpl) {
        pImpl->play();
    }
}

void InputFile::stop() {
    if (pImpl) {
        pImpl->stop();
    }
}

void InputFile::pause() {
    if (pImpl) {
        pImpl->pause();
    }
}

void InputFile::seek(long sample) {
    if (pImpl) {
        pImpl->seek(sample);
    }
}

/**
 * Attaches a Counter component to this Component. Counters are updated
 * whenever audio is requested from this component or its state is changed.
 * @param   counter     Audio Counter to attach
 */
void InputFile::addCounter(Audio::Counter *counter) {
    vector<Audio::Counter *>::iterator i 
        = find(facadeCounters.begin(), facadeCounters.end(), counter);
    if (i == facadeCounters.end()) {
        facadeCounters.push_back(counter);
        counter->setSample(0);
        counter->setTotalSamples(f_length_byte/4);
        counter->setState(state);
    }
    // If there is an active implementation, add the counter immediately.
    if (pImpl) {
        pImpl->addCounter(counter);
    }
}


/**
 * Remove an attached Counter.
 * @param   counter     The Audio Counter to remove
 */
void InputFile::removeCounter(Audio::Counter *counter) {
    vector<Audio::Counter *>::iterator i 
        = find(facadeCounters.begin(), facadeCounters.end(), counter);
    if (i != facadeCounters.end()) {
        facadeCounters.erase(i);
    }
    else {
        cout << "WARNING: Counter does not exist" << endl;
    }
    // If there is an active implementation, remove the counter immediately.
    if (pImpl) {
        pImpl->removeCounter(counter);
    }
}

void InputFile::setAutoReload(bool flag) {
    if (pImpl) {
        pImpl->setAutoReload(flag);
    }
}

bool InputFile::isLoaded() {
    if (pImpl) {
        return pImpl->isLoaded();
    }
    return false;
}


void InputFile::receiveMessage(PORT inPort, MESSAGE message) {
    if (inPort == IN0) {
        send(OUT0, message);
    }
    else {
        if (pImpl) {
            pImpl->receiveMessage(inPort, message);
        }
    }
}

void InputFile::onPatch(PORT localPort) {
    if (pImpl) {
        pImpl->onPatch(localPort);
    }
}

void InputFile::onUnpatch(PORT localPort) {
    if (pImpl) {
        pImpl->onUnpatch(localPort);
    }
}


void InputFile::threadExecute() {

}
