#include "files/LgsObjectFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsObject.h"

void LgsObjectFile::generateIR() {
    obj->getIRType(&codeGen);
    for (const auto& [_, method] : obj->methods) {
        method->generateIR(&codeGen);
    }
}

LgsObjectFile::~LgsObjectFile() {
    delete obj;
}
