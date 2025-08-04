#include "files/LgsInterfaceFile.h"

#include "funcs/LgsFunc.h"
#include "types/LgsInterface.h"

void LgsInterfaceFile::generateIR() {
    codeGen.setIRModule(name);
    for (const auto& [_, method] : interface->methods) {
        if (!method->stmtsBlock) continue;
        method->generateIR(&codeGen);
    }
}
