#include "loops/LgsInfiniteLoop.h"
#include "stmts/LgsVarDec.h"

Value* LgsInfiniteLoop::loopStart(LgsModule* module) {
    const auto type = module->builder.getIntPtrTy(dataLayout);
    return ConstantInt::get(type, 0);
}

Value* LgsInfiniteLoop::loopEnd(LgsModule* module) {
    return ConstantInt::getTrue(module->context);
}

void LgsInfiniteLoop::initIRLoop(LgsModule* module) {
    IRBodyBlock = BasicBlock::Create(module->context, LOGOS_LOOP_BODY);
    IRExitBlock = BasicBlock::Create(module->context, LOGOS_LOOP_EXIT);
    module->builder.CreateBr(IRBodyBlock);

    startBlock(module, IRBodyBlock);
    if (loopVars.empty()) return;
    const auto iValue = module->builder.CreateLoad(module->builder.getInt64Ty(), iPtr);
    loopVars[0]->setIRValue(iValue);
}

void LgsInfiniteLoop::exitIRLoop(LgsModule* module) const {
    module->builder.CreateBr(IRBodyBlock);
    startBlock(module, IRExitBlock);
}