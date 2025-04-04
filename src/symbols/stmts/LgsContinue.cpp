#include "stmts/LgsContinue.h"

#include "funcs/LgsFunc.h"

#include <loops/LgsLoop.h>

Value* LgsContinue::createIRValue(CodeGenMetadata* metadata) {
    const auto currentLoop = metadata->logosStack.currentLoop;
    const auto currentFunc = metadata->logosStack.currentFunc;
    const auto loopCondition = currentLoop->loopCondition;
    const auto branch = metadata->builder.CreateBr(loopCondition);
    const auto IRFunc = currentFunc->getIRFunc(metadata);
    const auto breakExtBlock = createBasicBlock("continue_ext");
    breakExtBlock->insertInto(IRFunc);
    metadata->builder.SetInsertPoint(breakExtBlock);
    return branch;
}
