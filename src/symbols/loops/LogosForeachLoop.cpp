#include "loops/LogosForeachLoop.h"

#include "exprs/LogosFuncCall.h"
#include "exprs/LogosSelection.h"
#include "exprs/LogosVariable.h"
#include "loops/LogosLoopVar.h"
#include "object/LogosField.h"

#include <exprs/LogosArray.h>
#include <exprs/LogosConstant.h>
#include <funcs/LogosBuiltinFunc.h>
#include <types/LogosInt.h>

Value* LogosForeachLoop::computeIRValue(CodeGenMetadata* metadata) {
    setIterable(metadata);
    if (!iterable) return nullptr;
    auto& builder = metadata->builder;
    const auto i32Type = builder.getInt32Ty();

    const auto iterableSize = iterable->size();
    const auto irStartRange = metadata->builder.getInt32(0);;
    const auto irEndRange = metadata->builder.getInt32(iterableSize);;
    const auto i = builder.CreateAlloca(i32Type);
    builder.CreateStore(irStartRange, i);
    builder.CreateBr(loopCondition);

    startBlock(metadata, loopCondition);
    const auto currentVal = builder.CreateLoad(i32Type, i);
    const auto condition = builder.CreateICmpSLT(currentVal, irEndRange);
    loopVar->setIRValue(currentVal);
    builder.CreateCondBr(condition, loopBody, loopEnd);

    startBlock(metadata, loopBody);
    metadata->logosStack.enterScope();
    metadata->logosStack.addLocalSymbol(loopVar->name, LogosSymbol(LOOP_VAR, loopVar));
    stmtBlock->writeIRValue(metadata);

    return nullptr;
}

void LogosForeachLoop::setIterable(CodeGenMetadata* metadata, const LogosVariable* const variable) {
    const auto symbol = metadata->logosStack.getSymbol(variable->name);
    switch (symbol->type) {
    case VAR_DEC: {
        iterable = dynamic_cast<LogosIterable*>(symbol->varDec->expr);
        return;
    }
    case LOOP_VAR: {
        iterable = dynamic_cast<LogosIterable*>(symbol->loopVar->expr);
        return;
    }
    case FIELD: {
        iterable = dynamic_cast<LogosIterable*>(symbol->field->expr);
        return;
    }
    case SELECTION: {
        iterable = dynamic_cast<LogosIterable*>(symbol->selection->getLastExpr());
        return;
    }
    default:
        return;
    }
}

void LogosForeachLoop::setIterable(CodeGenMetadata* metadata) {
    if (const auto var = dynamic_cast<LogosVariable*>(iterableExpr)) {
        setIterable(metadata, var);
    } else if (const auto funcCall = dynamic_cast<LogosFuncCall*>(iterableExpr)) {
        setIterable(metadata, funcCall);
    }
}

void LogosForeachLoop::setIterable(CodeGenMetadata* metadata, LogosFuncCall* variable) {
}

LogosForeachLoop::~LogosForeachLoop() {
    if (loopVar) {
        delete loopVar;
    }
    if (iterableExpr) {
        delete iterableExpr;
    }
    if (stmtBlock) {
        delete stmtBlock;
    }
}