#include "LogosMainFile.h"



Module* LogosMainFile::generateModule(IRBuilder<>& builder, LogosStack& theStack) const {
    const auto module = new Module(name, builder.getContext());
    auto codeGenMetadata = CodeGenMetadata{.builder = &builder, .theStack = &theStack, .module = module};
    for (const auto func : funcs) {
        func->getLLVMValue(&codeGenMetadata);
    }
    mainFunc->getLLVMValue(&codeGenMetadata);
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
