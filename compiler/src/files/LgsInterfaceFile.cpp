#include "files/LgsInterfaceFile.h"

#include <assert.h>

#include "LgsType.h"
#include "types/LgsInterface.h"

size_t LgsInterfaceFile::hashFile() {
    assert(0);
}

LgsInterfaceFile::~LgsInterfaceFile() {
    freeType(interface);
    interface = nullptr;
}

