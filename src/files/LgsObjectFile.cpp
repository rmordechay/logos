#include "files/LgsObjectFile.h"

void LgsObjectFile::generateIR() {
    LgsRuntime runtime;
    const auto name = obj->name;
    runtime.module = createEmptyModule(name, context);
    for (const auto& [_, method] : obj->methods) {
        method->generateIR(&runtime);
    }
    lock_guard lock(mtx);
    IRModules[name] = runtime.module;
}

LgsObjectFile::~LgsObjectFile() {
    delete obj;
}