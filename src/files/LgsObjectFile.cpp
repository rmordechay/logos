#include "files/LgsObjectFile.h"

size_t LgsObjectFile::hashFile() {
    assert(0);
}

LgsObjectFile::~LgsObjectFile() {
    freeType(obj);
    obj = nullptr;
}
