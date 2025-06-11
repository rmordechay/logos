#include "files/LgsObjectFile.h"
#include "utils/LgsUtils.h"

Module* LgsObjectFile::generateIR(LogosProject& project) {
    LgsRuntime runtime;
    runtime.module = createIRModule(name, context);
    for (const auto& [_, method] : obj->methods) {
        method->generateIR(&runtime);
    }
    return runtime.module;
}

LgsObjectFile::~LgsObjectFile() {
    delete obj;
}