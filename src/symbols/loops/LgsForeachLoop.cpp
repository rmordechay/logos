#include "loops/LgsForeachLoop.h"
#include "data/LgsDefinitions.h"
#include "exprs/unary/LgsIterIndex.h"
#include "stmts/LgsVarDec.h"
#include "stmts/LgsStmtBlock.h"
#include "types/LgsArray.h"
#include "types/LgsMap.h"
#include "utils/LgsUtils.h"

Value* LgsForeachLoop::loopStart(LgsRuntime* runtime) {
    return runtime->builder.getInt64(0);
}

Value* LgsForeachLoop::loopEnd(LgsRuntime* runtime) {
    const auto iterable = iterExpr->type->asIterable();
    return iterable->getLoopLength(runtime, iterExpr);
}

void LgsForeachLoop::initIRLoop(LgsRuntime* runtime) {
    IRCondBlock = createBasicBlock(LOGOS_LOOP_CONDITION, context);
    IRBodyBlock = createBasicBlock(LOGOS_LOOP_BODY, context);
    IRExitBlock = createBasicBlock(LOGOS_LOOP_EXIT, context);

    iPtr = runtime->builder.CreateAlloca(runtime->builder.getInt64Ty(), nullptr);
    runtime->builder.CreateStore(loopStart(runtime), iPtr);
    runtime->builder.CreateBr(IRCondBlock);

    // Condition
    startBlock(runtime, IRCondBlock);
    const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt64Ty(), iPtr);
    const auto upperBound = runtime->builder.CreateZExt(loopEnd(runtime), runtime->builder.getInt64Ty());
    const auto condition = runtime->builder.CreateICmpSLT(iValue, upperBound);
    runtime->builder.CreateCondBr(condition, IRBodyBlock, IRExitBlock);

    // Body
    startBlock(runtime, IRBodyBlock);
    iterPtr = iterExpr->getIRValue(runtime);
    const auto iterable = iterExpr->type->asIterable();
    if (const auto str = iterable->asStr()) {
        setIterVars(runtime, str);
    } else if (const auto arr = iterable->asArray()) {
        setIterVars(runtime, arr);
    } else if (const auto map = iterable->asMap()) {
        setIterVars(runtime, map);
    } else {
        assert(0);
    }
}

void LgsForeachLoop::exitIRLoop(LgsRuntime* runtime) const {
    // Increment loop variable
    const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt64Ty(), iPtr);
    const auto inc = runtime->builder.CreateAdd(iValue, runtime->builder.getInt64(1));
    runtime->builder.CreateStore(inc, iPtr);
    runtime->builder.CreateBr(IRCondBlock);
    startBlock(runtime, IRExitBlock);
}

void LgsForeachLoop::setIterVars(LgsRuntime* runtime, LgsStr* str) const {
    if (str->isStatic) {
        const auto i = runtime->builder.CreateLoad(runtime->builder.getInt64Ty(), iPtr);
        const auto gep = runtime->builder.CreateGEP(str->getIRType(), iterPtr, {runtime->builder.getInt32(0), i});
        const auto load = runtime->builder.CreateLoad(runtime->builder.getInt8Ty(), gep);
        loopVars[0]->setIRValue(load);
    } else {
        assert(0);
    }
}

void LgsForeachLoop::setIterVars(LgsRuntime* runtime, LgsArray* arr) const {
    if (arr->isStatic) {
        const auto i = runtime->builder.CreateLoad(runtime->builder.getInt64Ty(), iPtr);
        const auto gep = runtime->builder.CreateGEP(arr->getIRType(), iterPtr, {runtime->builder.getInt32(0), i});
        loopVars[0]->setIRValue(gep);
    } else {
        const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt64Ty(), iPtr);
        const auto v = arr->getFunc.callIR(runtime, {iterPtr, iValue});
        loopVars[0]->setIRValue(runtime->builder.CreateLoad(arr->getIRType(), v));
    }
}

void LgsForeachLoop::setIterVars(LgsRuntime* runtime, LgsMap* map) const {
    auto& builder = runtime->builder;
    const vector<Type*> structFields = {builder.getPtrTy(), builder.getInt64Ty(), builder.getInt64Ty()};
    map->mapStruct = getIRStructType(context, map->name, structFields);
    const auto bucketsGEP = runtime->builder.CreateStructGEP(map->mapStruct, iterPtr, 0);
    const vector<Type*> entryStructFields = {builder.getPtrTy(), builder.getPtrTy(), builder.getPtrTy()};
    const auto bucketsValue = builder.CreateLoad(builder.getPtrTy(), bucketsGEP);
    const auto isNull = builder.CreateICmpEQ(bucketsValue, Constant::getNullValue(builder.getPtrTy()));
    const auto notNullBlock = BasicBlock::Create(context, "notnull");
    builder.CreateCondBr(isNull, IRCondBlock, notNullBlock);

    startBlock(runtime, notNullBlock);
    const auto keyGEP = runtime->builder.CreateStructGEP(map->mapStruct, bucketsValue, 0);
    const auto valueGEP = runtime->builder.CreateStructGEP(map->mapStruct, bucketsValue, 1);
    loopVars[0]->IRValue = builder.CreateLoad(builder.getPtrTy(), keyGEP);
    loopVars[1]->IRValue = builder.CreateLoad(builder.getPtrTy(), valueGEP);
}

LgsForeachLoop::~LgsForeachLoop() {
    if (iterExpr) {
        delete iterExpr;
    }
    if (stmtBlock) {
        delete stmtBlock;
    }
}
