#include "files/LgsObjectFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

Module* LgsObjectFile::generateIR(LgsProject& project) {
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