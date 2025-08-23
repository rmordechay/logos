#include "files/LgsObjectFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

LgsObjectFile::~LgsObjectFile() {
    freeType(obj);
    obj = nullptr;
}
