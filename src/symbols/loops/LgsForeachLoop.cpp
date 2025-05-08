#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/constants/LgsStrConst.h"

int LgsForeachLoop::loopStart() {
    return 0;
}

int LgsForeachLoop::loopEnd() {
    const auto iterable = iterExpr->type->asIterable();
    assert(iterable->sizes.size() > 0);
    return iterable->sizes[0];
}

void LgsForeachLoop::setIRLoopVariable(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    assert(iterExpr);
    const auto iterIRValue = iterExpr->getIRValue(metadata);
    const auto iterable = iterExpr->type->asIterable();
    const vector<Value*> args = {builder.getInt32(0), iValue};
    const auto gep = builder.CreateInBoundsGEP(iterable->getIRType(), iterIRValue, args);
    const auto element = builder.CreateLoad(iterable->underlyingType->getIRType(), gep);
    const auto loopVar = loopVars[0];
    loopVar->setIRValue(element);
    metadata->lgsStack.addLocalSymbol(loopVar->name, LgsSymbol(loopVar));
}

LgsForeachLoop::~LgsForeachLoop() {
    if (iterExpr) {
        delete iterExpr;
    }
    if (stmtBlock) {
        delete stmtBlock;
    }
}
