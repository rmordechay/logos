#include "LogosMainFile.h"

#include "application/LogosUtils.h"

#include <llvm/IR/Module.h>
#include <llvm/Target/TargetMachine.h>

Module* LogosMainFile::generateModule(IRBuilder<>& builder, LogosStack& theStack) {
    const auto module = new Module(name, builder.getContext());
    for (const auto func : funcs) {
        func->getLLVMValue(&builder, &theStack, module);
    }
    mainFunc->getLLVMValue(&builder, &theStack, module);
    builder.CreateRet(builder.getInt32(EXIT_SUCCESS));
    return module;
}

void LogosMainFile::initModule(IRBuilder<>& builder, LogosStack& theStack) {
    const auto printFuncType = FunctionType::get(builder.getVoidTy(), builder.getInt32Ty(), false);
    const auto printFunc = Function::Create(printFuncType, Function::ExternalLinkage, "printInt");
    theStack.addFunc("print", printFunc);
    for (const LogosImportStmt* import : imports) {
        auto llvmType = import->primaryImport->getLLVMType(&builder);
    }
}

LogosMainFile::~LogosMainFile() {
    delete mainFunc;
    for (const auto func : funcs) {
        delete func;
    }
}
