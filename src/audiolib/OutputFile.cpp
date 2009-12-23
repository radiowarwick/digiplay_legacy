#include "OutputFile.h"
using Audio::OutputFile;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <dlfcn.h>

OutputFile::OutputFile(string filename) {
    this->filename = filename;
    unsigned int len = filename.size();
    string soName = "";

    if (filename.substr(len-4,4) == "flac") {
        soName = "libdpsaudio-flac.so";
    }
    else if (filename.substr(len-3,3) == "mp3") {
        soName = "libdpsaudio-mp3.so";
    }
    else {
        soName = "libdpsaudio-raw.so";
    }
    dlHandle = dlopen(soName.c_str(), RTLD_NOW | RTLD_GLOBAL);
    if (!dlHandle) {
        cerr << "No such module: " << soName << endl;
        throw 0;
    }
    OutputFileSO_Entry entry = (OutputFileSO_Entry)dlsym(dlHandle, OUTPUT_SO_SYM);
    if (!entry) {
        cerr << "No entry point in module: " << soName << endl;
        dlclose(dlHandle);
        throw 0;
    }
    cout << "Connecting..." << endl;
    pImpl = entry(filename, this);
    if (!pImpl) {
        cerr << "Module failed to create input file object." << endl;
        dlclose(dlHandle);
        throw 0;
    }
}

OutputFile::~OutputFile() {
    if (pImpl) {
        cout << "Unloading..." << endl;
        delete pImpl;
    }
    if (dlHandle) {
        dlclose(dlHandle);
    }
}

void OutputFile::receiveMessage(PORT inPort, MESSAGE message) {
    if (pImpl) {
        pImpl->receiveMessage(inPort, message);
    }
}

void OutputFile::onPatch(PORT localPort) {
    if (pImpl) {
        pImpl->onPatch(localPort);
    }
}

void OutputFile::onUnpatch(PORT localPort) {
    if (pImpl) {
        pImpl->onUnpatch(localPort);
    }
}
