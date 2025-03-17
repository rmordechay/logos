#include "loops/LgsForeachLoop.h"

#include "stmts/LgsVarDec.h"
#include "types/LgsArrayType.h"
#include "exprs/unary/LgsArrayIndex.h"
#include <exprs/unary/LgsArray.h>
#include <types/LgsInt.h>

int LgsForeachLoop::loopSize() {
    return getExprAsIterable()->size();
}

void LgsForeachLoop::setIRBody(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto arrValue = iterableExpr->getIRValue(metadata);
    const auto iterableIRType = iterableExpr->type->getIRType(loopSize());
    const auto gep = builder.CreateInBoundsGEP(iterableIRType, arrValue, {builder.getInt32(0), iValue});
    const auto arrayType = dynamic_cast<LgsArrayType*>(iterableExpr->type);
    const auto element = builder.CreateLoad(arrayType->underlyingType->getIRType(), gep);
    const auto loopVar = loopVars[0];
    loopVar->setIRValue(element);
    metadata->logosStack.addLocalSymbol(loopVar->name, LgsSymbol(VAR_DEC, loopVar));
    stmtBlock->getIRValue(metadata);
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
