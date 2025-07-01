#include "files/LgsObjectFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

LgsModule* LgsObjectFile::generateIR() {
    const auto runtime = new LgsModule();
    runtime->IRModule = createIRModule(name, runtime->context);
    for (const auto& [_, method] : obj->methods) {
        method->generateIR(runtime);
    }
    return runtime;
}

LgsObjectFile::~LgsObjectFile() {
    delete obj;
}