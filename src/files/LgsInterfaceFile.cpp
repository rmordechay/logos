#include "files/LgsInterfaceFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsInterface.h"
#include "utils/LgsUtils.h"

void LgsInterfaceFile::generateIR() {
    for (const auto& [_, method] : interface->methods) {
        if (!method->stmtsBlock) continue;
        method->generateIR(&codeGen);
    }
}

LgsInterfaceFile::~LgsInterfaceFile() {
    freeType(interface);
    interface = nullptr;
}
