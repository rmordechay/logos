#include "files/LgsMainFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsEnum.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

LgsModule* LgsMainFile::generateIR() {
    const auto runtime = new LgsModule();
    runtime->IRModule = createIRModule(LOGOS_MAIN_FILE_NAME, runtime->context);
    for (const auto [_, func] : funcs) {
        func->generateIR(runtime);
    }
    for (const auto object : objects) {
        for (const auto& [_, method] : object->methods) {
            method->generateIR(runtime);
        }
    }
    return runtime;
}

void LgsMainFile::format() {
    string indentStr = "";
    // ofstream outFile(absPath, ios::trunc);
}

LgsMainFile::~LgsMainFile() {
    for (const auto& func : funcs) {
        delete func.second;
    }
    for (const auto& object : objects) {
        delete object;
    }
    for (const auto lgsEnum : enums) {
        delete lgsEnum;
    }
}
