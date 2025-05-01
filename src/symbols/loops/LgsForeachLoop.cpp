#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsDArrType.h"
#include "exprs/unary/LgsArrayIndex.h"
#include "exprs/unary/constants/LgsStrConst.h"

int LgsForeachLoop::loopStart() {
    return 0;
}

int LgsForeachLoop::loopEnd() {
    assert(false);
}

void LgsForeachLoop::setIRLoopVariable(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto arrValue = expr->getIRValue(metadata);
    // const auto iterableIRType = iterable->getIRType(loopEnd() - loopStart());
    // const auto gep = builder.CreateInBoundsGEP(iterableIRType, arrValue, {builder.getInt32(0), iValue});
    // const auto element = builder.CreateLoad(iterable->underlyingType->getIRType(), gep);
    // const auto loopVar = loopVars[0];
    // loopVar->setIRValue(element);
    // metadata->lgsStack.addLocalSymbol(loopVar->name, LgsSymbol(loopVar));
}

LgsForeachLoop::~LgsForeachLoop() {
    if (expr) {
        delete expr;
    }
    if (stmtBlock) {
        delete stmtBlock;
    }
}
