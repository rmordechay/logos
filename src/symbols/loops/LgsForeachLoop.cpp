#include "loops/LgsForeachLoop.h"

#include "exprs/unary/LgsIterIndex.h"
#include "stmts/LgsVarDec.h"
#include "stmts/LgsStmtBlock.h"
#include "types/LgsArray.h"
#include "types/LgsMap.h"
#include "utils/LgsUtils.h"

Value* LgsForeachLoop::loopStart(LgsRuntime* runtime) {
    return runtime->builder.getInt32(0);
}

Value* LgsForeachLoop::loopEnd(LgsRuntime* runtime) {
    const auto iterable = iterExpr->type->asIterable();
    return iterable->getLoopLength(runtime, iterExpr);
}

void LgsForeachLoop::setIRIterable(LgsRuntime* runtime) {
    iterPtr = iterExpr->getIRValue(runtime);
}

void LgsForeachLoop::setIRLoopVars(LgsRuntime* runtime) {
    const auto iterable = iterExpr->type->asIterable();
    if (const auto map = iterable->asMap()) {
        setIterVars(runtime, map);
    } if (const auto arr = iterable->asArray()) {
        setIterVars(runtime, arr);
    } else {
        assert(false);
    }
}

void LgsForeachLoop::setIterVars(LgsRuntime* runtime, LgsArray* arr) const {
    if (arr->isStatic) {
        const auto i = runtime->builder.CreateLoad(runtime->builder.getInt32Ty(), iPtr);
        const auto gep = runtime->builder.CreateGEP(arr->getIRType(runtime), iterPtr, {runtime->builder.getInt32(0), i});
        loopVars[0]->setIRValue(gep);
    } else {
        const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt32Ty(), iPtr);
        const auto v = arr->get.callIR(runtime, {iterPtr, iValue});
        loopVars[0]->setIRValue(runtime->builder.CreateLoad(arr->getIRType(runtime), v));
    }
}

void LgsForeachLoop::setIterVars(LgsRuntime* runtime, LgsMap* map) const {
    auto& builder = runtime->builder;
    const vector<Type*> structFields = {builder.getPtrTy(), builder.getInt64Ty(), builder.getInt32Ty()};
    map->mapStruct = getArrStruct(context, map->name, structFields);
    const auto bucketsGep = runtime->builder.CreateStructGEP(map->mapStruct, iterPtr, 0);
    const vector<Type*> entryStructFields = {builder.getPtrTy(), builder.getPtrTy(), builder.getPtrTy()};
    const auto bucketsValue = builder.CreateLoad(builder.getPtrTy(), bucketsGep);
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
