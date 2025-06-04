#include "files/LgsObjectFile.h"

#include "logos/LgsProject.h"

void LgsObjectFile::generateIR(LogosProject& project) {
    LgsRuntime runtime;
    const auto name = obj->name;
    runtime.module = createEmptyModule(name, runtime.context);
    for (const auto& [_, method] : obj->methods) {
        method->generateIR(&runtime);
    }
}

LgsObjectFile::~LgsObjectFile() {
    delete obj;
}