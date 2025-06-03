#include "files/LgsObjectFile.h"

void LgsObjectFile::generateIR() {
    LgsRuntime runtime;
    const auto objName = obj->prettyName();
    if (IRModules.find(objName) != IRModules.end()) return;
    const auto module = createEmptyModule(objName);
    for (const auto& [_, method] : obj->methods) {
        method->generateIRCode(&runtime);
    }
    writeIRToFile(&runtime, objName);
}

LgsObjectFile::~LgsObjectFile() {
    delete obj;
}