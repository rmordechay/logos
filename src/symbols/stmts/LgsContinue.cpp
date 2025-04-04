#include "stmts/LgsContinue.h"

#include "funcs/LgsFunc.h"

#include <loops/LgsLoop.h>

Value* LgsContinue::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto currentLoop = metadata->logosStack.currentLoop;
    const auto loopCondition = currentLoop->loopCondBlock;
    const auto inc = builder.CreateAdd(currentLoop->iValue, builder.getInt32(1));
    builder.CreateStore(inc, currentLoop->iPtr);
    const auto branch = builder.CreateBr(loopCondition);
    return branch;
}
