#include "loops/LgsInfiniteLoop.h"

#include "data/LgsDefinitions.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsIRUtils.h"
#include "utils/LgsUtils.h"

Value* LgsInfiniteLoop::loopStart(LgsModule* module) {
    return ConstantInt::get(sizeTy(module), 0);
}

Value* LgsInfiniteLoop::loopEnd(LgsModule* module) {
    return ConstantInt::getTrue(module->context);
}

void LgsInfiniteLoop::initIRLoop(LgsModule* module) {
    IRBodyBlock = BasicBlock::Create(module->context, BLOCK_NAME_LOOP_BODY);
    IRExitBlock = BasicBlock::Create(module->context, BLOCK_NAME_LOOP_EXIT);
    module->builder.CreateBr(IRBodyBlock);

    startBlock(module, IRBodyBlock);
    if (loopVars.empty()) return;
    const auto iValue = module->builder.CreateLoad(i64Ty(module), iPtr);
    loopVars[0]->setIRValue(iValue);
}

void LgsInfiniteLoop::exitIRLoop(LgsModule* module) const {
    module->builder.CreateBr(IRBodyBlock);
    startBlock(module, IRExitBlock);
}
