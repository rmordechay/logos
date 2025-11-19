#include "files/LgsInterfaceFile.h"

size_t LgsInterfaceFile::hashFile() {
    assert(0);
}

LgsInterfaceFile::~LgsInterfaceFile() {
    freeType(interface);
    interface = nullptr;
}

