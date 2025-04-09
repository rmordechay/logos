#include "loops/LgsForeachLoop.h"

#include "stmts/LgsVarDec.h"
#include "types/LgsArrayType.h"
#include "exprs/unary/LgsArrayIndex.h"
#include <exprs/unary/LgsArray.h>

int LgsForeachLoop::loopStart() {
    return 0;
}

int LgsForeachLoop::loopEnd() {
    return getExprAsIterable()->length();
}

void LgsForeachLoop::setIRLoopVariable(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto arrValue = iterableExpr->getIRValue(metadata);
    const auto iterableIRType = iterableExpr->type->getIRType();
    const auto gep = builder.CreateInBoundsGEP(iterableIRType, arrValue, {builder.getInt32(0), iValue});
    const auto arrayType = dynamic_cast<LgsArrayType*>(iterableExpr->type);
    const auto element = builder.CreateLoad(arrayType->underlyingType->getIRType(), gep);
    const auto loopVar = loopVars[0];
    loopVar->setIRValue(element);
    metadata->lgsStack.addLocalSymbol(loopVar->name, LgsSymbol(loopVar));
}

LgsIterable* LgsForeachLoop::getExprAsIterable() const {
    return dynamic_cast<LgsIterable*>(iterableExpr);
}

LgsForeachLoop::~LgsForeachLoop() {
    if (iterableExpr) {
        delete iterableExpr;
    }
    if (stmtBlock) {
        delete stmtBlock;
    }
}
