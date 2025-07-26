#include "files/LgsObjectFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsObject.h"
#include "utils/LgsIRUtils.h"

LgsModule* LgsObjectFile::generateIR(LgsSymbolTable& globals) {
    const auto module = new LgsModule(globals);
    module->IRModule = createIRModule(name, module->context);
    obj->getIRType(module);
    for (const auto& [_, method] : obj->methods) {
        method->generateIR(module);
    }
    return module;
}

LgsObjectFile::~LgsObjectFile() {
    delete obj;
}
