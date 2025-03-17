#include "loops/LgsRangeLoop.h"

#include "constants/LgsIntConst.h"
#include "stmts/LgsVarDec.h"

#include <LgsStack.h>
#include <types/LgsInt.h>

int LgsRangeLoop::loopSize() {
    const int rangeStartValue = dynamic_cast<LgsIntConst*>(rangeStart)->value;
    const int rangeEndValue = dynamic_cast<LgsIntConst*>(rangeEnd)->value;
    return rangeEndValue - rangeStartValue;
}

Value* LgsRangeLoop::createIRValue(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    const auto i32Type = builder.getInt32Ty();

    const auto loopCondition = createBasicBlock(BB_LOOP_CONDITION);
    const auto loopBody = createBasicBlock(BB_LOOP_BODY);
    const auto loopExit = createBasicBlock(BB_LOOP_EXIT);

    // Init blocks
    const auto iPtr = builder.CreateAlloca(i32Type);
    builder.CreateStore(builder.getInt32(0), iPtr);
    builder.CreateBr(loopCondition);

    // Loop condition
    startBlock(metadata, loopCondition);
    const auto size = loopSize();
    const auto iValue = builder.CreateLoad(i32Type, iPtr);
    const auto condition = builder.CreateICmpSLT(iValue, builder.getInt32(size));
    builder.CreateCondBr(condition, loopBody, loopExit);

    // Loop body
    startBlock(metadata, loopBody);
    metadata->logosStack.enterScope();

    const auto loopVar = loopVars[0];
    loopVar->setIRValue(iValue);
    metadata->logosStack.addLocalSymbol(loopVar->name, LgsSymbol(VAR_DEC, loopVar));
    stmtBlock->getIRValue(metadata);

    // Increment loop variable
    const auto inc = builder.CreateAdd(iValue, builder.getInt32(1));
    builder.CreateStore(inc, iPtr);
    builder.CreateBr(loopCondition);

    // Loop end
    startBlock(metadata, loopExit);
    metadata->logosStack.exitScope();

    return nullptr;
}