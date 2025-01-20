#include "LogosMainFile.h"

#include "LogosUtils.h"

#include <llvm/IR/Module.h>
#include <llvm/Target/TargetMachine.h>

Module* LogosMainFile::generateModule(const TargetMachine& targetMachine, IRBuilder<>& builder) {
    LogosStack theStack;
    theStack.push(LogosStackFrame());

    auto module = Utils::createEmptyLLVMModule(LOGOS_MAIN_FILE, builder.getContext(), targetMachine);
    const auto printfType = FunctionType::get(builder.getVoidTy(), builder.getInt32Ty(), false);
    theStack.top().functions["print"] = Function::Create(printfType, Function::ExternalLinkage, "printInt", module);

    for (const auto func : funcs) {
        func->getLLVMValue(&builder, &theStack, module);
    }

    mainFunc->getLLVMValue(&builder, &theStack, module);
    builder.CreateRet(builder.getInt32(EXIT_SUCCESS));
    return module;
}

LogosMainFile::~LogosMainFile() {
    delete mainFunc;
    for (const auto func : funcs) {
        delete func;
    }
}
