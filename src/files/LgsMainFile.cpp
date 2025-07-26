#include "files/LgsMainFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsEnum.h"
#include "types/LgsObject.h"
#include "utils/LgsIRUtils.h"

LgsModule* LgsMainFile::generateIR(LgsSymbolTable& globals) {
    const auto module = new LgsModule(globals);
    module->IRModule = createIRModule(LOGOS_MAIN_FILE_NAME, module->context);
    for (const auto object : objects) {
        object->getIRType(module);
        for (const auto& [_, method] : object->methods) {
            method->generateIR(module);
        }
    }
    for (const auto [_, func] : funcs) {
        func->generateIR(module);
    }
    return module;
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
