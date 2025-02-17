#include "funcs/LogosPrint.h"

#include <llvm/IR/Module.h>

void checkPossibleTypes(Value* value) {
    if (auto* constantInt = dyn_cast<ConstantInt>(value)) {
        outs() << "It is a ConstantInt with value: " << constantInt->getValue() << "\n";
    } else if (auto* constantFP = dyn_cast<ConstantFP>(value)) {
        outs() << "It is a ConstantFP with value: " << constantFP->getValueAPF().convertToFloat() << "\n";
    } else if (auto* function = dyn_cast<Function>(value)) {
        outs() << "It is a Function with name: " << function->getName() << "\n";
    } else if (auto* loadInst = dyn_cast<LoadInst>(value)) {
        outs() << "It is a LoadInst\n";
    } else if (auto* storeInst = dyn_cast<StoreInst>(value)) {
        outs() << "It is a StoreInst\n";
    } else if (auto* binaryOp = dyn_cast<BinaryOperator>(value)) {
        outs() << "It is a BinaryOperator\n";
    } else if (auto* callInst = dyn_cast<CallInst>(value)) {
        outs() << "It is a CallInst\n";
    } else if (auto* allocaInst = dyn_cast<AllocaInst>(value)) {
        outs() << "It is an AllocaInst\n";
    } else if (auto* returnInst = dyn_cast<ReturnInst>(value)) {
        outs() << "It is a ReturnInst\n";
    } else if (auto* castInst = dyn_cast<CastInst>(value)) {
        outs() << "It is a CastInst\n";
    } else {
        outs() << "Unknown type\n";
    }
}

Value* LogosPrint::computeLLVMValue(CodeGenMetadata* metadata) {
    const auto printFuncType = FunctionType::get(LOGOS_VOID.llvmType, LOGOS_INT.llvmType, false);
    return Function::Create(printFuncType, Function::ExternalLinkage, "printInt");
}

Value* LogosPrint::callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {

    vector<Value*> llvmArgs;

    const auto argValue = args[0]->getLLVMValue(metadata);
    llvmArgs.emplace_back(argValue);
// if (const auto function = dyn_cast<Function>(argValue)) {
    //     auto funcType = function->getFunctionType()->getContainedType(0);
    // } else {
    //
    // }

    const auto funcType = FunctionType::get(metadata->builder->getVoidTy(), metadata->builder->getInt32Ty(), false);
    const auto func = metadata->module->getOrInsertFunction(llvmName, funcType);

    return metadata->builder->CreateCall(func, llvmArgs);
}
