#include "loops/LgsRangeLoop.h"
#include "data/LgsDefinitions.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"

Value* LgsRangeLoop::loopStart(LgsModule* module) {
    return rangeStart->getIRValue(module);
}

Value* LgsRangeLoop::loopEnd(LgsModule* module) {
    return rangeEnd->getIRValue(module);
}

void LgsRangeLoop::initIRLoop(LgsModule* module) {
    IRCondBlock = BasicBlock::Create(module->context, LOGOS_LOOP_CONDITION);
    IRBodyBlock = BasicBlock::Create(module->context, LOGOS_LOOP_BODY);
    IRExitBlock = BasicBlock::Create(module->context, LOGOS_LOOP_EXIT);
    iPtr = module->builder.CreateAlloca(module->builder.getInt32Ty());
    module->builder.CreateStore(loopStart(module), iPtr);
    module->builder.CreateBr(IRCondBlock);

    // Condition
    startBlock(module, IRCondBlock);
    auto iValue = module->builder.CreateLoad(module->builder.getInt32Ty(), iPtr);
    const auto upperBound = module->builder.CreateZExt(loopEnd(module), module->builder.getInt32Ty());
    const auto condition = module->builder.CreateICmpSLT(iValue, upperBound);
    module->builder.CreateCondBr(condition, IRBodyBlock, IRExitBlock);

    // Body
    startBlock(module, IRBodyBlock);
    iValue = module->builder.CreateLoad(module->builder.getInt32Ty(), iPtr);
    loopVars[0]->setIRValue(iValue);
}

void LgsRangeLoop::exitIRLoop(LgsModule* module) const {
    // Increment loop variable
    const auto iValue = module->builder.CreateLoad(module->builder.getInt32Ty(), iPtr);
    const auto inc = module->builder.CreateAdd(iValue, i32(module, 1));
    module->builder.CreateStore(inc, iPtr);
    module->builder.CreateBr(IRCondBlock);
    startBlock(module, IRExitBlock);
}

LgsRangeLoop::~LgsRangeLoop() {
    // rangeStart will be freed with varDec freeing
    delete rangeEnd;
}
