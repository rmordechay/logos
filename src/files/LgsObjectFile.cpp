#include "files/LgsObjectFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsObject.h"
#include "utils/LgsIRUtils.h"
#include "utils/LgsUtils.h"

LgsModule* LgsObjectFile::generateIR(LgsSymbolTable& globals) {
    const auto module = new LgsModule(globals);
    module->IRModule = createIRModule(name, module->context);
    for (const auto& [_, method] : obj->methods) {
        method->generateIR(module);
    }
    return module;
}

LgsObjectFile::~LgsObjectFile() {
    delete obj;
}
