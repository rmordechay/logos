#include "StoreExpr.h"

void StoreExpr::generateCode(RuntimeStackFrame* runtimeStack) {
    const auto value = expr->getLLVMValue(builder, runtimeStack);
    const auto allocaInst = builder->CreateAlloca(value->getType());
    builder->CreateStore(value, allocaInst);
    runtimeStack->symbolTable[name] = allocaInst;
}


