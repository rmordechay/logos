#include "LogosMainFile.h"



Module* LogosMainFile::generateModule(IRBuilder<>& builder, LogosStack& theStack) {
    const auto module = new Module(name, builder.getContext());
    for (const auto func : funcs) {
        func->getLLVMValue(&builder, &theStack, module);
    }
    mainFunc->getLLVMValue(&builder, &theStack, module);
    builder.CreateRet(builder.getInt32(EXIT_SUCCESS));
    writeIRToFile(module, name);
    return module;
}

LogosMainFile::~LogosMainFile() {
    delete mainFunc;
    for (const auto func : funcs) {
        delete func;
    }
}
