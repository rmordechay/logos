#include "LogosFuncCallExpr.h"

const LogosType& LogosFuncCallExpr::getType() const {
    return type;
}

Value* LogosFuncCallExpr::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) {
    const auto funcSymbol = stackFrame->functions[func.name];
    if (args.size() == 0) {
        return builder->CreateCall(funcSymbol);
    }
    std::vector<Value*> llvmArgs;
    for (const auto arg : args) {
        llvmArgs.push_back(arg->getLLVMValue(builder, stackFrame, module));
    }
    return builder->CreateCall(funcSymbol, ArrayRef(llvmArgs));
}
