#include "files/LgsObjectFile.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

LgsObjectFile::~LgsObjectFile() {
    freeType(obj);
    obj = nullptr;
}
