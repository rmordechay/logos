#include "loops/LgsForeachLoop.h"
#include "data/LgsDefinitions.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsIterIndex.h"
#include "stmts/LgsVarDec.h"
#include "stmts/LgsStmtBlock.h"
#include "types/LgsDArray.h"
#include "types/LgsIterator.h"
#include "types/LgsMap.h"

Value* LgsForeachLoop::loopStart(LgsModule* module) {
    return module->builder.getInt64(0);
}

Value* LgsForeachLoop::loopEnd(LgsModule* module) {
    const auto iterable = iterExpr->type->asIterable();
    return iterable->getLoopLength(module, iterExpr);
}

void LgsForeachLoop::initIPtr(LgsModule* module)
{
    iPtr = module->builder.CreateAlloca(module->builder.getInt64Ty(), nullptr);
    module->builder.CreateStore(loopStart(module), iPtr);
    module->builder.CreateBr(IRCondBlock);
    startBlock(module, IRCondBlock);
}

void LgsForeachLoop::initIRLoop(LgsModule* module) {
    IRCondBlock = BasicBlock::Create(module->context, LOGOS_LOOP_CONDITION);
    IRBodyBlock = BasicBlock::Create(module->context, LOGOS_LOOP_BODY);
    IRExitBlock = BasicBlock::Create(module->context, LOGOS_LOOP_EXIT);

    const auto iterable = iterExpr->type->asIterable();
    // With iterator
    if (iterable->asMap()) {
        LgsIterator iterator = iterExpr->toIterator();
        iterator.initIterator(module);
        initIPtr(module);
        module->builder.CreateCondBr(iterator.hasNext(module), IRBodyBlock, IRExitBlock);
        startBlock(module, IRBodyBlock);
        iterPtr = iterExpr->getIRValue(module);
        setMapIterVars(module, iterator);
        return;
    }

    // Without iterator
    setLoopCondition(module);
    startBlock(module, IRBodyBlock);
    iterPtr = iterExpr->getIRValue(module);
    if (const auto str = iterable->asStr()) {
        setStrIterVars(module, str);
    } else if (const auto arr = iterable->asDArray()) {
        setArrIterVars(module, arr);
    } else {
        assert(0);
    }
}

void LgsForeachLoop::exitIRLoop(LgsModule* module) const {
    // Increment loop variable
    const auto iValue = module->builder.CreateLoad(module->builder.getInt64Ty(), iPtr);
    const auto inc = module->builder.CreateAdd(iValue, module->builder.getInt64(1));
    module->builder.CreateStore(inc, iPtr);
    module->builder.CreateBr(IRCondBlock);
    startBlock(module, IRExitBlock);
}

void LgsForeachLoop::setStrIterVars(LgsModule* module, LgsStr* str) const {
    const auto i = module->builder.CreateLoad(module->builder.getInt64Ty(), iPtr);
    const auto gep = module->builder.CreateGEP(str->getIRType(module->context), iterPtr, {module->builder.getInt32(0), i});
    const auto load = module->builder.CreateLoad(module->builder.getInt8Ty(), gep);
    if (withIndex) {
        loopVars[0]->setIRValue(loadIPtr(module));
    }
    loopVars[0 + withIndex]->setIRValue(load);
}

void LgsForeachLoop::setArrIterVars(LgsModule* module, LgsDArray* arr) const {
    if (arr->asSArray()) {
        const auto i = module->builder.CreateLoad(module->builder.getInt64Ty(), iPtr);
        const auto gep = module->builder.CreateGEP(arr->getIRType(module->context), iterPtr, {module->builder.getInt32(0), i});
        if (withIndex) {
            loopVars[0]->setIRValue(loadIPtr(module));
        }
        loopVars[0 + withIndex]->setIRValue(gep);
    } else {
        const auto iValue = loadIPtr(module);
        if (withIndex) {
            loopVars[0]->setIRValue(iValue);
        }
        const auto v = arr->getFunc.callIR(module, {iterPtr, iValue});
        loopVars[0 + withIndex]->setIRValue(module->builder.CreateLoad(arr->getIRType(module->context), v));
    }
}

void LgsForeachLoop::setMapIterVars(LgsModule* module, const LgsIterator& iterator) const {
    const auto next = iterator.next(module);
    const auto entryType = getIRStructType(module->context, "MapEntry", {ptrTy(module->context), ptrTy(module->context)});
    const auto keyGEP = module->builder.CreateStructGEP(entryType, next, 0);
    const auto valueGEP = module->builder.CreateStructGEP(entryType, next, 1);
    if (withIndex) {
        loopVars[0]->setIRValue(loadIPtr(module));
    }
    loopVars[0 + withIndex]->setIRValue(keyGEP);
    loopVars[1 + withIndex]->setIRValue(valueGEP);
}

void LgsForeachLoop::setLoopCondition(LgsModule* module) {
    initIPtr(module);
    const auto iValue = module->builder.CreateLoad(module->builder.getInt64Ty(), iPtr);
    const auto upperBound = module->builder.CreateZExt(loopEnd(module), module->builder.getInt64Ty());
    const auto condition = module->builder.CreateICmpSLT(iValue, upperBound);
    module->builder.CreateCondBr(condition, IRBodyBlock, IRExitBlock);
}

LoadInst* LgsForeachLoop::loadIPtr(LgsModule* module) const {
    return module->builder.CreateLoad(module->builder.getInt64Ty(), iPtr);
}

LgsForeachLoop::~LgsForeachLoop() {
    if (iterExpr) {
        delete iterExpr;
    }
    if (stmtBlock) {
        delete stmtBlock;
    }
}
