#include "files/LgsMainFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsEnum.h"
#include "types/LgsObject.h"

void LgsMainFile::generateIR() {
    for (const auto object : objects) {
        object->getIRType(&codeGen);
        for (const auto& [_, method] : object->methods) {
            method->generateIR(&codeGen);
        }
    }
    for (const auto [_, func] : funcs) {
        func->generateIR(&codeGen);
    }
}

void LgsMainFile::format() {
    string indentStr = "";
}

LgsMainFile::~LgsMainFile() {
    for (const auto& [_, func] : funcs) {
        delete func;
    }
    for (const auto& object : objects) {
        delete object;
    }
    for (const auto lgsEnum : enums) {
        delete lgsEnum;
    }
}
