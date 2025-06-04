#include "files/LgsObjectFile.h"

#include "logos/LgsProject.h"

LgsRuntime* LgsObjectFile::generateIR(LogosProject& project) {
    const auto runtime = new LgsRuntime();
    const auto name = obj->name;
    runtime->module = createEmptyModule(name, runtime->context);
    for (const auto& [_, method] : obj->methods) {
        method->generateIR(runtime);
    }
    return runtime;
}

LgsObjectFile::~LgsObjectFile() {
    delete obj;
}