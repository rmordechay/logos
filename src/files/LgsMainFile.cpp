#include "files/LgsMainFile.h"

#include "funcs/LgsFunc.h"
#include "logos/LgsProject.h"
#include "types/LgsEnum.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

Module* LgsMainFile::generateIR(LgsProject& project) {
    LgsRuntime runtime;
    runtime.module = createIRModule(LOGOS_MAIN_FILE_NAME, context);
    for (const auto [_, func] : funcs) {
        func->generateIR(&runtime);
    }
    for (const auto object : objects) {
        for (const auto& [_, method] : object->methods) {
            method->generateIR(&runtime);
        }
    }
    return runtime.module;
}

void LgsMainFile::format() {
    string indentStr = "";
    // ofstream outFile(absPath, ios::trunc);
}

LgsMainFile::~LgsMainFile() {
    for (const auto& func : funcs) {
        delete func.second;
    }
}
