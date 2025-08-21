#include "files/LgsObjectFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

void LgsObjectFile::generateIR() {
    obj->getIRType(&codeGen);
    for (const auto& [_, method] : obj->methods) {
        method->generateIR(&codeGen);
    }
}

LgsObjectFile::~LgsObjectFile() {
    freeType(obj);
    obj = nullptr;
}
